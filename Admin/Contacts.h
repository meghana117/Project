#ifndef CONTACTS_H
#define CONTACTS_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QString>
#include <QComboBox>
#include <QMessageBox>
#include <QSignalMapper>
#include "Db_Class.h"
#include "contact_object.h"

class Contacts : public QWidget
{
    Q_OBJECT
public:
    explicit Contacts(QWidget *parent = nullptr);
    ~Contacts();
private:
    QPushButton *add,*cancel;
    QTableView *table;
    QStandardItemModel *model;
    QVBoxLayout *vb1,*vb2;
    QHBoxLayout *hb1,*hb2;
    QWidget *new_widget;
    Db_Class db;
    void initialize();
    void initialize_add();
    void initialize_update();


    QWidget *add_widget;
    QPushButton *add1,*cancel1;
    QFormLayout *form1;
    QVBoxLayout *vbox1;
    QHBoxLayout *hbox1,*hbox2,*hbox3,*hbox4,*hbox5,*hbox6,*hbox7;
    QLineEdit *name,*designation,*contact1,*contact2,*email;
    QLabel *name_label,*designation_label,*contact1_label,*contact2_label,*email_label,*error;

    QWidget *update_widget;
    QPushButton *update,*cancel2;
    QFormLayout *form2;
    QLineEdit *name_,*designation_,*contact1_,*contact2_,*email_;
    QLabel *name_label_,*designation_label_,*contact1_label_,*contact2_label_,*email_label_,*error_,*id;


signals:

public slots:
    void add_contact();
    void add_contact_to_db();
    void cancel_add();
    void delete_contact(int);
    void update_contact(int);
    void update_contact_to_db();
    void cancel_update();
};

#endif // CONTACTS_H
