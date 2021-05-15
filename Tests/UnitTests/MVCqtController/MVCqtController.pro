QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_mvcqtcontroller_unittest.cpp

unix {
    LIBS += -L/usr/lib/MVCqt/MVCqtController -lMVCqtController
    PRE_TARGETDEPS += /usr/lib/MVCqt/MVCqtController/libMVCqtController.a
    INCLUDEPATH += /usr/include/MVCqt/MVCqtActor \
                   /usr/include/MVCqt/MVCqtModel \
                   /usr/include/MVCqt/MVCqtView  \
                   /usr/include/MVCqt/MVCqtController
}
