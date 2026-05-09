#include "bloqueada.h"

#include "logger.h"

#include <QCloseEvent>
#include <QFocusEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QTimer>
#include <QVBoxLayout>

ModoBloqueado::ModoBloqueado(AppController *controller, QWidget *parent)
    : Pantalla(controller, parent)
{
    inicializarUI();
    conectarEventos();
    cargarDatos();
}

void ModoBloqueado::iniciarBloqueo(int segundos)
{
    m_segundos = segundos;
    m_label->setText("Demasiados intentos fallidos.\nEspere " + QString::number(m_segundos) + " segundos.");
    m_timer->start(1000);
    registrarEvento("Inicio bloqueo temporal.");
}

void ModoBloqueado::inicializarUI()
{
    setWindowTitle("Modo bloqueado");
    setObjectName("BlockedRoot");
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(40, 40, 40, 40);
    m_label = new QLabel("Bloqueado", this);
    m_label->setAlignment(Qt::AlignCenter);
    m_label->setObjectName("BlockedLabel");
    layout->addWidget(m_label);
    setStyleSheet(
        "#BlockedRoot { background: qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #fff5f5, stop:1 #fde7e7); }"
        "#BlockedLabel { font-size: 26px; color: #9f1d1d; font-weight: 700; padding: 26px; "
        "background: rgba(255,255,255,0.72); border: 1px solid #f1c8c8; border-radius: 14px; }");
}

void ModoBloqueado::conectarEventos()
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(tick()));
}

void ModoBloqueado::cargarDatos()
{
}

bool ModoBloqueado::validarEstado()
{
    return m_segundos >= 0;
}

void ModoBloqueado::registrarEvento(const QString &descripcion)
{
    Logger::log("Bloqueada: " + descripcion);
}

void ModoBloqueado::keyPressEvent(QKeyEvent *event)
{
    registrarEvento("Tecla bloqueada ignorada.");
    event->ignore();
}

void ModoBloqueado::mousePressEvent(QMouseEvent *event)
{
    registrarEvento("Click ignorado en modo bloqueado.");
    event->ignore();
}

void ModoBloqueado::resizeEvent(QResizeEvent *event)
{
    registrarEvento("Resize en bloqueado.");
    QWidget::resizeEvent(event);
}

void ModoBloqueado::closeEvent(QCloseEvent *event)
{
    registrarEvento("Intento de cierre durante bloqueo.");
    event->ignore();
}

void ModoBloqueado::focusInEvent(QFocusEvent *event)
{
    registrarEvento("Focus in en bloqueado.");
    QWidget::focusInEvent(event);
}

void ModoBloqueado::focusOutEvent(QFocusEvent *event)
{
    registrarEvento("Focus out en bloqueado.");
    QWidget::focusOutEvent(event);
}

void ModoBloqueado::tick()
{
    m_segundos--;
    if (m_segundos <= 0) {
        m_timer->stop();
        m_label->setText("Bloqueo finalizado.");
        emit bloqueoFinalizado();
        return;
    }
    m_label->setText("Demasiados intentos fallidos.\nEspere " + QString::number(m_segundos) + " segundos.");
}
