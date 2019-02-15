#ifndef PLACEMENT_H
#define PLACEMENT_H

#include <QWidget>
#include <QWidget>
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QHeaderView>
#include <QComboBox>
#include <QDate>
#include <QCalendarWidget>
#include <QMessageBox>
#include "Db_Class.h"
#include "placement_object.h"


class Placement : public QWidget
{
    Q_OBJECT
public:
    explicit Placement(QWidget *parent = nullptr);
    ~Placement();

private:
    Db_Class db;

    QPushButton *add,*del;
    QVBoxLayout *vb1;
    QHBoxLayout *hb1;
    QTableView *table;
    QStandardItemModel *model;

    QWidget *add_placement,*del_placement;
    QLabel *company,*title,*eligibility,*date,*venue,*package;
    QLineEdit *company_edit,*venue_edit,*package_edit,*title_edit;
    QTextEdit *eligibility_edit;
    QCalendarWidget *cal;
    QPushButton *calButton,*add1,*cancel;
    QDate date1;
    QVBoxLayout *vbox1;
    QHBoxLayout *hbox1,*hbox2,*hbox3,*hbox4,*hbox5,*hbox6,*hbox7;
    Placement_Object place;
    QMessageBox msgBox;


    QLabel *company_name;
    QComboBox *companies;
    QPushButton *del1;
    QVBoxLayout *vb;
    QHBoxLayout *hbx1,*hbx2;
    QPushButton *cancel1;

    void initialize_add();
    void initialize_del();
    void initialize();


signals:

public slots:
    void add_place();
    void onDateSelected(QDate);
    void add_placement_to_db();
    void delete_placement();
    void delete_place();
    void cancel_del();
    void cancel_add();

};

#endif // PLACEMENT_H

