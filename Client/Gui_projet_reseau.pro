#-------------------------------------------------
#
# Project created by QtCreator 2019-04-11T15:45:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gui_projet_reseau
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

CONFIG += c++17
CONFIG += app_bundle



SOURCES += \
    main.cpp client_engine.cpp mainwindow.cpp eventshandler.cpp \
    connectpage.cpp \
    privatemessagetab.cpp \
    chat.cpp



HEADERS += \
    eventshandler.hpp client.hpp mainwindow.h \
    connectpage.h \
    privatemessagetab.h \
    chat.h



FORMS += \
        mainwindow.ui \
    connectpage.ui \
    privatemessagetab.ui \
    chat.ui

ICON = message_icon.png


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unixq:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
