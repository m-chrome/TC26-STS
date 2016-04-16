TEMPLATE = lib
    HEADERS = include/statistical_tests/run.hpp
    SOURCES = src/run.cpp
    TARGET = runtest
    DESTDIR = libs/statistical_tests
    QMAKE_CXXFLAGS += -std=c++14
