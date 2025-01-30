#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <QString>

class Supplier
{
public:
    Supplier() = default;
    
private:
    QString name;
    QString contactPerson;
    QString phone;
    QString email;
    QString address;
};

#endif // SUPPLIER_H
