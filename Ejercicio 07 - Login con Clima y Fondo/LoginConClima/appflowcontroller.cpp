#include "appflowcontroller.h"

#include "backgrounddownloader.h"
#include "logger.h"
#include "login.h"
#include "ventana.h"

AppFlowController::AppFlowController(Login *login, Ventana *ventana, BackgroundDownloader *downloader,
                                     QObject *parent)
    : QObject(parent)
    , m_login(login)
    , m_ventana(ventana)
    , m_downloader(downloader)
{
}

void AppFlowController::onLoginSuccess()
{
    Logger::write("Login valido. Iniciando preparacion de la ventana principal");
    m_login->mostrarMensajeEstado("Preparando imagen principal...");
    m_login->setLoginEnabled(false);
    // La ventana principal solo se abre cuando el fondo esta listo.
    m_downloader->ensureBackgroundReady();
}

void AppFlowController::onBackgroundReady(const QPixmap &pixmap, bool fromCache)
{
    Logger::write(fromCache ? "Imagen principal lista desde cache" : "Imagen principal descargada");
    m_ventana->setBackground(pixmap);
    // Apertura en pantalla completa despues de tener imagen principal.
    m_ventana->showFullScreen();
    m_login->hide();
}

void AppFlowController::onBackgroundError(const QString &error)
{
    Logger::write("Error en descarga de imagen principal: " + error);
    m_login->mostrarMensajeEstado("No se pudo cargar la imagen principal. Reintenta.");
    m_login->setLoginEnabled(true);
}
