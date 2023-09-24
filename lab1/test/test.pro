QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
# INCLUDEPATH += "lib/googletest/googletest/include"
# INCLUDEPATH += "lib/googletest/googletest"

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../prog/src/matrix.h


win32: LIBS += -L$$PWD/../lib/googletest/lib/ -lgtest

INCLUDEPATH += $$PWD/../lib/googletest/include/googletest/include
DEPENDPATH += $$PWD/../lib/googletest/include/googletest/include
