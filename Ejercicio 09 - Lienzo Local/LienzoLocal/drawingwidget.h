#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    // Ventana contenedora del lienzo. Recibe el usuario para cargar sus trazos.
    explicit DrawingWidget(const QString &username, QWidget *parent = nullptr);
};

#endif // DRAWINGWIDGET_H
