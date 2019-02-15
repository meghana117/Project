#include "Login.h"

Login::Login(QObject *parent) : QObject(parent)
{

}

bool Login::check_log(Admin ad)
{
    bool present;
    Db_Class db;
    present=db.checklog(ad);
    if(present)
    {
        return true;
    }
    else {
        return false;
    }
}

Login::~Login()
{

}
