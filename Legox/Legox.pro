#-------------------------------------------------
#
# Project created by QtCreator 2017-10-28T17:43:15
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Legox
TEMPLATE = app

win32 {
    LIBS += -lopengl32
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    core/files/File.cpp \
    core/files/STL.cpp \
    core/model/Bloxs.cpp \
    core/session/History.cpp \
    core/Legox.cpp \
    main.cpp \
    mainwindow.cpp \
    myglwidget.cpp \
    core/files/OBJ.cpp \
    core/opengl/CubeEngine.cpp

HEADERS += \
    core/files/File.h \
    core/model/Bloxs.h \
    core/session/History.h \
    core/utils/utils.h \
    core/Legox.h \
    mainwindow.h \
    myglwidget.h \
    core/files/tiny_obj_loader.h \
    core/files/voxelizer.h \
    core/opengl/CubeEngine.h

RESOURCES += \
    shaders.qrc

OTHER_FILES += \
    vshader.glsl \
    fshader.glsl

FORMS += \
    mainwindow.ui
