#ifndef VALIDADORSINTAXIS_H
#define VALIDADORSINTAXIS_H

#include <QString>

class ValidadorSintaxis
{
public:
    virtual ~ValidadorSintaxis() = default;
    virtual bool validarLinea(const QString &linea, QString &diagnostico) const = 0;
};

class ValidadorCpp : public ValidadorSintaxis
{
public:
    bool validarLinea(const QString &linea, QString &diagnostico) const override;
};

class ValidadorPython : public ValidadorSintaxis
{
public:
    bool validarLinea(const QString &linea, QString &diagnostico) const override;
};

class ValidadorJava : public ValidadorSintaxis
{
public:
    bool validarLinea(const QString &linea, QString &diagnostico) const override;
};

#endif // VALIDADORSINTAXIS_H
