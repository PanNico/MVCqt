QT += gui webenginewidgets

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/mvcqtView.cpp \
    $$PWD/../MVCqtActor/src/mvcqtActor.cpp \
    $$PWD/../MVCqtActor/src/mvcqtDebug.cpp

HEADERS += \
    include/mvcqtView.h \
    $$PWD/../MVCqtActor/include/mvcqtActor.h \
    $$PWD/../MVCqtActor/include/mvcqtDebug.h


# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    DESTDIR = \"$$IN_PWD/../../Lib/Root/usr/lib/MVCqt/MVCqtView\"
}
!isEmpty(target.path): INSTALLS += target
