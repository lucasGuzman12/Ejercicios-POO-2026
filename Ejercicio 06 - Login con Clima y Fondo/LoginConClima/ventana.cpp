#include "ventana.h"
#include "ui_ventana.h"

#include "configmanager.h"
#include "logger.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>

Ventana::Ventana(QNetworkAccessManager *manager, ConfigManager *config, QWidget *parent)
    : Pantalla(parent)
    , ui(new Ui::Ventana)
    , m_manager(manager)
    , m_config(config)
{
    ui->setupUi(this);
    inicializarPantalla();
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::inicializarPantalla()
{
    // Pantalla principal (CV/Perfil) mostrada luego del login valido.
    setWindowTitle("Ventana Principal");
}

void Ventana::setBackground(const QPixmap &pixmap)
{
    m_backgroundOriginal = pixmap;
    refreshBackground();
}

void Ventana::resizeEvent(QResizeEvent *event)
{
    Pantalla::resizeEvent(event);
    refreshBackground();
}

void Ventana::refreshBackground()
{
    if (m_backgroundOriginal.isNull()) {
        return;
    }

    const QSize target = ui->lblBackground->size();
    // Ajuste manteniendo relacion de aspecto para evitar deformacion.
    const QPixmap scaled = m_backgroundOriginal.scaled(target, Qt::KeepAspectRatioByExpanding,
                                                       Qt::SmoothTransformation);
    ui->lblBackground->setPixmap(scaled);
}

void Ventana::procesarFotoPerfil(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Logger::write("No se pudo descargar foto de perfil: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    // Renderiza foto circular para estilo visual de perfil profesional.
    QPixmap original;
    if (!original.loadFromData(reply->readAll())) {
        reply->deleteLater();
        return;
    }

    const int side = qMin(ui->lblFoto->width(), ui->lblFoto->height());
    QPixmap circular(side, side);
    circular.fill(Qt::transparent);

    QPainter painter(&circular);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;
    path.addEllipse(0, 0, side, side);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0,
                       original.scaled(side, side, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

    ui->lblFoto->setPixmap(circular);
    reply->deleteLater();
}

void Ventana::onProfilePhotoFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) {
        return;
    }
    procesarFotoPerfil(reply);
}
