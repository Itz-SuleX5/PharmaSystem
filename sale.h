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
    QDateTime date;
    float total;
    int userId;
    QList<SaleItem> items;

    bool generatePDF(const QString &filePath) const;
};

#endif // SALE_H
