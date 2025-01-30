#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QSqlQuery>
#include <QDateTime>

MainWindow::MainWindow(const QString &userRole, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , userRole(userRole)
{
    ui->setupUi(this);
    setWindowTitle("Sistema de Gestión Farmacéutica");
    
    setupViews();
    setupMenus();
    configurePermissions();
    setupTimers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupViews()
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    
    inventoryView = new InventoryView(this);
    salesView = new SalesView(this);
    supplierView = new SupplierView(this);
    
    stackedWidget->addWidget(inventoryView);
    stackedWidget->addWidget(salesView);
    stackedWidget->addWidget(supplierView);
}

void MainWindow::setupMenus()
{
    connect(ui->actionInventario, &QAction::triggered, this, &MainWindow::on_actionInventario_triggered);
    connect(ui->actionVentas, &QAction::triggered, this, &MainWindow::on_actionVentas_triggered);
    connect(ui->actionProveedores, &QAction::triggered, this, &MainWindow::on_actionProveedores_triggered);
    connect(ui->actionSalir, &QAction::triggered, this, &MainWindow::on_actionSalir_triggered);
}

void MainWindow::configurePermissions()
{
    if (userRole == "vendedor") {
        ui->actionInventario->setEnabled(false);
        ui->actionProveedores->setEnabled(false);
        on_actionVentas_triggered();
    } else if (userRole == "inventarista") {
        ui->actionVentas->setEnabled(false);
        ui->actionProveedores->setEnabled(false);
        on_actionInventario_triggered();
    } else {
        // Admin por defecto va a inventario
        on_actionInventario_triggered();
    }
}

void MainWindow::setupTimers()
{
    // Check for low stock every hour
    QTimer *lowStockTimer = new QTimer(this);
    connect(lowStockTimer, &QTimer::timeout, this, &MainWindow::checkLowStock);
    lowStockTimer->start(3600000); // 1 hour
    
    // Check for expiring products daily
    QTimer *expiryTimer = new QTimer(this);
    connect(expiryTimer, &QTimer::timeout, this, &MainWindow::checkExpiringProducts);
    expiryTimer->start(86400000); // 24 hours
    
    // Initial checks
    checkLowStock();
    checkExpiringProducts();
}

void MainWindow::checkLowStock()
{
    QSqlQuery query;
    query.prepare("SELECT name, stock, min_stock FROM products WHERE stock <= min_stock");
    
    if (query.exec() && query.next()) {
        QString message = "Los siguientes productos tienen stock bajo:\n\n";
        do {
            message += QString("%1 (Stock: %2, Mínimo: %3)\n")
                .arg(query.value(0).toString())
                .arg(query.value(1).toString())
                .arg(query.value(2).toString());
        } while (query.next());
        
        QMessageBox::warning(this, "Alerta de Stock", message);
    }
}

void MainWindow::checkExpiringProducts()
{
    QSqlQuery query;
    query.prepare("SELECT name, expiry_date FROM products WHERE expiry_date <= date('now', '+30 days')");
    
    if (query.exec() && query.next()) {
        QString message = "Los siguientes productos están próximos a vencer:\n\n";
        do {
            message += QString("%1 (Vence: %2)\n")
                .arg(query.value(0).toString())
                .arg(query.value(1).toDate().toString("dd/MM/yyyy"));
        } while (query.next());
        
        QMessageBox::warning(this, "Alerta de Vencimiento", message);
    }
}

void MainWindow::on_actionInventario_triggered()
{
    stackedWidget->setCurrentWidget(inventoryView);
}

void MainWindow::on_actionVentas_triggered()
{
    stackedWidget->setCurrentWidget(salesView);
}

void MainWindow::on_actionProveedores_triggered()
{
    stackedWidget->setCurrentWidget(supplierView);
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}
