#ifndef DIALOGO_REGISTRO_H
#define DIALOGO_REGISTRO_H

#include <QDialog>

class QLineEdit;
class QLabel;

class DialogoRegistro : public QDialog
{
    Q_OBJECT

public:
    explicit DialogoRegistro(QWidget *parent = nullptr);

    QString usuario() const;
    QString contrasena() const;

private slots:
    void validarYContinuar();

private:
    QLineEdit *m_usuarioEdit;
    QLineEdit *m_contrasenaEdit;
    QLineEdit *m_confirmarEdit;
    QLabel *m_errorLabel;
};

#endif // DIALOGO_REGISTRO_H
