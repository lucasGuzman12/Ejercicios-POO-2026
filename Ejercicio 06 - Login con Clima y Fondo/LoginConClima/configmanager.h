#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>

class ConfigManager
{
public:
    explicit ConfigManager(const QString &path);

    void ensureDefaults() const;

    QString weatherApiKey() const;
    QString city() const;
    QString units() const;
    QString backgroundImageUrl() const;
    QString profileImageUrl() const;

    QString authBaseUrl() const;

    bool proxyEnabled() const;
    QString proxyHost() const;
    quint16 proxyPort() const;
    QString proxyUser() const;
    QString proxyPassword() const;

private:
    QString value(const QString &group, const QString &key, const QString &fallback) const;
    QString m_path;
};

#endif // CONFIGMANAGER_H
