#ifndef GESTOR_HISTORIAL_H
#define GESTOR_HISTORIAL_H

#include <QString>
#include <QStringList>

class GestorHistorial
{
public:
    GestorHistorial();

    QStringList entradas() const;
    void agregar(const QString &mensaje);

private:
    void cargar();
    void guardar();

    QStringList m_entradas;
};

#endif // GESTOR_HISTORIAL_H
