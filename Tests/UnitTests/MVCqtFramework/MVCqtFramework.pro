QT += testlib gui webengine webenginewidgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_mvcqtframework_unittest.cpp \
            backend/src/modelImp.cpp

unix {
    LIBS += -L/usr/lib/MVCqt -lMVCqt
    PRE_TARGETDEPS += /usr/lib/MVCqt/libMVCqt.a
    INCLUDEPATH += /usr/include/MVCqt/MVCqtActor \
                   /usr/include/MVCqt/MVCqtModel \
                   /usr/include/MVCqt/MVCqtView  \
                   /usr/include/MVCqt/MVCqtController \
                   /usr/include/MVCqt
}

RESOURCES += \
    conf_file.qrc \
    frontend.qrc

HEADERS += \
    backend/include/modelImp.h

