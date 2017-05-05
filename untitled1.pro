#-------------------------------------------------
#
# Project created by QtCreator 2017-03-28T23:17:12
#
#-------------------------------------------------

#QT += core
#QT -= gui
QT       += core gui
CONFIG += c++11

#TARGET = untitled1
CONFIG += console
CONFIG -= app_bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CPP_regression_project
TEMPLATE = app



# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include

#QMAKE_LFLAGS += -F/path/to/framework/directory/

LIBS += -framework Accelerate

SOURCES += main.cpp \
    csvreader.cpp \
    lsregression.cpp \
    robustregression.cpp \
    mainwindow.cpp \
    regression.cpp \
    dialog1.cpp \
    distribution.cpp

HEADERS += \
    csvreader.h \
    lsregression.h \
    robustregression.h \
    mainwindow.h \
    regression.h \
    dialog1.h \
    distribution.h

DESTDIR = $$PWD

FORMS    += mainwindow.ui \
    dialog1.ui

DISTFILES += \
    *.csv \


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/armadillo/7.800.2/lib/release/ -larmadillo.7.80.2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/armadillo/7.800.2/lib/debug/ -larmadillo.7.80.2
else:unix: LIBS += -L$$PWD/armadillo/7.800.2/lib/ -larmadillo.7.80.2

INCLUDEPATH += $$PWD/armadillo/7.800.2/include
DEPENDPATH += $$PWD/armadillo/7.800.2/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/armadillo/7.800.2/lib/release/ -larmadillo.7.80.2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/armadillo/7.800.2/lib/debug/ -larmadillo.7.80.2
else:unix: LIBS += -L$$PWD/armadillo/7.800.2/lib/ -larmadillo.7.80.2

INCLUDEPATH += $$PWD/armadillo/7.800.2/include
DEPENDPATH += $$PWD/armadillo/7.800.2/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/armadillo/7.800.2/lib/release/ -larmadillo.7.80.2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/armadillo/7.800.2/lib/debug/ -larmadillo.7.80.2
else:unix: LIBS += -L$$PWD/armadillo/7.800.2/lib/ -larmadillo.7.80.2

INCLUDEPATH += $$PWD/armadillo/7.800.2/include
DEPENDPATH += $$PWD/armadillo/7.800.2/include
