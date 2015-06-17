TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
QMAKE_CXXFLAGS -= -O
QMAKE_CXXFLAGS -= -O1
QMAKE_CXXFLAGS -= -O2
QMAKE_CXXFLAGS *= -O3
QMAKE_CXXFLAGS += -Wall

INCLUDEPATH += ../

LIBS += ../Graph/libGraph.a ../triangle/libtriangle.a
LIBS += /usr/local/lib/libpngwriter.a
LIBS += -lpng
PRE_TARGETDEPS += ../Graph/libGraph.a ../triangle/libtriangle.a

SOURCES += main.cpp \
    ConstrainedDelaunayTriangulation.cpp \
    MinimumWeightTriangulation.cpp \
    GreedyTriangulation.cpp \
    SubpolygonHeuristicTriangulation.cpp
TARGET = triangulate

CONFIG(debug, debug|release) {
    DESTDIR = ../build
} else {
    DESTDIR = ../build
}

HEADERS += \
    Triangulations.h
