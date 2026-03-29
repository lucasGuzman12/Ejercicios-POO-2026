#include "almacenamiento_app.h"

#include <QDir>
#include <QFile>
#include <QStandardPaths>

QString AlmacenamientoApp::directorioDatos()
{
    const QString base = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    return base.isEmpty() ? QDir::currentPath() : base;
}

QString AlmacenamientoApp::rutaArchivo(const QString &nombreArchivo)
{
    return QDir(directorioDatos()).filePath(nombreArchivo);
}

bool AlmacenamientoApp::asegurarDirectorioDatos()
{
    QDir dir(directorioDatos());
    if (dir.exists()) {
        return true;
    }
    return dir.mkpath(".");
}

QJsonDocument AlmacenamientoApp::leerJson(const QString &nombreArchivo, bool *ok)
{
    if (ok) {
        *ok = false;
    }

    QFile f(rutaArchivo(nombreArchivo));
    if (!f.exists()) {
        return QJsonDocument();
    }
    if (!f.open(QIODevice::ReadOnly)) {
        return QJsonDocument();
    }

    const QByteArray data = f.readAll();
    f.close();

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError) {
        return QJsonDocument();
    }

    if (ok) {
        *ok = true;
    }
    return doc;
}

bool AlmacenamientoApp::guardarJson(const QString &nombreArchivo, const QJsonDocument &doc)
{
    if (!asegurarDirectorioDatos()) {
        return false;
    }

    QFile f(rutaArchivo(nombreArchivo));
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    f.write(doc.toJson(QJsonDocument::Indented));
    f.close();
    return true;
}
