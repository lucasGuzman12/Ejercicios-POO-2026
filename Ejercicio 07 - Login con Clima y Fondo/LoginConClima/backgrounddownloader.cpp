#include "backgrounddownloader.h"

#include "configmanager.h"
#include "logger.h"

#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

BackgroundDownloader::BackgroundDownloader(QNetworkAccessManager *manager, ConfigManager *config, QObject *parent)
    : QObject(parent)
    , m_manager(manager)
    , m_config(config)
{
}

void BackgroundDownloader::ensureBackgroundReady()
{
    // Limpieza de cache legado para unificar estrategia de nombres por hash.
    const QString legacyCache = QDir(QCoreApplication::applicationDirPath()).filePath("cache/fondo_principal.jpg");
    if (QFileInfo::exists(legacyCache)) {
        QFile::remove(legacyCache);
    }

    // Si existe cache valido, evita red y emite fondo listo.
    const QString cachePath = cacheFilePath();
    if (QFileInfo::exists(cachePath)) {
        QPixmap cached(cachePath);
        if (!cached.isNull()) {
            emit backgroundReady(cached, true);
            return;
        }
    }

    const QString imageUrl = m_config->backgroundImageUrl();
    if (imageUrl.trimmed().isEmpty()) {
        emit backgroundError("La URL de imagen de fondo no esta configurada.");
        return;
    }

    // Descarga desde URL publica usando QNetworkAccessManager.
    Logger::write("Descargando imagen principal desde URL publica");
    QNetworkRequest request{QUrl(imageUrl)};
    request.setHeader(QNetworkRequest::UserAgentHeader, "LoginConClima/1.0");

    QNetworkReply *reply = m_manager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(onDownloadFinished()));
}

QString BackgroundDownloader::cacheFilePath() const
{
    // Cache local por URL (hash MD5) para soportar cambios de imagen y reutilizacion.
    const QString baseDir = QDir(QCoreApplication::applicationDirPath()).filePath("cache");
    QDir().mkpath(baseDir);
    const QByteArray urlBytes = m_config->backgroundImageUrl().trimmed().toUtf8();
    const QString hash = QString(QCryptographicHash::hash(urlBytes, QCryptographicHash::Md5).toHex());
    return QDir(baseDir).filePath("fondo_" + hash + ".jpg");
}

void BackgroundDownloader::processReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit backgroundError("Error de red al descargar fondo: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    // Valida que la respuesta sea una imagen utilizable.
    const QByteArray data = reply->readAll();
    QPixmap image;
    if (!image.loadFromData(data)) {
        emit backgroundError("La imagen descargada no tiene un formato valido.");
        reply->deleteLater();
        return;
    }

    QFile file(cacheFilePath());
    if (file.open(QIODevice::WriteOnly)) {
        file.write(data);
        file.close();
    } else {
        Logger::write("No se pudo persistir cache de fondo");
    }

    emit backgroundReady(image, false);
    reply->deleteLater();
}

void BackgroundDownloader::onDownloadFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) {
        return;
    }
    processReply(reply);
}
