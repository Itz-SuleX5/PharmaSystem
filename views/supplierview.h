#ifndef SUPPLIERVIEW_H
#define SUPPLIERVIEW_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

class SupplierView : public QWidget
{
    Q_OBJECT
public:
    explicit SupplierView(QWidget *parent = nullptr);

private slots:
    void addSupplier();
    void editSupplier();
    void deleteSupplier();
    void searchSuppliers();
    void refreshTable();

private:
    QTableWidget *tableWidget;
    QLineEdit *searchEdit;
    
    // Campos para agregar/editar proveedor
    QLineEdit *nameEdit;
    QLineEdit *contactEdit;
    QLineEdit *phoneEdit;
    QLineEdit *emailEdit;
    QLineEdit *addressEdit;

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *refreshButton;

    void setupUI();
    void setupConnections();
    void clearInputs();
    bool validateInputs();
};

#endif // SUPPLIERVIEW_H
