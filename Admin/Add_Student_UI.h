#ifndef ADD_STUDENT_UI_H
#define ADD_STUDENT_UI_H

#include <QWidget>
#include<QCalendarWidget>
#include<QRegExp>
#include<QValidator>
#include<QComboBox>
#include<QLineEdit>
#include <QFormLayout>
#include<QLabel>
#include<QString>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QDateEdit>
#include<QPushButton>
#include<QDoubleSpinBox>
#include<QSpinBox>
#include<QMessageBox>
#include <QDebug>
#include<QFileDialog>
#include "Db_Class.h"
#include "Student.h"



class Add_Student_UI : public QWidget
{
    Q_OBJECT
public:
    explicit Add_Student_UI(QWidget *parent = nullptr);
    ~Add_Student_UI();



private:
    QLabel *name,*usn,*dob,*email,*dept,*contact,*backlog,*cgpa,*error,*ten,*twelve,*or_label,*selecetd_file,*sems,*sem1,*sem2,*sem3,*sem4,*sem5,*sem6,*sem7,*sem8;
    QDoubleSpinBox *cgpa_edit,*ten_edit,*twelve_edit,*sem1_edit,*sem2_edit,*sem3_edit,*sem4_edit,*sem5_edit,*sem6_edit,*sem7_edit,*sem8_edit;
    QComboBox *dept_edit;
    QCalendarWidget *m_cal;
        QDate m_date;
    QDateEdit *DOB;
    QSpinBox *backlog_edit,*sems_edit;
    QPushButton *add,*cancel,*m_calButton,*add_csv,*choose_csv;
    QLineEdit *name_edit,*usn_edit,*pass_edit,*email_edit,*contact_edit;
    QVBoxLayout *vb1,*vb2,*vb3;
    QHBoxLayout *hb1,*hb2,*hb3,*hb4,*hb5,*hb6,*hb7,*hb8,*hb9,*hb10,*hb11,*hb12,*hb13,*hb14,*hb15;
    QFormLayout *form1;
    Db_Class db;
    QString fileName;




signals:

public slots:
    void onDateSelected(QDate);
        void add_stud();
        void toUpper(QString);
        void choose_file();
        void add_file();
        void cgpa_value(double);
        void disable_sgpa(int);
};

#endif // ADD_STUDENT_UI_H
