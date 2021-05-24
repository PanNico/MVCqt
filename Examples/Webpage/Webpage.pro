QT += gui webengine webenginewidgets

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        backend/src/modelImp.cpp

HEADERS += \
    backend/include/modelImp.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


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
    qrcs/frontend.qrc \
    qrcs/settings.qrc
