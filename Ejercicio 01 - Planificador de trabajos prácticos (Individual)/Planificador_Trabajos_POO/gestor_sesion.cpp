#include "gestor_sesion.h"
#include "almacenamiento_app.h"

#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

bool GestorSesion::cargarSesionValida(QString *usuario)
{
    if (usuario) {
        usuario->clear();
    }

    bool ok = false;
    QJsonDocument doc = AlmacenamientoApp::leerJson("sesion.json", &ok);
    if (!ok || !doc.isObject()) {
        doc = AlmacenamientoApp::leerJson("session.json", &ok);
    }
    if (!ok || !doc.isObject()) {
        return false;
    }

    const QJsonObject obj = doc.object();
    QString user = obj.value("usuario").toString();
    const qint64 ts = obj.value("timestamp").toVariant().toLongLong();
    if (user.isEmpty()) {
        user = obj.value("username").toString();
    }
    if (user.isEmpty() || ts <= 0) {
        return false;
    }

    const qint64 now = QDateTime::currentSecsSinceEpoch();
    if (now - ts > kSegundosSesion) {
        return false;
    }

    if (usuario) {
        *usuario = user;
    }
    return true;
}

void GestorSesion::guardarSesion(const QString &usuario)
{
    QJsonObject obj;
    obj.insert("usuario", usuario);
    obj.insert("timestamp", QDateTime::currentSecsSinceEpoch());
    AlmacenamientoApp::guardarJson("sesion.json", QJsonDocument(obj));
}

void GestorSesion::limpiarSesion()
{
    QFile::remove(AlmacenamientoApp::rutaArchivo("sesion.json"));
}
