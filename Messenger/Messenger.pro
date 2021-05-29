QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authandregistration.cpp \
    businesslogic.cpp \
    clientStuff.cpp \
    main.cpp \
    mainwindow.cpp \
    request.cpp \
    serializetojson.cpp

HEADERS += \
    authandregistration.h \
    businesslogic.h \
    clientStuff.h \
    mainwindow.h \
    request.h \
    serializetojson.h

FORMS += \
    authandregistration.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  images.qrc
