#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

class Logger
{
public:
    static void setLogPath(const QString &path);
    static void log(const QString &message);

private:
    static QString s_logPath;
};

#endif // LOGGER_H
