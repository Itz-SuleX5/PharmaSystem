#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>

Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("pharmacy.db");
}

bool Database::open()
{
    if (!db.open()) {
        qDebug() << "Error al abrir la base de datos:" << db.lastError().text();
        return false;
    }
    
    if (!createTables()) {
        qDebug() << "Error al crear las tablas";
        return false;
    }
    
    if (!createDefaultAdmin()) {
        qDebug() << "Error al crear el administrador por defecto";
        return false;
    }
    
    return true;
}

void Database::close()
{
    db.close();
}

bool Database::createTables()
{
    QSqlQuery query;
    
    // Users table
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "username TEXT UNIQUE NOT NULL,"
                   "password TEXT NOT NULL,"
                   "role TEXT NOT NULL,"
                   "created_at DATETIME DEFAULT CURRENT_TIMESTAMP)")) {
        qDebug() << "Error creating users table:" << query.lastError().text();
        return false;
    }
    
    // Products table
    if (!query.exec("CREATE TABLE IF NOT EXISTS products ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "code TEXT UNIQUE NOT NULL,"
                   "name TEXT NOT NULL,"
                   "category TEXT NOT NULL,"
                   "price REAL NOT NULL,"
                   "stock INTEGER NOT NULL,"
                   "min_stock INTEGER DEFAULT 10,"
                   "expiry_date DATE NOT NULL)")) {
        qDebug() << "Error creating products table:" << query.lastError().text();
        return false;
    }
    
    // Suppliers table
    if (!query.exec("CREATE TABLE IF NOT EXISTS suppliers ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "name TEXT NOT NULL,"
                   "contact TEXT NOT NULL,"
                   "phone TEXT NOT NULL,"
                   "email TEXT NOT NULL,"
                   "address TEXT NOT NULL)")) {
        qDebug() << "Error creating suppliers table:" << query.lastError().text();
        return false;
    }
    
    // Sales table
    if (!query.exec("CREATE TABLE IF NOT EXISTS sales ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "date DATETIME NOT NULL,"
                   "total REAL NOT NULL,"
                   "user_id INTEGER,"
                   "FOREIGN KEY(user_id) REFERENCES users(id))")) {
        qDebug() << "Error creating sales table:" << query.lastError().text();
        return false;
    }
    
    // Sale items table
    if (!query.exec("CREATE TABLE IF NOT EXISTS sale_items ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "sale_id INTEGER NOT NULL,"
                   "product_id INTEGER NOT NULL,"
                   "quantity INTEGER NOT NULL,"
                   "price REAL NOT NULL,"
                   "FOREIGN KEY(sale_id) REFERENCES sales(id),"
                   "FOREIGN KEY(product_id) REFERENCES products(id))")) {
        qDebug() << "Error creating sale_items table:" << query.lastError().text();
        return false;
    }
    
    // Purchases table
    if (!query.exec("CREATE TABLE IF NOT EXISTS purchases ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "date DATETIME NOT NULL,"
                   "total REAL NOT NULL,"
                   "supplier_id INTEGER NOT NULL,"
                   "FOREIGN KEY(supplier_id) REFERENCES suppliers(id))")) {
        qDebug() << "Error creating purchases table:" << query.lastError().text();
        return false;
    }
    
    // Purchase items table
    if (!query.exec("CREATE TABLE IF NOT EXISTS purchase_items ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "purchase_id INTEGER NOT NULL,"
                   "product_id INTEGER NOT NULL,"
                   "quantity INTEGER NOT NULL,"
                   "price REAL NOT NULL,"
                   "FOREIGN KEY(purchase_id) REFERENCES purchases(id),"
                   "FOREIGN KEY(product_id) REFERENCES products(id))")) {
        qDebug() << "Error creating purchase_items table:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool Database::createDefaultAdmin()
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users");
    if (query.exec() && query.next() && query.value(0).toInt() == 0) {
        QString password = QString(QCryptographicHash::hash("admin123", QCryptographicHash::Sha256).toHex());
        
        query.prepare("INSERT INTO users (username, password, role) VALUES (?, ?, ?)");
        query.addBindValue("admin");
        query.addBindValue(password);
        query.addBindValue("admin");
        
        if (!query.exec()) {
            qDebug() << "Error creating default admin:" << query.lastError().text();
            return false;
        }
    }
    return true;
}

bool Database::validateUser(const QString &username, const QString &password, QString &role)
{
    QSqlQuery query;
    query.prepare("SELECT role FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex()));
    
    if (query.exec() && query.next()) {
        role = query.value(0).toString();
        return true;
    }
    return false;
}
