#-------------------------------------------------
#
# Project created by QtCreator 2014-03-01T14:06:14
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iRC2KeyGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
		ircprocessor.cpp \
    windowskeyboardsim.cpp \
    visualstreaminfo.cpp \
    musicplayer.cpp

HEADERS  += mainwindow.h ircprocessor.h \
    windowskeyboardsim.h \
    visualstreaminfo.h \
    musicplayer.h

FORMS    += mainwindow.ui \
    visualstreaminfo.ui
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    res.qrc

OTHER_FILES += \
    ChangeLog.txt
