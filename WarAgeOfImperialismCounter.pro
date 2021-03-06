QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arrow.cpp \
    buildingdelegate.cpp \
    buildingschart.cpp \
    countrieschart.cpp \
    countriesframe.cpp \
    countriestablemodel.cpp \
    country.cpp \
    diplomacyframe.cpp \
    diplomacytablemodel.cpp \
    historyframe.cpp \
    historystate.cpp \
    incomechart.cpp \
    incometotalchart.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    playerdelegate.cpp \
    playersframe.cpp \
    playerstablemodel.cpp \
    technologyframe.cpp \
    techplayerbutton.cpp \
    techtreeframe.cpp \
    world.cpp

HEADERS += \
    arrow.h \
    buildingdelegate.h \
    buildingschart.h \
    countrieschart.h \
    countriesframe.h \
    countriestablemodel.h \
    country.h \
    diplomacyframe.h \
    diplomacytablemodel.h \
    historyframe.h \
    historystate.h \
    incomechart.h \
    incometotalchart.h \
    mainwindow.h \
    player.h \
    playerdelegate.h \
    playersframe.h \
    playerstablemodel.h \
    technologyframe.h \
    techplayerbutton.h \
    techtreeframe.h \
    world.h

FORMS += \
    countriesframe.ui \
    diplomacyframe.ui \
    historyframe.ui \
    mainwindow.ui \
    playersframe.ui \
    technologyframe.ui \
    techtreeframe.ui

TRANSLATIONS += \
    WarAgeOfImperialismCounter_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
