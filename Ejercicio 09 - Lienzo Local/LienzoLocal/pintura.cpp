#include "pintura.h"

#include "databasemanager.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QWheelEvent>

Pintura::Pintura(const QString &username, QWidget *parent)
    : QWidget(parent)
    , m_username(username)
    , m_currentColor(Qt::red)
    , m_brushWidth(3)
    , m_drawing(false)
{
    // StrongFocus permite que el widget reciba eventos de teclado.
    setFocusPolicy(Qt::StrongFocus);
    setMinimumSize(800, 500);
    setAutoFillBackground(true);

    // Se define el fondo blanco del lienzo.
    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::white);
    setPalette(p);

    // Al abrir el lienzo se reconstruyen los trazos guardados del usuario.
    m_strokes = DatabaseManager::loadStrokes(m_username);
}

void Pintura::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Se recorren todos los trazos ya confirmados para volver a pintarlos.
    for (const StrokeData &stroke : m_strokes) {
        painter.setPen(QPen(stroke.color, stroke.width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

        // Si el trazo tiene un solo punto, se dibuja como punto suelto.
        if (stroke.points.size() == 1) {
            painter.drawPoint(stroke.points.first());
            continue;
        }

        // Si tiene varios puntos, se unen con lineas consecutivas.
        for (int i = 1; i < stroke.points.size(); ++i) {
            painter.drawLine(stroke.points[i - 1], stroke.points[i]);
        }
    }

    // Mientras el mouse esta presionado tambien se dibuja el trazo en curso.
    painter.setPen(QPen(m_currentColor, m_brushWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = 1; i < m_currentPoints.size(); ++i) {
        painter.drawLine(m_currentPoints[i - 1], m_currentPoints[i]);
    }
}

void Pintura::mousePressEvent(QMouseEvent *event)
{
    // Solo se dibuja con el boton izquierdo.
    if (event->button() != Qt::LeftButton) {
        return;
    }

    // Se inicia un trazo nuevo desde la posicion actual del mouse.
    setFocus();
    m_drawing = true;
    m_currentPoints.clear();
    m_currentPoints.append(event->pos());
    update();
}

void Pintura::mouseMoveEvent(QMouseEvent *event)
{
    // Si no hay un trazo iniciado, el movimiento del mouse no dibuja.
    if (!m_drawing) {
        return;
    }

    // Cada movimiento agrega una coordenada al trazo actual.
    m_currentPoints.append(event->pos());
    update();
}

void Pintura::mouseReleaseEvent(QMouseEvent *event)
{
    // Al soltar otro boton, o si no se estaba dibujando, no se guarda nada.
    if (!m_drawing || event->button() != Qt::LeftButton) {
        return;
    }

    // Se agrega el ultimo punto y se prepara la informacion completa del trazo.
    m_drawing = false;
    m_currentPoints.append(event->pos());

    StrokeData stroke;
    stroke.color = m_currentColor;
    stroke.width = m_brushWidth;
    stroke.points = m_currentPoints;
    stroke.id = DatabaseManager::saveStroke(m_username, stroke.color, stroke.width, stroke.points);

    // Si la base devolvio un id valido, el trazo queda visible en memoria.
    if (stroke.id != -1) {
        m_strokes.append(stroke);

        // Un trazo nuevo reinicia la cuenta de deshacer consecutivos.
        m_undoBuffer.clear();
    }

    // Se limpia el trazo temporal para esperar el proximo dibujo.
    m_currentPoints.clear();
    update();
}

void Pintura::wheelEvent(QWheelEvent *event)
{
    // Rueda hacia arriba aumenta el grosor; hacia abajo lo disminuye.
    const int step = event->angleDelta().y() > 0 ? 1 : -1;

    // qBound mantiene el grosor dentro de un rango razonable.
    m_brushWidth = qBound(1, m_brushWidth + step, 40);
    event->accept();
}

void Pintura::keyPressEvent(QKeyEvent *event)
{
    // Teclas de color solicitadas por la consigna.
    if (event->key() == Qt::Key_R) {
        m_currentColor = Qt::red;
        return;
    }

    if (event->key() == Qt::Key_G) {
        m_currentColor = Qt::green;
        return;
    }

    if (event->key() == Qt::Key_B) {
        m_currentColor = Qt::blue;
        return;
    }

    // Escape limpia el lienzo visible y marca los trazos como borrados en SQLite.
    if (event->key() == Qt::Key_Escape) {
        m_strokes.clear();
        m_undoBuffer.clear();
        DatabaseManager::clearCanvas(m_username);
        update();
        return;
    }

    // QKeySequence::Undo permite reconocer Ctrl+Z segun la plataforma.
    if (event->matches(QKeySequence::Undo)) {
        undoLastStroke();
        return;
    }

    QWidget::keyPressEvent(event);
}

void Pintura::undoLastStroke()
{
    // Se permite deshacer solo si hay trazos y no se superaron 10 acciones.
    if (m_strokes.isEmpty() || m_undoBuffer.size() >= 10) {
        return;
    }

    // El ultimo trazo se quita de pantalla y se marca como borrado en SQLite.
    StrokeData stroke = m_strokes.takeLast();
    DatabaseManager::markStrokeDeleted(stroke.id);

    // El buffer registra cuantos trazos se deshicieron de forma consecutiva.
    m_undoBuffer.append(stroke);

    update();
}
