#ifndef SALESVIEW_H
#define SALESVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QSpinBox>
#include <QLabel>
#include <QMessageBox>
#include "../sale.h"

class SalesView : public QWidget
{
    Q_OBJECT
    
public:
    explicit SalesView(QWidget *parent = nullptr);
    
private slots:
    void onSearch();
    void onAddToCart();
    void onRemoveFromCart();
    void onProcessSale();
    void onGeneratePDF();
    
private:
    void setupUI();
    void loadProducts();
    void updateTotal();
    void clearCart();
    
    QLineEdit *searchEdit;
    QTableWidget *productsTable;
    QTableWidget *cartTable;
    QSpinBox *quantitySpinBox;
    QPushButton *addToCartButton;
    QPushButton *removeFromCartButton;
    QPushButton *processSaleButton;
    QPushButton *generatePDFButton;
    QLabel *totalLabel;
    
    float total;
    Sale currentSale;
};

#endif // SALESVIEW_H
