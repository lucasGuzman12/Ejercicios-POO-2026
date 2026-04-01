#include "dialogo_notas.h"

#include <QDialogButtonBox>
#include <QTextEdit>
#include <QVBoxLayout>

DialogoNotas::DialogoNotas(QWidget *parent)
    : QDialog(parent)
    , m_editorNotas(new QTextEdit(this))
{
    setWindowTitle("Notas");

    QDialogButtonBox *botones = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, this);
    connect(botones, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(botones, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *disposicion = new QVBoxLayout(this);
    disposicion->addWidget(m_editorNotas);
    disposicion->addWidget(botones);
}

void DialogoNotas::setNotas(const QString &notas)
{
    m_editorNotas->setPlainText(notas);
}

QString DialogoNotas::notas() const
{
    return m_editorNotas->toPlainText();
}
