#ifndef PAJARO_H
#define PAJARO_H

#include <QTimer>
#include <QWidget>

// Pajaro representa un obstaculo aereo.
// Cada instancia tiene su propio QTimer, como pide la consigna.
class Pajaro : public QWidget
{
    Q_OBJECT

public:
    explicit Pajaro(QWidget *parent = 0);
    ~Pajaro();

    // Inicia el timer propio del pajaro con la velocidad indicada.
    void start(int speed);

    // Permite actualizar la velocidad cuando el juego se vuelve mas rapido.
    void setSpeed(int speed);

    // Rectangulo usado por GameWidget para detectar choques contra el T-Rex.
    QRect collisionRect() const;

signals:
    // Se emite cuando el pajaro sale por el lado izquierdo de la pantalla.
    // GameWidget lo usa para quitarlo de la lista y liberar memoria.
    void leftScreen(Pajaro *pajaro);

public slots:
    // Slot conectado al timer propio del pajaro. Lo mueve hacia la izquierda.
    void moveLeft();

protected:
    // Dibuja el pajaro y alterna las alas para simular animacion.
    void paintEvent(QPaintEvent *event);

private:
    // Timer independiente de esta instancia de Pajaro.
    QTimer *m_timer;

    // Pixeles que avanza hacia la izquierda en cada timeout.
    int m_speed;

    // Estado simple para alternar la posicion del ala.
    int m_wingFrame;
};

#endif
