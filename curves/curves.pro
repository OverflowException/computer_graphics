TEMPLATE = app
TARGET = curves

DESTDIR += ./bin
OBJECTS_DIR += ./build
MOC_DIR += ./moc
INCLUDEPATH += ./inc
SOURCEPATH += ./src

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += ./inc/mainwindow.h
SOURCES += ./src/main.cpp

QT += widgets gui
