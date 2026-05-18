#ifndef TREX_H
#define TREX_H

#include <QWidget>

// TRex es el personaje del jugador.
// Hereda de QWidget para poder dibujarse a si mismo con paintEvent().
class TRex : public QWidget
{
    Q_OBJECT

public:
    explicit TRex(QWidget *parent = 0);

    // Devuelve al dinosaurio a su posicion inicial sobre el suelo.
    void reset(int groundY);

    // Inicia un salto si el dinosaurio no esta saltando.
    void jump();

    // Cambia entre posicion normal y posicion agachada.
    void crouch(bool enabled);

    // Mueve al T-Rex un poco hacia adelante.
    void advance();

    // Mueve al T-Rex un poco hacia atras.
    void brake();

    // Aplica gravedad y movimiento vertical durante el salto.
    void updatePhysics(int groundY);

    // Rectangulo usado para detectar colisiones.
    // Es un poco menor que el dibujo para que el juego se sienta mas justo.
    QRect collisionRect() const;

protected:
    // Dibuja el dinosaurio, normal o agachado.
    void paintEvent(QPaintEvent *event);

private:
    // Velocidad vertical actual. Negativa sube, positiva baja.
    int m_verticalVelocity;

    // Indica si el dinosaurio esta en el aire.
    bool m_jumping;

    // Indica si el dinosaurio esta agachado.
    bool m_crouching;
};

#endif
