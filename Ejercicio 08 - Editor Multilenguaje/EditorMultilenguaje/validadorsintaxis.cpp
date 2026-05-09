#include "validadorsintaxis.h"

static int contar(const QString &linea, QChar c)
{
    return linea.count(c);
}

bool ValidadorCpp::validarLinea(const QString &linea, QString &diagnostico) const
{
    const QString l = linea.trimmed();
    if (l.isEmpty() || l.startsWith("//")) {
        diagnostico = "Linea valida.";
        return true;
    }
    if (contar(l, '(') != contar(l, ')')) {
        diagnostico = "Parentesis desbalanceados en C++.";
        return false;
    }
    if (l.contains("cout") && !l.contains("<<")) {
        diagnostico = "Sugerencia: para cout usa el operador <<.";
        return false;
    }
    diagnostico = "Linea valida.";
    return true;
}

bool ValidadorPython::validarLinea(const QString &linea, QString &diagnostico) const
{
    if (linea.trimmed().isEmpty() || linea.trimmed().startsWith("#")) {
        diagnostico = "Linea valida.";
        return true;
    }
    if (linea.contains("{") || linea.contains("}")) {
        diagnostico = "Python no usa llaves para bloques.";
        return false;
    }
    if (linea.trimmed().startsWith("print ") && !linea.contains('(')) {
        diagnostico = "Usa print(...) en Python moderno.";
        return false;
    }
    diagnostico = "Linea valida.";
    return true;
}

bool ValidadorJava::validarLinea(const QString &linea, QString &diagnostico) const
{
    const QString l = linea.trimmed();
    if (l.isEmpty() || l.startsWith("//")) {
        diagnostico = "Linea valida.";
        return true;
    }
    if (contar(l, '(') != contar(l, ')')) {
        diagnostico = "Parentesis desbalanceados en Java.";
        return false;
    }
    if (l.contains("System.out.println") && !l.endsWith(";")) {
        diagnostico = "En Java suele faltar ';' al final de la instruccion.";
        return false;
    }
    diagnostico = "Linea valida.";
    return true;
}
