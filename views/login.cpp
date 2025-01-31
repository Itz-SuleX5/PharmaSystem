#include "login.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>

Login::Login(QWidget *parent) : QWidget(parent)
{
    setupUI();
    connect(loginButton, &QPushButton::clicked, this, &Login::onLoginClicked);
}

void Login::setupUI()
{
    setWindowTitle("Login - Sistema de Farmacia");
    setFixedSize(300, 200);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    QLabel *titleLabel = new QLabel("Iniciar Sesión", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    mainLayout->addSpacing(20);

    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Usuario");
    mainLayout->addWidget(usernameEdit);

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Contraseña");
    passwordEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(passwordEdit);

    mainLayout->addSpacing(10);

    loginButton = new QPushButton("Ingresar", this);
    loginButton->setFixedHeight(35);
    mainLayout->addWidget(loginButton);
}

void Login::onLoginClicked()
{
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor ingrese usuario y contraseña");
        return;
    }

    // Hash the password
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(QString::fromLatin1(hashedPassword));

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Error al verificar credenciales: " + query.lastError().text());
        return;
    }

    if (query.next()) {
        MainWindow *mainWindow = new MainWindow(username);
        mainWindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos");
        passwordEdit->clear();
        passwordEdit->setFocus();
    }
} 