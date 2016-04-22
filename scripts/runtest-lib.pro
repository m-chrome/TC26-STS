TEMPLATE = lib
    HEADERS += ../include/tc26/cephes.hpp \
        ../include/statistical_tests/run.hpp
    SOURCES = ../src/run.cpp \
        ../src/cephes.cpp
    TARGET = runtest
    DESTDIR = ../libs/statistical_tests
    INCLUDEPATH += ../
    QMAKE_CXXFLAGS += -std=c++14
