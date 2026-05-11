# Modulo de widgets para la interfaz grafica y sql para usar SQLite.
QT += widgets sql

# Se usa C++17 como estandar de compilacion del proyecto.
CONFIG += c++17

# Archivos fuente con la implementacion de cada clase.
SOURCES += \
    databasemanager.cpp \
    drawingwidget.cpp \
    loginwidget.cpp \
    main.cpp \
    pintura.cpp

# Archivos de cabecera con declaraciones de clases, senales y slots.
HEADERS += \
    databasemanager.h \
    drawingwidget.h \
    loginwidget.h \
    pintura.h

# Formularios creados con Qt Designer.
FORMS += \
    loginwidget.ui

# Configuracion de instalacion generada por Qt Creator para distintas plataformas.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
