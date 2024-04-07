QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
CONFIG += precompile_header
PRECOMPILED_HEADER = pch.h
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dx_iface.cpp \
    formdxffile.cpp \
    formdxffilectrlpannel.cpp \
    formdxflayout.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    formdxffile.h \
    formdxffilectrlpannel.h \
    formdxflayout.h \
    mainwindow.h \
    pch.h

FORMS += \
    formdxffile.ui \
    formdxffilectrlpannel.ui \
    formdxflayout.ui \
    mainwindow.ui







INCLUDEPATH += $$PWD/../third_party/libdxfrw/src\
 $$PWD/../third_party/libdxfrw/src/intern

LIBS += -L$$PWD/../third_party/libdxfrw\
       -llibdxfrw

LIBS += -L$$PWD/../third_party\
       -lWidgetCAD


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
