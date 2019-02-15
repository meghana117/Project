#ifndef SELECTSTUDENTS_H
#define SELECTSTUDENTS_H

#include <QWidget>
#include <QComboBox>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCoreApplication>
#include <QFile>
#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include <QStandardItemModel>
#include <QSpinBox>
#include <QHeaderView>
#include <QDoubleSpinBox>
#include <Db_Class.h>
#include "company_object.h"
#include "criteria_object.h"

class SelectStudents : public QWidget
{
    Q_OBJECT
public:
    explicit SelectStudents(QWidget *parent = nullptr);
    ~SelectStudents();

private:

    QLabel *Select,*Department,*Company,*Placed_Status,*Tenth,*Twelve,*Cgpa,*back;
    QPushButton *save,*cancel,*search;
    QComboBox *dept,*company,*combo,*placed;
    QDoubleSpinBox *ten,*twelve,*cgpa;
    QSpinBox *backlog;
    QTableView *table;
    QStandardItemModel *model;

    QVBoxLayout *vb1,*vb2;
    QHBoxLayout *hb1,*hb2,*hb3,*hb4,*hb5,*hb6,*hb7;

    Db_Class db;

    void initialize();

signals:

public slots:

    void combo_changed(const QString &);
    void placed_changed(const QString &);
    void search_db();
    void save_file();
};

#endif // SELECTSTUDENTS_H
