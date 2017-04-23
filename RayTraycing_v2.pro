#-------------------------------------------------
#
# Project created by QtCreator 2017-03-31T17:07:26
#
#-------------------------------------------------

QT       += core gui
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RayTraycing_v2
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TScene.cpp \
    TTriangle.cpp \
    TQuadrangle.cpp \
    TSphere.cpp

HEADERS  += MainWindow.h \
    TScene.h \
    TPoint.h \
    TMaterial.h \
    TLight.h \
    TFigure.h \
    TTriangle.h \
    FGeometry.h \
    TQuadrangle.h \
    TSphere.h \
    TColor.h

FORMS    += MainWindow.ui

DISTFILES += \
    scene_one.txt \
    ../build-RayTraycing_v2-Desktop_Qt_5_8_0_GCC_64bit-Debug/output.txt \
    ../build-RayTraycing_v2-Desktop_Qt_5_8_0_GCC_64bit-Debug/test_scene.txt \
    ../build-RayTraycing_v2-Desktop_Qt_5_8_0_GCC_64bit-Debug/test_scene_two.rt \
    ../build-RayTraycing_v2-Desktop_Qt_5_8_0_GCC_64bit-Debug/test_scene_three.rt \
    ../build-RayTraycing_v2-Desktop_Qt_5_8_0_GCC_64bit-Debug/test_scene_four.rt
