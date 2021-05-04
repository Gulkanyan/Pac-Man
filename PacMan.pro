QT       += core gui multimedia sql

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

INCLUDEPATH += GUI/ Core/

SOURCES += \
    Core/Database/Database.cpp \
    Core/Database/Utils/StandardQueries.cpp \
    Core/Ghost.cpp \
    Core/Ghosts/Blue.cpp \
    Core/CoreGlobals.cpp \
    Core/Starter.cpp \
    Core/Utils/StandardBlock.cpp \
    Core/Utils/Coin.cpp \
    Core/Utils/Levels.cpp \
    Core/Ghosts/Orange.cpp \
    Core/Ghosts/Purple.cpp \
    Core/Ghosts/Red.cpp \
    Core/Utils/Pill.cpp \
    GUI/About.cpp \
    GUI/ChooseGhost.cpp \
    GUI/Dialog.cpp \
    GUI/Game.cpp \
    GUI/Help.cpp \
    GUI/Player.cpp \
    GUI/ScoresPage.cpp \
    GUI/Settings.cpp \
    GUI/MainWindow.cpp \
    main.cpp

HEADERS += \
    Core/Database/Database.h \
    Core/Database/Utils/StandardQueries.h \
    Core/Ghost.h \
    Core/Ghosts/Blue.h \
    Core/CoreGlobals.h \
    Core/GlobalDefs.h \
    Core/Starter.h \
    Core/Utils/StandardBlock.h \
    Core/Utils/Coin.h \
    Core/Utils/DataStructs.h \
    Core/Utils/Enums.h \
    Core/Utils/Levels.h \
    Core/Ghosts/Orange.h \
    Core/Ghosts/Purple.h \
    Core/Ghosts/Red.h \
    Core/Utils/Pill.h \
    GUI/About.h \
    GUI/ChooseGhost.h \
    GUI/Dialog.h \
    GUI/Game.h \
    GUI/Help.h \
    GUI/MainWindow.h \
    GUI/Player.h \
    GUI/ScoresPage.h \
    GUI/Settings.h \

FORMS += \
    GUI/About.ui \
    GUI/ChooseGhost.ui \
    GUI/Dialog.ui \
    GUI/Help.ui \
    GUI/MainWindow.ui \
    GUI/ScoresPage.ui \
    GUI/Settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Rec.qrc
