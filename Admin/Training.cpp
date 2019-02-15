#include "Welcome.h"
#include "Training.h"

Training::Training(QWidget *parent) : QWidget(parent)
{

    table=new QTableView();

    model=new QStandardItemModel(1,4);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Training topic"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Details "));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("FROM "));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("TO "));
    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->setGeometry(700,300,600,500);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->verticalHeader()->setDefaultSectionSize(50);
//            horizontalHeader()->setDefaultSectionSize(int size)


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

    add_training->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    del_training->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    connect(add,SIGNAL(clicked(bool)),this,SLOT(add_train()));
    connect(del,SIGNAL(clicked(bool)),this,SLOT(delete_training()));


}

void Training::initialize()
{
    model->setRowCount(db.getTrainingCount());
    int count=db.getTrainingCount();
    Training_Object trainings[count];
    db.getTrainingDetail(trainings);
    model->setColumnCount(4);
    for(int i=0;i<count;i++)
    {
        QStandardItem *item1=new QStandardItem(trainings[i].topic);
        model->setItem(i,0,item1) ;
        QStandardItem *item2=new QStandardItem(trainings[i].details);
        model->setItem(i,1,item2);
        QStandardItem *item3=new QStandardItem(trainings[i].from);
        model->setItem(i,2,item3);
        QStandardItem *item4=new QStandardItem(trainings[i].to);
        model->setItem(i,3,item4);
    }
}
void Training::initialize_add()
{
    add1=new QPushButton("Add");
    add1->setAutoDefault(true);
    cancel=new QPushButton("Cancel");
    cancel->setAutoDefault(true);
    calButton1=new QPushButton("Select");
    calButton2=new QPushButton("Select");
    cal1=new QCalendarWidget();
    cal2=new QCalendarWidget();
    topic_edit=new QLineEdit();
    detail_edit=new QTextEdit();
    from=new QLabel("From");
    to=new QLabel("To");
    topic=new QLabel("TOpic");
    detail=new QLabel("Details");
    add_training=new QWidget();


    cal1->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    cal2->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    vbox1=new QVBoxLayout();
    hbox1=new QHBoxLayout();
    hbox2=new QHBoxLayout();
    hbox3=new QHBoxLayout();
    hbox4=new QHBoxLayout();
    hbox5=new QHBoxLayout();


    hbox1->addWidget(topic);
    hbox1->addWidget(topic_edit);
    vbox1->addLayout(hbox1);

    hbox2->addWidget(detail);
    hbox2->addWidget(detail_edit);
    vbox1->addLayout(hbox2);

    hbox3->addWidget(from);
    hbox3->addWidget(calButton1);
    vbox1->addLayout(hbox3);

    hbox4->addWidget(to);
    hbox4->addWidget(calButton2);
    vbox1->addLayout(hbox4);

    hbox5->addWidget(add1);
    hbox5->addWidget(cancel);
    vbox1->addLayout(hbox5);

    add_training->setLayout(vbox1);
    add_training->setGeometry(700,300,400,300);




}
void Training::initialize_del()
{
    del_training=new QWidget();
    topic_name=new QLabel("Select Training to delete");
    topics=new QComboBox();
    del1=new QPushButton("Delete");
    del1->setAutoDefault(true);
    cancel1=new QPushButton("Cancel");
    cancel1->setAutoDefault(true);
    vb=new QVBoxLayout();
    hbx1=new QHBoxLayout();
    hbx2=new QHBoxLayout();
    hbx1->addWidget(topic_name);
    hbx1->addWidget(topics);
    vb->addLayout(hbx1);
    hbx2->addWidget(del1);
    hbx2->addWidget(cancel1);
    vb->addLayout(hbx2);
    del_training->setLayout(vb);
    del_training->setGeometry(700,300,300,100);


}

void Training::add_train()
{
//    train.topic=
    add_training->show();
    this->setEnabled(false);

    connect(add1,SIGNAL(clicked(bool)),this,SLOT(add_training_to_db()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(cancel_add()));

    connect(calButton1,SIGNAL(clicked()),cal1,SLOT(show()),Qt::UniqueConnection);
    connect(cal1,SIGNAL(clicked(QDate)),this,SLOT(onDateSelected1(QDate)),Qt::UniqueConnection);
    connect(calButton2,SIGNAL(clicked()),cal2,SLOT(show()),Qt::UniqueConnection);
    connect(cal2,SIGNAL(clicked(QDate)),this,SLOT(onDateSelected2(QDate)),Qt::UniqueConnection);


}

void Training::add_training_to_db()
{
    train.topic=topic_edit->text();
    train.details=detail_edit->toPlainText();
    train.from=calButton1->text();
    train.to=calButton2->text();
    if(train.to=="Select")
    {
        train.to="NA";
    }

    if(train.topic==NULL || train.details==NULL || train.from=="Select")
    {
        msgBox.setText("Please enter valid values!");
        msgBox.exec();
    }

    else
    {
        if(db.add_training(train))
    {
        msgBox.setText("Training details added successfully");
        msgBox.exec();
        topic_edit->clear();
        detail_edit->clear();
        calButton1->setText("Select");
        calButton2->setText("Select");
        this->initialize();
    }
    else {
        msgBox.setText("Training details could not be added");
        msgBox.exec();
    }
    }
}

void Training::delete_training()
{
    Training_Object trainings[db.getTrainingCount()];
    topics->clear();
    db.getTrainingDetail(trainings);
    for(int i=0;i<db.getTrainingCount();i++)
    {
        topics->addItem(trainings[i].topic);
    }
    del_training->show();
    this->setEnabled(false);
    connect(del1,SIGNAL(clicked(bool)),this,SLOT(delete_train()));
    connect(cancel1,SIGNAL(clicked(bool)),this,SLOT(cancel_del()));

}
void Training::delete_train()
{

    if(db.delete_training(topics->currentText()))
    {
        msgBox.setText("Training deleted successfully");
        msgBox.exec();
        delete_training();
        this->initialize();

    }
    else {
        msgBox.setText("COuldn't delete Training details");
        msgBox.exec();
    }
}

void Training::onDateSelected1(QDate date)
{
    cal1->close();
    date1 = date;
    calButton1->setText(date1.toString("dd/MM/yyyy"));
}

void Training::onDateSelected2(QDate date)
{
    cal2->close();
    date2 = date;
    calButton2->setText(date2.toString("dd/MM/yyyy"));
}

void Training::cancel_add()
{
    this->setEnabled(true);
    if(this->isEnabled()){
       this->setWindowFlags(Qt::Window);
    }
    add_training->close();
}

void Training::cancel_del()
{
    this->setEnabled(true);
    del_training->close();

}

Training::~Training()
{

}
