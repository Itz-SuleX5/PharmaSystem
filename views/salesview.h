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
#include <QDoubleSpinBox>
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
    void onAmountPaidChanged(double value);
    
private:
    void setupUI();
    void loadProducts();
    void updateTotal();
    void clearCart();
    void updateChange();
    
    QLineEdit *searchEdit;
    QLineEdit *customerNameEdit;
    QTableWidget *productsTable;
    QTableWidget *cartTable;
    QSpinBox *quantitySpinBox;
    QDoubleSpinBox *amountPaidSpinBox;
    QPushButton *addToCartButton;
    QPushButton *removeFromCartButton;
    QPushButton *processSaleButton;
    QPushButton *generatePDFButton;
    QLabel *totalLabel;
    QLabel *changeLabel;
    
    float total;
    float change;
    Sale currentSale;
};

#endif // SALESVIEW_H
