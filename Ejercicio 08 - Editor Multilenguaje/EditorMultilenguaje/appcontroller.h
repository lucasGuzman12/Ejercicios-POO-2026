#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "configmanager.h"

#include <QObject>

class Pantalla;
class Login;
class EditorPrincipal;
class ModoBloqueado;

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = nullptr);
    ~AppController() override;

    void iniciar();
    const AppConfig &config() const;

    bool autenticar(const QString &usuario, const QString &clave);
    void pantallaLogin();
    void pantallaEditor();
    void pantallaBloqueada(int segundos);

private slots:
    void onBloqueoFinalizado();

private:
    void mostrarPantalla(Pantalla *pantalla);

    AppConfig m_config;
    Pantalla *m_actual = nullptr;
    Login *m_login = nullptr;
    EditorPrincipal *m_editor = nullptr;
    ModoBloqueado *m_bloqueada = nullptr;
};

#endif // APPCONTROLLER_H
