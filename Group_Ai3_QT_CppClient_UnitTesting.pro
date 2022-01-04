QT += testlib \
    quick \
    widgets
QT += gui core network
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_qtclientapp.cpp \
    nodeapicall.cpp

HEADERS += \
    nodeapicall.h

