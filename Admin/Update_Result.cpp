#include "Update_Result.h"

Update_Result::Update_Result(QWidget *parent) : QWidget(parent)
{
    form1=new QFormLayout();
    update=new QPushButton("Update");
    update1=new QPushButton("Update");
    cancel=new QPushButton("Cancel");
    choose=new QPushButton("Choose file");
    USN=new QLabel("USN");
    Sem=new QLabel("Semester");
    sem=new QLabel("Semester");
    error1=new QLabel();
    error2=new QLabel();
    error3=new QLabel();
    selected=new QLabel();
    Sems=new QComboBox();
    sems=new QComboBox();
    sgpa=new QLabel("SGPA");
    Sgpa=new QDoubleSpinBox();
    Sgpa->setMaximum(10.0);
    usn=new QLineEdit();
    OrLabel=new QLabel("OR");

    form1->addRow(USN,usn);
    form1->addRow(Sem,Sems);
    form1->addRow(sgpa,Sgpa);
    form1->addWidget(update);

    form1->addWidget(OrLabel);

    form1->addRow(sem,sems);
    form1->addWidget(error2);
    form1->addRow(choose,selected);
    form1->addWidget(error3);

    form1->addRow(update1,cancel);

    this->setLayout(form1);
}
