#-------------------------------------------------
#
# Project created by QtCreator 2019-10-14T10:38:09
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    condividi.cpp \
    editor.cpp \
    importa.cpp \
        main.cpp \
        loginpage.cpp \
        nuovo.cpp \
        principale.cpp \
    registrationpage.cpp \
    splashscreen.cpp \
    account.cpp

HEADERS += \
    condividi.h \
    editor.h \
    importa.h \
        loginpage.h \
        nuovo.h \
        principale.h \
    registrationpage.h \
    splashscreen.h \
    account.h

FORMS += \
    condividi.ui \
    editor.ui \
    importa.ui \
        loginpage.ui \
        nuovo.ui \
        principale.ui \
    registrationpage.ui \
    splashscreen.ui \
    account.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
