#include "inicio_sesion.h"
#include "widget_principal.h"
#include "gestor_sesion.h"

#include <QApplication>

namespace {
void aplicarEstiloApp(QApplication &app)
{
    const QString estilo = QStringLiteral(R"(
        QWidget {
            background-color: #f3f7f2;
            color: #1f2d1f;
            font-family: "Segoe UI";
            font-size: 12pt;
        }
        QLineEdit, QDateEdit, QComboBox, QTextEdit, QListWidget {
            background-color: #ffffff;
            border: 1px solid #c6d6c3;
            border-radius: 6px;
            padding: 6px;
            selection-background-color: #a8d5ba;
        }
        QLabel {
            color: #1f2d1f;
        }
        QPushButton {
            background-color: #3f7f5b;
            color: #ffffff;
            border: none;
            border-radius: 6px;
            padding: 6px 12px;
        }
        QPushButton:hover {
            background-color: #356b4c;
        }
        QPushButton:pressed {
            background-color: #2e5a41;
        }
        QGroupBox {
            border: 1px solid #c6d6c3;
            border-radius: 8px;
            margin-top: 10px;
            padding: 8px;
            background-color: #f8fbf7;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top left;
            padding: 0 6px;
        }
        QScrollArea {
            border: none;
        }
        QHeaderView::section {
            background-color: #e2efe6;
            color: #1f2d1f;
            padding: 6px;
            border: none;
        }
        QComboBox::drop-down {
            border: none;
        }
    )");
    app.setStyleSheet(estilo);
}
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    aplicarEstiloApp(a);

    InicioSesion inicioSesion;
    WidgetPrincipal *widgetPrincipal = nullptr;

    QString usuarioSesion;
    if (GestorSesion::cargarSesionValida(&usuarioSesion)) {
        widgetPrincipal = new WidgetPrincipal(usuarioSesion);
        widgetPrincipal->show();
    } else {
        inicioSesion.show();
    }

    QObject::connect(&inicioSesion, &InicioSesion::inicioCorrecto, [&](const QString &usuario) {
        if (!widgetPrincipal) {
            widgetPrincipal = new WidgetPrincipal(usuario);
            QObject::connect(widgetPrincipal, &WidgetPrincipal::cierreSesionSolicitado, [&]() {
                widgetPrincipal->hide();
                widgetPrincipal->deleteLater();
                widgetPrincipal = nullptr;
                inicioSesion.show();
            });
        }
        inicioSesion.hide();
        widgetPrincipal->show();
    });

    if (widgetPrincipal) {
        QObject::connect(widgetPrincipal, &WidgetPrincipal::cierreSesionSolicitado, [&]() {
            widgetPrincipal->hide();
            widgetPrincipal->deleteLater();
            widgetPrincipal = nullptr;
            inicioSesion.show();
        });
    }

    return QCoreApplication::exec();
}
