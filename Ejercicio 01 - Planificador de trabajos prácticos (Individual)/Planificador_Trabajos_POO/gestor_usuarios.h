#ifndef GESTOR_USUARIOS_H
#define GESTOR_USUARIOS_H

#include <QHash>
#include <QString>

class GestorUsuarios
{
public:
    GestorUsuarios();

    bool validar(const QString &usuario, const QString &contrasena) const;
    QStringList usuarios() const;
    bool agregarUsuario(const QString &usuario, const QString &contrasena, QString *error);

private:
    void cargar();
    void asegurarUsuariosPorDefecto();
    void guardar();

    QHash<QString, QString> m_usuarios;
};

#endif // GESTOR_USUARIOS_H
