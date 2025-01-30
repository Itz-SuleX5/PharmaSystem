#include "salesview.h"
#include "sale.h" // Include sale.h
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QDateTime>
#include <QSqlDatabase>

SalesView::SalesView(QWidget *parent) : QWidget(parent), total(0.0)
{
    setupUI();
    loadProducts();
    
    // Connect signals and slots
    connect(searchEdit, &QLineEdit::returnPressed, this, &SalesView::onSearch);
    connect(addToCartButton, &QPushButton::clicked, this, &SalesView::onAddToCart);
    connect(removeFromCartButton, &QPushButton::clicked, this, &SalesView::onRemoveFromCart);
    connect(processSaleButton, &QPushButton::clicked, this, &SalesView::onProcessSale);
    connect(generatePDFButton, &QPushButton::clicked, this, &SalesView::onGeneratePDF);
}

void SalesView::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Search section
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Buscar productos...");
    searchLayout->addWidget(searchEdit);
    mainLayout->addLayout(searchLayout);
    
    // Products section
    QHBoxLayout *productsLayout = new QHBoxLayout();
    
    // Products table
    productsTable = new QTableWidget(this);
    productsTable->setColumnCount(4);
    productsTable->setHorizontalHeaderLabels({"ID", "Nombre", "Precio", "Stock"});
    productsLayout->addWidget(productsTable);
    
    // Cart controls
    QVBoxLayout *controlsLayout = new QVBoxLayout();
    quantitySpinBox = new QSpinBox(this);
    quantitySpinBox->setMinimum(1);
    addToCartButton = new QPushButton("Agregar al Carrito", this);
    removeFromCartButton = new QPushButton("Quitar del Carrito", this);
    controlsLayout->addWidget(quantitySpinBox);
    controlsLayout->addWidget(addToCartButton);
    controlsLayout->addWidget(removeFromCartButton);
    controlsLayout->addStretch();
    productsLayout->addLayout(controlsLayout);
    
    // Cart table
    cartTable = new QTableWidget(this);
    cartTable->setColumnCount(4);
    cartTable->setHorizontalHeaderLabels({"ID", "Nombre", "Cantidad", "Subtotal"});
    productsLayout->addWidget(cartTable);
    
    mainLayout->addLayout(productsLayout);
    
    // Total and buttons section
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    totalLabel = new QLabel("Total: $0.00", this);
    processSaleButton = new QPushButton("Procesar Venta", this);
    generatePDFButton = new QPushButton("Generar Factura PDF", this);
    generatePDFButton->setEnabled(false);
    bottomLayout->addWidget(totalLabel);
    bottomLayout->addStretch();
    bottomLayout->addWidget(processSaleButton);
    bottomLayout->addWidget(generatePDFButton);
    
    mainLayout->addLayout(bottomLayout);
}

void SalesView::loadProducts()
{
    QSqlQuery query;
    if (!query.exec("SELECT id, name, price, stock FROM products WHERE stock > 0")) {
        QMessageBox::critical(this, "Error", "Error al cargar productos: " + query.lastError().text());
        return;
    }
    
    productsTable->setRowCount(0);
    while (query.next()) {
        int row = productsTable->rowCount();
        productsTable->insertRow(row);
        productsTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        productsTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        productsTable->setItem(row, 2, new QTableWidgetItem(QString::number(query.value(2).toFloat(), 'f', 2)));
        productsTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
    }
}

void SalesView::onSearch()
{
    QString searchText = searchEdit->text();
    QSqlQuery query;
    query.prepare("SELECT id, name, price, stock FROM products WHERE name LIKE ? AND stock > 0");
    query.addBindValue("%" + searchText + "%");
    
    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Error al buscar productos: " + query.lastError().text());
        return;
    }
    
    productsTable->setRowCount(0);
    while (query.next()) {
        int row = productsTable->rowCount();
        productsTable->insertRow(row);
        productsTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        productsTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        productsTable->setItem(row, 2, new QTableWidgetItem(QString::number(query.value(2).toFloat(), 'f', 2)));
        productsTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
    }
}

void SalesView::onAddToCart()
{
    QModelIndexList selection = productsTable->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor seleccione un producto");
        return;
    }
    
    int row = selection.first().row();
    int productId = productsTable->item(row, 0)->text().toInt();
    QString name = productsTable->item(row, 1)->text();
    float price = productsTable->item(row, 2)->text().toFloat();
    int stock = productsTable->item(row, 3)->text().toInt();
    int quantity = quantitySpinBox->value();
    
    if (quantity > stock) {
        QMessageBox::warning(this, "Error", "No hay suficiente stock disponible");
        return;
    }
    
    // Add to cart table
    int cartRow = cartTable->rowCount();
    cartTable->insertRow(cartRow);
    cartTable->setItem(cartRow, 0, new QTableWidgetItem(QString::number(productId)));
    cartTable->setItem(cartRow, 1, new QTableWidgetItem(name));
    cartTable->setItem(cartRow, 2, new QTableWidgetItem(QString::number(quantity)));
    cartTable->setItem(cartRow, 3, new QTableWidgetItem(QString::number(quantity * price, 'f', 2)));
    
    // Update total
    total += quantity * price;
    totalLabel->setText(QString("Total: $%1").arg(total, 0, 'f', 2));
}

void SalesView::onRemoveFromCart()
{
    QModelIndexList selection = cartTable->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor seleccione un item del carrito");
        return;
    }
    
    int row = selection.first().row();
    float subtotal = cartTable->item(row, 3)->text().toFloat();
    
    total -= subtotal;
    totalLabel->setText(QString("Total: $%1").arg(total, 0, 'f', 2));
    
    cartTable->removeRow(row);
}

void SalesView::onProcessSale()
{
    if (cartTable->rowCount() == 0) {
        QMessageBox::warning(this, "Error", "El carrito está vacío");
        return;
    }
    
    // Start transaction
    QSqlDatabase::database().transaction();
    
    // Create sale record
    QSqlQuery query;
    query.prepare("INSERT INTO sales (date, total, user_id) VALUES (?, ?, ?)");
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(total);
    query.addBindValue(1); // TODO: Get actual user ID
    
    if (!query.exec()) {
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "Error", "Error al crear la venta: " + query.lastError().text());
        return;
    }
    
    int saleId = query.lastInsertId().toInt();
    
    // Create sale items and update stock
    for (int row = 0; row < cartTable->rowCount(); ++row) {
        int productId = cartTable->item(row, 0)->text().toInt();
        int quantity = cartTable->item(row, 2)->text().toInt();
        float price = cartTable->item(row, 3)->text().toFloat() / quantity;
        
        // Create sale item
        query.prepare("INSERT INTO sale_items (sale_id, product_id, quantity, price) VALUES (?, ?, ?, ?)");
        query.addBindValue(saleId);
        query.addBindValue(productId);
        query.addBindValue(quantity);
        query.addBindValue(price);
        
        if (!query.exec()) {
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this, "Error", "Error al crear item de venta: " + query.lastError().text());
            return;
        }
        
        // Update stock
        query.prepare("UPDATE products SET stock = stock - ? WHERE id = ?");
        query.addBindValue(quantity);
        query.addBindValue(productId);
        
        if (!query.exec()) {
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this, "Error", "Error al actualizar stock: " + query.lastError().text());
            return;
        }
    }
    
    // Commit transaction
    if (!QSqlDatabase::database().commit()) {
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "Error", "Error al finalizar la venta");
        return;
    }
    
    // Store current sale for PDF generation
    Sale currentSale; // Declare Sale object
    currentSale.id = saleId;
    currentSale.date = QDateTime::currentDateTime();
    currentSale.total = total;
    currentSale.userId = 1; // TODO: Get actual user ID
    
    for (int row = 0; row < cartTable->rowCount(); ++row) {
        SaleItem item;
        item.productId = cartTable->item(row, 0)->text().toInt();
        item.productName = cartTable->item(row, 1)->text();
        item.quantity = cartTable->item(row, 2)->text().toInt();
        item.price = cartTable->item(row, 3)->text().toFloat() / item.quantity;
        currentSale.items.append(item);
    }
    
    // Enable PDF generation
    generatePDFButton->setEnabled(true);
    
    // Clear cart and reload products
    clearCart();
    loadProducts();
    
    QMessageBox::information(this, "Éxito", "Venta procesada correctamente");
}

void SalesView::onGeneratePDF()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                  "Guardar Factura",
                                                  QString("factura_%1.pdf").arg(currentSale.id),
                                                  "PDF Files (*.pdf)");
    
    if (filePath.isEmpty()) {
        return;
    }
    
    if (currentSale.generatePDF(filePath)) { // Use Sale object
        QMessageBox::information(this, "Éxito", "Factura generada correctamente");
    } else {
        QMessageBox::critical(this, "Error", "Error al generar la factura");
    }
}

void SalesView::updateTotal()
{
    total = 0.0;
    for (int row = 0; row < cartTable->rowCount(); ++row) {
        total += cartTable->item(row, 3)->text().toFloat();
    }
    totalLabel->setText(QString("Total: $%1").arg(total, 0, 'f', 2));
}

void SalesView::clearCart()
{
    cartTable->setRowCount(0);
    total = 0.0;
    totalLabel->setText("Total: $0.00");
    generatePDFButton->setEnabled(false);
}
