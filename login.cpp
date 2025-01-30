#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "database.h"
#include <QMessageBox>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowTitle("Iniciar Sesión");
    
    // Conectar el botón de login
    connect(ui->loginButton, &QPushButton::clicked, this, &Login::on_loginButton_clicked);
    
    // Permitir login con Enter
    connect(ui->passwordInput, &QLineEdit::returnPressed, this, &Login::on_loginButton_clicked);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor ingrese usuario y contraseña");
        return;
    }
    
    Database db;
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "No se pudo conectar a la base de datos");
        return;
    }
    
    QString role;
    if (db.validateUser(username, password, role)) {
        MainWindow *mainWindow = new MainWindow(role);
        mainWindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos");
    }
}
