QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    brush.cpp \
    brushtool.cpp \
    canvaslabel.cpp \
    imagetool.cpp \
    intsignalbutton.cpp \
    main.cpp \
    model.cpp \
    mousebutton.cpp \
    shape.cpp \
    spriteeditor.cpp

HEADERS += \
    brush.h \
    brushtool.h \
    canvaslabel.h \
    imagetool.h \
    intsignalbutton.h \
    model.h \
    mousebutton.h \
    shape.h \
    spriteeditor.h

FORMS += \
    spriteeditor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    uml.qmodel

RESOURCES += \
    Resources.qrc
