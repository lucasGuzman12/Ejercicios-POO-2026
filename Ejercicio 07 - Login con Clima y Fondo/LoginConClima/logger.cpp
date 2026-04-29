#include "logger.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

QString Logger::s_logFilePath;

void Logger::setLogFilePath(const QString &path)
{
    s_logFilePath = path;
}

void Logger::write(const QString &message)
{
    if (s_logFilePath.isEmpty()) {
        return;
    }

    const QFileInfo info(s_logFilePath);
    QDir().mkpath(info.absolutePath());

    QFile file(s_logFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        return;
    }

    // Registro de eventos con timestamp para trazabilidad de acciones.
    QTextStream out(&file);
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
        << " | " << message << '\n';
}
