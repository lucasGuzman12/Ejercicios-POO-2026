#include <QApplication>

#include "gamewidget.h"

int main(int argc, char *argv[])
{
    // QApplication administra el ciclo de vida de una aplicacion Qt.
    // Es obligatorio crearla antes de crear cualquier QWidget.
    QApplication app(argc, argv);

    // GameWidget es la ventana principal del juego.
    // Se usa QWidget directamente, tal como pide la consigna, en lugar de QMainWindow.
    GameWidget game;
    game.show();

    // app.exec() inicia el loop de eventos de Qt:
    // desde aca se procesan timers, teclado, repintados, botones, etc.
    return app.exec();
}
