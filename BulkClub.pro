QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminwindow.cpp \
    dbhandler.cpp \
    itemsalesreportform.cpp \
    main.cpp \
    mainwindow.cpp \
    managerwindow.cpp \
    memberhandler.cpp \
    membersexpirationform.cpp \
    memberspurchasesform.cpp \
    rebatesform.cpp \
    salesreportform.cpp

HEADERS += \
    adminwindow.h \
    consts.h \
    dbhandler.h \
    itemsalesreportform.h \
    mainwindow.h \
    managerwindow.h \
    memberhandler.h \
    membersexpirationform.h \
    memberspurchasesform.h \
    rebatesform.h \
    salesreportform.h

FORMS += \
    adminwindow.ui \
    itemsalesreportform.ui \
    mainwindow.ui \
    managerwindow.ui \
    membersexpirationform.ui \
    memberspurchasesform.ui \
    rebatesform.ui \
    salesreportform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../Text Files/day1.txt \
    ../../Text Files/day2.txt \
    ../../Text Files/day3.txt \
    ../../Text Files/day4.txt \
    ../../Text Files/day5.txt \
    ../../Text Files/day6.txt \
    ../../Text Files/day7.txt \
    ../../Text Files/warehouse shoppers.txt \
    day1.txt \
    day2.txt \
    day3.txt \
    day4.txt \
    day5.txt \
    day6.txt \
    day7.txt \
    warehouseshoppers.txt
