#include "salesview.h"
#include "sale.h" // Include sale.h
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QDateTime>
#include <QSqlDatabase>
#include <QGroupBox>
#include <QFormLayout>

SalesView::SalesView(QWidget *parent) : QWidget(parent), total(0.0), change(0.0)
{
    setupUI();
    loadProducts();
    
    // Connect signals and slots
    connect(searchEdit, &QLineEdit::returnPressed, this, &SalesView::onSearch);
    connect(addToCartButton, &QPushButton::clicked, this, &SalesView::onAddToCart);
    connect(removeFromCartButton, &QPushButton::clicked, this, &SalesView::onRemoveFromCart);
    connect(processSaleButton, &QPushButton::clicked, this, &SalesView::onProcessSale);
    connect(generatePDFButton, &QPushButton::clicked, this, &SalesView::onGeneratePDF);
    connect(amountPaidSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &SalesView::onAmountPaidChanged);
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
    productsTable->setSelectionBehavior(QAbstractItemView::SelectRows);  // Seleccionar fila completa
    productsTable->setSelectionMode(QAbstractItemView::SingleSelection); // Solo una fila a la vez
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
    
    // Customer and payment info
    QGroupBox *infoGroupBox = new QGroupBox("Información de Venta", this);
    QFormLayout *infoLayout = new QFormLayout(infoGroupBox);
    
    customerNameEdit = new QLineEdit(this);
    infoLayout->addRow("Nombre del Cliente:", customerNameEdit);
    
    amountPaidSpinBox = new QDoubleSpinBox(this);
    amountPaidSpinBox->setMaximum(999999.99);
    amountPaidSpinBox->setDecimals(2);
    amountPaidSpinBox->setMinimum(0.0);
    amountPaidSpinBox->setSingleStep(1.0);
    infoLayout->addRow("Monto Pagado:", amountPaidSpinBox);
    
    totalLabel = new QLabel("Total: $0.00", this);
    infoLayout->addRow("Total:", totalLabel);
    
    changeLabel = new QLabel("Cambio: $0.00", this);
    infoLayout->addRow("Cambio:", changeLabel);
    
    mainLayout->addWidget(infoGroupBox);
    
    // Total and buttons section
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    processSaleButton = new QPushButton("Procesar Venta", this);
    generatePDFButton = new QPushButton("Generar Factura PDF", this);
    generatePDFButton->setEnabled(false);
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
    
    // Buscar si el producto ya está en el carrito
    int existingRow = -1;
    for (int i = 0; i < cartTable->rowCount(); ++i) {
        if (cartTable->item(i, 0)->text().toInt() == productId) {
            existingRow = i;
            break;
        }
    }
    
    // Calcular cantidad total
    int totalQuantity = quantity;
    if (existingRow != -1) {
        totalQuantity += cartTable->item(existingRow, 2)->text().toInt();
    }
    
    if (totalQuantity > stock) {
        QMessageBox::warning(this, "Error", "No hay suficiente stock disponible");
        return;
    }
    
    if (existingRow != -1) {
        // Actualizar cantidad y subtotal del item existente
        cartTable->item(existingRow, 2)->setText(QString::number(totalQuantity));
        cartTable->item(existingRow, 3)->setText(QString::number(totalQuantity * price, 'f', 2));
    } else {
        // Agregar nuevo item al carrito
        int cartRow = cartTable->rowCount();
        cartTable->insertRow(cartRow);
        cartTable->setItem(cartRow, 0, new QTableWidgetItem(QString::number(productId)));
        cartTable->setItem(cartRow, 1, new QTableWidgetItem(name));
        cartTable->setItem(cartRow, 2, new QTableWidgetItem(QString::number(quantity)));
        cartTable->setItem(cartRow, 3, new QTableWidgetItem(QString::number(quantity * price, 'f', 2)));
    }
    
    // Update total y monto pagado
    updateTotal();
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
    
    // Update total y monto pagado
    updateTotal();
}

void SalesView::onAmountPaidChanged(double value)
{
    updateChange();
}

void SalesView::updateChange()
{
    change = amountPaidSpinBox->value() - total;
    changeLabel->setText(QString("Cambio: $%1").arg(change, 0, 'f', 2));
    
    // Enable/disable process sale button based on payment
    processSaleButton->setEnabled(amountPaidSpinBox->value() >= total);
}

void SalesView::updateTotal()
{
    total = 0.0;
    for (int row = 0; row < cartTable->rowCount(); ++row) {
        total += cartTable->item(row, 3)->text().toFloat();
    }
    totalLabel->setText(QString("Total: $%1").arg(total, 0, 'f', 2));
    
    // Actualizar el mínimo del spinbox al total actual
    amountPaidSpinBox->setMinimum(total);
    amountPaidSpinBox->setValue(total);  // Establecer el valor al total
    
    // Actualizar el cambio
    updateChange();
}

void SalesView::onProcessSale()
{
    if (cartTable->rowCount() == 0) {
        QMessageBox::warning(this, "Error", "El carrito está vacío");
        return;
    }
    
    if (customerNameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor ingrese el nombre del cliente");
        return;
    }

    QSqlDatabase::database().transaction();
    
    // Actualizar stock de productos
    for (int row = 0; row < cartTable->rowCount(); ++row) {
        int productId = cartTable->item(row, 0)->text().toInt();
        int quantity = cartTable->item(row, 2)->text().toInt();
        
        QSqlQuery updateStock;
        updateStock.prepare("UPDATE products SET stock = stock - ? WHERE id = ?");
        updateStock.addBindValue(quantity);
        updateStock.addBindValue(productId);
        
        if (!updateStock.exec()) {
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this, "Error", "Error al actualizar el stock: " + updateStock.lastError().text());
            return;
        }
    }

    // Create new sale
    currentSale.customerName = customerNameEdit->text().trimmed();
    currentSale.date = QDateTime::currentDateTime();
    currentSale.total = total;
    currentSale.amountPaid = amountPaidSpinBox->value();
    currentSale.change = change;
    currentSale.items.clear();

    // Add items to sale
    for (int row = 0; row < cartTable->rowCount(); ++row) {
        SaleItem item;
        item.productId = cartTable->item(row, 0)->text().toInt();
        item.productName = cartTable->item(row, 1)->text();
        item.quantity = cartTable->item(row, 2)->text().toInt();
        item.price = cartTable->item(row, 3)->text().toFloat() / item.quantity;
        currentSale.items.append(item);
    }
    
    if (!QSqlDatabase::database().commit()) {
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "Error", "Error al procesar la venta");
        return;
    }
    
    // Enable PDF generation before clearing cart
    generatePDFButton->setEnabled(true);
    
    // Clear cart and reload products
    cartTable->setRowCount(0);
    total = 0.0;
    totalLabel->setText("Total: $0.00");
    amountPaidSpinBox->setMinimum(0.0);
    amountPaidSpinBox->setValue(0.0);
    changeLabel->setText("Cambio: $0.00");
    
    loadProducts();
    
    // Clear customer info
    customerNameEdit->clear();
    
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
    
    if (currentSale.generatePDF(filePath)) {
        QMessageBox::information(this, "Éxito", "Factura generada correctamente");
    } else {
        QMessageBox::critical(this, "Error", "Error al generar la factura");
    }
}

void SalesView::clearCart()
{
    cartTable->setRowCount(0);
    total = 0.0;
    totalLabel->setText("Total: $0.00");
    amountPaidSpinBox->setMinimum(0.0);
    amountPaidSpinBox->setValue(0.0);
    changeLabel->setText("Cambio: $0.00");
    generatePDFButton->setEnabled(false);
}
