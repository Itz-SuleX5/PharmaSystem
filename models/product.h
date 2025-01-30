#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QDate>

class Product
{
public:
    Product() = default;
    
private:
    QString code;
    QString name;
    QString category;
    double price;
    int stock;
    QDate expiryDate;
    int minStock;
};

#endif // PRODUCT_H
