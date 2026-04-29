#include "clima.h"

#include "configmanager.h"
#include "logger.h"

#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkInterface>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>

Clima::Clima(QNetworkAccessManager *manager, ConfigManager *config, QObject *parent)
    : QObject(parent)
    , m_manager(manager)
    , m_config(config)
{
}

void Clima::actualizar()
{
    // Deteccion basica de conectividad: sin interfaz de red activa -> modo offline.
    if (!hasNetworkInterfaceUp()) {
        publicarDatosSimulados("Sin interfaz de red activa");
        return;
    }

    const QString apiKey = m_config->weatherApiKey().trimmed();
    if (apiKey.isEmpty()) {
        publicarDatosSimulados("API key vacia");
        emit errorClima("No hay API key configurada. Mostrando modo offline.");
        return;
    }

    // Consulta directa a API de terceros (sin SDK oficial).
    QUrl url("https://api.weatherapi.com/v1/current.json");
    QUrlQuery query;
    // Autenticacion simple por query param.
    query.addQueryItem("key", apiKey);
    // Parametro de ciudad desde configuracion.
    query.addQueryItem("q", m_config->city());
    query.addQueryItem("aqi", "no");
    query.addQueryItem("lang", "es");
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "LoginConClima/1.0");

    // Uso de QNetworkAccessManager + connect SIGNAL/SLOT clasico.
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(onWeatherReplyFinished()));
    connect(reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)),
            this, SLOT(onWeatherReplyError(QNetworkReply::NetworkError)));
}

bool Clima::hasNetworkInterfaceUp() const
{
    const auto interfaces = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface &iface : interfaces) {
        const bool usable = iface.flags().testFlag(QNetworkInterface::IsUp)
                            && iface.flags().testFlag(QNetworkInterface::IsRunning)
                            && !iface.flags().testFlag(QNetworkInterface::IsLoopBack);
        if (usable) {
            return true;
        }
    }
    return false;
}

void Clima::publicarDatosSimulados(const QString &motivo)
{
    // Modo offline: publica datos simulados amigables para no romper la UI.
    Logger::write("Modo offline de clima: " + motivo);
    const QString temp = "19.5 C (simulado)";
    const QString hora = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm");
    emit climaDisponible(temp, hora, true);
}

void Clima::procesarRespuesta(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Logger::write("Fallo WeatherAPI: " + reply->errorString());
        publicarDatosSimulados(reply->errorString());
        reply->deleteLater();
        return;
    }

    const QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if (!doc.isObject()) {
        // Validacion de datos recibidos: JSON debe ser objeto.
        Logger::write("Respuesta invalida de WeatherAPI (JSON no objeto)");
        publicarDatosSimulados("JSON invalido");
        emit errorClima("La respuesta del clima no fue valida. Mostrando datos simulados.");
        reply->deleteLater();
        return;
    }

    const QJsonObject root = doc.object();
    const QJsonObject current = root.value("current").toObject();
    const QJsonObject location = root.value("location").toObject();

    // Validacion de campos esperados de la API.
    if (!current.contains("temp_c") || !location.contains("localtime")) {
        Logger::write("Faltan campos esperados en WeatherAPI");
        publicarDatosSimulados("Campos faltantes");
        emit errorClima("Faltan datos del clima. Mostrando modo offline.");
        reply->deleteLater();
        return;
    }

    const QString units = m_config->units().toLower();
    const double tempC = current.value("temp_c").toDouble();
    const double tempF = current.value("temp_f").toDouble();
    // Seleccion de unidades para presentacion segun config.
    const QString temp = (units == "imperial")
                             ? QString::number(tempF, 'f', 1) + " F"
                             : QString::number(tempC, 'f', 1) + " C";
    const QString hora = location.value("localtime").toString();

    Logger::write("Clima actualizado para " + m_config->city() + ": " + temp + ", hora " + hora);
    emit climaDisponible(temp, hora, false);
    reply->deleteLater();
}

void Clima::onWeatherReplyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) {
        return;
    }
    procesarRespuesta(reply);
}

void Clima::onWeatherReplyError(QNetworkReply::NetworkError)
{
    emit errorClima("Error de red al consultar clima. Se usaran datos simulados.");
}
