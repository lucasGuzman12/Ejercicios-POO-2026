#ifndef APPFLOWCONTROLLER_H
#define APPFLOWCONTROLLER_H

#include <QObject>
#include <QPixmap>

class BackgroundDownloader;
class Login;
class Ventana;

class AppFlowController : public QObject
{
    Q_OBJECT
public:
    explicit AppFlowController(Login *login, Ventana *ventana, BackgroundDownloader *downloader,
                               QObject *parent = nullptr);

private slots:
    void onLoginSuccess();
    void onBackgroundReady(const QPixmap &pixmap, bool fromCache);
    void onBackgroundError(const QString &error);

private:
    Login *m_login;
    Ventana *m_ventana;
    BackgroundDownloader *m_downloader;
};

#endif // APPFLOWCONTROLLER_H
