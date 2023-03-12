QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += -lpcap -lnet
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arp_info.cpp \
    detailedfuc.cpp \
    flowsnifferwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    synflood.cpp \
    try.cpp


HEADERS += \
    arp_info.h \
    detailedfuc.h \
    flowsnifferwindow.h \
    mainwindow.h \
    synflood.h \
    try.h

FORMS += \
    flowsnifferwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/res.qrc
