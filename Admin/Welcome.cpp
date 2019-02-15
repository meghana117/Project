#include "Welcome.h"

Welcome::Welcome(QWidget *parent) : QWidget(parent)
{
//    QScreen *sc = qApp->primaryScreen();
//    int m_width = sc->geometry().width();
//    int m_height = sc->geometry().height();

    QPixmap setIcon(":/images/dr-ait-logo.png");
    QPixmap(10,15);

//    this->setGeometry(0,0,m_width,m_height);

    this->setMinimumSize(700,400);

    student=new QPushButton("Add Students");
    student->setObjectName("tab");
    student->setIcon(QIcon(":/images/add_group-512.png"));
    student->setIconSize(setIcon.rect().size());

   update=new QPushButton("Update Student Info");
   update->setObjectName("tab");
   update->setIcon(QIcon(":/images/update.png"));
   update->setIconSize(setIcon.rect().size());

    papers=new QPushButton("Placement Papers");
   papers->setObjectName("tab");
   papers->setIcon(QIcon(":/images/papers.png"));
   papers->setIconSize(setIcon.rect().size());

   training=new QPushButton("Training Schedule");
   training->setObjectName("tab");
  training->setIcon(QIcon(":/images/training.png"));
   training->setIconSize(setIcon.rect().size());

   placement=new QPushButton("Placement schedule");
   placement->setObjectName("tab");
   placement->setIcon(QIcon(":/images/placement.png"));
   placement->setIconSize(setIcon.rect().size());

   companies=new QPushButton("Companies visited");
   companies->setObjectName("tab");
   companies->setIcon(QIcon(":/images/IT-Companies-Logos[3].jpg"));
   companies->setIconSize(setIcon.rect().size());

    sort=new QPushButton("Sort/Select Students");
    sort->setObjectName("tab");
    sort->setIcon(QIcon(":/images/filter_and_sort.png"));
    sort->setIconSize(setIcon.rect().size());

    search=new QPushButton("Search Student");
    search->setObjectName("tab");
    search->setIcon(QIcon(":/images/search.png"));
    search->setIconSize(setIcon.rect().size());

    placed=new QPushButton("Placed Students");
    placed->setObjectName("tab");
    placed->setIcon(QIcon(":/images/placed.png"));
    placed->setIconSize(setIcon.rect().size());

    contact=new QPushButton("Contact");
    contact->setObjectName("tab");
    contact->setIcon(QIcon(":/images/contact.png"));
    contact->setIconSize(setIcon.rect().size());

    Logout=new QPushButton("Logout");
    Logout->setObjectName("tab");
    Logout->setIcon(QIcon(":/images/logout.png"));
    Logout->setIconSize(setIcon.rect().size());

    picture=new QLabel();
    hb6=new QHBoxLayout();

    QPixmap pic(":/images/dr-ait-logo.png");
    QPixmap scaled=pic.scaled ( this->geometry().width(), 150, Qt::IgnoreAspectRatio, Qt::FastTransformation );

    picture->setPixmap(scaled);
    picture->setObjectName("logo-pic");
    hb6->addWidget(picture);
    hb6->setObjectName("pic-layout");

    vb1=new QVBoxLayout();

    vb1->addLayout(hb6);
//    vb1->setAlignment(hb6,Qt::AlignTop);
    hb1=new QHBoxLayout();
    hb1->addWidget(student);
    hb1->addWidget(update);
    hb1->addWidget(search);
    vb1->addLayout(hb1);



    vb2=new QVBoxLayout();
    hb2=new QHBoxLayout();
    hb2->addWidget(papers);
    hb2->addWidget(training);
    hb2->addWidget(placement);
    vb1->addLayout(hb2);

    vb3=new QVBoxLayout();
    hb3=new QHBoxLayout();
    hb3->addWidget(companies);
    hb3->addWidget(sort);
    hb3->addWidget(placed);
    vb1->addLayout(hb3);

    vb4=new QVBoxLayout();
    hb4=new QHBoxLayout();
    hb4->addWidget(contact);
    hb4->addWidget(Logout);
    vb1->addLayout(hb4);

//    vb5=new QVBoxLayout();
//    vb5->addLayout(vb1);
//    vb5->addLayout(vb2);
//    vb5->addLayout(vb3);
//    vb5->addLayout(vb4);

    this->setLayout(vb1);


    connect(student,SIGNAL(clicked(bool)),this,SLOT(add_stud()));
    this->setStyleSheet("QPushButton:hovered{color:white;}");
    connect(search,SIGNAL(clicked(bool)),this,SLOT(search_student()));
    connect(training,SIGNAL(clicked(bool)),this,SLOT(training_details()));
    connect(placement,SIGNAL(clicked(bool)),this,SLOT(placement_details()));
    connect(companies,SIGNAL(clicked(bool)),this,SLOT(companies_visited()));
    connect(placed,SIGNAL(clicked(bool)),this,SLOT(placed_info()));
    connect(papers,SIGNAL(clicked(bool)),this,SLOT(placement_papers()));
    connect(contact,SIGNAL(clicked(bool)),this,SLOT(contact_details()));
    connect(sort,SIGNAL(clicked(bool)),this,SLOT(select_students()));
    connect(update,SIGNAL(clicked(bool)),this,SLOT(update_result()));

}

void Welcome::add_stud()
{
    this->setEnabled(false);
//    this->close();
    add_student.show();
    this->setEnabled(true);
}
void Welcome::update_result()
{
    Update.show();
}

void Welcome::search_student()
{
    search_stud.show();
}
void Welcome::training_details()
{
    train.show();
}
void Welcome::placement_details()
{
    place.show();
}
void Welcome::companies_visited()
{
    company.show();
}
void Welcome::placed_info()
{

    placed_ui.show();
}

void Welcome::placement_papers()
{
    paper.show();
}
void Welcome::contact_details()
{
    contct.show();
}
void Welcome::select_students()
{
    select.show();
}
Welcome::~Welcome()
{

}
