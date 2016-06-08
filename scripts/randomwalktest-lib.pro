TEMPLATE = lib
    HEADERS += ../include/tc26/cephes.hpp \
        ../include/statistical_tests/randomwalk.hpp
    SOURCES += ../src/randomwalk.cpp \
        ../src/cephes.cpp
    TARGET = randomwalktest
    DESTDIR = ../libs/statistical_tests
    INCLUDEPATH += ../
    QMAKE_CXXFLAGS += -std=c++14
