#ifndef ADD_PAPERS_H
#define ADD_PAPERS_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QFormLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QPrinter>
#include <QPainter>
#include <QDebug>
#include <QComboBox>
#include <QFileDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QFile>
#include <QByteArray>
#include <QHBoxLayout>
#include <QMessageBox>
#include "Db_Class.h"
#include "paper.h"

class Add_Papers : public QWidget
{
    Q_OBJECT
public:
    explicit Add_Papers(QWidget *parent = nullptr);

    ~Add_Papers();

private:
    QPushButton *add,*cancel2;
    QVBoxLayout *vbox1,*vbox2;
    QHBoxLayout *hbox1,*hbox2;
    QWidget *add_widget;

    QTableView *table;
    QStandardItemModel *model;

    Db_Class db;

    QPushButton *add1,*cancel,*choose;
    QLabel *desc;
    QLineEdit *description;
    QVBoxLayout *vb1,*vb2;
    QHBoxLayout *hb1,*hb2,*hb3;
    QFormLayout *form1;


    Paper paper;
    void initialize();
    void initialize_add();
    void initialize_del();

signals:

public slots:
    void add_paper();
    void add_paper_to_db();
    void download_pdf(int);
    void select_file();
    void cancel_add();
    void delete_paper(int);
};

#endif // ADD_PAPERS_H
