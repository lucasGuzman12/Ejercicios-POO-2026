#ifndef PINTURA_H
#define PINTURA_H

#include "databasemanager.h"

#include <QColor>
#include <QWidget>

class Pintura : public QWidget
{
    Q_OBJECT

public:
    // Crea el lienzo asociado a un usuario para cargar y guardar sus trazos.
    explicit Pintura(const QString &username, QWidget *parent = nullptr);

protected:
    // Redibuja todos los trazos guardados y el trazo que se esta dibujando.
    void paintEvent(QPaintEvent *event) override;

    // Inicia un nuevo trazo cuando se presiona el boton izquierdo del mouse.
    void mousePressEvent(QMouseEvent *event) override;

    // Agrega puntos al trazo mientras el mouse se mueve.
    void mouseMoveEvent(QMouseEvent *event) override;

    // Finaliza el trazo y lo guarda en la base de datos.
    void mouseReleaseEvent(QMouseEvent *event) override;

    // Cambia el grosor del pincel con la rueda del mouse.
    void wheelEvent(QWheelEvent *event) override;

    // Atiende las teclas R, G, B, Escape y Ctrl+Z.
    void keyPressEvent(QKeyEvent *event) override;

private:
    // Deshace como maximo los ultimos 10 trazos de la sesion actual.
    void undoLastStroke();

    // Usuario logueado; se usa para cargar y guardar sus propios dibujos.
    QString m_username;

    // Trazos visibles que se pintan en pantalla.
    QVector<StrokeData> m_strokes;

    // Trazos ya deshechos, usado para limitar el Ctrl+Z a 10 acciones.
    QVector<StrokeData> m_undoBuffer;

    // Puntos del trazo que todavia se esta dibujando.
    QVector<QPoint> m_currentPoints;

    // Estado actual del pincel.
    QColor m_currentColor;
    int m_brushWidth;

    // Indica si el usuario mantiene presionado el boton izquierdo dibujando.
    bool m_drawing;
};

#endif // PINTURA_H
