#include "loginwidget.h"
#include "ui_loginwidget.h"

#include "databasemanager.h"
#include "drawingwidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    // Carga los widgets, layouts y propiedades definidos en Qt Designer.
    ui->setupUi(this);

    // Se fija el tamano para mantener estable el diseno del formulario.
    setFixedSize(520, 420);

    // Estilos visuales del login: fondo, tarjeta, etiquetas, campos y boton.
    setStyleSheet(
        "QWidget#LoginWidget {"
        "  background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 #f8fafc, stop:1 #e2e8f0);"
        "  color: #0f172a;"
        "  font-family: 'Segoe UI';"
        "}"
        "QFrame#cardFrame {"
        "  background: #ffffff;"
        "  border: 1px solid #dbe3ee;"
        "  border-radius: 16px;"
        "}"
        "QLabel#lblTitle {"
        "  background: transparent;"
        "  font-size: 24px;"
        "  font-weight: 700;"
        "  color: #0f172a;"
        "}"
        "QLabel#lblSubtitle {"
        "  background: transparent;"
        "  font-size: 13px;"
        "  color: #475569;"
        "}"
        "QLabel#label, QLabel#label_2 {"
        "  background: transparent;"
        "  font-size: 12px;"
        "  color: #334155;"
        "  font-weight: 600;"
        "}"
        "QLineEdit {"
        "  background: #f8fafc;"
        "  color: #0f172a;"
        "  border: 1px solid #cbd5e1;"
        "  border-radius: 10px;"
        "  padding: 8px 10px;"
        "  font-size: 13px;"
        "}"
        "QLineEdit:focus {"
        "  border: 1px solid #0284c7;"
        "  background: #ffffff;"
        "}"
        "QLineEdit::placeholder {"
        "  color: #94a3b8;"
        "}"
        "QLineEdit {"
        "  selection-background-color: #0ea5e9;"
        "  selection-color: #ffffff;"
        "}"
        "QPushButton#btnLogin {"
        "  background: #0f172a;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 10px;"
        "  padding: 10px;"
        "  font-weight: 600;"
        "}"
        "QPushButton#btnLogin:hover {"
        "  background: #1e293b;"
        "}"
        "QPushButton#btnLogin:pressed {"
        "  background: #020617;"
        "}"
        "QLabel#lblStatus {"
        "  background: transparent;"
        "  color: #b91c1c;"
        "  min-height: 18px;"
        "}"
    );

    // Textos de ayuda dentro de los campos de entrada.
    ui->editUser->setPlaceholderText("Usuario");
    ui->editPass->setPlaceholderText("********");

    // Conexiones clasicas solicitadas: clic o Enter en contrasena intentan ingresar.
    connect(ui->btnLogin, SIGNAL(clicked()), this, SLOT(tryLogin()));
    connect(ui->editPass, SIGNAL(returnPressed()), this, SLOT(tryLogin()));
}

LoginWidget::~LoginWidget()
{
    // Qt Designer crea los controles dentro de ui; aca se liberan.
    delete ui;
}

void LoginWidget::tryLogin()
{
    // Se toman los datos ingresados. El usuario se recorta para evitar espacios.
    const QString username = ui->editUser->text().trimmed();
    const QString password = ui->editPass->text();

    // Si faltan datos, se informa y se registra como intento fallido.
    if (username.isEmpty() || password.isEmpty()) {
        ui->lblStatus->setText("Completa usuario y contrasena.");
        DatabaseManager::logAccess(username, false, "Campos vacios");
        return;
    }

    // Si las credenciales son validas, se registra el acceso y se emite la senal.
    if (DatabaseManager::validateUser(username, password)) {
        DatabaseManager::logAccess(username, true, "Acceso exitoso");
        emit loginSuccess(username);
        return;
    }

    // Si falla la validacion, no se guarda la contrasena y se limpia el campo.
    DatabaseManager::logAccess(username, false, "Credenciales invalidas");
    ui->lblStatus->setText("Usuario o contrasena incorrecta.");
    ui->editPass->clear();
}

void LoginWidget::openDrawing(const QString &username)
{
    // Se crea la ventana de dibujo para el usuario que acaba de iniciar sesion.
    auto *drawing = new DrawingWidget(username);

    // Al cerrar la ventana, Qt libera automaticamente el objeto.
    drawing->setAttribute(Qt::WA_DeleteOnClose);
    drawing->show();

    // Se cierra el formulario de login porque ya no se necesita.
    close();
}
