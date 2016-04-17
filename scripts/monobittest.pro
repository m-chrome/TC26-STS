TEMPLATE = lib
    HEADERS += ../include/tc26/cephes.hpp \
        ../include/statistical_tests/monobit.hpp
    SOURCES += ../src/monobit.cpp \
        ../src/cephes.cpp
    TARGET = monobittest
    DESTDIR = ../libs/statistical_tests
    QMAKE_CXXFLAGS += -std=c++14
