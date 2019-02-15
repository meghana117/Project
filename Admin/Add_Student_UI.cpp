#include "Add_Student_UI.h"


Add_Student_UI::Add_Student_UI(QWidget *parent) : QWidget(parent)
{

    m_calButton = new QPushButton("Select");
    m_calButton->setFlat(true);

    this->setGeometry(700,300,600,600);

    add=new QPushButton("Add");
//    add->setObjectName("add_syudent_button");
    add->setAutoDefault(true);
    cancel=new QPushButton("Cancel");
    cancel->setAutoDefault(true);
    name=new QLabel("Name");
    usn=new QLabel("USN");
    dob=new QLabel("DOB");
    email=new QLabel("Email");
    dept=new QLabel("Department");
    contact=new QLabel("Contact no.");
    cgpa=new QLabel("CGPA");
    backlog=new QLabel("No. of backlogs");
    error=new QLabel();
    ten=new QLabel("10th Percentage");
    twelve=new QLabel("12th Percentage");
    sems=new QLabel("Semesters available");
    sem1=new QLabel("SGPA1");
    sem2=new QLabel("SGPA2");
    sem3=new QLabel("SGPA3");
    sem4=new QLabel("SGPA4");
    sem5=new QLabel("SGPA5");
    sem6=new QLabel("SGPA6");
    sem7=new QLabel("SGPA7");
    sem8=new QLabel("SGPA8");

    sems_edit=new QSpinBox();
    sems_edit->setMinimum(5);
    sems_edit->setMaximum(8);

    sem1_edit=new QDoubleSpinBox();
    sem1_edit->setMaximum(10);

    sem2_edit=new QDoubleSpinBox();
    sem2_edit->setMaximum(10);

    sem3_edit=new QDoubleSpinBox();
    sem3_edit->setMaximum(10);

    sem4_edit=new QDoubleSpinBox();
    sem4_edit->setMaximum(10);

    sem5_edit=new QDoubleSpinBox();
    sem5_edit->setMaximum(10);

    sem6_edit=new QDoubleSpinBox();
    sem6_edit->setMaximum(10);

    sem7_edit=new QDoubleSpinBox();
    sem7_edit->setMaximum(10);

    sem8_edit=new QDoubleSpinBox();
    sem8_edit->setMaximum(10);

    name_edit=new QLineEdit();
    QRegExp valid_name("[a-zA-Z ]+");
    QRegExpValidator *validate_name=new QRegExpValidator(valid_name,this);
    name_edit->setValidator(validate_name);

    QRegExp expusn("^[1]{1}[Dd]{1}[Aa]{1}[0-9]{2}[A-Za-z]{2}[0-9]{3}$/i");
    QRegExpValidator *validate_usn=new QRegExpValidator(expusn,this);
    usn_edit=new QLineEdit();
    usn_edit->setValidator(validate_usn);


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

    add=new QPushButton("Add");
    cancel=new QPushButton("Cancel");

    add_csv=new QPushButton("Add file");
    choose_csv=new QPushButton("Choose file");

    or_label=new QLabel("OR");

    selecetd_file=new QLabel();

    vb1=new QVBoxLayout();
    hb1=new QHBoxLayout();
    hb2=new QHBoxLayout();

    form1=new QFormLayout();
    form1->addRow(name,name_edit);
    form1->addRow(usn,usn_edit);
    form1->addRow(dob,m_calButton);
    form1->addRow(email,email_edit);
    form1->addRow(contact,contact_edit);
    form1->addRow(dept,dept_edit);
    form1->addRow(sems,sems_edit);
    form1->addRow(sem1,sem1_edit);
    form1->addRow(sem2,sem2_edit);
    form1->addRow(sem3,sem3_edit);
    form1->addRow(sem4,sem4_edit);
    form1->addRow(sem5,sem5_edit);
    form1->addRow(sem6,sem6_edit);
    form1->addRow(sem7,sem7_edit);
    form1->addRow(sem8,sem8_edit);
    form1->addRow(cgpa,cgpa_edit);
    sem6_edit->setEnabled(false);
    sem7_edit->setEnabled(false);
    sem8_edit->setEnabled(false);
    cgpa_edit->setEnabled(false);
    form1->addRow(backlog,backlog_edit);
    form1->addRow(ten,ten_edit);
    form1->addRow(twelve,twelve_edit);
    form1->addRow(error);
    hb1->addWidget(add);
    hb1->addWidget(cancel);


    vb1->addLayout(form1);
    vb1->addLayout(hb1);
    vb1->addWidget(or_label);
    vb1->addWidget(selecetd_file);
    hb2->addWidget(choose_csv);
    hb2->addWidget(add_csv);
    vb1->addLayout(hb2);

    form1->setRowWrapPolicy(QFormLayout::DontWrapRows);

    form1->setFormAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    form1->setLabelAlignment(Qt::AlignLeft);
    form1->setAlignment(or_label,Qt::AlignCenter);

    this->setLayout(vb1);

    connect(m_calButton,SIGNAL(clicked()),m_cal,SLOT(show()),Qt::UniqueConnection);
    connect(m_cal,SIGNAL(clicked(QDate)),this,SLOT(onDateSelected(QDate)),Qt::UniqueConnection);
    connect(add,SIGNAL(clicked(bool)),this,SLOT(add_stud()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(usn_edit,SIGNAL(textEdited(QString)),this,SLOT(toUpper(QString)));
    connect(choose_csv,SIGNAL(clicked()),this,SLOT(choose_file()));
    connect(add_csv,SIGNAL(clicked()),this,SLOT(add_file()));
    connect(sem1_edit,SIGNAL(valueChanged(double)),this,SLOT(cgpa_value(double)));
    connect(sem2_edit,SIGNAL(valueChanged(double)),this,SLOT(cgpa_value(double)));
    connect(sem3_edit,SIGNAL(valueChanged(double)),this,SLOT(cgpa_value(double)));
    connect(sem4_edit,SIGNAL(valueChanged(double)),this,SLOT(cgpa_value(double)));
    connect(sem5_edit,SIGNAL(valueChanged(double)),this,SLOT(cgpa_value(double)));
    connect(sem6_edit,SIGNAL(valueChanged(double)),this,SLOT(cgpa_value(double)));
    connect(sem7_edit,SIGNAL(valueChanged(double)),this,SLOT(cgpa_value(double)));
    connect(sem8_edit,SIGNAL(valueChanged(double)),this,SLOT(cgpa_value(double)));
    connect(sems_edit,SIGNAL(valueChanged(int)),this,SLOT(disable_sgpa(int)));


}

void Add_Student_UI::add_stud()
{
    QDate today;
    Student student;
    today=today.currentDate();
    student.name=name_edit->text();
    student.usn=usn_edit->text();
    student.backlogs=backlog_edit->value();
    student.cgpa=cgpa_edit->value();
    student.contact=contact_edit->text();
    student.dept=dept_edit->currentText();
    student.email=email_edit->text();
    student.password=m_date.toString("dd/MM/yyyy");
    student.dob=m_date.toString("dd/MM/yyyy");
    student.ten=ten_edit->value();
    student.twelve=twelve_edit->value();
    student.sem1=sem1_edit->value();
    student.sem2=sem2_edit->value();
    student.sem3=sem3_edit->value();
    student.sem4=sem4_edit->value();
    student.sem5=sem5_edit->value();
    student.sem6=sem6_edit->value();
    student.sem7=sem7_edit->value();
    student.sem8=sem8_edit->value();


    if(student.name.isEmpty()||student.usn.isEmpty()||student.usn.length()<10 || student.contact==NULL || student.email.isEmpty()|| student.usn.isEmpty()|| student.dept.isEmpty() || student.ten<=0 || student.twelve<=0)
    {
        QMessageBox msgBox;
        msgBox.setText("Please enter valid data for all the fields");
        msgBox.exec();
    }
    else
    {

        if(db.add_student(student))
        {
            QMessageBox msgBox;
            msgBox.setText("Student added Successfully!");
            msgBox.exec();
            name_edit->clear();
            usn_edit->clear();
//            dept_edit->clear();
            contact_edit->clear();
            email_edit->clear();
            cgpa_edit->clear();
            backlog_edit->clear();
            ten_edit->clear();
            twelve_edit->clear();
            sem1_edit->clear();
            sem2_edit->clear();
            sem3_edit->clear();
            sem4_edit->clear();
            sem5_edit->clear();
            sem6_edit->clear();
            sem7_edit->clear();
            sem8_edit->clear();
            error->setText(" ");
        }
        else
        {
            error->setText("Duplicate USN");
        }
    }
}

void Add_Student_UI::toUpper(QString txt)
{
    usn_edit->setText(txt.toUpper());
}
void Add_Student_UI::onDateSelected(QDate date)
{
    m_cal->close();
    m_date = date;
    m_calButton->setText(date.toString("dd/MM/yyyy"));
}

void Add_Student_UI::choose_file()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Open file"), "",tr("Pdf(*.csv)"));
    selecetd_file->setText(fileName);

}
void Add_Student_UI::add_file()

{
     if(db.savedata(fileName))
     {
         QMessageBox msgBox;
         msgBox.setText("File added Successfully!");
         msgBox.exec();
         selecetd_file->clear();
     }
     else
     {
         QMessageBox msgBox;
         msgBox.setText("File couldn't be added!");
         msgBox.exec();
     }

}
void Add_Student_UI::disable_sgpa(int i)
{
    sem6_edit->setEnabled(true);
    sem7_edit->setEnabled(true);
    sem8_edit->setEnabled(true);

    if(i==5)
    {
        sem6_edit->setValue(0);
        sem7_edit->setValue(0);
        sem8_edit->setValue(0);
        sem6_edit->setEnabled(false);
        sem7_edit->setEnabled(false);
        sem8_edit->setEnabled(false);
    }
    if(i==6)
    {
        sem7_edit->setValue(0);
        sem8_edit->setValue(0);
        sem7_edit->setEnabled(false);
        sem8_edit->setEnabled(false);
    }
    if(i==7)
    {
        sem8_edit->setValue(0);
        sem8_edit->setEnabled(false);
    }
}
void Add_Student_UI::cgpa_value(double d)
{
    double val=(sem1_edit->value()+sem2_edit->value()+sem3_edit->value()+sem4_edit->value()+sem5_edit->value()+sem6_edit->value()+sem7_edit->value()+sem8_edit->value())/sems_edit->value();
    cgpa_edit->setValue(val);
}
Add_Student_UI::~Add_Student_UI()
{
}
