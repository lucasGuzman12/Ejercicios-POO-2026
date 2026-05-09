#ifndef BLOQUEADA_H
#define BLOQUEADA_H

#include "pantalla.h"

class QLabel;
class QTimer;

class ModoBloqueado : public Pantalla
{
    Q_OBJECT
public:
    explicit ModoBloqueado(AppController *controller, QWidget *parent = nullptr);

    void iniciarBloqueo(int segundos);

    void inicializarUI() override;
    void conectarEventos() override;
    void cargarDatos() override;
    bool validarEstado() override;
    void registrarEvento(const QString &descripcion) override;

signals:
    void bloqueoFinalizado();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private slots:
    void tick();

private:
    QLabel *m_label = nullptr;
    QTimer *m_timer = nullptr;
    int m_segundos = 0;
};

#endif // BLOQUEADA_H
