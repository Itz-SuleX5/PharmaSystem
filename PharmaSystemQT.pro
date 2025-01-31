QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PharmaSystemQT
TEMPLATE = app

# Configuración específica para Windows
win32 {
    RC_ICONS = icon.ico
    VERSION = 1.0.0.0
    QMAKE_TARGET_COMPANY = "Tu Compañía"
    QMAKE_TARGET_PRODUCT = "PharmaSystemQT"
    QMAKE_TARGET_DESCRIPTION = "Sistema de Gestión de Farmacia"
    QMAKE_TARGET_COPYRIGHT = "Copyright (C) 2024"
}

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controllers/inventorycontroller.cpp \
    controllers/salescontroller.cpp \
    controllers/usercontroller.cpp \
    database.cpp \
    main.cpp \
    mainwindow.cpp \
    models/product.cpp \
    models/sale.cpp \
    models/supplier.cpp \
    models/user.cpp \
    utils/databasebackup.cpp \
    utils/pdfgenerator.cpp \
    views/inventoryview.cpp \
    views/login.cpp \
    views/salesview.cpp \
    views/supplierview.cpp

HEADERS += \
    controllers/inventorycontroller.h \
    controllers/salescontroller.h \
    controllers/usercontroller.h \
    database.h \
    mainwindow.h \
    models/product.h \
    models/sale.h \
    models/supplier.h \
    models/user.h \
    utils/databasebackup.h \
    utils/pdfgenerator.h \
    views/inventoryview.h \
    views/login.h \
    views/salesview.h \
    views/supplierview.h

FORMS += \
    views/inventoryview.ui \
    views/mainwindow.ui \
    views/salesview.ui \
    views/supplierview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
