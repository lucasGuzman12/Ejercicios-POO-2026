#include "configmanager.h"

#include <QSettings>

AppConfig ConfigManager::cargar(const QString &filePath)
{
    AppConfig cfg;
    QSettings s(filePath, QSettings::IniFormat);
    cfg.usuario = s.value("auth/usuario", cfg.usuario).toString();
    cfg.clave = s.value("auth/clave", cfg.clave).toString();
    cfg.segundosBloqueo = s.value("auth/segundos_bloqueo", cfg.segundosBloqueo).toInt();
    cfg.lenguajePorDefecto = s.value("editor/lenguaje_defecto", cfg.lenguajePorDefecto).toString();
    cfg.rutaExportacion = s.value("editor/ruta_exportacion", cfg.rutaExportacion).toString();
    cfg.rutaLog = s.value("sistema/ruta_log", cfg.rutaLog).toString();
    return cfg;
}
