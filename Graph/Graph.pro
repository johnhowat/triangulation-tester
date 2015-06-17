#-------------------------------------------------
#
# Project created by QtCreator 2014-05-09T11:56:25
#
#-------------------------------------------------

QT       -= core gui


TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
DEFINES *= NO_FREETYPE
QMAKE_CXXFLAGS -= -O
QMAKE_CXXFLAGS -= -O1
QMAKE_CXXFLAGS -= -O2
QMAKE_CXXFLAGS *= -O3
TARGET = Graph

SOURCES += Graph.cpp \
    Edge.cpp \
    Face.cpp \
    HalfEdge.cpp \
    Iterators.cpp \
    Vertex.cpp

HEADERS += Graph.h \
    Edge.h \
    Face.h \
    HalfEdge.h \
    Iterators.h \
    Vertex.h
