QT += quick svg

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

SOURCES += \
        abstracttool.cpp \
        buildTool/builder.cpp \
        deployTool/windeployqt.cpp \
        installTool/finstaller.cpp \
        installTool/installerhelper.cpp \
        main.cpp \
        qmldirTool/qmldir.cpp \
        toolsdetector.cpp \
        toolssaver.cpp \
        translationTool/lupdate.cpp \
        worker.cpp

TRANSLATIONS = translation/ts_files/QtAutoTools_en.ts


RESOURCES += qml.qrc \
    icon.qrc \
    translation.qrc

#DESTDIR = ../Deploy
#QMAKE_POST_LINK += $$(QTDIR)/bin/windeployqt --qmldir $$PWD $$DESTDIR

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD/qml
QML2_IMPORT_PATH = $$PWD/qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    abstracttool.h \
    buildTool/builder.h \
    deployTool//windeployqt.h \
    installTool/finstaller.h \
    installTool/installerhelper.h \
    qmldirTool//qmldir.h \
    toolsdetector.h \
    toolssaver.h \
    translationTool/lupdate.h \
    worker.h

DISTFILES +=
