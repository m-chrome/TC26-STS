QT += core
QT -= gui

TARGET = TC26
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main_console.cpp \
    src/core.cpp \
    src/monobit.cpp \
    src/run.cpp \
    src/console.cpp \
    src/cephes.cpp \
    src/maurer.cpp \
    src/chisquared.cpp \
    src/weak.cpp \
    src/utility.cpp \
    src/gap.cpp \
    src/randomwalk.cpp


HEADERS += \
    include/statistical_tests/run.hpp \
    include/statistical_tests/monobit.hpp \
    include/statistical_tests/maurer.hpp \
    include/decisions/weak.hpp \
    include/decisions/chisquared.hpp \
    include/tc26/core.hpp \
    include/tc26/logger.hpp \
    include/tc26/types.hpp \
    include/tc26/utility.hpp \
    include/tc26/cephes.hpp \
    include/ui/console.hpp \
    include/statistical_tests/gap.hpp \
    include/statistical_tests/randomwalk.hpp

QMAKE_CXXFLAGS += -std=c++14
