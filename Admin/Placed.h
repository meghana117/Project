#ifndef PLACED_H
#define PLACED_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QComboBox>
#include <QMessageBox>
#include "company_object.h"
#include "Db_Class.h"
#include "placed_object.h"

class Placed : public QWidget
{
    Q_OBJECT
public:
    explicit Placed(QWidget *parent = nullptr);
    ~Placed();

private:
    Db_Class db;

    QPushButton *add,*del;
    QVBoxLayout *vb1;
    QHBoxLayout *hb1;
    QTableView *table;
    QStandardItemModel *model;

    QWidget *add_placed,*del_placed;


    QLabel *company,*usn,*salary;
    QLineEdit *usn_edit,*salary_edit;
    QComboBox *company_list;
    QPushButton *add1,*cancel;
    QVBoxLayout *vbox1;
    QHBoxLayout *hbox1,*hbox2,*hbox3,*hbox4,*hbox5,*hbox6,*hbox7;
    Placed_object placed;
    QMessageBox msgBox;


    QLabel *USN,*company_selected;
    QLineEdit *USNEdit;
    QComboBox *companies;
    QPushButton *del1;
    QVBoxLayout *vb;
    QHBoxLayout *hbx1,*hbx2,*hbx3;
    QPushButton *cancel1;

    Company_Object comp;

public:
    void initialize_add();
    void initialize_del();
    void initialize();


signals:

public slots:
    void add_place();
    void delete_placed();
    void add_placed_to_db();
    void delete_place();
    void usnedited(QString);
    void cancel_add();
    void cancel_del();
    void toUpper(QString);
};

#endif // PLACED_H
