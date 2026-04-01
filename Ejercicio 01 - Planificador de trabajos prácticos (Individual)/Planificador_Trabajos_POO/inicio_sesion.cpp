#include "inicio_sesion.h"
#include "gestor_sesion.h"
#include "gestor_usuarios.h"
#include "dialogo_registro.h"

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

InicioSesion::InicioSesion(QWidget *parent)
    : QWidget(parent)
    , m_usuarioEdit(new QLineEdit(this))
    , m_contrasenaEdit(new QLineEdit(this))
    , m_botonIngresar(new QPushButton("Ingresar", this))
    , m_botonRegistrar(new QPushButton("Registrarse", this))
    , m_estadoLabel(new QLabel(this))
{
    setWindowTitle("Inicio de sesion");
    setFixedSize(360, 220);

    m_contrasenaEdit->setEchoMode(QLineEdit::Password);

    QFormLayout *formulario = new QFormLayout;
    formulario->addRow("Usuario", m_usuarioEdit);
    formulario->addRow("Contrasena", m_contrasenaEdit);

    QVBoxLayout *disposicion = new QVBoxLayout(this);
    disposicion->addLayout(formulario);
    disposicion->addWidget(m_botonIngresar);
    disposicion->addWidget(m_botonRegistrar);
    disposicion->addWidget(m_estadoLabel);

    connect(m_botonIngresar, &QPushButton::clicked, this, &InicioSesion::intentarLogin);
    connect(m_botonRegistrar, &QPushButton::clicked, this, &InicioSesion::abrirRegistro);
    connect(m_usuarioEdit, &QLineEdit::returnPressed, this, &InicioSesion::intentarLogin);
    connect(m_contrasenaEdit, &QLineEdit::returnPressed, this, &InicioSesion::intentarLogin);
    m_botonIngresar->setDefault(true);
}

InicioSesion::~InicioSesion() = default;

void InicioSesion::intentarLogin()
{
    const QString usuario = m_usuarioEdit->text().trimmed();
    const QString contrasena = m_contrasenaEdit->text();

    if (usuario.isEmpty() || contrasena.isEmpty()) {
        m_estadoLabel->setText("Completa usuario y contrasena.");
        return;
    }

    GestorUsuarios users;
    if (!users.validar(usuario, contrasena)) {
        m_estadoLabel->setText("Usuario o contrasena incorrectos.");
        return;
    }

    GestorSesion::guardarSesion(usuario);
    m_estadoLabel->setText("OK");
    emit inicioCorrecto(usuario);
}

void InicioSesion::abrirRegistro()
{
    DialogoRegistro dlg(this);
    if (dlg.exec() != QDialog::Accepted) {
        return;
    }

    GestorUsuarios usuarios;
    QString error;
    if (!usuarios.agregarUsuario(dlg.usuario(), dlg.contrasena(), &error)) {
        m_estadoLabel->setText(error);
        return;
    }

    m_usuarioEdit->setText(dlg.usuario());
    m_contrasenaEdit->setText(dlg.contrasena());
    m_estadoLabel->setText("Usuario creado. Puedes iniciar sesion.");
}
