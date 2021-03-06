QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/mvcqtActor.cpp \
    src/mvcqtDebug.cpp

HEADERS += \
    include/mvcqtActor.h \
    include/mvcqtDebug.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
    DESTDIR = \"$$IN_PWD/../../Lib/Root/usr/lib/MVCqt/MVCqtActor\"
}
!isEmpty(target.path): INSTALLS += target
