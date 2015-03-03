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
    RunTime/lambda_calculus.hpp \
    Compiletime/BCKW_system.hpp \
    Compiletime/church_numeral.hpp \
    Compiletime/example.hpp \
    Compiletime/int.hpp \
    Compiletime/Iota.hpp \
    Compiletime/lambda_calculus.hpp \
    Compiletime/list.hpp \
    Compiletime/pair.hpp \
    Compiletime/parser.hpp \
    Compiletime/propositional_logic.hpp \
    Compiletime/SKI_combinator_calculus.hpp \
    Compiletime/Y_combinator.hpp \
    Runtime/lambda_calculus.hpp \
    Runtime/Compiletime_Runtime.hpp
