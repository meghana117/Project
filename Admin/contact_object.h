#ifndef CONTACT_OBJECT_H
#define CONTACT_OBJECT_H

#include <QString>

class Contact_Object
{
public:
    Contact_Object();
    ~Contact_Object();

    QString name,designation,email,contact1,contact2;
    int id;

};

#endif // CONTACT_OBJECT_H
