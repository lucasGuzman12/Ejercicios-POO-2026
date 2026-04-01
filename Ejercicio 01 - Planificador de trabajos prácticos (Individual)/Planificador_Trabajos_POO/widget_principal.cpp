#include "widget_principal.h"
#include "dialogo_notas.h"
#include "dialogo_trabajo.h"
#include "gestor_sesion.h"

#include <QComboBox>
#include <QDate>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

namespace {
QString siguienteEstado(const QString &estado)
{
    if (estado == "Pendiente") return "En progreso";
    if (estado == "En progreso") return "Entregado";
    return "Pendiente";
}
}

WidgetPrincipal::WidgetPrincipal(const QString &usuario, QWidget *parent)
    : QWidget(parent)
    , m_usuario(usuario)
    , m_filtroEstado(new QComboBox(this))
    , m_filtroPrioridad(new QComboBox(this))
    , m_grilla(new QGridLayout)
    , m_contenedorGrilla(new QWidget(this))
    , m_scroll(new QScrollArea(this))
    , m_listaHistorial(new QListWidget(this))
    , m_botonNuevo(new QPushButton("Nuevo trabajo", this))
    , m_botonCerrarSesion(new QPushButton("Cerrar sesion", this))
{
    construirUi();
    refrescarGrilla();
    agregarHistorial("Inicio de sesion: " + m_usuario);
}

void WidgetPrincipal::construirUi()
{
    setWindowTitle("Planificador de trabajos practicos");
    setMinimumSize(900, 600);

    m_filtroEstado->addItems({"Todos", "Pendiente", "En progreso", "Entregado"});
    m_filtroPrioridad->addItems({"Todas", "Baja", "Media", "Alta"});

    connect(m_filtroEstado, &QComboBox::currentTextChanged, this, &WidgetPrincipal::alCambiarFiltro);
    connect(m_filtroPrioridad, &QComboBox::currentTextChanged, this, &WidgetPrincipal::alCambiarFiltro);
    connect(m_botonNuevo, &QPushButton::clicked, this, &WidgetPrincipal::alAgregarTrabajo);
    connect(m_botonCerrarSesion, &QPushButton::clicked, this, &WidgetPrincipal::alCerrarSesion);

    QHBoxLayout *filtros = new QHBoxLayout;
    filtros->addWidget(new QLabel("Estado:"));
    filtros->addWidget(m_filtroEstado);
    filtros->addSpacing(16);
    filtros->addWidget(new QLabel("Prioridad:"));
    filtros->addWidget(m_filtroPrioridad);
    filtros->addStretch();
    filtros->addWidget(m_botonNuevo);
    filtros->addWidget(m_botonCerrarSesion);

    m_contenedorGrilla->setLayout(m_grilla);
    m_scroll->setWidget(m_contenedorGrilla);
    m_scroll->setWidgetResizable(true);

    QGroupBox *cajaHistorial = new QGroupBox("Historial de acciones", this);
    QVBoxLayout *disposicionHistorial = new QVBoxLayout(cajaHistorial);
    disposicionHistorial->addWidget(m_listaHistorial);

    QVBoxLayout *principal = new QVBoxLayout(this);
    principal->addLayout(filtros);
    principal->addWidget(m_scroll, 1);
    principal->addWidget(cajaHistorial, 0);

    m_listaHistorial->addItems(m_gestorHistorial.entradas());
}

void WidgetPrincipal::alAgregarTrabajo()
{
    DialogoTrabajo dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        Trabajo t = dlg.trabajo();
        if (t.titulo.isEmpty()) {
            QMessageBox::warning(this, "Validacion", "El titulo no puede estar vacio.");
            return;
        }
        t.usuario = m_usuario;
        m_gestorTrabajos.agregarTrabajo(t);
        agregarHistorial("Alta de trabajo: " + t.titulo);
        refrescarGrilla();
    }
}

void WidgetPrincipal::alCambiarFiltro()
{
    refrescarGrilla();
}

void WidgetPrincipal::alCerrarSesion()
{
    GestorSesion::limpiarSesion();
    agregarHistorial("Cierre de sesion: " + m_usuario);
    emit cierreSesionSolicitado();
}

void WidgetPrincipal::refrescarGrilla()
{
    limpiarGrilla();

    const QString filtroEstado = m_filtroEstado->currentText();
    const QString filtroPrioridad = m_filtroPrioridad->currentText();

    QStringList encabezados = {"Titulo", "Materia", "Vence", "Estado", "Prioridad", "Usuario", "Acciones"};
    for (int c = 0; c < encabezados.size(); ++c) {
        QLabel *etiqueta = new QLabel("<b>" + encabezados[c] + "</b>");
        etiqueta->setStyleSheet("background-color: #d7eadb; padding: 6px; border-radius: 0px;");
        etiqueta->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        m_grilla->addWidget(etiqueta, 0, c);
    }

    int fila = 1;
    for (const Trabajo &t : m_gestorTrabajos.trabajos()) {
        if (filtroEstado != "Todos" && t.estado != filtroEstado) {
            continue;
        }
        if (filtroPrioridad != "Todas" && t.prioridad != filtroPrioridad) {
            continue;
        }

        m_grilla->addWidget(new QLabel(t.titulo), fila, 0);
        m_grilla->addWidget(new QLabel(t.materia), fila, 1);
        m_grilla->addWidget(new QLabel(t.fechaVencimiento.toString("yyyy-MM-dd")), fila, 2);
        m_grilla->addWidget(new QLabel(t.estado), fila, 3);
        m_grilla->addWidget(new QLabel(t.prioridad), fila, 4);
        m_grilla->addWidget(new QLabel(t.usuario.isEmpty() ? "N/D" : t.usuario), fila, 5);

        QWidget *acciones = new QWidget(this);
        QHBoxLayout *disposicionAcciones = new QHBoxLayout(acciones);
        disposicionAcciones->setContentsMargins(0, 0, 0, 0);

        QPushButton *botonEditar = new QPushButton("Editar", acciones);
        QPushButton *botonNotas = new QPushButton("Notas", acciones);
        QPushButton *botonCambiar = new QPushButton("Cambiar", acciones);
        QPushButton *botonEliminar = new QPushButton("Eliminar", acciones);

        disposicionAcciones->addWidget(botonEditar);
        disposicionAcciones->addWidget(botonNotas);
        disposicionAcciones->addWidget(botonCambiar);
        disposicionAcciones->addWidget(botonEliminar);

        m_grilla->addWidget(acciones, fila, 6);

        connect(botonEditar, &QPushButton::clicked, this, [this, t]() {
            DialogoTrabajo dlg(this);
            dlg.setTrabajo(t);
            if (dlg.exec() == QDialog::Accepted) {
                Trabajo updated = dlg.trabajo();
                if (updated.titulo.isEmpty()) {
                    QMessageBox::warning(this, "Validacion", "El titulo no puede estar vacio.");
                    return;
                }
                m_gestorTrabajos.actualizarTrabajo(updated);
                agregarHistorial("Edicion de trabajo: " + updated.titulo);
                refrescarGrilla();
            }
        });

        connect(botonNotas, &QPushButton::clicked, this, [this, t]() {
            DialogoNotas dlg(this);
            dlg.setNotas(t.notas);
            if (dlg.exec() == QDialog::Accepted) {
                Trabajo updated = t;
                updated.notas = dlg.notas();
                m_gestorTrabajos.actualizarTrabajo(updated);
                agregarHistorial("Notas guardadas: " + updated.titulo);
                refrescarGrilla();
            }
        });

        connect(botonCambiar, &QPushButton::clicked, this, [this, t]() {
            Trabajo updated = t;
            updated.estado = siguienteEstado(updated.estado);
            m_gestorTrabajos.actualizarTrabajo(updated);
            agregarHistorial("Cambio de estado: " + updated.titulo + " -> " + updated.estado);
            refrescarGrilla();
        });

        connect(botonEliminar, &QPushButton::clicked, this, [this, t]() {
            const auto respuesta = QMessageBox::question(this, "Eliminar", "Eliminar el trabajo seleccionado?");
            if (respuesta == QMessageBox::Yes) {
                m_gestorTrabajos.eliminarTrabajo(t.id);
                agregarHistorial("Eliminacion de trabajo: " + t.titulo);
                refrescarGrilla();
            }
        });

        ++fila;
    }

    m_grilla->setColumnStretch(0, 2);
    m_grilla->setColumnStretch(1, 2);
    m_grilla->setColumnStretch(2, 1);
    m_grilla->setColumnStretch(3, 1);
    m_grilla->setColumnStretch(4, 1);
    m_grilla->setColumnStretch(5, 1);
    m_grilla->setColumnStretch(6, 2);
    m_grilla->setRowStretch(fila, 1);
}

void WidgetPrincipal::limpiarGrilla()
{
    while (QLayoutItem *item = m_grilla->takeAt(0)) {
        if (QWidget *w = item->widget()) {
            w->deleteLater();
        }
        if (QLayout *l = item->layout()) {
            delete l;
        }
        delete item;
    }
}

void WidgetPrincipal::agregarHistorial(const QString &mensaje)
{
    m_gestorHistorial.agregar(mensaje);
    m_listaHistorial->clear();
    m_listaHistorial->addItems(m_gestorHistorial.entradas());
}
