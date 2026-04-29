#include "login.h"
#include "ui_login.h"

#include "clima.h"
#include "logger.h"

#include <QPushButton>
#include <QTimer>

Login::Login(Clima *clima, QWidget *parent)
    : Pantalla(parent)
    , ui(new Ui::Login)
    , m_clima(clima)
    , m_lockTimer(new QTimer(this))
    , m_failedAttempts(0)
{
    ui->setupUi(this);
    inicializarPantalla();
}

Login::~Login()
{
    delete ui;
}

void Login::inicializarPantalla()
{
    m_lockTimer->setInterval(1000);
    // Signals/slots con sintaxis clasica para bloqueo, login y actualizacion de clima.
    connect(m_lockTimer, SIGNAL(timeout()), this, SLOT(actualizarEstadoBloqueo()));
    connect(ui->btnIngresar, SIGNAL(clicked()), this, SLOT(onBtnIngresarClicked()));
    connect(m_clima, SIGNAL(climaDisponible(QString,QString,bool)),
            this, SLOT(onClimaDisponible(QString,QString,bool)));
    connect(m_clima, SIGNAL(errorClima(QString)), this, SLOT(onErrorClima(QString)));

    ui->lblEstado->setText("Ingrese sus credenciales.");
    ui->lblClima->setText("Temperatura: consultando...");
    ui->lblHora->setText("Hora local: consultando...");
}

void Login::mostrarMensajeEstado(const QString &mensaje)
{
    ui->lblEstado->setText(mensaje);
}

void Login::setLoginEnabled(bool enabled)
{
    ui->btnIngresar->setEnabled(enabled);
    ui->editUsuario->setEnabled(enabled);
    ui->editPassword->setEnabled(enabled);
}

void Login::onBtnIngresarClicked()
{
    const QString username = ui->editUsuario->text().trimmed();
    const QString password = ui->editPassword->text();

    // Si esta bloqueado temporalmente, no deja reintentar hasta vencer el tiempo.
    if (QDateTime::currentDateTime() < m_lockedUntil) {
        actualizarEstadoBloqueo();
        return;
    }

    if (username.isEmpty() || password.isEmpty()) {
        mostrarMensajeEstado("Completa usuario y contrasena.");
        Logger::write("Intento de login con campos vacios");
        return;
    }

    // Credenciales locales requeridas por consigna: admin / 1234.
    if (username == "admin" && password == "1234") {
        Logger::write("Credenciales locales validas para usuario admin");
        mostrarMensajeEstado("Usuario valido.");
        m_failedAttempts = 0;
        // Notifica al controlador para abrir la ventana principal.
        emit solicitarVentanaPrincipal();
        return;
    }

    registrarIntentoFallido();
}

void Login::actualizarEstadoBloqueo()
{
    const QDateTime now = QDateTime::currentDateTime();
    if (now >= m_lockedUntil) {
        m_lockTimer->stop();
        m_failedAttempts = 0;
        setLoginEnabled(true);
        mostrarMensajeEstado("Bloqueo finalizado. Reintenta.");
        return;
    }

    const int remaining = now.secsTo(m_lockedUntil);
    mostrarMensajeEstado(QString("Demasiados intentos fallidos. Espere %1 segundos.").arg(remaining));
}

void Login::onClimaDisponible(const QString &temperatura, const QString &horaLocal, bool offline)
{
    // Muestra temperatura y hora local en login; agrega etiqueta si viene en modo offline.
    ui->lblClima->setText("Temperatura: " + temperatura);
    ui->lblHora->setText("Hora local: " + horaLocal + (offline ? " (offline)" : ""));
}

void Login::onErrorClima(const QString &mensaje)
{
    mostrarMensajeEstado(mensaje);
}

void Login::registrarIntentoFallido()
{
    ++m_failedAttempts;
    Logger::write("Login fallido. Intento " + QString::number(m_failedAttempts));
    ui->editPassword->clear();

    // Bloqueo temporal tras 3 intentos fallidos (30 segundos).
    if (m_failedAttempts >= 3) {
        m_lockedUntil = QDateTime::currentDateTime().addSecs(30);
        setLoginEnabled(false);
        m_lockTimer->start();
        actualizarEstadoBloqueo();
        Logger::write("Usuario bloqueado temporalmente por 30 segundos");
    } else {
        const int restantes = 3 - m_failedAttempts;
        mostrarMensajeEstado(QString("Usuario o contrasena incorrectos. Intentos restantes: %1").arg(restantes));
    }
}
