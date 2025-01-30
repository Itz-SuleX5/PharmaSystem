QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    login.cpp \
    database.cpp \
    models/product.cpp \
    models/user.cpp \
    models/sale.cpp \
    models/supplier.cpp \
    controllers/inventorycontroller.cpp \
    controllers/salescontroller.cpp \
    controllers/usercontroller.cpp \
    views/inventoryview.cpp \
    views/salesview.cpp \
    views/supplierview.cpp \
    utils/pdfgenerator.cpp \
    utils/databasebackup.cpp

HEADERS += \
    mainwindow.h \
    login.h \
    database.h \
    models/product.h \
    models/user.h \
    models/sale.h \
    models/supplier.h \
    controllers/inventorycontroller.h \
    controllers/salescontroller.h \
    controllers/usercontroller.h \
    views/inventoryview.h \
    views/salesview.h \
    views/supplierview.h \
    utils/pdfgenerator.h \
    utils/databasebackup.h

FORMS += \
    mainwindow.ui \
    login.ui \
    views/inventoryview.ui \
    views/salesview.ui \
    views/supplierview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
