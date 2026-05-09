#ifndef PANTALLA_H
#define PANTALLA_H

#include <QWidget>

class AppController;

class Pantalla : public QWidget
{
    Q_OBJECT
public:
    explicit Pantalla(AppController *controller, QWidget *parent = nullptr);
    ~Pantalla() override;

    virtual void inicializarUI() = 0;
    virtual void conectarEventos() = 0;
    virtual void cargarDatos() = 0;
    virtual bool validarEstado() = 0;
    virtual void registrarEvento(const QString &descripcion) = 0;

protected:
    AppController *m_controller;
};

#endif // PANTALLA_H
