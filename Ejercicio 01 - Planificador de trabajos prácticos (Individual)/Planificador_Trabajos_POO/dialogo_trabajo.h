#ifndef DIALOGO_TRABAJO_H
#define DIALOGO_TRABAJO_H

#include <QDialog>
#include "gestor_trabajos.h"

class QLineEdit;
class QDateEdit;
class QComboBox;

class DialogoTrabajo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogoTrabajo(QWidget *parent = nullptr);

    void setTrabajo(const Trabajo &trabajo);
    Trabajo trabajo() const;

private:
    QLineEdit *m_tituloEdit;
    QLineEdit *m_materiaEdit;
    QDateEdit *m_vencimientoEdit;
    QComboBox *m_estadoBox;
    QComboBox *m_prioridadBox;

    Trabajo m_trabajo;
};

#endif // DIALOGO_TRABAJO_H
