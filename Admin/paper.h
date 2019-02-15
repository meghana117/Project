#ifndef PAPER_H
#define PAPER_H

#include <QString>
#include <QByteArray>
class Paper
{
public:
    Paper();
    ~Paper();
    QString name;
    QByteArray file;
    int id;
};

#endif // PAPER_H
