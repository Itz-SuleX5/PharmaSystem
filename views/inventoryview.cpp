#include "inventoryview.h"
#include <QSpinBox>
#include <QDoubleValidator>
#include <QHeaderView>
#include <QDateTime>

InventoryView::InventoryView(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    setupConnections();
    loadCategories();
    refreshTable();
}

void InventoryView::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Search section
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Buscar productos...");
    searchTypeCombo = new QComboBox(this);
    searchTypeCombo->addItems({"Nombre", "Código", "Categoría"});
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchTypeCombo);
    mainLayout->addLayout(searchLayout);

    // Table
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(7);
    tableWidget->setHorizontalHeaderLabels({
        "ID", "Código", "Nombre", "Categoría", 
        "Precio", "Stock", "Fecha Vencimiento"
    });
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(tableWidget);

    // Input form
    QGridLayout *formLayout = new QGridLayout();
    
    codeEdit = new QLineEdit(this);
    nameEdit = new QLineEdit(this);
    priceEdit = new QLineEdit(this);
    priceEdit->setValidator(new QDoubleValidator(0, 999999.99, 2, this));
    stockEdit = new QSpinBox(this);
    stockEdit->setRange(0, 999999);
    expiryEdit = new QDateEdit(this);
    expiryEdit->setCalendarPopup(true);
    expiryEdit->setDate(QDate::currentDate());
    categoryCombo = new QComboBox(this);

    formLayout->addWidget(new QLabel("Código:"), 0, 0);
    formLayout->addWidget(codeEdit, 0, 1);
    formLayout->addWidget(new QLabel("Nombre:"), 0, 2);
    formLayout->addWidget(nameEdit, 0, 3);
    formLayout->addWidget(new QLabel("Precio:"), 1, 0);
    formLayout->addWidget(priceEdit, 1, 1);
    formLayout->addWidget(new QLabel("Stock:"), 1, 2);
    formLayout->addWidget(stockEdit, 1, 3);
    formLayout->addWidget(new QLabel("Vencimiento:"), 2, 0);
    formLayout->addWidget(expiryEdit, 2, 1);
    formLayout->addWidget(new QLabel("Categoría:"), 2, 2);
    formLayout->addWidget(categoryCombo, 2, 3);

    mainLayout->addLayout(formLayout);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Agregar", this);
    editButton = new QPushButton("Editar", this);
    deleteButton = new QPushButton("Eliminar", this);
    refreshButton = new QPushButton("Actualizar", this);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(refreshButton);
    mainLayout->addLayout(buttonLayout);
}

void InventoryView::setupConnections()
{
    connect(addButton, &QPushButton::clicked, this, &InventoryView::addProduct);
    connect(editButton, &QPushButton::clicked, this, &InventoryView::editProduct);
    connect(deleteButton, &QPushButton::clicked, this, &InventoryView::deleteProduct);
    connect(refreshButton, &QPushButton::clicked, this, &InventoryView::refreshTable);
    connect(searchEdit, &QLineEdit::textChanged, this, &InventoryView::searchProducts);
}

void InventoryView::loadCategories()
{
    categoryCombo->clear();
    QSqlQuery query;
    query.exec("SELECT DISTINCT category FROM products ORDER BY category");
    while (query.next()) {
        categoryCombo->addItem(query.value(0).toString());
    }
    categoryCombo->setEditable(true);
}

void InventoryView::refreshTable()
{
    tableWidget->setRowCount(0);
    QSqlQuery query;
    query.exec("SELECT id, code, name, category, price, stock, expiry_date FROM products ORDER BY name");
    
    while (query.next()) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        
        for(int i = 0; i < 7; i++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            if (i == 4) { // Precio
                item->setText(QString::number(query.value(i).toDouble(), 'f', 2));
            } else if (i == 6) { // Fecha
                item->setText(query.value(i).toDate().toString("dd/MM/yyyy"));
            } else {
                item->setText(query.value(i).toString());
            }
            tableWidget->setItem(row, i, item);
        }
    }
}

void InventoryView::searchProducts()
{
    QString searchText = searchEdit->text();
    QString searchType = searchTypeCombo->currentText();
    QString column;
    
    if (searchType == "Nombre") column = "name";
    else if (searchType == "Código") column = "code";
    else column = "category";

    tableWidget->setRowCount(0);
    QSqlQuery query;
    query.prepare(QString("SELECT id, code, name, category, price, stock, expiry_date "
                         "FROM products WHERE %1 LIKE ? ORDER BY name").arg(column));
    query.addBindValue("%" + searchText + "%");
    
    if (query.exec()) {
        while (query.next()) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            
            for(int i = 0; i < 7; i++) {
                QTableWidgetItem *item = new QTableWidgetItem();
                if (i == 4) {
                    item->setText(QString::number(query.value(i).toDouble(), 'f', 2));
                } else if (i == 6) {
                    item->setText(query.value(i).toDate().toString("dd/MM/yyyy"));
                } else {
                    item->setText(query.value(i).toString());
                }
                tableWidget->setItem(row, i, item);
            }
        }
    }
}

void InventoryView::addProduct()
{
    if (!validateInputs()) {
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO products (code, name, category, price, stock, expiry_date) "
                 "VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(codeEdit->text());
    query.addBindValue(nameEdit->text());
    query.addBindValue(categoryCombo->currentText());
    query.addBindValue(priceEdit->text().toDouble());
    query.addBindValue(stockEdit->value());
    query.addBindValue(expiryEdit->date());

    if (query.exec()) {
        QMessageBox::information(this, "Éxito", "Producto agregado correctamente");
        clearInputs();
        refreshTable();
        loadCategories();
    } else {
        QMessageBox::critical(this, "Error", "Error al agregar el producto: " + query.lastError().text());
    }
}

void InventoryView::editProduct()
{
    QList<QTableWidgetItem*> items = tableWidget->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Por favor seleccione un producto para editar");
        return;
    }

    if (!validateInputs()) {
        return;
    }

    int row = tableWidget->row(items.first());
    QString id = tableWidget->item(row, 0)->text();

    QSqlQuery query;
    query.prepare("UPDATE products SET code=?, name=?, category=?, price=?, stock=?, expiry_date=? "
                 "WHERE id=?");
    query.addBindValue(codeEdit->text());
    query.addBindValue(nameEdit->text());
    query.addBindValue(categoryCombo->currentText());
    query.addBindValue(priceEdit->text().toDouble());
    query.addBindValue(stockEdit->value());
    query.addBindValue(expiryEdit->date());
    query.addBindValue(id);

    if (query.exec()) {
        QMessageBox::information(this, "Éxito", "Producto actualizado correctamente");
        clearInputs();
        refreshTable();
        loadCategories();
    } else {
        QMessageBox::critical(this, "Error", "Error al actualizar el producto: " + query.lastError().text());
    }
}

void InventoryView::deleteProduct()
{
    QList<QTableWidgetItem*> items = tableWidget->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Por favor seleccione un producto para eliminar");
        return;
    }

    int row = tableWidget->row(items.first());
    QString id = tableWidget->item(row, 0)->text();
    QString name = tableWidget->item(row, 2)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmar eliminación",
                                QString("¿Está seguro que desea eliminar el producto '%1'?").arg(name),
                                QMessageBox::Yes|QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM products WHERE id = ?");
        query.addBindValue(id);

        if (query.exec()) {
            QMessageBox::information(this, "Éxito", "Producto eliminado correctamente");
            clearInputs();
            refreshTable();
            loadCategories();
        } else {
            QMessageBox::critical(this, "Error", "Error al eliminar el producto: " + query.lastError().text());
        }
    }
}

void InventoryView::clearInputs()
{
    codeEdit->clear();
    nameEdit->clear();
    priceEdit->clear();
    stockEdit->setValue(0);
    expiryEdit->setDate(QDate::currentDate());
    categoryCombo->setCurrentIndex(0);
}

bool InventoryView::validateInputs()
{
    if (codeEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validación", "El código es obligatorio");
        return false;
    }
    if (nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validación", "El nombre es obligatorio");
        return false;
    }
    if (priceEdit->text().isEmpty() || priceEdit->text().toDouble() <= 0) {
        QMessageBox::warning(this, "Validación", "El precio debe ser mayor a 0");
        return false;
    }
    if (stockEdit->value() < 0) {
        QMessageBox::warning(this, "Validación", "El stock no puede ser negativo");
        return false;
    }
    if (expiryEdit->date() <= QDate::currentDate()) {
        QMessageBox::warning(this, "Validación", "La fecha de vencimiento debe ser futura");
        return false;
    }
    if (categoryCombo->currentText().isEmpty()) {
        QMessageBox::warning(this, "Validación", "La categoría es obligatoria");
        return false;
    }
    return true;
}
