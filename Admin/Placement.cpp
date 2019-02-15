#include "Placement.h"

Placement::Placement(QWidget *parent) : QWidget(parent)
{
    table=new QTableView();
    model=new QStandardItemModel(1,6);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Comapany"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Job Title "));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Package (in lpa) "));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Eligibility "));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date "));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Venue "));
    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setGeometry(700,300,700,500);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->verticalHeader()->setDefaultSectionSize(50);
//    table->verticalHeader()->resetDefaultSectionSize();
    /*(QHeaderView::Stretch);*/
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

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




    add_placement->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    del_placement->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    connect(add,SIGNAL(clicked(bool)),this,SLOT(add_place()));
    connect(del,SIGNAL(clicked(bool)),this,SLOT(delete_placement()));


}

void Placement::initialize()
{
    model->setRowCount(db.getPlacementCount());
    int count=db.getPlacementCount();
    Placement_Object placements[count];
    db.getPlacementDetail(placements);
    model->setColumnCount(4);
    for(int i=0;i<count;i++)
    {
        QStandardItem *item1=new QStandardItem(placements[i].company);
        model->setItem(i,0,item1) ;
        QStandardItem *item2=new QStandardItem(placements[i].title);
        model->setItem(i,1,item2);
        QString pack=QString::number(placements[i].package);
        QStandardItem *item3=new QStandardItem(pack);
        model->setItem(i,2,item3);
        QStandardItem *item4=new QStandardItem(placements[i].eligibility);
        model->setItem(i,3,item4);
        QStandardItem *item5=new QStandardItem(placements[i].date);
        model->setItem(i,4,item5);
        QStandardItem *item6=new QStandardItem(placements[i].venue);
        model->setItem(i,5,item6);
    }
}
void Placement::initialize_add()
{
    add1=new QPushButton("Add");
    add1->setAutoDefault(true);
    cancel=new QPushButton("Cancel");
    cancel->setAutoDefault(true);
    calButton=new QPushButton("Select");
    cal=new QCalendarWidget();
    company_edit=new QLineEdit();
    eligibility_edit=new QTextEdit();
    venue_edit=new QLineEdit();
    QRegExp expcontact("[0-9]+[\.][0-9]+");
    package_edit=new QLineEdit();
    QRegExpValidator *validate_package=new QRegExpValidator(expcontact,this);
    package_edit->setValidator(validate_package);
    title_edit=new QLineEdit();
    company=new QLabel("Company");
    title=new QLabel("Title");
    package=new QLabel("Package offered");
    eligibility=new QLabel("Eligibility");
    date=new QLabel("Date");
    venue=new QLabel("Venue");
    add_placement=new QWidget();


    cal->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    vbox1=new QVBoxLayout();
    hbox1=new QHBoxLayout();
    hbox2=new QHBoxLayout();
    hbox3=new QHBoxLayout();
    hbox4=new QHBoxLayout();
    hbox5=new QHBoxLayout();
    hbox6=new QHBoxLayout();
    hbox7=new QHBoxLayout();


    hbox1->addWidget(company);
    hbox1->addWidget(company_edit);
    vbox1->addLayout(hbox1);

    hbox2->addWidget(title);
    hbox2->addWidget(title_edit);
    vbox1->addLayout(hbox2);

    hbox4->addWidget(package);
    hbox4->addWidget(package_edit);
    vbox1->addLayout(hbox4);

    hbox6->addWidget(eligibility);
    hbox6->addWidget(eligibility_edit);
    vbox1->addLayout(hbox6);

    hbox3->addWidget(date);
    hbox3->addWidget(calButton);
    vbox1->addLayout(hbox3);

    hbox7->addWidget(venue);
    hbox7->addWidget(venue_edit);
    vbox1->addLayout(hbox7);

    hbox5->addWidget(add1);
    hbox5->addWidget(cancel);
    vbox1->addLayout(hbox5);

    add_placement->setGeometry(700,300,400,400);

    add_placement->setLayout(vbox1);




}
void Placement::initialize_del()
{
    del_placement=new QWidget();
    company_name=new QLabel("Select Placement to delete");
    companies=new QComboBox();
    del1=new QPushButton("Delete");
    del1->setAutoDefault(true);
    cancel1=new QPushButton("Cancel");
    cancel1->setAutoDefault(true);
    vb=new QVBoxLayout();
    hbx1=new QHBoxLayout();
    hbx2=new QHBoxLayout();
    hbx1->addWidget(company_name);
    hbx1->addWidget(companies);
    vb->addLayout(hbx1);
    hbx2->addWidget(del1);
    hbx2->addWidget(cancel1);
    vb->addLayout(hbx2);
    del_placement->setLayout(vb);

    del_placement->setGeometry(700,300,300,100);


}

void Placement::add_place()
{
//    train.topic=
    add_placement->show();
    this->setEnabled(false);

    connect(add1,SIGNAL(clicked(bool)),this,SLOT(add_placement_to_db()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(cancel_add()));

    connect(calButton,SIGNAL(clicked()),cal,SLOT(show()),Qt::UniqueConnection);
    connect(cal,SIGNAL(clicked(QDate)),this,SLOT(onDateSelected(QDate)),Qt::UniqueConnection);

}

void Placement::add_placement_to_db()
{
    place.company=company_edit->text();
    place.eligibility=eligibility_edit->toPlainText();
    place.date=calButton->text();
    place.title=title_edit->text();
    place.package=package_edit->text().toFloat();
    place.venue=venue_edit->text();

    if(place.title==NULL)
    {
        place.title="NA";
    }
    if(place.company==NULL || place.eligibility==NULL || place.date=="Select" || place.venue==NULL || package_edit->text()==NULL)
    {
        msgBox.setText("Please enter valid values!");
        msgBox.exec();
    }

    else
    {
        if(db.add_placement(place))
    {
        msgBox.setText("Placement details added successfully");
        msgBox.exec();
        company_edit->clear();
        eligibility_edit->clear();
        venue_edit->clear();
        title_edit->clear();
        package_edit->clear();
        calButton->setText("Select");

        this->initialize();
    }
    else {
        msgBox.setText("Placement details could not be added");
        msgBox.exec();
    }
    }
}

void Placement::delete_placement()
{
    Placement_Object placements[db.getPlacementCount()];
    companies->clear();
    db.getPlacementDetail(placements);
    for(int i=0;i<db.getPlacementCount();i++)
    {
        companies->addItem(placements[i].company);
    }
    del_placement->show();
    this->setEnabled(false);
    connect(del1,SIGNAL(clicked(bool)),this,SLOT(delete_place()));
    connect(cancel1,SIGNAL(clicked(bool)),this,SLOT(cancel_del()));

}
void Placement::delete_place()
{

    if(db.delete_placement(companies->currentText()))
    {
        msgBox.setText("Placement deleted successfully");
        msgBox.exec();
        delete_placement();
        this->initialize();

    }
    else {
        msgBox.setText("COuldn't delete Placement details");
        msgBox.exec();
    }
}

void Placement::onDateSelected(QDate date)
{
    cal->close();
    date1 = date;
    calButton->setText(date1.toString("dd/MM/yyyy"));
}

void Placement::cancel_add()
{
    this->setEnabled(true);
    add_placement->close();
}

void Placement::cancel_del()
{
    this->setEnabled(true);
    del_placement->close();
}
Placement::~Placement()
{

}
