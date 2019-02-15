#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "Admin.h"
#include "Login.h"
#include "Welcome.h"
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();


private:
    QVBoxLayout *vb1,*vb2;
    QHBoxLayout *hb1,*hb2,*hb3,*hb4,*hb5;
    QPushButton *login;
    QLineEdit *uname,*upass;
    QLabel *name,*pass,*head,*showlabel;
    Welcome welcome;

public slots:
    void check();

};

#endif // MAINWIDGET_H
