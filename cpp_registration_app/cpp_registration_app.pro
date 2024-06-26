QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

include(./utility/utility.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    finishwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    registrationwindow.cpp

HEADERS += \
    finishwindow.h \
    loginwindow.h \
    mainwindow.h \
    registrationwindow.h

FORMS += \
    finishwindow.ui \
    loginwindow.ui \
    mainwindow.ui \
    registrationwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

