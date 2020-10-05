QT       += core gui
QT       += widgets
QT       += xml
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddAxis.cpp \
    AddConst.cpp \
    AddElement.cpp \
    CutChoise.cpp \
    CutView.cpp \
    Element.cpp \
    GlobalConstant.cpp \
    ObjectWindow.cpp \
    PlanView.cpp \
    ProjectBase.cpp \
    SetConst.cpp \
    UnitBase.cpp \
    XmlLoader.cpp \
    XmlSaver.cpp \
    createnewobwindow.cpp \
    dorcad_tests.cpp \
    dormath.cpp \
    main.cpp \
    mainwindow.cpp \
    objectwindowform.cpp \
    roadcadast.cpp \
    table_view.cpp

HEADERS += \
    AddAxis.h \
    AddConst.h \
    AddElement.h \
    CutChoise.h \
    CutView.h \
    Element.h \
    GlobalConstant.h \
    ObjectWindow.h \
    PlanView.h \
    ProjectBase.h \
    SetConst.h \
    UnitBase.h \
    XmlLoader.h \
    XmlSaver.h \
    createnewobwindow.h \
    dorcad_tests.h \
    dormath.h \
    mainwindow.h \
    objectwindowform.h \
    searchfonumberslist.h \
    table_view.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    ../../../mnt/qt_pr/DORCAD/DORCAD.pro

FORMS +=

DISTFILES += \
    ../../../mnt/qt_pr/DORCAD/DORCAD.pro.user \
    ../../../mnt/qt_pr/DORCAD/DORCAD.pro.user.4.8-pre1 \
    ../../../mnt/qt_pr/DORCAD/DORCAD.pro.user.e1ebe78.22 \
    ../../../mnt/qt_pr/DORCAD/DORCAD_ru_RU.ts \
    DorCad.pro.user
