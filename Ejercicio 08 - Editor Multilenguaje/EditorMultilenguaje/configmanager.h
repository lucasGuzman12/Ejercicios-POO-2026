#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>

struct AppConfig
{
    QString usuario = "admin";
    QString clave = "1234";
    int segundosBloqueo = 15;
    QString lenguajePorDefecto = "C++";
    QString rutaExportacion = "./exportado_codigo.jpg";
    QString rutaLog = "./eventos.log";
};

class ConfigManager
{
public:
    static AppConfig cargar(const QString &filePath);
};

#endif // CONFIGMANAGER_H
