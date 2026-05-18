#include "pajaro.h"

#include <QPainter>

Pajaro::Pajaro(QWidget *parent)
    : QWidget(parent),
      // Cada pajaro tiene su propio QTimer independiente.
      m_timer(new QTimer(this)),
      m_speed(7),
      m_wingFrame(0)
{
    // Tamano fijo del widget donde se dibuja el pajaro.
    setFixedSize(52, 34);

    // Conexion pedida por la consigna: el timer llama al slot moveLeft().
    connect(m_timer, SIGNAL(timeout()), this, SLOT(moveLeft()));
}

Pajaro::~Pajaro()
{
    // No hace falta borrar m_timer manualmente porque tiene como padre a este Pajaro.
}

void Pajaro::start(int speed)
{
    // Guarda la velocidad recibida desde GameWidget.
    m_speed = speed;

    // Inicia el movimiento del pajaro. Cada 28 ms se ejecuta moveLeft().
    m_timer->start(28);
}

void Pajaro::setSpeed(int speed)
{
    // Permite que GameWidget aumente la velocidad a medida que pasa el tiempo.
    m_speed = speed;
}

QRect Pajaro::collisionRect() const
{
    // Rectangulo de choque reducido para ajustarse mejor al cuerpo dibujado.
    return QRect(x() + 5, y() + 7, width() - 10, height() - 13);
}

void Pajaro::moveLeft()
{
    // Movimiento horizontal hacia la izquierda.
    move(x() - m_speed, y());

    // Alterna entre 0 y 1 para cambiar la posicion del ala en cada repintado.
    m_wingFrame = 1 - m_wingFrame;
    update();

    // Si salio por completo de la pantalla, se detiene y avisa a GameWidget.
    if (x() + width() < 0) {
        m_timer->stop();
        emit leftScreen(this);
    }
}

void Pajaro::paintEvent(QPaintEvent *event)
{
    // El parametro event no se usa directamente.
    Q_UNUSED(event);

    // Dibujo simple del pajaro usando QPainter.
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(40, 42, 48));

    // Cuerpo, cabeza y pico.
    painter.drawEllipse(18, 12, 24, 14);
    painter.drawEllipse(36, 10, 12, 12);
    painter.drawPolygon(QPolygon() << QPoint(47, 15) << QPoint(52, 18) << QPoint(47, 21));

    // Ala animada: se dibuja arriba o abajo segun m_wingFrame.
    if (m_wingFrame == 0) {
        painter.drawPolygon(QPolygon() << QPoint(24, 15) << QPoint(4, 3) << QPoint(20, 22));
    } else {
        painter.drawPolygon(QPolygon() << QPoint(25, 18) << QPoint(4, 31) << QPoint(20, 13));
    }

    // Ojo.
    painter.setBrush(Qt::white);
    painter.drawEllipse(42, 13, 3, 3);
}
