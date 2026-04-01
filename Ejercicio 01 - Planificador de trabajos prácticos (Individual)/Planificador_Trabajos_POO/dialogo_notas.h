#ifndef DIALOGO_NOTAS_H
#define DIALOGO_NOTAS_H

#include <QDialog>

class QTextEdit;

class DialogoNotas : public QDialog
{
    Q_OBJECT

public:
    explicit DialogoNotas(QWidget *parent = nullptr);

    void setNotas(const QString &notas);
    QString notas() const;

private:
    QTextEdit *m_editorNotas;
};

#endif // DIALOGO_NOTAS_H
