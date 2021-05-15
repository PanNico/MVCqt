QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_mvcqtactor_unittest.cpp

unix {
    LIBS += -L/usr/lib/MVCqt/MVCqtActor -lMVCqtActor
    PRE_TARGETDEPS += /usr/lib/MVCqt/MVCqtActor/libMVCqtActor.a
    INCLUDEPATH += /usr/include/MVCqt/MVCqtActor
}
