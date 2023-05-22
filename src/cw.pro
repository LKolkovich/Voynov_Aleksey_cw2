QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QT       += core gui

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cutdialog.cpp \
    dialogdrawline.cpp \
    drawlinemenudialog.cpp \
    image.cpp \
    infodialog.cpp \
    invertusingcircledialog.cpp \
    invertusingsquaredialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    cutdialog.h \
    dialogdrawline.h \
    drawlinemenudialog.h \
    image.h \
    infodialog.h \
    invertusingcircledialog.h \
    invertusingsquaredialog.h \
    mainwindow.h

FORMS += \
    cutdialog.ui \
    dialogdrawline.ui \
    drawlinemenudialog.ui \
    infodialog.ui \
    invertusingcircledialog.ui \
    invertusingsquaredialog.ui \
    mainwindow.ui

INCLUDEPATH = D:\qt\lpng1639

LIBS += D:\qt\5.14.2\mingw73_32\lib\libqtlibpng.a

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    img/appIcon.png \
    img/backArrow.png \
    img/cutIcon.png \
    img/invertCircleIcon.png \
    img/invertSquareIcon.png \
    img/line.png

RESOURCES += \
    images.qrc
