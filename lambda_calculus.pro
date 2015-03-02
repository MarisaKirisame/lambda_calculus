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
    CompileTime/BCKW_system.hpp \
    CompileTime/church_numeral.hpp \
    CompileTime/example.hpp \
    CompileTime/int.hpp \
    CompileTime/Iota.hpp \
    CompileTime/CompileTime_lambda_calculus.hpp \
    CompileTime/list.hpp \
    CompileTime/pair.hpp \
    CompileTime/parser.hpp \
    CompileTime/propositional_logic.hpp \
    CompileTime/SKI_combinator_calculus.hpp \
    CompileTime/Y_combinator.hpp \
    RunTime/CompileTime_lambda_calculus.hpp
