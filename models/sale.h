#ifndef SALE_H
#define SALE_H

#include <QString>
#include <QDateTime>
#include <QList>

struct SaleItem {
    int productId;
    QString productName;
    int quantity;
    float price;
};

class Sale {
public:
    int id;
    QString customerName;
    QDateTime date;
    float total;
    float amountPaid;
    float change;
    QList<SaleItem> items;

    bool generatePDF(const QString &filePath);
};

#endif // SALE_H
