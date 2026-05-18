#include "trex.h"

#include <QPainter>

TRex::TRex(QWidget *parent)
    : QWidget(parent),
      m_verticalVelocity(0),
      m_jumping(false),
      m_crouching(false)
{
    // Tamano normal del dinosaurio cuando esta parado.
    setFixedSize(58, 72);
}

void TRex::reset(int groundY)
{
    // Limpia el estado de movimiento.
    m_verticalVelocity = 0;
    m_jumping = false;
    m_crouching = false;

    // Restaura el tamano normal.
    setFixedSize(58, 72);

    // Posicion inicial: x fija y apoyado sobre el suelo.
    move(80, groundY - height());

    // Solicita repintar el widget.
    update();
}

void TRex::jump()
{
    // Solo se puede saltar si no esta ya en el aire.
    if (!m_jumping) {
        // Velocidad negativa significa moverse hacia arriba.
        m_verticalVelocity = -22;
        m_jumping = true;

        // Si estaba agachado, vuelve a forma normal antes de saltar.
        crouch(false);
    }
}

void TRex::crouch(bool enabled)
{
    // No se permite agacharse en medio de un salto.
    if (m_jumping) {
        return;
    }

    // Si ya esta en el estado solicitado, no hace falta recalcular nada.
    if (m_crouching == enabled) {
        return;
    }

    // Se guarda la posicion inferior para que al cambiar de alto siga tocando el suelo.
    int bottom = y() + height();
    m_crouching = enabled;

    // Agachado: mas ancho y mas bajo. Parado: mas angosto y mas alto.
    setFixedSize(enabled ? QSize(78, 42) : QSize(58, 72));
    move(x(), bottom - height());
    update();
}

void TRex::advance()
{
    // Avanza un poco hacia la derecha.
    int nextX = x() + 18;

    // Evita que el dinosaurio se vaya fuera del borde derecho.
    if (parentWidget()) {
        nextX = qMin(nextX, parentWidget()->width() - width() - 20);
    }
    move(nextX, y());
}

void TRex::brake()
{
    // Retrocede un poco, sin pasar el borde izquierdo.
    move(qMax(20, x() - 18), y());
}

void TRex::updatePhysics(int groundY)
{
    // Si no esta saltando, simplemente se lo mantiene apoyado en el suelo.
    if (!m_jumping) {
        move(x(), groundY - height());
        return;
    }

    // Aplica la velocidad vertical actual.
    move(x(), y() + m_verticalVelocity);

    // Gravedad: en cada tick la velocidad aumenta hacia abajo.
    m_verticalVelocity += 2;

    // Cuando vuelve al suelo, termina el salto.
    if (y() + height() >= groundY) {
        move(x(), groundY - height());
        m_verticalVelocity = 0;
        m_jumping = false;
    }
}

QRect TRex::collisionRect() const
{
    // Rectangulo levemente reducido respecto al dibujo.
    // Esto evita perder por tocar apenas una esquina transparente/visual.
    return QRect(x() + 8, y() + 8, width() - 16, height() - 10);
}

void TRex::paintEvent(QPaintEvent *event)
{
    // El parametro no se usa, pero la firma es obligatoria al sobrescribir paintEvent().
    Q_UNUSED(event);

    // El T-Rex se dibuja con figuras simples para no depender de imagenes externas.
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Colores del cuerpo y del ojo.
    QColor body(52, 52, 52);
    QColor eye(250, 250, 250);
    painter.setPen(Qt::NoPen);
    painter.setBrush(body);

    if (m_crouching) {
        // Dibujo del dinosaurio agachado: cuerpo largo y bajo.
        painter.drawRoundedRect(8, 14, 48, 20, 5, 5);
        painter.drawRoundedRect(46, 6, 24, 18, 5, 5);
        painter.drawRect(17, 30, 8, 10);
        painter.drawRect(42, 30, 8, 10);
        painter.drawRect(3, 20, 14, 6);
        painter.setBrush(eye);
        painter.drawEllipse(60, 11, 4, 4);
    } else {
        // Dibujo del dinosaurio parado.
        painter.drawRoundedRect(13, 28, 30, 30, 7, 7);
        painter.drawRoundedRect(33, 10, 22, 23, 5, 5);
        painter.drawRect(7, 37, 14, 7);
        painter.drawRect(20, 55, 8, 15);
        painter.drawRect(36, 55, 8, 15);
        painter.drawRect(43, 24, 11, 5);
        painter.setBrush(eye);
        painter.drawEllipse(47, 16, 4, 4);
    }
}
