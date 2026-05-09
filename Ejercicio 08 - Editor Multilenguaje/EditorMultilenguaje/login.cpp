#include "login.h"

#include "appcontroller.h"
#include "logger.h"

#include <QCloseEvent>
#include <QFocusEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPushButton>
#include <QResizeEvent>
#include <QVBoxLayout>

Login::Login(AppController *controller, QWidget *parent)
    : Pantalla(controller, parent)
{
    inicializarUI();
    conectarEventos();
    cargarDatos();
}

void Login::inicializarUI()
{
    setWindowTitle("Login");
    setMinimumSize(520, 360);
    setObjectName("LoginRoot");
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(44, 40, 44, 40);
    layout->setSpacing(12);
    auto *titulo = new QLabel("Editor Multilenguaje - Ingreso", this);
    titulo->setObjectName("LoginTitle");
    auto *lblUsuario = new QLabel("Usuario", this);
    lblUsuario->setObjectName("LoginFieldLabel");
    m_usuario = new QLineEdit(this);
    auto *lblClave = new QLabel("Clave", this);
    lblClave->setObjectName("LoginFieldLabel");
    m_clave = new QLineEdit(this);
    m_estado = new QLabel("Ingrese credenciales.", this);
    m_estado->setObjectName("LoginStatus");
    m_boton = new QPushButton("Entrar", this);
    m_boton->setObjectName("LoginButton");

    m_usuario->setPlaceholderText("Usuario");
    m_clave->setPlaceholderText("Clave");
    m_clave->setEchoMode(QLineEdit::Password);
    m_usuario->setMinimumHeight(42);
    m_clave->setMinimumHeight(42);
    m_boton->setMinimumHeight(42);
    m_estado->setMinimumHeight(32);
    m_estado->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    layout->addWidget(titulo);
    layout->addWidget(lblUsuario);
    layout->addWidget(m_usuario);
    layout->addWidget(lblClave);
    layout->addWidget(m_clave);
    layout->addWidget(m_boton);
    layout->addWidget(m_estado);

    setStyleSheet(
        "#LoginRoot { background: #eef2f6; }"
        "#LoginTitle { font-size: 24px; font-weight: 700; color: #102030; margin-bottom: 10px; }"
        "#LoginFieldLabel { color: #1f2f3f; font-size: 13px; font-weight: 600; margin-top: 2px; }"
        "#LoginStatus { color: #304356; font-size: 13px; background: #ffffff; border: 1px solid #d3dce6; border-radius: 8px; padding: 6px 10px; }"
        "QLineEdit { color: #122333; background: #ffffff; border: 1px solid #bcc9d6; border-radius: 10px; padding: 10px 12px; font-size: 14px; }"
        "QLineEdit::placeholder { color: #6e7f90; }"
        "QLineEdit:focus { border: 1px solid #1f7aec; }"
        "#LoginButton { background: #1f7aec; color: white; border: none; border-radius: 10px; font-weight: 600; font-size: 14px; }"
        "#LoginButton:hover { background: #1768cb; }"
        "#LoginButton:pressed { background: #1357aa; }");
}

void Login::conectarEventos()
{
    connect(m_boton, SIGNAL(clicked()), this, SLOT(intentarLogin()));
}

void Login::cargarDatos()
{
    m_usuario->setText(m_controller->config().usuario);
    m_clave->clear();
}

bool Login::validarEstado()
{
    return !m_usuario->text().trimmed().isEmpty() && !m_clave->text().isEmpty();
}

void Login::registrarEvento(const QString &descripcion)
{
    Logger::log("Login: " + descripcion);
}

void Login::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        intentarLogin();
        return;
    }
    registrarEvento("Tecla presionada.");
    QWidget::keyPressEvent(event);
}

void Login::mousePressEvent(QMouseEvent *event)
{
    registrarEvento("Click en login.");
    QWidget::mousePressEvent(event);
}

void Login::resizeEvent(QResizeEvent *event)
{
    registrarEvento("Resize login a " + QString::number(event->size().width()) + "x" + QString::number(event->size().height()));
    QWidget::resizeEvent(event);
}

void Login::closeEvent(QCloseEvent *event)
{
    registrarEvento("Cierre desde login.");
    event->accept();
}

void Login::focusInEvent(QFocusEvent *event)
{
    registrarEvento("Focus in en login.");
    QWidget::focusInEvent(event);
}

void Login::focusOutEvent(QFocusEvent *event)
{
    registrarEvento("Focus out en login.");
    QWidget::focusOutEvent(event);
}

void Login::intentarLogin()
{
    if (!validarEstado()) {
        m_estado->setText("Complete usuario y clave.");
        m_estado->setStyleSheet("color:#b3261e; font-weight:600; background:#fff1f1; border:1px solid #edc8c8; border-radius:8px; padding:6px 10px;");
        registrarEvento("Intento con campos incompletos.");
        return;
    }

    if (m_controller->autenticar(m_usuario->text(), m_clave->text())) {
        m_estado->setText("Acceso concedido.");
        m_estado->setStyleSheet("color:#1b7f3a; font-weight:600; background:#eef9f1; border:1px solid #bee3c7; border-radius:8px; padding:6px 10px;");
        registrarEvento("Login exitoso.");
        m_intentosFallidos = 0;
        m_controller->pantallaEditor();
    } else {
        m_intentosFallidos++;
        m_estado->setText("Credenciales invalidas. Intento " + QString::number(m_intentosFallidos) + " de 3.");
        m_estado->setStyleSheet("color:#b3261e; font-weight:600; background:#fff1f1; border:1px solid #edc8c8; border-radius:8px; padding:6px 10px;");
        registrarEvento("Login fallido.");
        if (m_intentosFallidos >= 3) {
            registrarEvento("Bloqueo temporal por 3 intentos fallidos.");
            m_intentosFallidos = 0;
            m_controller->pantallaBloqueada(m_controller->config().segundosBloqueo);
        }
    }
}
