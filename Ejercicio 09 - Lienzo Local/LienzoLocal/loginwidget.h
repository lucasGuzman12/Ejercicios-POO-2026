#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWidget;
}
QT_END_NAMESPACE

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    // Construye la pantalla de ingreso definida en Qt Designer.
    explicit LoginWidget(QWidget *parent = nullptr);

    // Libera la interfaz generada por el archivo .ui.
    ~LoginWidget() override;

signals:
    // Se emite cuando el usuario ingreso credenciales validas.
    void loginSuccess(const QString &username);

private slots:
    // Lee usuario y contrasena, valida contra SQLite y registra el acceso.
    void tryLogin();

    // Abre el lienzo del usuario despues de un login exitoso.
    void openDrawing(const QString &username);

private:
    // Puntero a los controles creados desde loginwidget.ui.
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H
