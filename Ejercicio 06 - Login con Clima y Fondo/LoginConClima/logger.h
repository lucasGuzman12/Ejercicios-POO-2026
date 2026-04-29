#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

class Logger
{
public:
    static void setLogFilePath(const QString &path);
    static void write(const QString &message);

private:
    static QString s_logFilePath;
};

#endif // LOGGER_H
