#ifndef INVENTORYVIEW_H
#define INVENTORYVIEW_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSpinBox>

class InventoryView : public QWidget
{
    Q_OBJECT
public:
    explicit InventoryView(QWidget *parent = nullptr);

private slots:
    void addProduct();
    void editProduct();
    void deleteProduct();
    void searchProducts();
    void refreshTable();
    void loadCategories();

private:
    QTableWidget *tableWidget;
    QLineEdit *searchEdit;
    QComboBox *searchTypeCombo;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *refreshButton;

    // Campos para agregar/editar producto
    QLineEdit *nameEdit;
    QLineEdit *codeEdit;
    QLineEdit *priceEdit;
    QSpinBox *stockEdit;
    QDateEdit *expiryEdit;
    QComboBox *categoryCombo;

    void setupUI();
    void setupConnections();
    void clearInputs();
    bool validateInputs();
};

#endif // INVENTORYVIEW_H
