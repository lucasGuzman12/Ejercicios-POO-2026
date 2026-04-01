#ifndef ALMACENAMIENTO_APP_H
#define ALMACENAMIENTO_APP_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

class AlmacenamientoApp
{
public:
    static QString directorioDatos();
    static QString rutaArchivo(const QString &nombreArchivo);
    static bool asegurarDirectorioDatos();

    static QJsonDocument leerJson(const QString &nombreArchivo, bool *ok = nullptr);
    static bool guardarJson(const QString &nombreArchivo, const QJsonDocument &doc);
};

#endif // ALMACENAMIENTO_APP_H
