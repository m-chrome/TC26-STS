TEMPLATE = lib
    HEADERS = include/statistical_tests/monobit.hpp
    SOURCES = src/monobit.cpp
    TARGET = monobittest
    DESTDIR = libs/statistical_tests
    QMAKE_CXXFLAGS += -std=c++14
