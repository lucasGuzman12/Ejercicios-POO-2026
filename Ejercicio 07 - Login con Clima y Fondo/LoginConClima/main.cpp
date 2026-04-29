#include "appflowcontroller.h"
#include "backgrounddownloader.h"
#include "clima.h"
#include "configmanager.h"
#include "logger.h"
#include "login.h"
#include "ventana.h"

#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkProxy>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("LoginConClima");
    app.setOrganizationName("Universidad");

    // Carga configuracion desde archivo INI (API key, ciudad, proxy, URLs, etc.).
    const QString configPath = QDir(QCoreApplication::applicationDirPath()).filePath("config.ini");
    ConfigManager config(configPath);
    config.ensureDefaults();

    // Inicializa archivo de log para registrar eventos con fecha/hora.
    const QString logPath = QDir(QCoreApplication::applicationDirPath()).filePath("eventos.log");
    Logger::setLogFilePath(logPath);
    Logger::write("Aplicacion iniciada");

    // Soporte de proxy a nivel de aplicacion segun config.ini.
    if (config.proxyEnabled()) {
        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(config.proxyHost());
        proxy.setPort(config.proxyPort());
        proxy.setUser(config.proxyUser());
        proxy.setPassword(config.proxyPassword());
        QNetworkProxy::setApplicationProxy(proxy);
        Logger::write("Proxy habilitado: " + config.proxyHost() + ":" + QString::number(config.proxyPort()));
    } else {
        QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
        Logger::write("Proxy deshabilitado");
    }

    // Uso obligatorio de un unico QNetworkAccessManager compartido.
    QNetworkAccessManager manager;
    Clima clima(&manager, &config, &app);
    BackgroundDownloader downloader(&manager, &config, &app);

    Login login(&clima);
    Ventana ventana(&manager, &config);
    AppFlowController flow(&login, &ventana, &downloader, &app);

    // Conexiones con sintaxis clasica SIGNAL/SLOT como pide la consigna.
    QObject::connect(&login, SIGNAL(solicitarVentanaPrincipal()), &flow, SLOT(onLoginSuccess()));
    QObject::connect(&downloader, SIGNAL(backgroundReady(QPixmap,bool)),
                     &flow, SLOT(onBackgroundReady(QPixmap,bool)));
    QObject::connect(&downloader, SIGNAL(backgroundError(QString)),
                     &flow, SLOT(onBackgroundError(QString)));

    login.show();
    clima.actualizar();

    return app.exec();
}
