/********************************************************************************
** Form generated from reading UI file 'supplierview.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUPPLIERVIEW_H
#define UI_SUPPLIERVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SupplierView
{
public:

    void setupUi(QWidget *SupplierView)
    {
        if (SupplierView->objectName().isEmpty())
            SupplierView->setObjectName("SupplierView");
        SupplierView->resize(800, 600);

        retranslateUi(SupplierView);

        QMetaObject::connectSlotsByName(SupplierView);
    } // setupUi

    void retranslateUi(QWidget *SupplierView)
    {
        (void)SupplierView;
    } // retranslateUi

};

namespace Ui {
    class SupplierView: public Ui_SupplierView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUPPLIERVIEW_H
