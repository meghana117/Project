#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{
public:
    Student();
    QString usn,password,name,email,dept,contact,dob;
    float ten,twelve,cgpa,sem1,sem2,sem3,sem4,sem5,sem6,sem7,sem8;
    int offer,backlogs;

    ~Student();
};

#endif // STUDENT_H
