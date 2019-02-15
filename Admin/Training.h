#ifndef TRAINING_H
#define TRAINING_H

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
#include <QComboBox>
#include <QHeaderView>
#include <QScrollBar>
#include <QDate>
#include <QCalendarWidget>
#include <QMessageBox>
#include "Db_Class.h"
#include "training_object.h"

class Training : public QWidget
{
    Q_OBJECT
public:
    explicit Training(QWidget *parent = nullptr);
    ~Training();

private:
    Db_Class db;

    QPushButton *add,*del;
    QVBoxLayout *vb1;
    QHBoxLayout *hb1;
    QTableView *table;
    QStandardItemModel *model;

    QWidget *add_training,*del_training;
    QLabel *topic,*detail,*from,*to;
    QLineEdit *topic_edit;
    QTextEdit *detail_edit;
    QCalendarWidget *cal1,*cal2;
    QPushButton *calButton1,*calButton2,*add1,*cancel;
    QDate date1,date2;
    QVBoxLayout *vbox1;
    QHBoxLayout *hbox1,*hbox2,*hbox3,*hbox4,*hbox5;
    Training_Object train;
    QMessageBox msgBox;
    QLabel *topic_name;
    QComboBox *topics;
    QPushButton *del1;
    QVBoxLayout *vb;
    QHBoxLayout *hbx1,*hbx2;
    QPushButton *cancel1;


    void initialize_add();
    void initialize_del();
    void initialize();


signals:

public slots:
    void add_train();
    void onDateSelected1(QDate);
    void onDateSelected2(QDate);
    void add_training_to_db();
    void delete_training();
    void delete_train();
    void cancel_del();
    void cancel_add();

};

#endif // TRAINING_H
