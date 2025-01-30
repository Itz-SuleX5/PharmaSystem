#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

class User
{
public:
    User() = default;
    
private:
    QString username;
    QString password;
    QString role;
    QDateTime lastLogin;
};

#endif // USER_H
