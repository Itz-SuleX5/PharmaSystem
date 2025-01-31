#include <QApplication>
#include "mainwindow.h"
#include "database.h"
#include "views/login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Database db;
    if (!db.open()) {
        return 1;
    }

    Login w;
    w.show();

    return a.exec();
}
