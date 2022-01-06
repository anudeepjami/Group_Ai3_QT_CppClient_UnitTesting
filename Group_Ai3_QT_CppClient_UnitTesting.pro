QT += testlib gui core network widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_qtclientapp.cpp \
    nodeapicall.cpp

HEADERS += \
    nodeapicall.h

