#include "gestor_trabajos.h"
#include "almacenamiento_app.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUuid>

GestorTrabajos::GestorTrabajos()
{
    cargar();
}

const QVector<Trabajo> &GestorTrabajos::trabajos() const
{
    return m_trabajos;
}

void GestorTrabajos::agregarTrabajo(const Trabajo &trabajo)
{
    Trabajo t = trabajo;
    if (t.id.isEmpty()) {
        t.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    }
    m_trabajos.push_back(t);
    guardar();
}

bool GestorTrabajos::actualizarTrabajo(const Trabajo &trabajo)
{
    for (int i = 0; i < m_trabajos.size(); ++i) {
        if (m_trabajos[i].id == trabajo.id) {
            m_trabajos[i] = trabajo;
            guardar();
            return true;
        }
    }
    return false;
}

bool GestorTrabajos::eliminarTrabajo(const QString &idTrabajo)
{
    for (int i = 0; i < m_trabajos.size(); ++i) {
        if (m_trabajos[i].id == idTrabajo) {
            m_trabajos.removeAt(i);
            guardar();
            return true;
        }
    }
    return false;
}

Trabajo GestorTrabajos::trabajoPorId(const QString &idTrabajo) const
{
    for (const Trabajo &t : m_trabajos) {
        if (t.id == idTrabajo) {
            return t;
        }
    }
    return Trabajo();
}

void GestorTrabajos::guardar()
{
    QJsonArray arr;
    for (const Trabajo &t : m_trabajos) {
        QJsonObject obj;
        obj.insert("id", t.id);
        obj.insert("titulo", t.titulo);
        obj.insert("materia", t.materia);
        obj.insert("fechaVencimiento", t.fechaVencimiento.toString(Qt::ISODate));
        obj.insert("estado", t.estado);
        obj.insert("prioridad", t.prioridad);
        obj.insert("usuario", t.usuario);
        obj.insert("notas", t.notas);
        arr.append(obj);
    }
    AlmacenamientoApp::guardarJson("trabajos.json", QJsonDocument(arr));
}

void GestorTrabajos::cargar()
{
    m_trabajos.clear();
    bool ok = false;
    QJsonDocument doc = AlmacenamientoApp::leerJson("trabajos.json", &ok);
    if (!ok || !doc.isArray()) {
        doc = AlmacenamientoApp::leerJson("tasks.json", &ok);
    }
    if (!ok || !doc.isArray()) {
        return;
    }

    const QJsonArray arr = doc.array();
    for (const QJsonValue &val : arr) {
        const QJsonObject obj = val.toObject();
        Trabajo t;
        t.id = obj.value("id").toString();
        t.titulo = obj.value("titulo").toString();
        t.materia = obj.value("materia").toString();
        t.fechaVencimiento = QDate::fromString(obj.value("fechaVencimiento").toString(), Qt::ISODate);
        t.estado = obj.value("estado").toString();
        t.prioridad = obj.value("prioridad").toString();
        t.usuario = obj.value("usuario").toString();
        t.notas = obj.value("notas").toString();
        if (t.titulo.isEmpty()) {
            t.titulo = obj.value("title").toString();
        }
        if (t.materia.isEmpty()) {
            t.materia = obj.value("subject").toString();
        }
        if (!t.fechaVencimiento.isValid()) {
            t.fechaVencimiento = QDate::fromString(obj.value("dueDate").toString(), Qt::ISODate);
        }
        if (t.estado.isEmpty()) {
            t.estado = obj.value("status").toString();
        }
        if (t.prioridad.isEmpty()) {
            t.prioridad = obj.value("priority").toString();
        }
        if (t.usuario.isEmpty()) {
            t.usuario = obj.value("owner").toString();
        }
        if (t.notas.isEmpty()) {
            t.notas = obj.value("notes").toString();
        }
        if (!t.titulo.isEmpty()) {
            m_trabajos.push_back(t);
        }
    }
}
