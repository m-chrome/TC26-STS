TEMPLATE = lib
HEADERS += ../include/tc26/cephes.hpp \
           ../include/statistical_tests/gap.hpp
SOURCES += ../src/gap.cpp \
           ../src/cephes.cpp
TARGET = gaptest
DESTDIR = ../libs/statistical_tests
INCLUDEPATH += ../
QMAKE_CXXFLAGS += -std=c++14
