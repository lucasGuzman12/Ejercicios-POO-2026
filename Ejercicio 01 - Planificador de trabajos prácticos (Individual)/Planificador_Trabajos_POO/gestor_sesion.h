#ifndef GESTOR_SESION_H
#define GESTOR_SESION_H

#include <QString>

class GestorSesion
{
public:
    static bool cargarSesionValida(QString *usuario);
    static void guardarSesion(const QString &usuario);
    static void limpiarSesion();

    static constexpr int kSegundosSesion = 300; // 5 minutos
};

#endif // GESTOR_SESION_H
