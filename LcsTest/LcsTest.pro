QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
            ../lcs.cpp \
    tst_lcs_test.cpp

HEADERS += ../lcs.h
