QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    confirmrefund.cpp \
    form.cpp \
    iconhelper.cpp \
    journey.cpp \
    main.cpp \
    sliderbar.cpp \
    subwindow.cpp \
    triwindow.cpp

HEADERS += \
    confirmrefund.h \
    form.h \
    iconhelper.h \
    journey.h \
    passenger.h \
    sliderbar.h \
    subwindow.h \
    triwindow.h

FORMS += \
    confirmrefund.ui \
    form.ui \
    subwindow.ui \
    triwindow.ui

RESOURCES += \
    demo/demo.qrc \
    demo/image.qrc \
    other/main.qrc \
    other/qss.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
