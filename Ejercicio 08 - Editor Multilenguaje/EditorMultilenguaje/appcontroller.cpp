#include "appcontroller.h"

#include "bloqueada.h"
#include "editorprincipal.h"
#include "logger.h"
#include "login.h"
#include "pantalla.h"

AppController::AppController(QObject *parent)
    : QObject(parent), m_config(ConfigManager::cargar("config.ini"))
{
    Logger::setLogPath(m_config.rutaLog);
}

AppController::~AppController()
{
    delete m_login;
    delete m_editor;
    delete m_bloqueada;
}

void AppController::iniciar()
{
    Logger::log("Aplicacion iniciada.");
    pantallaLogin();
}

const AppConfig &AppController::config() const
{
    return m_config;
}

bool AppController::autenticar(const QString &usuario, const QString &clave)
{
    return usuario == m_config.usuario && clave == m_config.clave;
}

void AppController::pantallaLogin()
{
    if (!m_login) {
        m_login = new Login(this);
    }
    mostrarPantalla(m_login);
}

void AppController::pantallaEditor()
{
    if (!m_editor) {
        m_editor = new EditorPrincipal(this);
    }
    mostrarPantalla(m_editor);
    m_editor->showFullScreen();
    Logger::log("Editor abierto en pantalla completa.");
}

void AppController::pantallaBloqueada(int segundos)
{
    if (!m_bloqueada) {
        m_bloqueada = new ModoBloqueado(this);
        connect(m_bloqueada, SIGNAL(bloqueoFinalizado()), this, SLOT(onBloqueoFinalizado()));
    }
    m_bloqueada->iniciarBloqueo(segundos);
    mostrarPantalla(m_bloqueada);
}

void AppController::onBloqueoFinalizado()
{
    Logger::log("Finalizo bloqueo temporal.");
    pantallaLogin();
}

void AppController::mostrarPantalla(Pantalla *pantalla)
{
    if (m_actual) {
        m_actual->hide();
    }
    m_actual = pantalla;
    m_actual->show();
    m_actual->raise();
}
