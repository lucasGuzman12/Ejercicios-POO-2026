#ifndef VENTANA_H
#define VENTANA_H

#include "pantalla.h"

#include <QPixmap>

class ConfigManager;
class QNetworkAccessManager;
class QNetworkReply;

namespace Ui {
class Ventana;
}

class Ventana : public Pantalla
{
    Q_OBJECT
public:
    explicit Ventana(QNetworkAccessManager *manager, ConfigManager *config, QWidget *parent = nullptr);
    ~Ventana() override;

    void inicializarPantalla() override;
    void setBackground(const QPixmap &pixmap);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onProfilePhotoFinished();

private:
    void refreshBackground();
    void procesarFotoPerfil(QNetworkReply *reply);

    Ui::Ventana *ui;
    QPixmap m_backgroundOriginal;
    QNetworkAccessManager *m_manager;
    ConfigManager *m_config;
};

#endif // VENTANA_H
