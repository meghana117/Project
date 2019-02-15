#ifndef CRITERIA_OBJECT_H
#define CRITERIA_OBJECT_H

#include <QString>

class Criteria_object
{
public:
    Criteria_object();
    ~Criteria_object();
    QString dept,company,combo,placed_status;
    double cgpa,ten,twelve;
    int backlogs;
};

#endif // CRITERIA_OBJECT_H
