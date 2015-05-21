TEMPLATE = app
TARGET = Calculator

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    calcgui.h \
    calc.h

SOURCES += \
    calcgui.cpp \
    main.cpp \
    calc.cpp

