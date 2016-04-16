QT += core
QT -= gui

TARGET = TC26
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    src/core.cpp \
    tests/test-decision.cpp \
    src/weak_test.cpp \
    src/chi-squared_test.cpp \
    src/monobit.cpp \
    src/run.cpp \
    src/console.cpp \
    main_console.cpp \
    src/cephes.c


HEADERS += \
    include/statistical_tests/tests.hpp \
    include/statistical_tests/run.hpp \
    include/statistical_tests/monobit.hpp \
    include/decisions/weak_test.hpp \
    include/decisions/chi-squared_test.hpp \
    include/tc26/core.hpp \
    include/tc26/logger.hpp \
    include/tc26/types.hpp \
    include/ui/console.hpp \
    include/tc26/utility.hpp \
    include/tc26/cephes.h \
    libs/decisions/decision_module.hpp \
    libs/statistical tests/tests.hpp


QMAKE_CXXFLAGS += -std=c++14

DISTFILES += \
    compiletests.sh \
    monobittest.pro \
    runtest.pro \
    libs/statistical_tests/libmonobittest.so \
    libs/statistical_tests/libmonobittest.so.1 \
    libs/statistical_tests/libmonobittest.so.1.0 \
    libs/statistical_tests/libmonobittest.so.1.0.0 \
    libs/statistical_tests/libruntest.so \
    libs/statistical_tests/libruntest.so.1 \
    libs/statistical_tests/libruntest.so.1.0 \
    libs/statistical_tests/libruntest.so.1.0.0
