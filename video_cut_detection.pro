######################################################################
# Automatically generated by qmake (2.01a) Tue Apr 22 07:20:13 2014
######################################################################

TEMPLATE = app
TARGET = 

CONFIG += console link_pkgconfig
PKGCONFIG += opencv
QT += opengl

# Input
HEADERS += glWindow.h \
           Worker.h \
           QCustomGraph/qcustomplot.h \
           QCustomGraph/qcustomplotwidget.h

SOURCES += glWindow.cpp \
           main.cpp \
           Worker.cpp \
           QCustomGraph/qcustomplot.cpp \
           QCustomGraph/qcustomplotwidget.cpp
