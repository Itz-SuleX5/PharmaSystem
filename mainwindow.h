#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "views/inventoryview.h"
#include "views/salesview.h"
#include "views/supplierview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &userRole, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionInventario_triggered();
    void on_actionVentas_triggered();
    void on_actionProveedores_triggered();
    void on_actionSalir_triggered();
    void checkLowStock();
    void checkExpiringProducts();

private:
    Ui::MainWindow *ui;
    QString userRole;
    QStackedWidget *stackedWidget;
    InventoryView *inventoryView;
    SalesView *salesView;
    SupplierView *supplierView;

    void setupViews();
    void setupMenus();
    void configurePermissions();
    void setupTimers();
};
#endif // MAINWINDOW_H
