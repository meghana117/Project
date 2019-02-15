#include "Contacts.h"

Contacts::Contacts(QWidget *parent) : QWidget(parent)
{
    table=new QTableView();
    model=new QStandardItemModel(1,6);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Name"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Designation"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Contact"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Update"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Delete"));

    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setGeometry(700,300,700,500);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setDefaultSectionSize(50);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    add=new QPushButton("Add");
    cancel=new QPushButton("Cancel");
    vb1=new QVBoxLayout();
    hb1=new QHBoxLayout();

    vb1->addWidget(table);
    hb1->addWidget(add);
    hb1->addWidget(cancel);
    vb1->addLayout(hb1);

    this->setLayout(vb1);
    this->setGeometry(700,300,600,600);

    initialize();
    initialize_add();
    initialize_update();

    this->setLayout(vb1);

    connect(add,SIGNAL(clicked(bool)),this,SLOT(add_contact()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(close()));

}
void Contacts::initialize()
{
    int count=db.getContactCount();
    Contact_Object contacts[count];
    db.getContactDetail(contacts);

    QPushButton *update_buttons[count];
    QPushButton *del_buttons[count];

    QSignalMapper *update_mapper=new QSignalMapper(this);
    connect(update_mapper,SIGNAL(mapped(int)),this,SLOT(update_contact(int)));

    QSignalMapper *delete_mapper=new QSignalMapper(this);
    connect(delete_mapper,SIGNAL(mapped(int)),this,SLOT(delete_contact(int)));

    model->setRowCount(db.getContactCount());
    model->setColumnCount(6);
    for(int i=0;i<count;i++)
    {
        QStandardItem *item1=new QStandardItem(contacts[i].name);
        model->setItem(i,0,item1) ;
        qDebug()<<contacts[i].name<<"Name ";
        QStandardItem *item2=new QStandardItem(contacts[i].designation);
        model->setItem(i,1,item2) ;
        if(contacts[i].contact2==NULL)
        {
            QStandardItem *item3=new QStandardItem(contacts[i].contact1);
            model->setItem(i,2,item3) ;
        }
        else{
            QStandardItem *item3=new QStandardItem(contacts[i].contact1+", "+contacts[i].contact2);
            model->setItem(i,2,item3) ;
        }
        QStandardItem *item4=new QStandardItem(contacts[i].email);
        model->setItem(i,3,item4) ;
        update_buttons[i]=new QPushButton("Update");
        table->setIndexWidget(model->index(i,4), update_buttons[i]);
        connect(update_buttons[i],SIGNAL(clicked()),update_mapper,SLOT(map()));
        update_mapper->setMapping(update_buttons[i],contacts[i].id);
        del_buttons[i]=new QPushButton("Delete");
        table->setIndexWidget(model->index(i,5),del_buttons[i]);
        connect(del_buttons[i],SIGNAL(clicked()),delete_mapper,SLOT(map()));
        delete_mapper->setMapping(del_buttons[i],contacts[i].id);
    }
}
void Contacts::initialize_add()
{
    add1=new QPushButton("Add");
    cancel1=new QPushButton("Cancel");

    name_label=new QLabel("Name");
    designation_label=new QLabel("Designation");
    contact1_label=new QLabel("Contact No.");
    contact2_label=new QLabel("Alternate Contact");
    email_label=new QLabel("Email");
    name=new QLineEdit();
    QRegExp valid_name("[a-zA-Z ]+");
    QRegExpValidator *validate_name=new QRegExpValidator(valid_name,this);
    name->setValidator(validate_name);
    designation=new QLineEdit();
    contact1=new QLineEdit();
    QRegExp expcontact("[1-9]{1}[0-9]{9}");
    QRegExpValidator *validate_contact=new QRegExpValidator(expcontact,this);
    contact1->setValidator(validate_contact);
    contact2=new QLineEdit();
    contact2->setValidator(validate_contact);
    email=new QLineEdit();
    error=new QLabel();

    form1=new QFormLayout();


    form1->addRow(name_label,name);
    form1->addRow(designation_label,designation);
    form1->addRow(contact1_label,contact1);
    form1->addRow(contact2_label,contact2);
    form1->addRow(email_label,email);
    form1->addRow(error);
    form1->addRow(add1,cancel1);

    add_widget=new QWidget();
    add_widget->setLayout(form1);
    add_widget->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    connect(add1,SIGNAL(clicked(bool)),this,SLOT(add_contact_to_db()));
    connect(cancel1,SIGNAL(clicked(bool)),this,SLOT(cancel_add()));

}
void Contacts::initialize_update()
{
    update=new QPushButton("Update");
    cancel2=new QPushButton("Cancel");

    update_widget=new QWidget();
    form2=new QFormLayout();

    name_label_=new QLabel("Name");
    designation_label_=new QLabel("Designation");
    contact1_label_=new QLabel("Contact No.");
    contact2_label_=new QLabel("Alternate Contact");
    email_label_=new QLabel("Email");
    name_=new QLineEdit();
    designation_=new QLineEdit();
    contact1_=new QLineEdit();
    contact2_=new QLineEdit();
    email_=new QLineEdit();
    error_=new QLabel();
    id=new QLabel();

    form2=new QFormLayout();

    form2->addRow(name_label_,name_);
    form2->addRow(designation_label_,designation_);
    form2->addRow(contact1_label_,contact1_);
    form2->addRow(contact2_label_,contact2_);
    form2->addRow(email_label_,email_);
    form2->addRow(error_);
    form2->addRow(update,cancel2);
    update_widget->setLayout(form2);
    update_widget->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    connect(update,SIGNAL(clicked(bool)),this,SLOT(update_contact_to_db()));
    connect(cancel2,SIGNAL(clicked(bool)),this,SLOT(cancel_update()));
}
void Contacts::add_contact()
{

    this->setEnabled(false);
    add_widget->show();
}
void Contacts::add_contact_to_db()
{
    Contact_Object contact;
    QMessageBox msg;
    contact.name=name->text();
    contact.email=email->text();
    contact.contact1=contact1->text();
    contact.contact2=contact2->text();
    contact.designation=designation->text();

    if(contact.name==NULL || contact.email==NULL || contact.contact1==NULL || contact.designation==NULL)
    {
        error->setText("Please enter value for required fields");
    }

    else {
        if(db.add_contact_to_db(contact))
        {
            msg.setText("Contact details inserted to db");
            this->initialize();
            msg.exec();
        }
        else {
            msg.setText("Couldn't insert data into databse!");
            msg.exec();
        }
    }
}
void Contacts::cancel_add()
{
    this->setEnabled(true);
    add_widget->close();
}
void Contacts::delete_contact(int id)
{
    QMessageBox msgbx;
    QMessageBox msg;

     msg.setInformativeText("Are you sure you want to delete?");
     msg.setStandardButtons(QMessageBox::Yes |  QMessageBox::Cancel);
     msg.setDefaultButton(QMessageBox::Yes);
     int ret = msg.exec();

     switch (ret) {
       case QMessageBox::Yes:
         if(db.delete_contact(id))
         {
             msgbx.setText("Deleted Contact successfully");
             msgbx.exec();
             this->initialize();
         }
         else {
             msgbx.setText("Couldn't delete contact ");
             msgbx.exec();
         }
           break;
       case QMessageBox::Cancel:
           // Don't Delete was clicked
           break;
       default:
           // Should never be reached
           break;
     }

}
void Contacts::update_contact(int id)
{
    Contact_Object contact=db.getContact(id);
    name_->setText(contact.name);
    designation_->setText(contact.designation);
    contact1_->setText(contact.contact1);
    contact2_->setText(contact.contact2);
    email_->setText(contact.email);
    this->id->setText(QString::number(id));

    this->setEnabled(false);
    update_widget->show();
}
void Contacts::update_contact_to_db()
{
    Contact_Object contact;
    contact.id=id->text().toInt();
    contact.name=name_->text();
    contact.email=email_->text();
    contact.designation=designation_->text();
    contact.contact1=contact1_->text();
    contact.contact2=contact2_->text();
    if(contact.name==NULL || contact.email==NULL || contact.contact1==NULL || contact.designation==NULL)
    {
        error_->setText("Please enter value for required fields");
    }
    QMessageBox msg;
    if(db.update_contact(contact))
    {
        msg.setText("Contact updated successfully");
        msg.exec();
        initialize();
    }
    else {
        msg.setText("Couldn't update contact!");
        msg.exec();
    }
}
void Contacts::cancel_update()
{
    this->setEnabled(true);
    update_widget->close();
}
Contacts::~Contacts()
{
}
