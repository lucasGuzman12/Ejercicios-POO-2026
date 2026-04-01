#include "gestor_usuarios.h"
#include "almacenamiento_app.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

GestorUsuarios::GestorUsuarios()
{
    cargar();
}

bool GestorUsuarios::validar(const QString &usuario, const QString &contrasena) const
{
    return m_usuarios.contains(usuario) && m_usuarios.value(usuario) == contrasena;
}

QStringList GestorUsuarios::usuarios() const
{
    return m_usuarios.keys();
}

bool GestorUsuarios::agregarUsuario(const QString &usuario, const QString &contrasena, QString *error)
{
    if (usuario.trimmed().isEmpty() || contrasena.isEmpty()) {
        if (error) {
            *error = "Usuario y contrasena son obligatorios.";
        }
        return false;
    }
    if (m_usuarios.contains(usuario)) {
        if (error) {
            *error = "El usuario ya existe.";
        }
        return false;
    }
    m_usuarios.insert(usuario, contrasena);
    guardar();
    return true;
}

void GestorUsuarios::cargar()
{
    m_usuarios.clear();
    bool ok = false;
    QJsonDocument doc = AlmacenamientoApp::leerJson("usuarios.json", &ok);
    if (!ok || !doc.isArray()) {
        doc = AlmacenamientoApp::leerJson("users.json", &ok);
    }
    if (!ok || !doc.isArray()) {
        asegurarUsuariosPorDefecto();
        return;
    }

    const QJsonArray arr = doc.array();
    for (const QJsonValue &val : arr) {
        const QJsonObject obj = val.toObject();
        QString usuario = obj.value("usuario").toString();
        QString contrasena = obj.value("contrasena").toString();
        if (usuario.isEmpty()) {
            usuario = obj.value("username").toString();
        }
        if (contrasena.isEmpty()) {
            contrasena = obj.value("password").toString();
        }
        if (!usuario.isEmpty()) {
            m_usuarios.insert(usuario, contrasena);
        }
    }

    if (m_usuarios.isEmpty()) {
        asegurarUsuariosPorDefecto();
    }
}

void GestorUsuarios::asegurarUsuariosPorDefecto()
{
    m_usuarios.clear();
    m_usuarios.insert("admin", "admin");
    m_usuarios.insert("estudiante", "1234");

    QJsonArray arr;
    for (auto it = m_usuarios.cbegin(); it != m_usuarios.cend(); ++it) {
        QJsonObject obj;
        obj.insert("usuario", it.key());
        obj.insert("contrasena", it.value());
        arr.append(obj);
    }

    AlmacenamientoApp::guardarJson("usuarios.json", QJsonDocument(arr));
}

void GestorUsuarios::guardar()
{
    QJsonArray arr;
    for (auto it = m_usuarios.cbegin(); it != m_usuarios.cend(); ++it) {
        QJsonObject obj;
        obj.insert("usuario", it.key());
        obj.insert("contrasena", it.value());
        arr.append(obj);
    }
    AlmacenamientoApp::guardarJson("usuarios.json", QJsonDocument(arr));
}
