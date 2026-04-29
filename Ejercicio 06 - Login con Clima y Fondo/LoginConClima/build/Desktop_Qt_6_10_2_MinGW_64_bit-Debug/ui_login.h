/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *card;
    QVBoxLayout *verticalLayout;
    QLabel *lblTitulo;
    QLabel *lblSubtitulo;
    QLabel *labelUsuario;
    QLineEdit *editUsuario;
    QLabel *labelPassword;
    QLineEdit *editPassword;
    QPushButton *btnIngresar;
    QLabel *lblEstado;
    QLabel *lblClima;
    QLabel *lblHora;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(860, 560);
        Login->setStyleSheet(QString::fromUtf8("QWidget#Login {\n"
"    background-color: #f3f5f9;\n"
"}\n"
"QFrame#card {\n"
"    background: white;\n"
"    border: 1px solid #dce1ea;\n"
"    border-radius: 14px;\n"
"}\n"
"QLabel#lblTitulo {\n"
"    font-size: 26px;\n"
"    font-weight: 700;\n"
"    color: #12324a;\n"
"}\n"
"QLabel#lblSubtitulo {\n"
"    font-size: 13px;\n"
"    color: #1f3449;\n"
"}\n"
"QLabel {\n"
"    color: #13283b;\n"
"}\n"
"QLineEdit {\n"
"    border: 1px solid #c5cfdb;\n"
"    border-radius: 8px;\n"
"    padding: 8px;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton {\n"
"    background: #0a66c2;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 9px;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"}\n"
"QPushButton:disabled {\n"
"    background: #9aa8b9;\n"
"}\n"
"QLabel#lblEstado {\n"
"    color: #6f1414;\n"
"    font-size: 12px;\n"
"}\n"
"QLabel#lblClima, QLabel#lblHora {\n"
"    color: #10293f;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"}"));
        horizontalLayout = new QHBoxLayout(Login);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(30, 30, 30, 30);
        card = new QFrame(Login);
        card->setObjectName("card");
        verticalLayout = new QVBoxLayout(card);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(24, 24, 24, 24);
        lblTitulo = new QLabel(card);
        lblTitulo->setObjectName("lblTitulo");

        verticalLayout->addWidget(lblTitulo);

        lblSubtitulo = new QLabel(card);
        lblSubtitulo->setObjectName("lblSubtitulo");

        verticalLayout->addWidget(lblSubtitulo);

        labelUsuario = new QLabel(card);
        labelUsuario->setObjectName("labelUsuario");

        verticalLayout->addWidget(labelUsuario);

        editUsuario = new QLineEdit(card);
        editUsuario->setObjectName("editUsuario");

        verticalLayout->addWidget(editUsuario);

        labelPassword = new QLabel(card);
        labelPassword->setObjectName("labelPassword");

        verticalLayout->addWidget(labelPassword);

        editPassword = new QLineEdit(card);
        editPassword->setObjectName("editPassword");
        editPassword->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(editPassword);

        btnIngresar = new QPushButton(card);
        btnIngresar->setObjectName("btnIngresar");

        verticalLayout->addWidget(btnIngresar);

        lblEstado = new QLabel(card);
        lblEstado->setObjectName("lblEstado");

        verticalLayout->addWidget(lblEstado);

        lblClima = new QLabel(card);
        lblClima->setObjectName("lblClima");

        verticalLayout->addWidget(lblClima);

        lblHora = new QLabel(card);
        lblHora->setObjectName("lblHora");

        verticalLayout->addWidget(lblHora);


        horizontalLayout->addWidget(card);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Login con Clima", nullptr));
        lblTitulo->setText(QCoreApplication::translate("Login", "Ingreso al sistema", nullptr));
        lblSubtitulo->setText(QCoreApplication::translate("Login", "Usuario por defecto: admin / 1234", nullptr));
        labelUsuario->setText(QCoreApplication::translate("Login", "Usuario", nullptr));
        labelPassword->setText(QCoreApplication::translate("Login", "Contrasena", nullptr));
        btnIngresar->setText(QCoreApplication::translate("Login", "Ingresar", nullptr));
        lblEstado->setText(QString());
        lblClima->setText(QCoreApplication::translate("Login", "Temperatura: -", nullptr));
        lblHora->setText(QCoreApplication::translate("Login", "Hora local: -", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
