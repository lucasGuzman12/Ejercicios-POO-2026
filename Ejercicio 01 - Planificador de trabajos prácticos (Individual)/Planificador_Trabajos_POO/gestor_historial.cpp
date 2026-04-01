#include "gestor_historial.h"
#include "almacenamiento_app.h"

#include <QDateTime>
#include <QJsonArray>
#include <QJsonDocument>

GestorHistorial::GestorHistorial()
{
    cargar();
}

QStringList GestorHistorial::entradas() const
{
    return m_entradas;
}

void GestorHistorial::agregar(const QString &mensaje)
{
    const QString ts = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    m_entradas.prepend(ts + " - " + mensaje);

    if (m_entradas.size() > 500) {
        m_entradas = m_entradas.mid(0, 500);
    }
    guardar();
}

void GestorHistorial::cargar()
{
    m_entradas.clear();
    bool ok = false;
    QJsonDocument doc = AlmacenamientoApp::leerJson("historial.json", &ok);
    if (!ok || !doc.isArray()) {
        doc = AlmacenamientoApp::leerJson("history.json", &ok);
    }
    if (!ok || !doc.isArray()) {
        return;
    }

    const QJsonArray arr = doc.array();
    for (const QJsonValue &val : arr) {
        const QString entry = val.toString();
        if (!entry.isEmpty()) {
            m_entradas.append(entry);
        }
    }
}

void GestorHistorial::guardar()
{
    QJsonArray arr;
    for (const QString &entry : m_entradas) {
        arr.append(entry);
    }
    AlmacenamientoApp::guardarJson("historial.json", QJsonDocument(arr));
}
