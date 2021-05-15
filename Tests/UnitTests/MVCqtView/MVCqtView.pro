QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_mvcqtview_unittest.cpp

unix {
    LIBS += -L/usr/lib/MVCqt/MVCqtView -lMVCqtView
    PRE_TARGETDEPS += /usr/lib/MVCqt/MVCqtView/libMVCqtView.a
    INCLUDEPATH += /usr/include/MVCqt/MVCqtActor /usr/include/MVCqt/MVCqtView
}
