TEMPLATE = subdirs
CONFIG += c++11
SUBDIRS += \
    ../Graph \
    ../Main \
    ../triangle
Main.depends += Graph
Main.depends += triangle
