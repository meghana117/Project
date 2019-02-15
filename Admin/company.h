#ifndef COMPANY_H
#define COMPANY_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QLabel>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QMessageBox>
#include "Db_Class.h"
#include "company_object.h"

class Company : public QWidget
{
    Q_OBJECT
public:
    explicit Company(QWidget *parent = nullptr);
    ~Company();

private:
    Db_Class db;

    QPushButton *add,*close;
    QVBoxLayout *vb1;
    QHBoxLayout *hb1;
    QTableView *table;
    QStandardItemModel *model;

    QWidget *add_company;
    QLabel *company_name;
    QLineEdit *company_edit;
    QPushButton *add1,*cancel;
    QVBoxLayout *vbox1;
    QHBoxLayout *hbox1,*hbox2;
    QMessageBox msgBox;

    Company_Object company;

    void initialize_add();
    void initialize();


signals:

public slots:
    void add_comp();
    void cancel_add();
    void add_company_to_db();

};

#endif // COMPANY_H
