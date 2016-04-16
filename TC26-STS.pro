QT += core
QT -= gui

TARGET = TC26
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    src/core.cpp \
    tests/test-decision.cpp \
    src/weak_test.cpp \
    src/chi-squared_test.cpp \
    src/monobit.cpp \
    src/run.cpp

HEADERS += \
    include/statistical_tests/tests.hpp \
    include/statistical_tests/run.hpp \
    include/statistical_tests/monobit.hpp \
    include/decisions/weak_test.hpp \
    include/decisions/chi-squared_test.hpp \
    include/tc26/core.hpp \
    include/tc26/logger.hpp \
    include/tc26/types.hpp \
    include/ui/console.hpp

QMAKE_CXXFLAGS += -std=c++14
