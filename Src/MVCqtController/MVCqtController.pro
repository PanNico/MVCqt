QT += gui webenginewidgets

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/mvcqtQController.cpp \
    $$PWD/../MVCqtActor/src/mvcqtActor.cpp \
    $$PWD/../MVCqtActor/src/mvcqtDebug.cpp \
    $$PWD/../MVCqtModel/src/mvcqtModel.cpp \
    $$PWD/../MVCqtView/src/mvcqtView.cpp

HEADERS += \
    include/mvcqtController.h \
    $$PWD/../MVCqtActor/include/mvcqtActor.h \
    $$PWD/../MVCqtActor/include/mvcqtDebug.h \
    $$PWD/../MVCqtModel/include/mvcqtModel.h \
    $$PWD/../MVCqtView/include/mvcqtView.h \
    include/mvcqtQController.h \
    include/rpcsChannel.h \
    include/rpcsListener.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    DESTDIR = \"$$IN_PWD/../../Lib/Root/usr/lib/MVCqt/MVCqtController\"
}
!isEmpty(target.path): INSTALLS += target
