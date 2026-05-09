#include "logger.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

QString Logger::s_logPath = "eventos.log";

void Logger::setLogPath(const QString &path)
{
    s_logPath = path;
}

void Logger::log(const QString &message)
{
    QFile file(s_logPath);
    QDir().mkpath(QFileInfo(file).absolutePath());
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
        << " | " << message << "\n";
}
