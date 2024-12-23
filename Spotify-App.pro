QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatbox.cpp \
    comment_like.cpp \
    main.cpp \
    mainwindow.cpp \
    playlist_songs.cpp \
    premium.cpp \
    register.cpp

HEADERS += \
    NewPlaylistDialog.h \
    chatbox.h \
    comment_like.h \
    mainwindow.h \
    playlist_songs.h \
    premium.h \
    register.h

FORMS += \
    chatbox.ui \
    comment_like.ui \
    mainwindow.ui \
    playlist_songs.ui \
    premium.ui \
    register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Pictures.qrc
