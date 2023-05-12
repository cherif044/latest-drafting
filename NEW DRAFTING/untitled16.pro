QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Main_Ahmed.cpp \
    RKclassStruct.cpp \
    RKphrasesClassStrcut.cpp \
    RKsentencesClassStruct.cpp \
    file.cpp \
    main.cpp \
    mainwindow.cpp \
    start.cpp \
    startwindow.cpp

HEADERS += \
    File.h \
    Main_ahmed.h \
    RKphrases.h \
    RKsentences.h \
    RabinKarp.h \
    common_lang.h \
    english.h \
    mainwindow.h \
    start.h \
    startwindow.h \
    stemming.h

FORMS += \
    mainwindow.ui \
    startwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
