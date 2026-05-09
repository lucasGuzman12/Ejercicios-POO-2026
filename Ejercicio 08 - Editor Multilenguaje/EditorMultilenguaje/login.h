#ifndef LOGIN_H
#define LOGIN_H

#include "pantalla.h"

class QLineEdit;
class QLabel;
class QPushButton;

class Login : public Pantalla
{
    Q_OBJECT
public:
    explicit Login(AppController *controller, QWidget *parent = nullptr);

    void inicializarUI() override;
    void conectarEventos() override;
    void cargarDatos() override;
    bool validarEstado() override;
    void registrarEvento(const QString &descripcion) override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private slots:
    void intentarLogin();

private:
    QLineEdit *m_usuario = nullptr;
    QLineEdit *m_clave = nullptr;
    QLabel *m_estado = nullptr;
    QPushButton *m_boton = nullptr;
    int m_intentosFallidos = 0;
};

#endif // LOGIN_H
