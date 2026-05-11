#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QColor>
#include <QPoint>
#include <QString>
#include <QVector>

struct StrokeData {
    // Identificador del trazo dentro de la base de datos.
    int id = -1;

    // Color y grosor con los que se debe reconstruir el trazo.
    QColor color = Qt::black;
    int width = 2;

    // Lista ordenada de coordenadas que forman el dibujo a mano alzada.
    QVector<QPoint> points;
};

class DatabaseManager
{
public:
    // Prepara la conexion a SQLite y crea las tablas necesarias si no existen.
    static bool initialize();

    // Devuelve el ultimo error registrado durante la inicializacion.
    static QString lastError();

    // Verifica si el usuario y la contrasena coinciden con lo guardado en SQLite.
    static bool validateUser(const QString &username, const QString &password);

    // Guarda un intento de acceso exitoso o fallido sin almacenar la contrasena.
    static void logAccess(const QString &username, bool success, const QString &detail);

    // Persiste un trazo completo: primero el trazo y despues cada punto asociado.
    static int saveStroke(const QString &username, const QColor &color, int width, const QVector<QPoint> &points);

    // Carga todos los trazos no borrados de un usuario para reconstruir el lienzo.
    static QVector<StrokeData> loadStrokes(const QString &username);

    // Marca un trazo como borrado para que no se vuelva a dibujar al cargar.
    static bool markStrokeDeleted(int strokeId);

    // Marca como borrados todos los trazos del usuario actual.
    static bool clearCanvas(const QString &username);

private:
    // Convierte una contrasena en hash SHA-256 para no guardarla en texto plano.
    static QString hashPassword(const QString &password);

    // Mensaje auxiliar con el ultimo error importante de base de datos.
    static QString m_lastError;
};

#endif // DATABASEMANAGER_H
