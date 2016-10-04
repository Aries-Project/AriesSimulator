#-------------------------------------------------
#
# Project created by QtCreator 2016-04-17T15:30:27
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AriesSimulator
TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle

MOC_DIR=moc

SOURCES += src/main.cpp \
    aries_wrap.cpp \
    src/MainWindow.cpp \
    src/World.cpp \
    src/PhysicsWorld.cpp \
    src/CollisionShape.cpp \
    src/NGLScene.cpp \
    src/WorldObject.cpp \
    src/PhysicsMaterial.cpp \
    src/ShaderMaterial.cpp

HEADERS  += include/MainWindow.h \
    include/World.h \
    include/PhysicsWorld.h \
    include/CollisionShape.h \
    include/NGLScene.h \
    include/WorldObject.h \
    include/PhysicsMaterial.h \
    include/ShaderMaterial.h

FORMS    += MainWindow.ui

INCLUDEPATH += ./include

include("UseBullet.pri")
include("UsePython2_7.pri")

NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
        message("including $HOME/NGL")
        include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
        message("Using custom NGL location")
        include($(NGLDIR)/UseNGL.pri)
}

DISTFILES += \
    aries.i \
    init.py \
    notes.txt

SWIG_FILES = aries.i

swig.output  = ${QMAKE_FILE_BASE}_wrap.cpp
swig.commands = swig -python -c++ -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
swig.depends = include/World.h include/WorldObject.h
swig.input = SWIG_FILES
swig.CONFIG = no_link

QMAKE_EXTRA_COMPILERS += swig
