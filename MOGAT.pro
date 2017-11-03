

CONFIG += c++14 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    mainapplication.cpp \
    Desktop/intro.cpp \
    singleton.cpp \
    Desktop/desktopmainpage.cpp







win32: LIBS += -L$$PWD/../../Server/WebServer/Wt-4.0.0-msvs2015-Windows-x64-SDK/lib/ -lwt

INCLUDEPATH += $$PWD/../../Server/WebServer/Wt-4.0.0-msvs2015-Windows-x64-SDK/include
DEPENDPATH += $$PWD/../../Server/WebServer/Wt-4.0.0-msvs2015-Windows-x64-SDK/include


win32: LIBS += -L$$PWD/../../Server/WebServer/Wt-4.0.0-msvs2015-Windows-x64-SDK/lib/ -lwthttp

INCLUDEPATH += $$PWD/../../Server/WebServer/Wt-4.0.0-msvs2015-Windows-x64-SDK/include
DEPENDPATH += $$PWD/../../Server/WebServer/Wt-4.0.0-msvs2015-Windows-x64-SDK/include

HEADERS += \
    mainapplication.h \
    Desktop/intro.h \
    singleton.h \
    Desktop/desktopmainpage.h






LIBS += -L$$PWD/../../Server/WebServer/Wt-4.0.0-msvs2015-Windows-x64-SDK/lib/ -lwt

INCLUDEPATH += $$PWD/../../Server/WebServer/Wt-4.0.0-msvs2015-Windows-x64-SDK/include
DEPENDPATH += $$PWD/../../Server/WebServer/Wt-4.0.0-msvs2015-Windows-x64-SDK/include

DISTFILES += \
    ../build-MOGAT-Desktop_Qt_5_9_1_MSVC2015_64bit2-Release/css/intro.css
