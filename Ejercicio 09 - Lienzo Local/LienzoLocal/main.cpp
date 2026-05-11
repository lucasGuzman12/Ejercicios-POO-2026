#include "databasemanager.h"
#include "loginwidget.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    // Objeto principal de toda aplicacion Qt con widgets.
    QApplication a(argc, argv);

    // Inicializa SQLite y crea las tablas necesarias antes de mostrar pantallas.
    if (!DatabaseManager::initialize()) {
        QMessageBox::critical(nullptr, "Error", "No se pudo iniciar SQLite: " + DatabaseManager::lastError());
        return 1;
    }

    // Primera ventana de la aplicacion: formulario de login.
    LoginWidget login;

    // Conexion clasica: cuando el login es correcto, se abre el lienzo.
    QObject::connect(&login, SIGNAL(loginSuccess(QString)), &login, SLOT(openDrawing(QString)));

    login.show();

    // Inicia el bucle de eventos de Qt.
    return a.exec();
}
