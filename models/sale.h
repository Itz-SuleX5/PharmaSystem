#ifndef SALE_H
#define SALE_H

#include <QString>
#include <QDateTime>

class Sale
{
public:
    Sale() = default;
    
private:
    QString invoiceNumber;
    int userId;
    double totalAmount;
    QDateTime saleDate;
};

#endif // SALE_H
