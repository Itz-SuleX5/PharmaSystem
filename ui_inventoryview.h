/********************************************************************************
** Form generated from reading UI file 'inventoryview.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVENTORYVIEW_H
#define UI_INVENTORYVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InventoryView
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *InventoryView)
    {
        if (InventoryView->objectName().isEmpty())
            InventoryView->setObjectName("InventoryView");
        InventoryView->resize(800, 600);
        verticalLayout = new QVBoxLayout(InventoryView);
        verticalLayout->setObjectName("verticalLayout");

        retranslateUi(InventoryView);

        QMetaObject::connectSlotsByName(InventoryView);
    } // setupUi

    void retranslateUi(QWidget *InventoryView)
    {
        InventoryView->setWindowTitle(QCoreApplication::translate("InventoryView", "Inventario", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InventoryView: public Ui_InventoryView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVENTORYVIEW_H
