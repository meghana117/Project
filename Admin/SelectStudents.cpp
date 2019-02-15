#include "SelectStudents.h"

SelectStudents::SelectStudents(QWidget *parent) : QWidget(parent)
{
    table=new QTableView();
    model=new QStandardItemModel(1,5);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("USN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Department"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Contact"));

    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setGeometry(700,300,700,500);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setDefaultSectionSize(50);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    Select=new QLabel("Select List");
    Department=new QLabel("Department");
    Company=new QLabel("Company");
    Placed_Status=new QLabel("Placed Status");
    Tenth=new QLabel("10th %");
    Twelve=new QLabel("12th %");
    Cgpa=new QLabel("Cgpa");
    back=new QLabel("Backlogs");

    combo=new QComboBox();
    dept=new QComboBox();
    cgpa=new QDoubleSpinBox();
    ten=new QDoubleSpinBox();
    twelve=new QDoubleSpinBox();

    placed=new QComboBox();
    company=new QComboBox();
    search=new QPushButton("Search");
    backlog=new QSpinBox();

    save=new QPushButton("Save file(csv)");
    cancel=new QPushButton("Cancel");
    vb1=new QVBoxLayout();
    vb2=new QVBoxLayout();
    hb1=new QHBoxLayout();
    hb2=new QHBoxLayout();
    hb3=new QHBoxLayout();
    hb4=new QHBoxLayout();
    hb5=new QHBoxLayout();
    hb6=new QHBoxLayout();
    hb7=new QHBoxLayout();

    hb1->addWidget(Select);
    hb1->addWidget(combo);

    hb2->addWidget(Department);
    hb2->addWidget(dept);
    hb2->addWidget(Cgpa);
    hb2->addWidget(cgpa);
    hb2->addWidget(Tenth);
    hb2->addWidget(ten);
    hb2->addWidget(Twelve);
    hb2->addWidget(twelve);
    hb2->addWidget(back);
    hb2->addWidget(backlog);

    hb3->addWidget(Placed_Status);
    hb3->addWidget(placed);

    hb4->addWidget(Company);
    hb4->addWidget(company);

    hb5->addWidget(search);

    hb6->addWidget(table);
    hb7->addWidget(save);
    hb7->addWidget(cancel);

    vb1->addLayout(hb1);
    vb1->addLayout(hb2);
    vb1->addLayout(hb3);
    vb1->addLayout(hb4);
    vb1->addLayout(hb5);
    vb1->addLayout(hb6);
    vb1->addLayout(hb7);

    this->setLayout(vb1);

    initialize();

    connect(combo,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(combo_changed(const QString &)));
    connect(placed,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(placed_changed(const QString &)));
    connect(search,SIGNAL(clicked()),this,SLOT(search_db()));
    connect(save,SIGNAL(clicked()),this,SLOT(save_file()));
    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));

}
void SelectStudents::initialize()
{
    QStringList ll={"All","Department wise"};
    combo->addItems(ll);

    QStringList list={"Computer Science and Engineering","Electronics and Communications Engineering","Mechanical Engineering","Civil Engineering","Electrical Engineering","Medical Electronics Engineering","Information Science and Engineering","Telecommunication and Engineering"};
    dept->addItems(list);

    company->addItem("All");
    Company_Object comp[db.getCompanyCount()];
    db.getCompanyDetail(comp);
    for(int i=0;i<db.getCompanyCount();i++)
    {
        company->addItem(comp[i].company_name);
    }

    cgpa->setMaximum(10);
    ten->setMaximum(100);
    twelve->setMaximum(100);
    backlog->setMaximum(10);

    QStringList l={"All","Placed","Unplaced"};
    placed->addItems(l);

    Department->hide();
    Cgpa->hide();
    Tenth->hide();
    Twelve->hide();
    back->hide();
    Company->hide();

    dept->hide();
    cgpa->hide();
    ten->hide();
    twelve->hide();
    backlog->hide();

    company->hide();



}
void SelectStudents::combo_changed(const QString &opt)
{
    if(opt=="All")
    {
        Department->hide();
        Cgpa->hide();
        Tenth->hide();
        Twelve->hide();
        back->hide();
        dept->hide();
        cgpa->hide();
        ten->hide();
        twelve->hide();
        backlog->hide();

    }
    else if (opt=="Department wise") {
        Department->show();
        Cgpa->show();
        Tenth->show();
        Twelve->show();
        back->show();
        dept->show();
        cgpa->show();
        ten->show();
        twelve->show();
        backlog->show();
    }
}
void SelectStudents::placed_changed(const QString &opt)
{
    if(opt=="All")
    {
        Company->hide();
        company->hide();
    }
    else if (opt=="Placed") {
        Company->show();
        company->show();
    }
    else if (opt=="Unplaced") {
        Company->hide();
        company->hide();
    }
}
void SelectStudents::search_db()
{
    Criteria_object criteria;
    criteria.ten=ten->value();
    criteria.twelve=twelve->value();
    criteria.dept=dept->currentText();
    criteria.company=company->currentText();
    criteria.cgpa=cgpa->value();
    criteria.combo=combo->currentText();
    criteria.placed_status=placed->currentText();

    model->setRowCount(db.get_count(criteria));
    int count=db.get_count(criteria);
    qDebug()<<count;
    Student students[count];
    db.get_list(criteria,students);
    model->setColumnCount(4);
    for(int i=0;i<count;i++)
    {
        QStandardItem *item1=new QStandardItem(students[i].usn);
        model->setItem(i,0,item1) ;
        QStandardItem *item2=new QStandardItem(students[i].name);
        model->setItem(i,1,item2);
        QStandardItem *item3=new QStandardItem(students[i].dept);
        model->setItem(i,2,item3);
        QStandardItem *item4=new QStandardItem(students[i].contact);
        model->setItem(i,3,item4);
        QStandardItem *item5=new QStandardItem(students[i].email);
        model->setItem(i,4,item5);
    }
}
void SelectStudents::save_file()
{
    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName=QFileDialog::getSaveFileName(0,"Save file",QCoreApplication::applicationDirPath(),filters,&defaultFilter);

    QFile file(fileName);

    QAbstractItemModel *model=table->model();
    if(file.open(QFile::WriteOnly| QFile::Truncate))
    {
        QTextStream data(&file);
        QStringList strList;
        for(int i=0;i<model->columnCount();i++)
        {
            if(model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString().length()>0)
            {
                strList.append("\""+model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString()+"\"");
            }
            else {
                strList.append("");
            }
        }
        data<<strList.join(";")<<"\n";
        for (int i = 0; i < model->rowCount(); i++) {
             strList.clear();
             for (int j = 0; j < model->columnCount(); j++) {
                   if (model->data(model->index(i, j)).toString().length() > 0)
                            strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                   else
                            strList.append("");
             }
             data << strList.join(";") + "\n";
        }
        file.close();
    }
}
SelectStudents::~SelectStudents()
{

}
