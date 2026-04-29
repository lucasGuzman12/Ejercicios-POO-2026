#ifndef BACKGROUNDDOWNLOADER_H
#define BACKGROUNDDOWNLOADER_H

#include <QObject>
#include <QPixmap>

class ConfigManager;
class QNetworkAccessManager;
class QNetworkReply;

class BackgroundDownloader : public QObject
{
    Q_OBJECT
public:
    explicit BackgroundDownloader(QNetworkAccessManager *manager, ConfigManager *config, QObject *parent = nullptr);
    void ensureBackgroundReady();

signals:
    void backgroundReady(const QPixmap &pixmap, bool fromCache);
    void backgroundError(const QString &message);

private slots:
    void onDownloadFinished();

private:
    QString cacheFilePath() const;
    void processReply(QNetworkReply *reply);

    QNetworkAccessManager *m_manager;
    ConfigManager *m_config;
};

#endif // BACKGROUNDDOWNLOADER_H
