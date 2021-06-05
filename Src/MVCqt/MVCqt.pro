QT += gui webengine webenginewidgets

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    $$PWD/../MVCqtActor/src/mvcqtActor.cpp \
    $$PWD/../MVCqtActor/src/mvcqtDebug.cpp \
    $$PWD/../MVCqtModel/src/mvcqtModel.cpp \
    $$PWD/../MVCqtView/src/mvcqtView.cpp \
    $$PWD/../MVCqtController/src/mvcqtQController.cpp

HEADERS += \
    include/mvcqt.h \
    $$PWD/../MVCqtActor/include/mvcqtActor.h \
    $$PWD/../MVCqtActor/include/mvcqtDebug.h \
    $$PWD/../MVCqtModel/include/mvcqtModel.h \
    $$PWD/../MVCqtView/include/mvcqtView.h \
    $$PWD/../MVCqtController/include/mvcqtController.h \
    $$PWD/../MVCqtController/include/mvcqtQController.h \
    $$PWD/../MVCqtController/include/rpcsChannel.h \
    $$PWD/../MVCqtController/include/rpcsListener.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    DESTDIR = \"$$IN_PWD/../../Lib/Root/usr/lib/MVCqt\"
}
!isEmpty(target.path): INSTALLS += target
