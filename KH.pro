QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cases.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mngcase.cpp \
    mngpatient.cpp \
    mngperm.cpp \
    mngroles.cpp \
    mngstaff.cpp \
    patient.cpp \
    perm.cpp \
    roles.cpp \
    staff.cpp

HEADERS += \
    cases.h \
    connection.h \
    login.h \
    mainwindow.h \
    mngcase.h \
    mngpatient.h \
    mngperm.h \
    mngroles.h \
    mngstaff.h \
    patient.h \
    perm.h \
    roles.h \
    staff.h

FORMS += \
    cases.ui \
    login.ui \
    mainwindow.ui \
    mngcase.ui \
    mngpatient.ui \
    mngperm.ui \
    mngroles.ui \
    mngstaff.ui \
    patient.ui \
    perm.ui \
    roles.ui \
    staff.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
