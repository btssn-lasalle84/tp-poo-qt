QT -= gui
QT += widgets testlib

CONFIG += c++11 console
#CONFIG += cmdline
CONFIG -= app_bundle

# pour make check
#CONFIG += testcase

TARGET = test-convertisseur.out

INCLUDEPATH += ../src

SOURCES += testconvertisseur.cpp\
        ../src/ihmconvertisseur.cpp

HEADERS  += ../src/ihmconvertisseur.h
