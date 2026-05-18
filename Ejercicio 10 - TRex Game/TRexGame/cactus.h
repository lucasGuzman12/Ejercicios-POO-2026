#ifndef CACTUS_H
#define CACTUS_H

#include <QWidget>

// Cactus representa un obstaculo terrestre.
// No tiene timer propio: GameWidget los mueve con el QTimer principal.
class Cactus : public QWidget
{
    Q_OBJECT

public:
    explicit Cactus(QWidget *parent = 0);

    // Cambia el ancho, alto y variante visual para que no todos sean iguales.
    void randomizeShape();

    // Rectangulo usado para detectar colisiones con el T-Rex.
    QRect collisionRect() const;

protected:
    // Dibuja el cactus con QPainter.
    void paintEvent(QPaintEvent *event);

private:
    // Variante visual: cactus simple, doble o mas ancho.
    int m_variant;
};

#endif
