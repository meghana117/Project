#include "Search_Student.h"

Search_Student::Search_Student(QWidget *parent) : QWidget(parent)
{
    USN=new QLabel("USN");
    this->setGeometry(700,300,400,200);
    usn_edit=new QLineEdit();
    QRegExp expusn("^[1]{1}[Dd]{1}[Aa]{1}[0-9]{2}[A-Za-z]{2}[0-9]{3}$/i");
    QRegExpValidator *validate_usn=new QRegExpValidator(expusn,this);
    usn_edit->setValidator(validate_usn);
    error=new QLabel();
    search=new QPushButton("Search");
    cancel=new QPushButton("Cancel");

//    this->setAttribute(Qt::WA_DeleteOnClose,true);
//    vbx1=new QVBoxLayout();
    search_widget=new QWidget();

    qDebug()<<this->parent();
    update_widget=new QWidget();

    vbox1=new QVBoxLayout();
    vbox2=new QVBoxLayout();

    hbox1=new QHBoxLayout();
    hbox2=new QHBoxLayout();
    hbox3=new QHBoxLayout();
    hbox4=new QHBoxLayout();

    hbox1->addWidget(USN);
    hbox1->addWidget(usn_edit);
    vbox1->addLayout(hbox1);

    hbox3->addWidget(error);
    vbox1->addLayout(hbox3);

    hbox2->addWidget(search);
    hbox2->addWidget(cancel);
    vbox1->addLayout(hbox2);

    this->setLayout(vbox1);

        initialize_search();
        initialize_update();

        update_widget->setWindowFlags(Qt::Window
        | Qt::WindowMinimizeButtonHint
        | Qt::WindowMaximizeButtonHint);


    connect(search,SIGNAL(clicked(bool)),this,SLOT(search_action()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(usn_edit,SIGNAL(textEdited(QString)),this,SLOT(toUpper(QString)));



}

void Search_Student::initialize_search()
{

    hbx1=new QHBoxLayout();
    hbx2=new QHBoxLayout();
    hbx3=new QHBoxLayout();
    hbx4=new QHBoxLayout();
    hbx5=new QHBoxLayout();
    hbx6=new QHBoxLayout();
    hbx7=new QHBoxLayout();
    hbx8=new QHBoxLayout();
    hbx9=new QHBoxLayout();
    hbx10=new QHBoxLayout();
    hbx11=new QHBoxLayout();
    hbx12=new QHBoxLayout();

    update=new QPushButton("Update");
    del=new QPushButton("Delete");

    sname=new QLabel("Name");
    ssname=new QLabel();

    susn=new QLabel("USN");
    ssusn=new QLabel();

    sdob=new QLabel("DOB");
    ssdob=new QLabel();

    semail=new QLabel("Email");
    ssemail=new QLabel();

    soffer=new QLabel("Offers");
    ssoffer=new QLabel();

    sdept=new QLabel("Department");
    ssdept=new QLabel();

    scontact=new QLabel("Contact");
    sscontact=new QLabel();

    sbacklog=new QLabel("Backlogs");
    ssbacklog=new QLabel();

    scgpa=new QLabel("CGPA");
    sscgpa=new QLabel();

    sten=new QLabel("10th Percentage");
    ssten=new QLabel();

    stwelve=new QLabel("12th Percentage");
    sstwelve=new QLabel();

    sem1=new QLabel("Sem1");
    ssem1=new QLabel();

    sem2=new QLabel("Sem2");
    ssem2=new QLabel();

    sem3=new QLabel("Sem3");
    ssem3=new QLabel();

    sem4=new QLabel("Sem4");
    ssem4=new QLabel();

    sem5=new QLabel("Sem5");
    ssem5=new QLabel();

    sem6=new QLabel("Sem6");
    ssem6=new QLabel();

    sem7=new QLabel("Sem7");
    ssem7=new QLabel();

    sem8=new QLabel("Sem8");
    ssem8=new QLabel();

    form1=new QFormLayout();

//    hbx1->addWidget(sname);
//    hbx1->addWidget(ssname);
//    vbx1->addLayout(hbx1);

    form1->addRow(sname,ssname);

//    hbx2->addWidget(susn);
//    hbx2->addWidget(ssusn);
//    vbx1->addLayout(hbx2);

    form1->addRow(susn,ssusn);

//    hbx3->addWidget(sdob);
//    hbx3->addWidget(ssdob);
//    vbx1->addLayout(hbx3);

    form1->addRow(sdob,ssdob);

//    hbx4->addWidget(semail);
//    hbx4->addWidget(ssemail);
//    vbx1->addLayout(hbx4);

    form1->addRow(semail,ssemail);

//    hbx5->addWidget(sdept);
//    hbx5->addWidget(ssdept);
//    vbx1->addLayout(hbx5);

    form1->addRow(sdept,ssdept);

//    hbx12->addWidget(soffer);
//    hbx12->addWidget(ssoffer);
//    vbx1->addLayout(hbx12);

    form1->addRow(soffer,ssoffer);

//    hbx6->addWidget(scontact);
//    hbx6->addWidget(sscontact);
//    vbx1->addLayout(hbx6);

    form1->addRow(scontact,sscontact);

//    hbx7->addWidget(sbacklog);
//    hbx7->addWidget(ssbacklog);
//    vbx1->addLayout(hbx7);

    form1->addRow(sbacklog,ssbacklog);
    form1->addRow(sem1,ssem1);
    form1->addRow(sem2,ssem2);
    form1->addRow(sem3,ssem3);
    form1->addRow(sem4,ssem4);
    form1->addRow(sem5,ssem5);
    form1->addRow(sem6,ssem6);
    form1->addRow(sem7,ssem7);
    form1->addRow(sem8,ssem8);

//    hbx8->addWidget(scgpa);
//    hbx8->addWidget(sscgpa);
//    vbx1->addLayout(hbx8);

    form1->addRow(scgpa,sscgpa);

//    hbx9->addWidget(sten);
//    hbx9->addWidget(ssten);
//    vbx1->addLayout(hbx9);

    form1->addRow(sten,ssten);

//    hbx10->addWidget(stwelve);
//    hbx10->addWidget(sstwelve);
//    vbx1->addLayout(hbx10);

    form1->addRow(stwelve,sstwelve);

//    hbx11->addWidget(update);
//    hbx11->addWidget(del);
//    vbx1->addLayout(hbx11);

    form1->addRow(update,del);

    search_widget->setLayout(form1);


}
void Search_Student::search_action()
{
//    student.~Student();
    student.usn=usn_edit->text();
    search_widget->hide();

//    qDebug()<<"AFter line_edit";
    this->repaint();
    usn_edit->setEnabled(true);
    search->setEnabled(true);
    student.name="";
    student=db.search_student(student);
    if(student.name=="" )
    {
        if(flag1)
        {
            vbox1->removeWidget(search_widget);
                    flag1=0;
        }
        search_widget->hide();

        error->setText("No Student record found for "+usn_edit->text());
        error->setStyleSheet("color:red");
        this->repaint();
    }
    else
    {
        if(flag1)
        {
            vbox1->removeWidget(search_widget);
                    flag1=0;
        }

        error->setText("");
        ssname->setText(student.name);
        ssusn->setText(student.usn);
        ssdob->setText(student.dob);
        ssemail->setText(student.email);
        ssdept->setText(student.dept);
        sscontact->setText(student.contact);
        ssbacklog->setText(QString::number(student.backlogs));
        sscgpa->setText(QString::number(student.cgpa));
        ssten->setText(QString::number(student.ten));
        sstwelve->setText(QString::number(student.twelve));
        ssoffer->setText(QString::number(student.offer));
        ssem1->setText(QString::number(student.sem1));
        ssem2->setText(QString::number(student.sem2));
        ssem3->setText(QString::number(student.sem3));
        ssem4->setText(QString::number(student.sem4));
        ssem5->setText(QString::number(student.sem5));

        if(student.sem6==0)
        {
            sem6->hide();
            ssem6->hide();
        }
        else {
            sem6->show();
            ssem6->show();
            ssem6->setText(QString::number(student.sem6));
        }
        if(student.sem7==0)
        {
            sem7->hide();
            ssem7->hide();
        }
        else {
            sem7->show();
            ssem7->show();
            ssem7->setText(QString::number(student.sem6));
        }
        if(student.sem8==0)
        {
            sem8->hide();
            ssem8->hide();
        }
        else {
            sem8->show();
            ssem8->show();
            ssem8->setText(QString::number(student.sem6));
        }

        flag1=1;

        search_widget->close();
        search_widget->repaint();
        this->setGeometry(700,300,500,350);
        search_widget->show();

        vbox1->addWidget(search_widget);

        this->repaint();

        connect(update,SIGNAL(clicked(bool)),this,SLOT(update_action()));
        connect(del,SIGNAL(clicked(bool)),this,SLOT(delete_stud()));


    }

}

void Search_Student::initialize_update()
{
    m_calButton = new QPushButton("Select");
    m_calButton->setFlat(true);

    name=new QLabel("Name");
    usn=new QLabel("USN");
    dob=new QLabel("DOB");
    email=new QLabel("Email");
    dept=new QLabel("Department");
    contact=new QLabel("Contact no.");
    cgpa=new QLabel("CGPA");
    backlog=new QLabel("No. of backlogs");
    error1=new QLabel();
    ten=new QLabel("10th Percentage");
    twelve=new QLabel("12th Percentage");
    se1=new QLabel("Sem1");
    se2=new QLabel("Sem2");
    se3=new QLabel("Sem3");
    se4=new QLabel("Sem4");
    se5=new QLabel("Sem5");
    se6=new QLabel("Sem6");
    se7=new QLabel("Sem7");
    se8=new QLabel("Sem8");

    se1_edit=new QDoubleSpinBox();
    se1_edit->setMaximum(10.0);

    se2_edit=new QDoubleSpinBox();
    se2_edit->setMaximum(10.0);

    se3_edit=new QDoubleSpinBox();
    se3_edit->setMaximum(10.0);

    se4_edit=new QDoubleSpinBox();
    se4_edit->setMaximum(10.0);

    se5_edit=new QDoubleSpinBox();
    se5_edit->setMaximum(10.0);

    se6_edit=new QDoubleSpinBox();
    se6_edit->setMaximum(10.0);

    se7_edit=new QDoubleSpinBox();
    se7_edit->setMaximum(10.0);

    se8_edit=new QDoubleSpinBox();
    se8_edit->setMaximum(10.0);

    name_edit=new QLineEdit();

    QRegExp valid_name("[a-zA-Z ]+");
    QRegExpValidator *validate_name=new QRegExpValidator(valid_name,this);
    name_edit->setValidator(validate_name);

    QRegExp expusn("^[1]{1}[Dd]{1}[Aa]{1}[0-9]{2}[A-Za-z]{2}[0-9]{3}$/i");
    QRegExpValidator *validate_usn=new QRegExpValidator(expusn,this);
    usnedit=new QLineEdit();
    usnedit->setValidator(validate_usn);

    m_cal = new QCalendarWidget;
    m_cal->setMaximumDate(QDate::currentDate());
    m_cal->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    QRegExp rx("^[a-zA-Z0-9_/./-]+@[a-zA-Z0-9_/./-]+/.[a-zA-Z]{2,5}$");
    QRegExpValidator *validate_email=new QRegExpValidator(rx,this);
    email_edit=new QLineEdit();
    email_edit->setValidator(validate_email);

    dept_edit=new QComboBox();
    QStringList list={"Computer Science and Engineering","Electronics and Communications Engineering","Mechanical Engineering","Civil Engineering","Electrical Engineering","Medical Electronics Engineering","Information Science and Engineering","Telecommunication and Engineering"};
    dept_edit->addItems(list);

    QRegExp expcontact("[1-9]{1}[0-9]{9}");
    QRegExpValidator *validate_contact=new QRegExpValidator(expcontact,this);
    contact_edit=new QLineEdit();
    contact_edit->setValidator(validate_contact);

    cgpa_edit=new QDoubleSpinBox();
    cgpa_edit->setMaximum(10.0);

    ten_edit=new QDoubleSpinBox();
    ten_edit->setMaximum(100.0);

    twelve_edit=new QDoubleSpinBox();
    twelve_edit->setMaximum(100.0);

    backlog_edit=new QSpinBox();
    backlog_edit->setMaximum(10);

    update1=new QPushButton("Update");
    cancel2=new QPushButton("Cancel");

    vb1=new QVBoxLayout();
    vb2=new QVBoxLayout();
    hb1=new QHBoxLayout();
    hb2=new QHBoxLayout();
    hb3=new QHBoxLayout();
    hb4=new QHBoxLayout();
    hb5=new QHBoxLayout();
    hb6=new QHBoxLayout();
    hb7=new QHBoxLayout();
    hb8=new QHBoxLayout();
    hb9=new QHBoxLayout();
    hb10=new QHBoxLayout();
    hb11=new QHBoxLayout();
    hb12=new QHBoxLayout();

    form2=new QFormLayout();

//    hb1->addWidget(name);
//    hb1->addWidget(name_edit);

    form2->addRow(name,name_edit);

//    hb2->addWidget(dob);
//    hb2->addWidget(m_calButton);

    form2->addRow(dob,m_calButton);

//    hb3->addWidget(email);
//    hb3->addWidget(email_edit);

    form2->addRow(email,email_edit);

//    hb4->addWidget(contact);
//    hb4->addWidget(contact_edit);

    form2->addRow(contact,contact_edit);

//    hb5->addWidget(dept);
//    hb5->addWidget(dept_edit);

    form2->addRow(dept,dept_edit);

//    hb6->addWidget(usn);
//    hb6->addWidget(usnedit);

    form2->addRow(usn,usnedit);
    form2->addRow(se1,se1_edit);
    form2->addRow(se2,se2_edit);
    form2->addRow(se3,se3_edit);
    form2->addRow(se4,se4_edit);
    form2->addRow(se5,se5_edit);
    form2->addRow(se6,se6_edit);
    form2->addRow(se7,se7_edit);
    form2->addRow(se8,se8_edit);

//    hb7->addWidget(cgpa);
//    hb7->addWidget(cgpa_edit);

    form2->addRow(cgpa,cgpa_edit);

//    hb8->addWidget(backlog);
//    hb8->addWidget(backlog_edit);

    form2->addRow(backlog,backlog_edit);

    form2->addRow(ten,ten_edit);
    form2->addRow(twelve,twelve_edit);


//    hb9->addWidget(error1);
    form2->addWidget(error1);

    form2->addRow(update1,cancel2);

//    hb10->addWidget(update1);
//    hb10->addWidget(cancel2);

//    hb11->addWidget(ten);
//    hb11->addWidget(ten_edit);

//    hb12->addWidget(twelve);
//    hb12->addWidget(twelve_edit);

//    vb1->addLayout(hb1);
//    vb1->addLayout(hb2);
//    vb1->addLayout(hb3);
//    vb1->addLayout(hb4);
//    vb1->addLayout(hb5);
//    vb1->addLayout(hb6);
//    vb1->addLayout(hb7);
//    vb1->addLayout(hb8);
//    vb1->addLayout(hb11);
//    vb1->addLayout(hb12);
//    vb1->addLayout(hb9);
//    vb1->addLayout(hb10);

    update_widget->setLayout(form2);



}
void Search_Student::update_action()
{
    this->setEnabled(false);
    name_edit->setText(student.name);
    usnedit->setText(student.usn);
    usnedit->setEnabled(false);

    m_calButton->setText(student.dob);

    email_edit->setText(student.email);
    dept_edit->currentTextChanged(student.dept);

    contact_edit->setText(student.contact);

    cgpa_edit->setValue(student.cgpa);
    cgpa_edit->setEnabled(false);

    ten_edit->setValue(student.ten);
    twelve_edit->setValue(student.twelve);

    backlog_edit->setValue(student.backlogs);

    se1_edit->setValue(student.sem1);
    se2_edit->setValue(student.sem2);
    se3_edit->setValue(student.sem3);
    se4_edit->setValue(student.sem4);
    se5_edit->setValue(student.sem5);

    if(student.sem6==0)
    {
        se6->hide();
        se6_edit->setValue(0);
        se6_edit->hide();
    }
    else {
        se6->show();
        se6_edit->show();
        se6_edit->setValue(student.sem6);
    }
    if(student.sem7==0)
    {
        se7->hide();
        se7_edit->setValue(0);
        se7_edit->hide();
    }
    else {
        se7->show();
        se7_edit->show();
        se7_edit->setValue(student.sem6);
    }

    if(student.sem8==0)
    {
        se8->hide();
        se8_edit->setValue(0);
        se8_edit->hide();
    }
    else {
        se8->show();
        se8_edit->show();
        se8_edit->setValue(student.sem6);
    }


    update_widget->setGeometry(700,350,400,400);
    update_widget->show();
    this->repaint();
//    setStyleSheet("background-color:#FFFCCC;");

    connect(m_calButton,SIGNAL(clicked()),m_cal,SLOT(show()),Qt::UniqueConnection);
    connect(m_cal,SIGNAL(clicked(QDate)),this,SLOT(onDateSelected(QDate)),Qt::UniqueConnection);

    connect(update1,SIGNAL(clicked(bool)),this,SLOT(update_stud()));
    connect(cancel2,SIGNAL(clicked(bool)),this,SLOT(close_update()));
//    connect(update_widget,SIGNAL(closeEvent()),this,SLOT(close_update()));

}

void Search_Student::update_stud()
{
     Student stud;
     stud.name=name_edit->text();
     stud.usn=usnedit->text();
     stud.email=email_edit->text();
     stud.dept=dept_edit->currentText();
     stud.contact=contact_edit->text();
     stud.dob=m_calButton->text();
     stud.cgpa=cgpa_edit->value();
     stud.ten=ten_edit->value();
     stud.twelve=twelve_edit->value();
     stud.backlogs=backlog_edit->value();
     stud.sem1=se1_edit->value();
     stud.sem2=se2_edit->value();
     stud.sem3=se3_edit->value();
     stud.sem4=se4_edit->value();
     stud.sem5=se5_edit->value();
     stud.sem6=se6_edit->value();
     stud.sem7=se7_edit->value();
     stud.sem8=se8_edit->value();

     if(db.update_student(stud))
     {
         msgBox.setText("Successfully updated student data");
         msgBox.exec();
     }
     else {
         msgBox.setText("Couldn't update Student data");
         msgBox.exec();
     }
}

void Search_Student::onDateSelected(QDate date)
{
    m_cal->close();
    m_date = date;
    m_calButton->setText(date.toString("dd MMM yyyy,ddd"));
}

void Search_Student::delete_stud()
{
    QMessageBox msg;

     msg.setInformativeText("Are you sure you want to delete?");
     msg.setStandardButtons(QMessageBox::Yes |  QMessageBox::Cancel);
     msg.setDefaultButton(QMessageBox::Yes);
     int ret = msg.exec();

     switch (ret) {
       case QMessageBox::Yes:
         if(db.delete_student(student))
         {
             msgBox.setText("Deleted student successfully");
             msgBox.exec();
         }
         else {
             msgBox.setText("Couldn't delete student ");
             msgBox.exec();
         }
           break;
       case QMessageBox::Cancel:
           // Don't Save was clicked
           break;
       default:
           // should never be reached
           break;
     }


}

void Search_Student::toUpper(QString txt)
{
    usn_edit->setText(txt.toUpper());
}
void Search_Student::close_update()
{
    update_widget->close();
    update_widget->deleteLater();
    this->setEnabled(true);
}
void Search_Student::closeEvent(QCloseEvent *event)
{
    event->accept();
}
Search_Student::~Search_Student()
{
}
