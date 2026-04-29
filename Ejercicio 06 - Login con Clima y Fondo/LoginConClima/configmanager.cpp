#include "configmanager.h"

#include <QFileInfo>
#include <QSettings>

ConfigManager::ConfigManager(const QString &path)
    : m_path(path)
{
}

void ConfigManager::ensureDefaults() const
{
    QSettings settings(m_path, QSettings::IniFormat);
    const QString newBackgroundUrl = "https://wallpapers.com/images/hd/1920-x-1080-hd-b5dm81xdpze6sjbr.jpg";

    // Crea valores por defecto si no existe config.ini.
    if (!QFileInfo::exists(m_path)) {
        settings.setValue("weather/apiKey", "56aa9234283144a592a203159262704");
        settings.setValue("weather/city", "Cordoba");
        settings.setValue("weather/units", "metric");
        settings.setValue("images/backgroundUrl", newBackgroundUrl);
        settings.setValue("images/profileUrl", "https://images.unsplash.com/photo-1560250097-0b93528c311a?auto=format&fit=crop&w=512&q=80");
        settings.setValue("auth/baseUrl", "");
        settings.setValue("proxy/enabled", false);
        settings.setValue("proxy/host", "");
        settings.setValue("proxy/port", 8080);
        settings.setValue("proxy/user", "");
        settings.setValue("proxy/password", "");
        return;
    }

    // Migra URL de fondo antigua a una publica mas estable.
    const QString currentBg = settings.value("images/backgroundUrl").toString().trimmed();
    if (currentBg.isEmpty() || currentBg.contains("images.unsplash.com/photo-1500375592092-40eb2168fd21")) {
        settings.setValue("images/backgroundUrl", newBackgroundUrl);
    }
}

QString ConfigManager::weatherApiKey() const
{
    return value("weather", "apiKey", "");
}

QString ConfigManager::city() const
{
    return value("weather", "city", "Cordoba");
}

QString ConfigManager::units() const
{
    return value("weather", "units", "metric");
}

QString ConfigManager::backgroundImageUrl() const
{
    return value("images", "backgroundUrl", "");
}

QString ConfigManager::profileImageUrl() const
{
    return value("images", "profileUrl", "");
}

QString ConfigManager::authBaseUrl() const
{
    return value("auth", "baseUrl", "");
}

bool ConfigManager::proxyEnabled() const
{
    QSettings settings(m_path, QSettings::IniFormat);
    return settings.value("proxy/enabled", false).toBool();
}

QString ConfigManager::proxyHost() const
{
    return value("proxy", "host", "");
}

quint16 ConfigManager::proxyPort() const
{
    QSettings settings(m_path, QSettings::IniFormat);
    return static_cast<quint16>(settings.value("proxy/port", 8080).toUInt());
}

QString ConfigManager::proxyUser() const
{
    return value("proxy", "user", "");
}

QString ConfigManager::proxyPassword() const
{
    return value("proxy", "password", "");
}

QString ConfigManager::value(const QString &group, const QString &key, const QString &fallback) const
{
    QSettings settings(m_path, QSettings::IniFormat);
    settings.beginGroup(group);
    const QString result = settings.value(key, fallback).toString();
    settings.endGroup();
    return result;
}
