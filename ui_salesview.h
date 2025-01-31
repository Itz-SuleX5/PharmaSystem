/********************************************************************************
** Form generated from reading UI file 'salesview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SALESVIEW_H
#define UI_SALESVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SalesView
{
public:

    void setupUi(QWidget *SalesView)
    {
        if (SalesView->objectName().isEmpty())
            SalesView->setObjectName(QString::fromUtf8("SalesView"));
        SalesView->resize(800, 600);

        retranslateUi(SalesView);

        QMetaObject::connectSlotsByName(SalesView);
    } // setupUi

    void retranslateUi(QWidget *SalesView)
    {
        (void)SalesView;
    } // retranslateUi

};

namespace Ui {
    class SalesView: public Ui_SalesView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SALESVIEW_H
