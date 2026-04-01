#ifndef GESTOR_TRABAJOS_H
#define GESTOR_TRABAJOS_H

#include <QDate>
#include <QString>
#include <QVector>

struct Trabajo
{
    QString id;
    QString titulo;
    QString materia;
    QDate fechaVencimiento;
    QString estado;
    QString prioridad;
    QString usuario;
    QString notas;
};

class GestorTrabajos
{
public:
    GestorTrabajos();

    const QVector<Trabajo> &trabajos() const;

    void agregarTrabajo(const Trabajo &trabajo);
    bool actualizarTrabajo(const Trabajo &trabajo);
    bool eliminarTrabajo(const QString &idTrabajo);
    Trabajo trabajoPorId(const QString &idTrabajo) const;

    void guardar();

private:
    void cargar();

    QVector<Trabajo> m_trabajos;
};

#endif // GESTOR_TRABAJOS_H
