#include "Placed.h"

Placed::Placed(QWidget *parent) : QWidget(parent)
{
    table=new QTableView();
    model=new QStandardItemModel(1,4);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("USN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Company"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Package (in lpa) "));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Department "));
    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setGeometry(700,300,700,500);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->verticalHeader()->setDefaultSectionSize(50);



    add=new QPushButton("Add");
    del=new QPushButton("Delete");

    vb1=new QVBoxLayout();
    hb1=new QHBoxLayout();

    vb1->addWidget(table);
    hb1->addWidget(add);
    hb1->addWidget(del);
    vb1->addLayout(hb1);
    this->setLayout(vb1);

    initialize();
    initialize_add();
    initialize_del();

    table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    connect(add,SIGNAL(clicked(bool)),this,SLOT(add_place()));
    connect(del,SIGNAL(clicked(bool)),this,SLOT(delete_placed()));

}

void Placed::initialize()
{
    model->setRowCount(db.getPlacedCount());
    int count=db.getPlacedCount();
    Placed_object placed[count];
    db.getPlacedDetail(placed);
    model->setColumnCount(4);
    for(int i=0;i<count;i++)
    {
        QStandardItem *item1=new QStandardItem(placed[i].USN);
        model->setItem(i,0,item1) ;

        QStandardItem *item2=new QStandardItem(db.get_name(placed[i].USN));
        model->setItem(i,1,item2);

        QStandardItem *item3=new QStandardItem(placed[i].company);
        model->setItem(i,2,item3);

        QString pack=QString::number(placed[i].salary);
        QStandardItem *item4=new QStandardItem(pack);
        model->setItem(i,3,item4);

        QStandardItem *item5=new QStandardItem(db.get_dept(placed[i].USN));
        model->setItem(i,4,item5);

    }
}
void Placed::initialize_add()
{
    add1=new QPushButton("Add");
    add1->setAutoDefault(true);
    cancel=new QPushButton("Cancel");
    cancel->setAutoDefault(true);

    company=new QLabel("Company");
    usn=new QLabel("USN");
    salary=new QLabel("Salary");

    QRegExp expusn("^[1]{1}[Dd]{1}[Aa]{1}[0-9]{2}[A-Za-z]{2}[0-9]{3}$/i");
    QRegExpValidator *validate_usn=new QRegExpValidator(expusn,this);
    usn_edit=new QLineEdit();
    usn_edit->setValidator(validate_usn);

    salary_edit=new QLineEdit();
    company_list=new QComboBox();

    Company_Object comp[db.getCompanyCount()];
    company_list->clear();
    db.getCompanyDetail(comp);
    for(int i=0;i<db.getCompanyCount();i++)
    {
        company_list->addItem(comp[i].company_name);
    }

    add_placed=new QWidget();

    vbox1=new QVBoxLayout();
    hbox1=new QHBoxLayout();
    hbox2=new QHBoxLayout();
    hbox3=new QHBoxLayout();
    hbox4=new QHBoxLayout();
    hbox5=new QHBoxLayout();


    hbox1->addWidget(usn);
    hbox1->addWidget(usn_edit);
    vbox1->addLayout(hbox1);

    hbox2->addWidget(company);
    hbox2->addWidget(company_list);
    vbox1->addLayout(hbox2);

    hbox4->addWidget(salary);
    hbox4->addWidget(salary_edit);
    vbox1->addLayout(hbox4);

    hbox5->addWidget(add1);
    hbox5->addWidget(cancel);
    vbox1->addLayout(hbox5);


    add_placed->setLayout(vbox1);
    add_placed->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    add_placed->setGeometry(700,300,300,100);

    connect(usn_edit,SIGNAL(textEdited(QString)),this,SLOT(toUpper(QString)));



}
void Placed::initialize_del()
{
    del_placed=new QWidget();
    USN=new QLabel("Enter Student usn");

    QRegExp expusn("^[1]{1}[Dd]{1}[Aa]{1}[0-9]{2}[A-Za-z]{2}[0-9]{3}$/i");
    QRegExpValidator *validate_usn=new QRegExpValidator(expusn,this);
    USNEdit=new QLineEdit();
    USNEdit->setValidator(validate_usn);

    companies=new QComboBox();
    company_selected=new QLabel("Selected company");
    del1=new QPushButton("Delete");
    del1->setAutoDefault(true);
    cancel1=new QPushButton("Cancel");
    cancel1->setAutoDefault(true);
    vb=new QVBoxLayout();
    hbx1=new QHBoxLayout();
    hbx2=new QHBoxLayout();
    hbx3=new QHBoxLayout();

    hbx1->addWidget(USN);
    hbx1->addWidget(USNEdit);
    vb->addLayout(hbx1);

    hbx2->addWidget(company_selected);
    hbx2->addWidget(companies);
    vb->addLayout(hbx2);

    hbx3->addWidget(del1);
    hbx3->addWidget(cancel1);
    vb->addLayout(hbx3);

    del_placed->setLayout(vb);

    del_placed->setGeometry(700,300,300,100);

    del_placed->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    connect(USNEdit,SIGNAL(textEdited(QString)),this,SLOT(usnedited(QString)));

}

void Placed::add_place()
{
//    train.topic=
    add_placed->show();
    this->setEnabled(false);

    connect(add1,SIGNAL(clicked(bool)),this,SLOT(add_placed_to_db()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(cancel_add()));

}

void Placed::add_placed_to_db()
{
    Placed_object placed;
    placed.company=company_list->currentText();
    placed.USN=usn_edit->text();
    placed.salary=salary_edit->text().toFloat();

    if(placed.company==NULL)
    {
        msgBox.setText("Please select valid company!");
        msgBox.exec();
    }

    if(placed.USN==NULL)
    {
        msgBox.setText("Please enter valid USN!");
        msgBox.exec();
    }
    if(placed.salary==NULL)
    {
        msgBox.setText("Please enter valid salary!");
        msgBox.exec();
    }
    else
    {
        if(db.add_placed(placed))
    {
        msgBox.setText("Placed details added successfully");
        msgBox.exec();
//        company_list->clear();
        usn_edit->clear();
        salary_edit->clear();

        this->initialize();
    }
    else {
        msgBox.setText("Invalid USN or salary");
        msgBox.exec();
    }
    }
}

void Placed::delete_placed()
{
    del_placed->show();
    this->setEnabled(false);
    connect(del1,SIGNAL(clicked(bool)),this,SLOT(delete_place()));
    connect(cancel1,SIGNAL(clicked(bool)),this,SLOT(cancel_del()));

}
void Placed::delete_place()
{

    QString Susn;
    Susn=USNEdit->text();

    if(Susn==NULL || Susn.length()<10 || companies->currentText()=="")
    {
        msgBox.setText("Enter valid USN or company name");
        msgBox.exec();
    }

    else if(db.delete_placed(companies->currentText(),Susn))
    {
        msgBox.setText("Placed deleted successfully");
        msgBox.exec();
        delete_placed();
        this->initialize();
    }
    else {
        msgBox.setText("COuldn't delete Placed details");
        msgBox.exec();
    }
}
void Placed::usnedited(QString txt)
{
    USNEdit->setText(txt.toUpper());
//    int count=0;

//    if(txt.length()==10)
//    {
//         count=db.get_usn_placed_count(txt);
//         qDebug()<<"Value of count: "<<count;
//    }
//    if(count>=1)
//    {
    Company_Object comps[5];
    companies->clear();
    for(int i=0;i<5;i++)
    {
        comps[i].company_name="";
    }
        db.get_placed_companies(comps,txt);
        for(int i=0;i<5;i++)
        {
            if(comps[i].company_name!="")
                companies->addItem(comps[i].company_name);
        }
//    }
    if(txt.length()==10 && comps[0].company_name=="")
    {
        msgBox.setText("Student not found under placed list");
        msgBox.exec();
    }
}

void Placed::cancel_add()
{
    this->setEnabled(true);
    add_placed->close();
}

void Placed::cancel_del()
{
    this->setEnabled(true);
    del_placed->close();
}

void Placed::toUpper(QString txt)
{
    usn_edit->setText(txt.toUpper());
}
Placed::~Placed()
{

}


