#ifndef EDITORPRINCIPAL_H
#define EDITORPRINCIPAL_H

#include "pantalla.h"

#include <QMap>

class QComboBox;
class QLabel;
class QSplitter;
class ValidadorSintaxis;
class LineAwareTextEdit;

class EditorPrincipal : public Pantalla
{
    Q_OBJECT
public:
    explicit EditorPrincipal(AppController *controller, QWidget *parent = nullptr);
    ~EditorPrincipal() override;

    void inicializarUI() override;
    void conectarEventos() override;
    void cargarDatos() override;
    bool validarEstado() override;
    void registrarEvento(const QString &descripcion) override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private slots:
    void cambiarLenguaje(const QString &lenguaje);
    void validarLinea(int linea);
    void validarLineaFoco(int linea);
    void exportarJPG();
    void limpiarEditor();

private:
    void actualizarResaltado();
    QString textoLinea(int linea) const;
    void actualizarBarraErrores(const QString &mensaje, bool esError);
    void ejecutarChequeoCompiladorCpp();
    QString extraerMensajeCompilador(const QString &salida, const QString &archivoTemporal) const;
    int extraerLineaErrorCompilador(const QString &salida, const QString &archivoTemporal) const;
    QString resumenErrorBasico(const QString &diagnostico) const;

    QComboBox *m_selectorLenguaje = nullptr;
    LineAwareTextEdit *m_editor = nullptr;
    QLabel *m_diagnostico = nullptr;
    QLabel *m_barraErrores = nullptr;
    QSplitter *m_splitter = nullptr;
    ValidadorSintaxis *m_validadorActual = nullptr;
    QMap<int, QString> m_erroresPorLinea;
    int m_lineaErrorCompilador = -1;
};

#endif // EDITORPRINCIPAL_H
