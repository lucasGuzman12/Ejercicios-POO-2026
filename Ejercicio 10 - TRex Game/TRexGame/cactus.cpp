#include "cactus.h"

#include <QPainter>
#include <QRandomGenerator>

Cactus::Cactus(QWidget *parent)
    : QWidget(parent),
      m_variant(0)
{
    // Tamano inicial. Luego randomizeShape() puede cambiarlo.
    setFixedSize(34, 62);
}

void Cactus::randomizeShape()
{
    // Elige una variante visual aleatoria entre 0, 1 y 2.
    m_variant = QRandomGenerator::global()->bounded(3);

    // Cambia ancho y alto para que los obstaculos no sean identicos.
    setFixedSize(30 + (m_variant * 12), 52 + QRandomGenerator::global()->bounded(18));
    update();
}

QRect Cactus::collisionRect() const
{
    // Rectangulo de colision un poco menor que el widget completo.
    return QRect(x() + 5, y() + 5, width() - 10, height() - 5);
}

void Cactus::paintEvent(QPaintEvent *event)
{
    // No se usa el parametro event.
    Q_UNUSED(event);

    // Dibuja el cactus directamente dentro del QWidget.
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(24, 120, 78));

    // Tronco principal centrado.
    int baseW = 14;
    int centerX = width() / 2 - baseW / 2;
    painter.drawRoundedRect(centerX, 0, baseW, height(), 5, 5);

    // Brazos laterales del cactus base.
    painter.drawRoundedRect(centerX - 10, 20, 11, 28, 5, 5);
    painter.drawRoundedRect(centerX + baseW - 1, 13, 11, 31, 5, 5);

    // Segun la variante, se agregan partes extra para hacerlo mas ancho.
    if (m_variant > 0) {
        painter.drawRoundedRect(4, height() / 3, 10, height() / 2, 5, 5);
    }
    if (m_variant > 1) {
        painter.drawRoundedRect(width() - 14, height() / 4, 10, height() / 2, 5, 5);
    }
}
