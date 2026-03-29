QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    almacenamiento_app.cpp \
    dialogo_notas.cpp \
    dialogo_registro.cpp \
    dialogo_trabajo.cpp \
    gestor_historial.cpp \
    gestor_sesion.cpp \
    gestor_trabajos.cpp \
    gestor_usuarios.cpp \
    inicio_sesion.cpp \
    principal.cpp \
    widget_principal.cpp

HEADERS += \
    almacenamiento_app.h \
    dialogo_notas.h \
    dialogo_registro.h \
    dialogo_trabajo.h \
    gestor_historial.h \
    gestor_sesion.h \
    gestor_trabajos.h \
    gestor_usuarios.h \
    inicio_sesion.h \
    widget_principal.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
