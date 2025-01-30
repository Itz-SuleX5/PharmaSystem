#include "supplierview.h"
#include <QHeaderView>
#include <QRegularExpression>

SupplierView::SupplierView(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    setupConnections();
    refreshTable();
}

void SupplierView::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Search section
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Buscar proveedores...");
    searchLayout->addWidget(searchEdit);
    mainLayout->addLayout(searchLayout);

    // Table
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(6);
    tableWidget->setHorizontalHeaderLabels({
        "ID", "Nombre", "Contacto", "Teléfono", "Email", "Dirección"
    });
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(tableWidget);

    // Input form
    QGridLayout *formLayout = new QGridLayout();
    
    nameEdit = new QLineEdit(this);
    contactEdit = new QLineEdit(this);
    phoneEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);
    addressEdit = new QLineEdit(this);

    formLayout->addWidget(new QLabel("Nombre:"), 0, 0);
    formLayout->addWidget(nameEdit, 0, 1);
    formLayout->addWidget(new QLabel("Contacto:"), 0, 2);
    formLayout->addWidget(contactEdit, 0, 3);
    formLayout->addWidget(new QLabel("Teléfono:"), 1, 0);
    formLayout->addWidget(phoneEdit, 1, 1);
    formLayout->addWidget(new QLabel("Email:"), 1, 2);
    formLayout->addWidget(emailEdit, 1, 3);
    formLayout->addWidget(new QLabel("Dirección:"), 2, 0);
    formLayout->addWidget(addressEdit, 2, 1, 1, 3);

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

void SupplierView::setupConnections()
{
    connect(addButton, &QPushButton::clicked, this, &SupplierView::addSupplier);
    connect(editButton, &QPushButton::clicked, this, &SupplierView::editSupplier);
    connect(deleteButton, &QPushButton::clicked, this, &SupplierView::deleteSupplier);
    connect(refreshButton, &QPushButton::clicked, this, &SupplierView::refreshTable);
    connect(searchEdit, &QLineEdit::textChanged, this, &SupplierView::searchSuppliers);
}

void SupplierView::refreshTable()
{
    tableWidget->setRowCount(0);
    QSqlQuery query;
    query.exec("SELECT id, name, contact, phone, email, address FROM suppliers ORDER BY name");
    
    while (query.next()) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        
        for(int i = 0; i < 6; i++) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(i).toString());
            tableWidget->setItem(row, i, item);
        }
    }
}

void SupplierView::searchSuppliers()
{
    QString searchText = searchEdit->text();
    tableWidget->setRowCount(0);
    
    QSqlQuery query;
    query.prepare("SELECT id, name, contact, phone, email, address FROM suppliers "
                 "WHERE name LIKE ? OR contact LIKE ? ORDER BY name");
    query.addBindValue("%" + searchText + "%");
    query.addBindValue("%" + searchText + "%");
    
    if (query.exec()) {
        while (query.next()) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            
            for(int i = 0; i < 6; i++) {
                QTableWidgetItem *item = new QTableWidgetItem(query.value(i).toString());
                tableWidget->setItem(row, i, item);
            }
        }
    }
}

void SupplierView::addSupplier()
{
    if (!validateInputs()) {
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO suppliers (name, contact, phone, email, address) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(nameEdit->text());
    query.addBindValue(contactEdit->text());
    query.addBindValue(phoneEdit->text());
    query.addBindValue(emailEdit->text());
    query.addBindValue(addressEdit->text());

    if (query.exec()) {
        QMessageBox::information(this, "Éxito", "Proveedor agregado correctamente");
        clearInputs();
        refreshTable();
    } else {
        QMessageBox::critical(this, "Error", "Error al agregar el proveedor: " + query.lastError().text());
    }
}

void SupplierView::editSupplier()
{
    QList<QTableWidgetItem*> items = tableWidget->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Por favor seleccione un proveedor para editar");
        return;
    }

    if (!validateInputs()) {
        return;
    }

    int row = tableWidget->row(items.first());
    QString id = tableWidget->item(row, 0)->text();

    QSqlQuery query;
    query.prepare("UPDATE suppliers SET name=?, contact=?, phone=?, email=?, address=? WHERE id=?");
    query.addBindValue(nameEdit->text());
    query.addBindValue(contactEdit->text());
    query.addBindValue(phoneEdit->text());
    query.addBindValue(emailEdit->text());
    query.addBindValue(addressEdit->text());
    query.addBindValue(id);

    if (query.exec()) {
        QMessageBox::information(this, "Éxito", "Proveedor actualizado correctamente");
        clearInputs();
        refreshTable();
    } else {
        QMessageBox::critical(this, "Error", "Error al actualizar el proveedor: " + query.lastError().text());
    }
}

void SupplierView::deleteSupplier()
{
    QList<QTableWidgetItem*> items = tableWidget->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Por favor seleccione un proveedor para eliminar");
        return;
    }

    int row = tableWidget->row(items.first());
    QString id = tableWidget->item(row, 0)->text();
    QString name = tableWidget->item(row, 1)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmar eliminación",
                                QString("¿Está seguro que desea eliminar el proveedor '%1'?").arg(name),
                                QMessageBox::Yes|QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM suppliers WHERE id = ?");
        query.addBindValue(id);

        if (query.exec()) {
            QMessageBox::information(this, "Éxito", "Proveedor eliminado correctamente");
            clearInputs();
            refreshTable();
        } else {
            QMessageBox::critical(this, "Error", "Error al eliminar el proveedor: " + query.lastError().text());
        }
    }
}

void SupplierView::clearInputs()
{
    nameEdit->clear();
    contactEdit->clear();
    phoneEdit->clear();
    emailEdit->clear();
    addressEdit->clear();
}

bool SupplierView::validateInputs()
{
    if (nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validación", "El nombre es obligatorio");
        return false;
    }
    if (contactEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validación", "El contacto es obligatorio");
        return false;
    }
    if (phoneEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validación", "El teléfono es obligatorio");
        return false;
    }
    
    QRegularExpression emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b");
    if (!emailRegex.match(emailEdit->text()).hasMatch()) {
        QMessageBox::warning(this, "Validación", "El email no es válido");
        return false;
    }
    
    if (addressEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validación", "La dirección es obligatoria");
        return false;
    }
    return true;
}
