#include "dialogo_registro.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

DialogoRegistro::DialogoRegistro(QWidget *parent)
    : QDialog(parent)
    , m_usuarioEdit(new QLineEdit(this))
    , m_contrasenaEdit(new QLineEdit(this))
    , m_confirmarEdit(new QLineEdit(this))
    , m_errorLabel(new QLabel(this))
{
    setWindowTitle("Registro de usuario");
    m_contrasenaEdit->setEchoMode(QLineEdit::Password);
    m_confirmarEdit->setEchoMode(QLineEdit::Password);

    QFormLayout *formulario = new QFormLayout;
    formulario->addRow("Usuario", m_usuarioEdit);
    formulario->addRow("Contrasena", m_contrasenaEdit);
    formulario->addRow("Confirmar", m_confirmarEdit);

    QDialogButtonBox *botones = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(botones, &QDialogButtonBox::accepted, this, &DialogoRegistro::validarYContinuar);
    connect(botones, &QDialogButtonBox::rejected, this, &QDialog::reject);
    if (QPushButton *ok = botones->button(QDialogButtonBox::Ok)) {
        ok->setDefault(true);
    }

    QVBoxLayout *disposicion = new QVBoxLayout(this);
    disposicion->addLayout(formulario);
    disposicion->addWidget(botones);
    disposicion->addWidget(m_errorLabel);

    m_usuarioEdit->setPlaceholderText("Ej: estudiante");
    m_contrasenaEdit->setPlaceholderText("Minimo 4 caracteres");
    m_confirmarEdit->setPlaceholderText("Repite la contrasena");

    m_usuarioEdit->setFocus();
}

QString DialogoRegistro::usuario() const
{
    return m_usuarioEdit->text().trimmed();
}

QString DialogoRegistro::contrasena() const
{
    return m_contrasenaEdit->text();
}

void DialogoRegistro::validarYContinuar()
{
    const QString u = usuario();
    const QString c1 = m_contrasenaEdit->text();
    const QString c2 = m_confirmarEdit->text();

    if (u.isEmpty() || c1.isEmpty()) {
        m_errorLabel->setText("Usuario y contrasena son obligatorios.");
        return;
    }
    if (c1.size() < 4) {
        m_errorLabel->setText("La contrasena debe tener al menos 4 caracteres.");
        return;
    }
    if (c1 != c2) {
        m_errorLabel->setText("Las contrasenas no coinciden.");
        return;
    }

    accept();
}
