#ifndef CLIMA_H
#define CLIMA_H

#include <QObject>
#include <QNetworkReply>

class ConfigManager;
class QNetworkAccessManager;

class Clima : public QObject
{
    Q_OBJECT
public:
    explicit Clima(QNetworkAccessManager *manager, ConfigManager *config, QObject *parent = nullptr);

    void actualizar();

signals:
    void climaDisponible(const QString &temperatura, const QString &horaLocal, bool offline);
    void errorClima(const QString &mensaje);

private slots:
    void onWeatherReplyFinished();
    void onWeatherReplyError(QNetworkReply::NetworkError code);

private:
    bool hasNetworkInterfaceUp() const;
    void publicarDatosSimulados(const QString &motivo);
    void procesarRespuesta(QNetworkReply *reply);

    QNetworkAccessManager *m_manager;
    ConfigManager *m_config;
};

#endif // CLIMA_H
