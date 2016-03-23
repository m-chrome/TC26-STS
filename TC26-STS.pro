QT += core
QT -= gui

TARGET = TC26
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    src/core.cpp \
    tests/test-decision.cpp

HEADERS += \
    include/tc26/console.hpp \
    include/tc26/core.hpp \
    include/tc26/logger.hpp \
    include/tc26/types.hpp \
    modules/decisions/decision_module.hpp \
    include/decisions/decisions.hpp \
    include/statistical tests/tests.hpp \
    include/ui/console.hpp \
    include/statistical tests/tests.hpp

