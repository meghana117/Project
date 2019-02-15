#include "company.h"

Company::Company(QWidget *parent) : QWidget(parent)
{

    table=new QTableView();
    model=new QStandardItemModel(1,6);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Comapany"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("No. of Intake"));
    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setGeometry(700,300,600,500);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->verticalHeader()->setDefaultSectionSize(50);

    add=new QPushButton("Add");
    close=new QPushButton("Close");

    vb1=new QVBoxLayout();
    hb1=new QHBoxLayout();

    vb1->addWidget(table);
    hb1->addWidget(add);
    hb1->addWidget(close);
    vb1->addLayout(hb1);
    this->setLayout(vb1);

    initialize();
    initialize_add();

    add_company->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    connect(add,SIGNAL(clicked(bool)),this,SLOT(add_comp()));
    connect(close,SIGNAL(clicked(bool)),this,SLOT(close()));


}
void Company::initialize()
{
    model->setRowCount(db.getCompanyCount());
    qDebug()<<db.getCompanyCount();
    int count=db.getCompanyCount();
    Company_Object companies[count];
    db.getCompanyDetail(companies);
    model->setColumnCount(2);
    for(int i=0;i<count;i++)
    {
        QStandardItem *item1=new QStandardItem(companies[i].company_name);
        model->setItem(i,0,item1) ;
        QString in=QString::number(companies[i].intake);
        QStandardItem *item2=new QStandardItem(in);
        model->setItem(i,1,item2);

    }
}
void Company::initialize_add()
{
    add1=new QPushButton("Add");
    add1->setAutoDefault(true);
    cancel=new QPushButton("Cancel");
    cancel->setAutoDefault(true);
    company_name=new QLabel("Company Name");
    company_edit=new QLineEdit();

    add_company=new QWidget();


    vbox1=new QVBoxLayout();
    hbox1=new QHBoxLayout();
    hbox2=new QHBoxLayout();

    hbox1->addWidget(company_name);
    hbox1->addWidget(company_edit);
    vbox1->addLayout(hbox1);

    hbox2->addWidget(add1);
    hbox2->addWidget(cancel);
    vbox1->addLayout(hbox2);


    add_company->setLayout(vbox1);
    add_company->setGeometry(700,300,300,100);

}

void Company::add_comp()
{
//    train.topic=
    add_company->show();
    this->setEnabled(false);

    connect(add1,SIGNAL(clicked(bool)),this,SLOT(add_company_to_db()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(cancel_add()));

}

void Company::add_company_to_db()
{
    company.company_name=company_edit->text();

    if(company.company_name==NULL)
    {
        msgBox.setText("Please enter valid values!");
        msgBox.exec();
    }
    else
    {
        if(db.add_company(company))
    {
        msgBox.setText("Company added successfully");
        msgBox.exec();
        company_edit->clear();
        this->initialize();
    }
    else {
        msgBox.setText("Company could not be added");
        msgBox.exec();
    }
    }
}
void Company::cancel_add()
{
    this->setEnabled(true);
    add_company->close();
}
Company::~Company()
{

}
