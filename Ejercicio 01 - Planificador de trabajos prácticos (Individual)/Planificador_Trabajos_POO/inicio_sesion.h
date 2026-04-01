#ifndef INICIO_SESION_H
#define INICIO_SESION_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QLabel;

class InicioSesion : public QWidget
{
    Q_OBJECT

public:
    explicit InicioSesion(QWidget *parent = nullptr);
    ~InicioSesion() override;

signals:
    void inicioCorrecto(const QString &username);

private slots:
    void intentarLogin();
    void abrirRegistro();

private:
    QLineEdit *m_usuarioEdit;
    QLineEdit *m_contrasenaEdit;
    QPushButton *m_botonIngresar;
    QPushButton *m_botonRegistrar;
    QLabel *m_estadoLabel;
};

#endif // INICIO_SESION_H
