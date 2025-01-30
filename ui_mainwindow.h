/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionInventario;
    QAction *actionVentas;
    QAction *actionProveedores;
    QAction *actionSalir;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuSistema;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionInventario = new QAction(MainWindow);
        actionInventario->setObjectName("actionInventario");
        actionVentas = new QAction(MainWindow);
        actionVentas->setObjectName("actionVentas");
        actionProveedores = new QAction(MainWindow);
        actionProveedores->setObjectName("actionProveedores");
        actionSalir = new QAction(MainWindow);
        actionSalir->setObjectName("actionSalir");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuSistema = new QMenu(menubar);
        menuSistema->setObjectName("menuSistema");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuSistema->menuAction());
        menuSistema->addAction(actionInventario);
        menuSistema->addAction(actionVentas);
        menuSistema->addAction(actionProveedores);
        menuSistema->addSeparator();
        menuSistema->addAction(actionSalir);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Sistema de Gesti\303\263n Farmac\303\251utica", nullptr));
        actionInventario->setText(QCoreApplication::translate("MainWindow", "Inventario", nullptr));
        actionVentas->setText(QCoreApplication::translate("MainWindow", "Ventas", nullptr));
        actionProveedores->setText(QCoreApplication::translate("MainWindow", "Proveedores", nullptr));
        actionSalir->setText(QCoreApplication::translate("MainWindow", "Salir", nullptr));
        menuSistema->setTitle(QCoreApplication::translate("MainWindow", "Sistema", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
