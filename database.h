#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>

class Database
{
public:
    Database();
    bool open();
    void close();
    bool validateUser(const QString &username, const QString &password, QString &role);

private:
    QSqlDatabase db;
    bool createTables();
    bool createDefaultAdmin();
};

#endif // DATABASE_H
