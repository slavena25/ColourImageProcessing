QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += charts

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    colorconversion.cpp \
    colourmodel_cmy.cpp \
    colourmodel_cmyk.cpp \
    colourmodel_hsi.cpp \
    colourmodel_rgb.cpp \
    main.cpp \
    mainwindow.cpp \
    rgbhistogramwidget.cpp

HEADERS += \
    colorconversion.h \
    colourmodel_cmy.h \
    colourmodel_cmyk.h \
    colourmodel_hsi.h \
    colourmodel_rgb.h \
    mainwindow.h \
    rgbhistogramwidget.h

FORMS += \
    mainwindow.ui

RC_ICONS += ../iconImage/paint_palette_brush_icon_231489.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
