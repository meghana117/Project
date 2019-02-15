#ifndef DB_CLASS_H
#define DB_CLASS_H

#include <QObject>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlError>
#include<QtSql/QSqlQuery>
#include<QDebug>
#include "training_object.h"
#include "Admin.h"
#include<QDir>
#include<QByteArray>
#include "Student.h"
#include "placement_object.h"
#include "placed_object.h"
#include "company_object.h"
#include "paper.h"
#include "contact_object.h"
#include "criteria_object.h"


class Db_Class : public QObject
{
    Q_OBJECT
public:
    explicit Db_Class(QObject *parent = nullptr);
    ~Db_Class();
    bool checklog(Admin);
    bool add_student(Student student);
    Student search_student(Student);
    bool update_student(Student);
    bool delete_student(Student);

    bool add_training(Training_Object);
    int getTrainingCount();
    void getTrainingDetail(Training_Object[]);
    bool delete_training(QString);

    bool add_placement(Placement_Object);
    int getPlacementCount();
    void getPlacementDetail(Placement_Object[]);
    bool delete_placement(QString);

    bool add_company(Company_Object);
    int getCompanyCount();
    void getCompanyDetail(Company_Object[]);

    bool add_placed(Placed_object);
    int getPlacedCount();
    void getPlacedDetail(Placed_object[]);
    bool delete_placed(QString,QString);
    QString get_name(QString);
    QString get_dept(QString);

    int get_usn_placed_count(QString);
    void get_placed_companies(Company_Object[],QString);

    bool add_paper_to_db(Paper);
    bool delete_papers(int);
    int getpapersCount();
    void getPaperDetail(Paper[]);
    Paper getBlob(int);

    bool add_contact_to_db(Contact_Object);
    bool delete_contact(int);
    bool update_contact(Contact_Object);
    int getContactCount();
    void getContactDetail(Contact_Object[]);
    Contact_Object getContact(int);
    bool savedata(QString);

    bool get_list(Criteria_object,Student[]);
    int get_count(Criteria_object);


signals:

public slots:
};

#endif // DB_CLASS_H
