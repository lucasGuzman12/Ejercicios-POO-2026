/********************************************************************************
** Form generated from reading UI file 'ventana.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENTANA_H
#define UI_VENTANA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ventana
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lblBackground;
    QVBoxLayout *overlayLayout;
    QSpacerItem *verticalSpacerTop;
    QFrame *cardCV;
    QHBoxLayout *horizontalLayout;
    QLabel *lblFoto;
    QVBoxLayout *verticalLayoutCard;
    QLabel *lblNombre;
    QLabel *lblCargo;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QLabel *lblResumen;
    QSpacerItem *verticalSpacerBottom;

    void setupUi(QWidget *Ventana)
    {
        if (Ventana->objectName().isEmpty())
            Ventana->setObjectName("Ventana");
        Ventana->resize(1280, 720);
        Ventana->setStyleSheet(QString::fromUtf8("QWidget#Ventana {\n"
"    background: #0e1b2a;\n"
"}\n"
"QLabel#lblBackground {\n"
"    background: #0e1b2a;\n"
"}\n"
"QFrame#cardCV {\n"
"    background: rgba(255, 255, 255, 235);\n"
"    border-radius: 18px;\n"
"    border: 1px solid #b9c7d8;\n"
"}\n"
"QLabel#lblNombre {\n"
"    font-size: 30px;\n"
"    font-weight: 700;\n"
"    color: #0d2b45;\n"
"}\n"
"QLabel#lblCargo {\n"
"    font-size: 16px;\n"
"    color: #154166;\n"
"    font-weight: 600;\n"
"}\n"
"QLabel#lblResumen {\n"
"    font-size: 14px;\n"
"    color: #223a52;\n"
"}"));
        verticalLayout = new QVBoxLayout(Ventana);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblBackground = new QLabel(Ventana);
        lblBackground->setObjectName("lblBackground");
        lblBackground->setScaledContents(false);
        overlayLayout = new QVBoxLayout(lblBackground);
        overlayLayout->setObjectName("overlayLayout");
        overlayLayout->setContentsMargins(40, 40, 40, 40);
        verticalSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        overlayLayout->addItem(verticalSpacerTop);

        cardCV = new QFrame(lblBackground);
        cardCV->setObjectName("cardCV");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cardCV->sizePolicy().hasHeightForWidth());
        cardCV->setSizePolicy(sizePolicy);
        cardCV->setMinimumSize(QSize(620, 320));
        cardCV->setMaximumSize(QSize(620, 2000));
        horizontalLayout = new QHBoxLayout(cardCV);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(24, 24, 24, 24);
        lblFoto = new QLabel(cardCV);
        lblFoto->setObjectName("lblFoto");
        lblFoto->setMinimumSize(QSize(130, 130));
        lblFoto->setMaximumSize(QSize(130, 130));
        lblFoto->setStyleSheet(QString::fromUtf8("background: #d8e3f0; border-radius: 65px;"));
        lblFoto->setPixmap(QPixmap(QString::fromUtf8(":/img/EGRESADOSICO2023(152).jpg")));
        lblFoto->setScaledContents(true);
        lblFoto->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lblFoto->setWordWrap(false);

        horizontalLayout->addWidget(lblFoto);

        verticalLayoutCard = new QVBoxLayout();
        verticalLayoutCard->setObjectName("verticalLayoutCard");
        lblNombre = new QLabel(cardCV);
        lblNombre->setObjectName("lblNombre");

        verticalLayoutCard->addWidget(lblNombre);

        lblCargo = new QLabel(cardCV);
        lblCargo->setObjectName("lblCargo");

        verticalLayoutCard->addWidget(lblCargo);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutCard->addItem(verticalSpacer);

        label_2 = new QLabel(cardCV);
        label_2->setObjectName("label_2");
        QPalette palette;
        QBrush brush(QColor(34, 58, 82, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush);
        QBrush brush1(QColor(34, 58, 82, 128));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush1);
#endif
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush1);
#endif
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush1);
#endif
        label_2->setPalette(palette);
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_2->setFont(font);

        verticalLayoutCard->addWidget(label_2);

        lblResumen = new QLabel(cardCV);
        lblResumen->setObjectName("lblResumen");
        lblResumen->setWordWrap(true);

        verticalLayoutCard->addWidget(lblResumen);


        horizontalLayout->addLayout(verticalLayoutCard);


        overlayLayout->addWidget(cardCV, 0, Qt::AlignmentFlag::AlignHCenter);

        verticalSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        overlayLayout->addItem(verticalSpacerBottom);


        verticalLayout->addWidget(lblBackground);


        retranslateUi(Ventana);

        QMetaObject::connectSlotsByName(Ventana);
    } // setupUi

    void retranslateUi(QWidget *Ventana)
    {
        Ventana->setWindowTitle(QCoreApplication::translate("Ventana", "Ventana Principal", nullptr));
        lblBackground->setText(QString());
        lblFoto->setText(QString());
        lblNombre->setText(QCoreApplication::translate("Ventana", "Lucas Guzm\303\241n", nullptr));
        lblCargo->setText(QCoreApplication::translate("Ventana", "Desarrollador de Software | Qt C++ | Docker", nullptr));
        label_2->setText(QCoreApplication::translate("Ventana", "Acerca de", nullptr));
        lblResumen->setText(QCoreApplication::translate("Ventana", "<html><head/><body><p>Soy estudiante de Ingenier\303\255a en Inform\303\241tica con experiencia en desarrollo de software, abarcando tanto backend como aplicaciones de escritorio y proyectos interactivos. Trabajo con tecnolog\303\255as como FastAPI, C++ con Qt, Docker y MySQL, desarrollando sistemas completos con arquitectura cliente-servidor y despliegue en VPS. Me enfoco en construir soluciones s\303\263lidas, bien estructuradas y funcionales, aplicando principios de programaci\303\263n orientada a objetos e integraci\303\263n entre m\303\272ltiples componentes.</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Ventana: public Ui_Ventana {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENTANA_H
