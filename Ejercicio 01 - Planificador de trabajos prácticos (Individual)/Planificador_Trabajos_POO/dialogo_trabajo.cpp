#include "dialogo_trabajo.h"

#include <QComboBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

DialogoTrabajo::DialogoTrabajo(QWidget *parent)
    : QDialog(parent)
    , m_tituloEdit(new QLineEdit(this))
    , m_materiaEdit(new QLineEdit(this))
    , m_vencimientoEdit(new QDateEdit(QDate::currentDate(), this))
    , m_estadoBox(new QComboBox(this))
    , m_prioridadBox(new QComboBox(this))
{
    setWindowTitle("Trabajo practico");
    m_vencimientoEdit->setCalendarPopup(true);

    m_estadoBox->addItems({"Pendiente", "En progreso", "Entregado"});
    m_prioridadBox->addItems({"Baja", "Media", "Alta"});

    QFormLayout *formulario = new QFormLayout;
    formulario->addRow("Titulo", m_tituloEdit);
    formulario->addRow("Materia", m_materiaEdit);
    formulario->addRow("Vence", m_vencimientoEdit);
    formulario->addRow("Estado", m_estadoBox);
    formulario->addRow("Prioridad", m_prioridadBox);

    QDialogButtonBox *botones = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(botones, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(botones, &QDialogButtonBox::rejected, this, &QDialog::reject);
    if (QPushButton *ok = botones->button(QDialogButtonBox::Ok)) {
        ok->setDefault(true);
    }

    QVBoxLayout *disposicion = new QVBoxLayout(this);
    disposicion->addLayout(formulario);
    disposicion->addWidget(botones);
}

void DialogoTrabajo::setTrabajo(const Trabajo &trabajo)
{
    m_trabajo = trabajo;
    m_tituloEdit->setText(trabajo.titulo);
    m_materiaEdit->setText(trabajo.materia);
    if (trabajo.fechaVencimiento.isValid()) {
        m_vencimientoEdit->setDate(trabajo.fechaVencimiento);
    }

    const int statusIndex = m_estadoBox->findText(trabajo.estado);
    if (statusIndex >= 0) {
        m_estadoBox->setCurrentIndex(statusIndex);
    }

    const int priorityIndex = m_prioridadBox->findText(trabajo.prioridad);
    if (priorityIndex >= 0) {
        m_prioridadBox->setCurrentIndex(priorityIndex);
    }
}

Trabajo DialogoTrabajo::trabajo() const
{
    Trabajo t = m_trabajo;
    t.titulo = m_tituloEdit->text().trimmed();
    t.materia = m_materiaEdit->text().trimmed();
    t.fechaVencimiento = m_vencimientoEdit->date();
    t.estado = m_estadoBox->currentText();
    t.prioridad = m_prioridadBox->currentText();
    return t;
}
