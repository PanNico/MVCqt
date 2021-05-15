QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_mvcqtmodel_unittest.cpp

unix {
    LIBS += -L/usr/lib/MVCqt/MVCqtModel -lMVCqtModel
    PRE_TARGETDEPS += /usr/lib/MVCqt/MVCqtModel/libMVCqtModel.a
    INCLUDEPATH += /usr/include/MVCqt/MVCqtActor /usr/include/MVCqt/MVCqtModel
}
