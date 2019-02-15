#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include "Admin.h"
#include "Db_Class.h"

class Login : public QObject
{
    Q_OBJECT
public:
    explicit Login(QObject *parent = nullptr);
    ~Login();

    bool check_log(Admin);

signals:

public slots:
};

#endif // LOGIN_H
