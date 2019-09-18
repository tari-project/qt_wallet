QT += core
QT += qml
QT += quick
QT += remoteobjects
QT += concurrent
QT += testlib
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
HEADERS += \
    components/messagelist.h \
    components/models/messagemodel.h \
    components/models/peermodel.h \
    components/peerlist.h \
    constructs/ThreadedWorker/walletworker.h \
    constructs/ThreadedWorker/workerservice.h \
    constructs/ThreadedWorker/workerthread.h \
    constructs/message.h \
    constructs/myclass.h \
    constructs/peer.h \
    constructs/receivedmessage.h \
    constructs/sentmessage.h \
    constructs/wallet.h \
    constructs/walletsettings.h \
    helpers/jsonhelper.h \

SOURCES += \
    components/messagelist.cpp \
    components/models/messagemodel.cpp \
        components/models/peermodel.cpp \
        components/peerlist.cpp \
        constructs/ThreadedWorker/walletworker.cpp \
        constructs/ThreadedWorker/workerservice.cpp \
        #constructs/ThreadedWorker/workerthread.cpp \ # necessary to seperate a generics implementation into seperate implementation files, cpp file is included directly in the header
    constructs/message.cpp \
        constructs/myclass.cpp \
        constructs/peer.cpp \
    constructs/receivedmessage.cpp \
    constructs/sentmessage.cpp \
        constructs/wallet.cpp \
        constructs/walletsettings.cpp \
        helpers/jsonhelper.cpp \
        main.cpp \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

release: INCLDIR = release
debug:   INCLDIR = debug

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
macx: LIBS += -L$$PWD/../tari/target/$$INCLDIR/ -ltari_ffi

INCLUDEPATH += $$PWD/../tari/target/$$INCLDIR/
DEPENDPATH += $$PWD/../tari/target/$$INCLDIR/
