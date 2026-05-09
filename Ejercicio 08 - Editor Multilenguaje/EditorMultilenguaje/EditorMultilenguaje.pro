QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appcontroller.cpp \
    bloqueada.cpp \
    configmanager.cpp \
    editorprincipal.cpp \
    lineawaretextedit.cpp \
    logger.cpp \
    login.cpp \
    main.cpp \
    pantalla.cpp \
    validadorsintaxis.cpp

HEADERS += \
    appcontroller.h \
    bloqueada.h \
    configmanager.h \
    editorprincipal.h \
    lineawaretextedit.h \
    logger.h \
    login.h \
    pantalla.h \
    validadorsintaxis.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
