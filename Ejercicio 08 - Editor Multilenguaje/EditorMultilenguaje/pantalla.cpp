#include "pantalla.h"

Pantalla::Pantalla(AppController *controller, QWidget *parent)
    : QWidget(parent), m_controller(controller)
{
}

Pantalla::~Pantalla() = default;
