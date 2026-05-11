#include "databasemanager.h"

#include <QCryptographicHash>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

QString DatabaseManager::m_lastError;

bool DatabaseManager::initialize()
{
    // Antes de abrir la base se comprueba que Qt tenga disponible el driver SQLite.
    if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
        m_lastError = "No esta disponible el driver QSQLITE.";
        return false;
    }

    // La base se crea en la carpeta desde donde se ejecuta la aplicacion.
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("lienzo.sqlite");

    if (!db.open()) {
        m_lastError = db.lastError().text();
        return false;
    }

    // Tabla de usuarios: se guarda solo el hash de la contrasena.
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "username TEXT UNIQUE NOT NULL,"
                    "password_hash TEXT NOT NULL)")) {
        m_lastError = query.lastError().text();
        return false;
    }

    // Tabla de auditoria: registra ingresos correctos y fallidos, sin contrasenas.
    if (!query.exec("CREATE TABLE IF NOT EXISTS access_logs ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "username TEXT NOT NULL,"
                    "success INTEGER NOT NULL,"
                    "detail TEXT,"
                    "created_at TEXT DEFAULT CURRENT_TIMESTAMP)")) {
        m_lastError = query.lastError().text();
        return false;
    }

    // Tabla principal de trazos. El campo deleted permite ocultarlos sin eliminarlos.
    if (!query.exec("CREATE TABLE IF NOT EXISTS strokes ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "username TEXT NOT NULL,"
                    "color TEXT NOT NULL,"
                    "width INTEGER NOT NULL,"
                    "deleted INTEGER NOT NULL DEFAULT 0,"
                    "created_at TEXT DEFAULT CURRENT_TIMESTAMP)")) {
        m_lastError = query.lastError().text();
        return false;
    }

    // Cada trazo se reconstruye leyendo sus puntos en el orden indicado por seq.
    if (!query.exec("CREATE TABLE IF NOT EXISTS points ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "stroke_id INTEGER NOT NULL,"
                    "seq INTEGER NOT NULL,"
                    "x INTEGER NOT NULL,"
                    "y INTEGER NOT NULL,"
                    "FOREIGN KEY(stroke_id) REFERENCES strokes(id))")) {
        m_lastError = query.lastError().text();
        return false;
    }

    // Usuario inicial para poder probar la aplicacion sin cargar datos manualmente.
    QSqlQuery checkUser;
    checkUser.prepare("SELECT COUNT(*) FROM users WHERE username = ?");
    checkUser.addBindValue("admin");
    if (!checkUser.exec() || !checkUser.next()) {
        m_lastError = checkUser.lastError().text();
        return false;
    }

    if (checkUser.value(0).toInt() == 0) {
        QSqlQuery insertUser;
        insertUser.prepare("INSERT INTO users(username, password_hash) VALUES(?, ?)");
        insertUser.addBindValue("admin");
        insertUser.addBindValue(hashPassword("1234"));
        if (!insertUser.exec()) {
            m_lastError = insertUser.lastError().text();
            return false;
        }
    }

    return true;
}

QString DatabaseManager::lastError()
{
    return m_lastError;
}

bool DatabaseManager::validateUser(const QString &username, const QString &password)
{
    // Se busca el hash guardado del usuario y se compara contra el hash ingresado.
    QSqlQuery query;
    query.prepare("SELECT password_hash FROM users WHERE username = ?");
    query.addBindValue(username.trimmed());

    if (!query.exec() || !query.next()) {
        return false;
    }

    const QString savedHash = query.value(0).toString();
    return savedHash == hashPassword(password);
}

void DatabaseManager::logAccess(const QString &username, bool success, const QString &detail)
{
    // El log guarda usuario, resultado y detalle, pero nunca la contrasena.
    QSqlQuery query;
    query.prepare("INSERT INTO access_logs(username, success, detail) VALUES(?, ?, ?)");
    query.addBindValue(username.trimmed());
    query.addBindValue(success ? 1 : 0);
    query.addBindValue(detail);
    query.exec();
}

int DatabaseManager::saveStroke(const QString &username, const QColor &color, int width, const QVector<QPoint> &points)
{
    // Un trazo sin puntos no se puede reconstruir, por eso no se guarda.
    if (points.isEmpty()) {
        return -1;
    }

    // Se usa una transaccion para que el trazo y sus puntos se guarden juntos.
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.transaction()) {
        return -1;
    }

    // Primero se guarda la cabecera del trazo: usuario, color y grosor.
    QSqlQuery strokeQuery;
    strokeQuery.prepare("INSERT INTO strokes(username, color, width, deleted) VALUES(?, ?, ?, 0)");
    strokeQuery.addBindValue(username.trimmed());
    strokeQuery.addBindValue(color.name());
    strokeQuery.addBindValue(width);

    if (!strokeQuery.exec()) {
        db.rollback();
        return -1;
    }

    const int strokeId = strokeQuery.lastInsertId().toInt();

    // Luego se guardan todas las coordenadas con su posicion dentro del trazo.
    QSqlQuery pointQuery;
    pointQuery.prepare("INSERT INTO points(stroke_id, seq, x, y) VALUES(?, ?, ?, ?)");

    for (int i = 0; i < points.size(); ++i) {
        pointQuery.addBindValue(strokeId);
        pointQuery.addBindValue(i);
        pointQuery.addBindValue(points[i].x());
        pointQuery.addBindValue(points[i].y());
        if (!pointQuery.exec()) {
            db.rollback();
            return -1;
        }
        pointQuery.clear();
        pointQuery.prepare("INSERT INTO points(stroke_id, seq, x, y) VALUES(?, ?, ?, ?)");
    }

    // Si todo salio bien se confirma la transaccion.
    if (!db.commit()) {
        db.rollback();
        return -1;
    }

    return strokeId;
}

QVector<StrokeData> DatabaseManager::loadStrokes(const QString &username)
{
    QVector<StrokeData> strokes;

    // Se cargan solo los trazos activos del usuario, respetando el orden de dibujo.
    QSqlQuery strokeQuery;
    strokeQuery.prepare("SELECT id, color, width FROM strokes "
                        "WHERE username = ? AND deleted = 0 ORDER BY id ASC");
    strokeQuery.addBindValue(username.trimmed());

    if (!strokeQuery.exec()) {
        return strokes;
    }

    while (strokeQuery.next()) {
        StrokeData stroke;
        stroke.id = strokeQuery.value(0).toInt();
        stroke.color = QColor(strokeQuery.value(1).toString());
        stroke.width = strokeQuery.value(2).toInt();

        // Para cada trazo se recuperan sus puntos en el orden original.
        QSqlQuery pointQuery;
        pointQuery.prepare("SELECT x, y FROM points WHERE stroke_id = ? ORDER BY seq ASC");
        pointQuery.addBindValue(stroke.id);

        if (pointQuery.exec()) {
            while (pointQuery.next()) {
                stroke.points.append(QPoint(pointQuery.value(0).toInt(), pointQuery.value(1).toInt()));
            }
        }

        if (!stroke.points.isEmpty()) {
            strokes.append(stroke);
        }
    }

    return strokes;
}

bool DatabaseManager::markStrokeDeleted(int strokeId)
{
    // No se borran filas fisicamente: se marcan como eliminadas.
    QSqlQuery query;
    query.prepare("UPDATE strokes SET deleted = 1 WHERE id = ?");
    query.addBindValue(strokeId);
    return query.exec();
}

bool DatabaseManager::clearCanvas(const QString &username)
{
    // Limpia el lienzo ocultando todos los trazos del usuario actual.
    QSqlQuery query;
    query.prepare("UPDATE strokes SET deleted = 1 WHERE username = ?");
    query.addBindValue(username.trimmed());
    return query.exec();
}

QString DatabaseManager::hashPassword(const QString &password)
{
    // SHA-256 transforma la contrasena en un texto hexadecimal no reversible.
    const QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}
