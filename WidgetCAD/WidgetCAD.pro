QT += widgets

TEMPLATE = lib
DEFINES += WIDGETCAD_LIBRARY

CONFIG += c++20
CONFIG += precompile_header
PRECOMPILED_HEADER = pch.h

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cadfile.cpp \
    canvasview.cpp \
    devicesence.cpp \
    dx_data.cpp \
    dx_iface.cpp \
    graphicsitem.cpp

HEADERS += \
    ShapeDefine.h \
    WidgetCAD_global.h \
    cadfile.h \
    canvasview.h \
    devicesence.h \
    dx_data.h \
    dx_iface.h \
    graphicsitem.h \
    pch.h \
    widgetcad.h



INCLUDEPATH += $$PWD/../third_party/libdxfrw/src\
 $$PWD/../third_party/libdxfrw/src/intern

LIBS += -L$$PWD/../third_party/libdxfrw\
       -llibdxfrw
QT += openglwidgets
LIBS += -lDbgHelp

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
