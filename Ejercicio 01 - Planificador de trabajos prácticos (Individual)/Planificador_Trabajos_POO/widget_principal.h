#ifndef WIDGET_PRINCIPAL_H
#define WIDGET_PRINCIPAL_H

#include <QWidget>
#include "gestor_historial.h"
#include "gestor_trabajos.h"

class QComboBox;
class QGridLayout;
class QListWidget;
class QPushButton;
class QScrollArea;

class WidgetPrincipal : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPrincipal(const QString &usuario, QWidget *parent = nullptr);

signals:
    void cierreSesionSolicitado();

private slots:
    void alAgregarTrabajo();
    void alCambiarFiltro();
    void alCerrarSesion();

private:
    void construirUi();
    void refrescarGrilla();
    void limpiarGrilla();
    void agregarHistorial(const QString &mensaje);

    QString m_usuario;
    GestorTrabajos m_gestorTrabajos;
    GestorHistorial m_gestorHistorial;

    QComboBox *m_filtroEstado;
    QComboBox *m_filtroPrioridad;
    QGridLayout *m_grilla;
    QWidget *m_contenedorGrilla;
    QScrollArea *m_scroll;
    QListWidget *m_listaHistorial;
    QPushButton *m_botonNuevo;
    QPushButton *m_botonCerrarSesion;
};

#endif // WIDGET_PRINCIPAL_H
