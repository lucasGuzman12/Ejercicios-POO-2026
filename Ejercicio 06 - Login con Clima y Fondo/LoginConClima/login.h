#ifndef LOGIN_H
#define LOGIN_H

#include "pantalla.h"

#include <QDateTime>

class Clima;
class QTimer;

namespace Ui {
class Login;
}

class Login : public Pantalla
{
    Q_OBJECT
public:
    explicit Login(Clima *clima, QWidget *parent = nullptr);
    ~Login() override;

    void inicializarPantalla() override;
    void mostrarMensajeEstado(const QString &mensaje);
    void setLoginEnabled(bool enabled);

signals:
    void solicitarVentanaPrincipal();

private slots:
    void onBtnIngresarClicked();
    void actualizarEstadoBloqueo();
    void onClimaDisponible(const QString &temperatura, const QString &horaLocal, bool offline);
    void onErrorClima(const QString &mensaje);

private:
    void registrarIntentoFallido();

    Ui::Login *ui;
    Clima *m_clima;
    QTimer *m_lockTimer;
    int m_failedAttempts;
    QDateTime m_lockedUntil;
};

#endif // LOGIN_H
