#include "drawingwidget.h"

#include "pintura.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QFrame>
#include <QVBoxLayout>

DrawingWidget::DrawingWidget(const QString &username, QWidget *parent)
    : QWidget(parent)
{
    // Nombre de objeto usado por la hoja de estilos.
    setObjectName("DrawingWidget");
    setWindowTitle("Lienzo SQLite");
    resize(1000, 700);

    // Estilos de la ventana principal, barra superior y etiquetas informativas.
    setStyleSheet(
        "QWidget#DrawingWidget {"
        "  background: #f1f5f9;"
        "  color: #0f172a;"
        "  font-family: 'Segoe UI';"
        "}"
        "QFrame#topBar {"
        "  background: #ffffff;"
        "  border: 1px solid #dbe3ee;"
        "  border-radius: 12px;"
        "}"
        "QLabel#titleLabel {"
        "  background: transparent;"
        "  font-size: 18px;"
        "  font-weight: 700;"
        "  color: #0f172a;"
        "}"
        "QLabel#helpLabel {"
        "  background: transparent;"
        "  font-size: 13px;"
        "  color: #475569;"
        "}"
        "QLabel#userChip {"
        "  background: #e2e8f0;"
        "  color: #1e293b;"
        "  border-radius: 10px;"
        "  padding: 6px 10px;"
        "  font-weight: 600;"
        "}"
    );

    // Layout vertical: arriba una barra de informacion y abajo el lienzo.
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(12);

    // Barra superior con titulo, ayuda rapida y usuario activo.
    auto *topBar = new QFrame(this);
    topBar->setObjectName("topBar");
    auto *topLayout = new QHBoxLayout(topBar);
    topLayout->setContentsMargins(14, 10, 14, 10);

    auto *title = new QLabel("Lienzo Local", this);
    title->setObjectName("titleLabel");
    auto *help = new QLabel("R/G/B color | Rueda grosor | ESC limpiar | Ctrl+Z deshacer", this);
    help->setObjectName("helpLabel");
    auto *userChip = new QLabel("Usuario: " + username, this);
    userChip->setObjectName("userChip");

    // Se acomodan los textos de la barra superior.
    topLayout->addWidget(title);
    topLayout->addSpacing(16);
    topLayout->addWidget(help, 1);
    topLayout->addWidget(userChip, 0, Qt::AlignRight);

    // Widget de dibujo real: maneja mouse, teclado, pintura y persistencia.
    auto *canvas = new Pintura(username, this);
    canvas->setObjectName("canvasArea");

    // Estilo visual del area de dibujo.
    canvas->setStyleSheet(
        "QWidget#canvasArea {"
        "  background: #ffffff;"
        "  border: 1px solid #dbe3ee;"
        "  border-radius: 14px;"
        "}"
    );

    // Se agrega la barra y el lienzo a la ventana.
    layout->addWidget(topBar);
    layout->addWidget(canvas, 1);
}
