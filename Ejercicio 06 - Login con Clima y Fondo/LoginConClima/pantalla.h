#ifndef PANTALLA_H
#define PANTALLA_H

#include <QWidget>

class Pantalla : public QWidget
{
    Q_OBJECT
public:
    explicit Pantalla(QWidget *parent = nullptr);
    ~Pantalla() override;

    // Interfaz comun obligatoria para todas las pantallas de la app.
    virtual void inicializarPantalla() = 0;
};

#endif // PANTALLA_H
