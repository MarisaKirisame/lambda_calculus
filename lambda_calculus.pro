TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++1z
SOURCES += main.cpp

OTHER_FILES += \
    LICENSE \
    README.md

HEADERS += \
    BCKW_system.hpp \
    church_numeral.hpp \
    example.hpp \
    int.hpp \
    Iota.hpp \
    lambda_calculus.hpp \
    list.hpp \
    pair.hpp \
    parser.hpp \
    propositional_logic.hpp \
    SKI_combinator_calculus.hpp \
    Y_combinator.hpp
