
#include "Db_Class.h"

Db_Class::Db_Class(QObject *parent) : QObject(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
        db.setDatabaseName("Placement");
        db.setPort(3306);
        db.setUserName("meghana");
        db.setPassword("meghana");

    if(db.open())
    {
        qDebug() << "DB File Opened" << endl;

        QSqlQuery query;
        query.prepare("PRAGMA foreign_keys=ON");
        query.exec();
        query.prepare("create table if not exists Admin(name varchar(100) primary key,password varchar(50),email TEXT)");
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
        query.prepare("Insert into Admin (name,password,email) values('admin','admin123','meghanar1998@gmail.com')");
        query.exec();
        query.prepare("create table if not exists Student(usn varchar(12) PRIMARY KEY,password varchar(20),"
                      "name varchar(50) NOT NULL,email varchar(100) NOT NULL,dept varchar(150) NOT NULL,contact varchar(15) NOT NULL,"
                      "ten FLOAT NOT NULL,twelve FLOAT NOT NULL,sem1 FLOAT,sem2 FLOAT,sem3 FLOAT,sem4 FLOAT,sem5 FLOAT,sem6 FLOAT,sem7 FLOAT,sem8 FLOAT,cgpa FLOAT NOT NULL,offer INTEGER,backlog INTEGER,resume BLOB,dob varchar(15) NOT NULL)");
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
        QSqlQuery q;
        q.prepare("create table if not exists Training(id int Primary key AUTO_INCREMENT ,topic varchar(100),details varchar(2000),fromdate varchar(15),todate varchar(15))");
        if(!q.exec())
            qDebug()<<q.lastError();

        q.prepare("create table if not exists Placement(id int Primary key AUTO_INCREMENT,company varchar(500),title varchar(200),package FLOAT, eligibility varchar(5000), schedule varchar(15),venue varchar(250))");
        if(!q.exec())
        {
            qDebug()<<q.lastError();
        }

        q.prepare("create table if not exists Company(id int Primary key AUTO_INCREMENT, company_name varchar(500) NOT NULL UNIQUE,intake int)");
        if(!q.exec())
            qDebug()<<q.lastError();

        q.prepare("create table if not exists Placed(id int Primary key AUTO_INCREMENT, USN varchar(15) NOT NULL, company_name varchar(500) NOT NULL,salary float NOT NULL,CONSTRAINT fk_comp Foreign key(company_name) references Company(company_name)  ON DELETE CASCADE, CONSTRAINT fk_stud Foreign key(USN) references Student(usn) ON DELETE CASCADE)");
        if(!q.exec())
            qDebug()<<q.lastError();

        q.prepare("create table if not exists Papers(id int Primary key NOT NULL AUTO_INCREMENT,name varchar(50) NOT NULL UNIQUE,data BLOB NOT NULL)");
        if(!q.exec())
            qDebug()<<q.lastError();

        q.prepare("create table if not exists Contact(id int Primary key NOT NULL AUTO_INCREMENT,name varchar(50) NOT NULL UNIQUE,designation varchar(200) NOT NULL,contact1 varchar(15) NOT NULL, contact2 varchar(15) DEFAULT NULL, email varchar(100) NOT NULL)");
        if(!q.exec())
            qDebug()<<q.lastError();

        qDebug() << "Tables created " << db.lastError();
    }
    else{
        qDebug() << "DB File didnt open" << endl;
    }
}
bool Db_Class::checklog(Admin a)
{
    QSqlQuery qry;
    QString n,p;
    qry.prepare("SELECT * from Admin");
    if(qry.exec()){
        while(qry.next())
        {
            n=qry.value("name").toString();
            qDebug()<<n<<""<<p<<endl;
            p=qry.value("password").toString();
            if(n==a.name && p==a.pass)
            {
                return true;
            }
        }
    }
    qDebug()<<qry.lastError();
    return false;
}

bool Db_Class::add_student(Student student)
{
    QSqlQuery query;
    query.prepare("insert into Student(name,USN,email,dept,contact,cgpa,backlog,password,DOB,ten,sem1,sem2,sem3,sem4,sem5,sem6,sem7,sem8,twelve,offer) values (:Name,:Usn,:Email,:Dept,:Contact,:Cgpa,:Backlog,:Password,:Dob,:Ten,:Sem1,:Sem2,:Sem3,:Sem4,:Sem5,:Sem6,:Sem7,:Sem8,:Twelve,:Offers);");
    query.bindValue(":Name",student.name);
    query.bindValue(":Usn",student.usn);
    query.bindValue(":Email",student.email);
    query.bindValue(":Dept",student.dept);
    query.bindValue(":Contact",student.contact);
    query.bindValue(":Cgpa",student.cgpa);
    query.bindValue(":Backlog",student.backlogs);
    query.bindValue(":Password",student.password);
    query.bindValue(":Dob",student.dob);
    query.bindValue(":Ten",student.ten);
    query.bindValue(":Sem1",student.sem1);
    query.bindValue(":Sem2",student.sem2);
    query.bindValue(":Sem3",student.sem3);
    query.bindValue(":Sem4",student.sem4);
    query.bindValue(":Sem5",student.sem5);
    query.bindValue(":Sem6",student.sem6);
    query.bindValue(":Sem7",student.sem7);
    query.bindValue(":Sem8",student.sem8);
    query.bindValue(":Twelve",student.twelve);
    query.bindValue(":Offers",0);
    if(query.exec())
    {
        return true;
    }
    else
    {
    qDebug()<<query.lastError()<< "Error ";
    return false;
    }
}
bool Db_Class::savedata(QString fileName)
{

    QFile file(fileName);
    if(file.open (QIODevice::ReadOnly)){
        QSqlQuery que;
        QTextStream ts (&file);
        int i=0;
        while(!ts.atEnd()){

            QString req = "INSERT INTO Student(usn,name,email,dept,contact,ten,twelve,sem1,sem2,sem3,sem4,sem5,sem6,sem7,sem8,cgpa,offer,backlog,dob) VALUES(";
            // split every lines on comma
            QStringList line = ts.readLine().split(',');
            if(i==0)
            {
                i=1;
                continue;
            }
            /*for every values on a line,
                append it to the INSERT request*/
            for(int i=0; i<line .length ();i++){
                req.append("'"+line.at(i)+"'");
                req.append(",");
            }
            req.chop(1); // remove the trailing comma
            req.append(");"); // close the "VALUES([...]" with a ");"
            if(!que.exec(req))
            {
                qDebug()<<que.lastError();
            }
        }
        return true;
    }
    else {
        return false;
    }
}

Student Db_Class::search_student(Student student)
{
    QSqlQuery query;
    query.prepare("Select * From Student where USN=:susn");
    query.bindValue(":susn",student.usn);
    if(query.exec())
    {
        while (query.next()) {

        student.name=query.value("name").toString();
        student.usn=query.value("USN").toString();
        student.email=query.value("email").toString();
        student.dob=query.value("DOB").toString();
        student.contact=query.value("contact").toString();
        student.backlogs=query.value("backlog").toInt();
        student.cgpa=query.value("cgpa").toFloat();
        student.dept=query.value("dept").toString();
        student.ten=query.value("ten").toFloat();
        student.twelve=query.value("twelve").toFloat();
        student.offer=query.value("offer").toInt();
        student.offer=query.value("offer").toInt();
        student.sem1=query.value("sem1").toFloat();
        student.sem2=query.value("sem2").toFloat();
        student.sem3=query.value("sem3").toFloat();
        student.sem4=query.value("sem4").toFloat();
        student.sem5=query.value("sem5").toFloat();
        student.sem6=query.value("sem6").toFloat();
        student.sem7=query.value("sem7").toFloat();
        student.sem8=query.value("sem8").toFloat();
        }

        return student;
    }
    else {
        qDebug()<<query.lastError()<<" DB Error\n";
    }
}
bool Db_Class::update_student(Student student)
{
    QSqlQuery query;
    query.prepare("UPDATE Student SET name=:Name,email=:Email,dept=:Dept,contact=:Contact,cgpa=:Cgpa,backlog=:Backlog,DOB=:Dob,sem1=:Sem1,sem2=:Sem2,sem3=:Sem3,sem4=:Sem4,sem5=:Sem5,sem6=:Sem6,sem7=:Sem7,sem8=:Sem8,ten=:Ten,twelve=:Twelve  Where USN=:USN");
    query.bindValue(":USN",student.usn);
    query.bindValue(":Name",student.name);
    query.bindValue(":Email",student.email);
    query.bindValue(":Dept",student.dept);
    query.bindValue(":Contact",student.contact);
    query.bindValue(":Cgpa",student.cgpa);
    query.bindValue(":Backlog",student.backlogs);
    query.bindValue(":Dob",student.dob);
    query.bindValue(":Ten",student.ten);
    query.bindValue(":Twelve",student.twelve);
    query.bindValue(":Sem1",student.sem1);
    query.bindValue(":Sem2",student.sem2);
    query.bindValue(":Sem3",student.sem3);
    query.bindValue(":Sem4",student.sem4);
    query.bindValue(":Sem5",student.sem5);
    query.bindValue(":Sem6",student.sem6);
    query.bindValue(":Sem7",student.sem7);
    query.bindValue(":Sem8",student.sem8);

    if(query.exec())
    {
        return true;
    }
    else {
        qDebug()<<query.lastError()<<" DB Error\n";

        return false;
    }

}
bool Db_Class::delete_student(Student student)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Student where USN=:usn");
    query.bindValue(":usn",student.usn);
    if(query.exec())
    {
        return true;
    }
    else {
        qDebug()<<query.lastError()<<" DB Error\n";

        return false;
    }
}
bool Db_Class::add_training(Training_Object training)
{

    QSqlQuery query;

    query.prepare("INSERT INTO Training (topic,details,fromdate,todate) values (:Topic,:Details,:From,:To)");
    query.bindValue(":Topic",training.topic);
    query.bindValue(":Details",training.details);
    query.bindValue(":From",training.from);
    query.bindValue(":To",training.to);

    if(query.exec())
    {
        return true;
    }
    else {
        qDebug()<<query.lastError()<<"Db error\n";
        return false;
    }
}
int Db_Class::getTrainingCount()
{
    QSqlQuery qry;
    qry.prepare("Select count(*) from Training;");
    qry.exec();
    while (qry.next()) {
        return (qry.value(0).toInt());
    }
    return 0;
}
void Db_Class::getTrainingDetail(Training_Object trainings[])
{
    QSqlQuery query;
    int i=0;
    query.prepare("SELECT * from Training");
    if(query.exec())
    {
        while(query.next())
        {
            trainings[i].topic=query.value("topic").toString();
            trainings[i].details=query.value("details").toString();
            trainings[i].from=query.value("fromdate").toString();
            trainings[i].to=query.value("todate").toString();
            i++;

        }
    }
    else {
        qDebug()<<query.lastError();
    }
}
bool Db_Class::delete_training(QString topic)
{
    QSqlQuery query;
    query.prepare("Delete from Training where topic=:Topic");
    query.bindValue(":Topic",topic);
    if(query.exec())
        return true;
    else {
        qDebug()<<query.lastError();
        return false;
    }
}

bool Db_Class::add_placement(Placement_Object placement)
{

    QSqlQuery query;

    query.prepare("INSERT INTO Placement (company,title,package,eligibility,schedule,venue) values (:Company,:Title,:Package,:Eligibility,:Schedule,:Venue)");
    query.bindValue(":Company",placement.company);
    query.bindValue(":Title",placement.title);
    query.bindValue(":Package",placement.package);
    query.bindValue(":Eligibility",placement.eligibility);
    query.bindValue(":Schedule",placement.date);
    query.bindValue(":Venue",placement.venue);

    if(query.exec())
    {
        return true;
    }
    else {
        qDebug()<<query.lastError()<<"Db error\n";
        return false;
    }
}
int Db_Class::getPlacementCount()
{
    QSqlQuery qry;
    qry.prepare("Select count(*) from Placement;");
    qry.exec();
    while (qry.next()) {
        return (qry.value(0).toInt());
    }
    return 0;
}
void Db_Class::getPlacementDetail(Placement_Object placements[])
{
    QSqlQuery query;
    int i=0;
    query.prepare("SELECT * from Placement");
    if(query.exec())
    {
        while(query.next())
        {
            placements[i].company=query.value("company").toString();
            placements[i].eligibility=query.value("eligibility").toString();
            placements[i].date=query.value("schedule").toString();
            placements[i].title=query.value("title").toString();
            placements[i].package=query.value("package").toFloat();
            placements[i].venue=query.value("venue").toString();
            i++;

        }
    }
    else {
        qDebug()<<query.lastError();
    }
}
bool Db_Class::delete_placement(QString company)
{
    QSqlQuery query;
    query.prepare("Delete from Placement where company=:Company");
    query.bindValue(":Company",company);
    if(query.exec())
        return true;
    else {
        qDebug()<<query.lastError();
        return false;
    }
}

bool Db_Class::add_company(Company_Object company)
{

    QSqlQuery query;


    query.prepare("INSERT INTO Company (company_name,intake) values (:Company,:zero)");
    query.bindValue(":Company",company.company_name);
    query.bindValue(":zero",0);

    if(query.exec())
    {
        return true;
    }
    else {
        qDebug()<<query.lastError()<<"Db Company error\n";
        return false;
    }
}
int Db_Class::getCompanyCount()
{
    QSqlQuery qry;
    qry.prepare("Select count(*) from Company;");
    qry.exec();
    while (qry.next()) {
        return (qry.value(0).toInt());
    }
    return 0;
}
void Db_Class::getCompanyDetail(Company_Object companies[] )
{
    QSqlQuery query;
    int i=0;
    query.prepare("SELECT * from Company");
    if(query.exec())
    {
        while(query.next())
        {
            companies[i].company_name=query.value("company_name").toString();
            companies[i].intake=query.value("intake").toInt();
            i++;
        }
    }
    else {
        qDebug()<<query.lastError();
    }
}
bool Db_Class::add_placed(Placed_object placed)
{

    QSqlQuery query,qry;
    int i=0;
    query.prepare("SELECT count(usn) from Student where usn=:Usn");
    query.bindValue(":Usn",placed.USN);
    query.exec();
    if(query.next())
    {
        if(query.value(0)==0)
            return false;
    }
    qry.prepare("SELECT * from Placed where USN=:Usn and company_name=:Company");
    qry.bindValue("Usn",placed.USN);
    qry.bindValue("Company",placed.company);
    qry.exec();
    while(qry.next())
    {
        i++;
    }

    if(i>0)
    {
        return false;
    }
    query.prepare("INSERT INTO Placed (USN,company_name,salary) values (:Usn,:Company,:Salary)");
    query.bindValue(":Company",placed.company);
    query.bindValue(":Usn",placed.USN);
    query.bindValue(":Salary",placed.salary);

    if(query.exec())
    {
        qry.prepare("UPDATE Student Set offer=offer+1 where usn=:Usn");
        qry.bindValue(":Usn",placed.USN);
        if(!qry.exec())
            qDebug()<<qry.lastError();


        qry.prepare("UPDATE Company Set intake=intake+1 where company_name=:Company");
        qry.bindValue(":Company",placed.company);
        if(!qry.exec())
            qDebug()<<qry.lastError();
        else {
            return true;
        }
    }
    else {
        qDebug()<<query.lastError()<<"Db error\n";
        return false;
    }
    return false;
}
int Db_Class::getPlacedCount()
{
    QSqlQuery qry;
    qry.prepare("Select count(*) from Placed;");
    qry.exec();
    while (qry.next()) {
        return (qry.value(0).toInt());
    }
    return 0;
}
void Db_Class::getPlacedDetail(Placed_object placed[])
{
    QSqlQuery query;
    int i=0;
    query.prepare("SELECT * from Placed");
    if(query.exec())
    {
        while(query.next())
        {
            placed[i].company=query.value("company_name").toString();
            placed[i].USN=query.value("USN").toString();
            placed[i].salary=query.value("salary").toFloat();
            i++;

        }
    }
    else {
        qDebug()<<query.lastError();
    }
}
bool Db_Class::delete_placed(QString company,QString usn)
{
    QSqlQuery query,qry;
    query.prepare("Delete from Placed where company_name=:Company and USN=:Usn");
    query.bindValue(":Company",company);
    query.bindValue(":Usn",usn);
    if(!query.exec())
    {
        qDebug()<<"Error deleted placed";
        qDebug()<<query.lastError();
    }
    query.prepare("UPDATE Student set offer=offer-1 where usn=:Usn");
    query.bindValue(":Usn",usn);

    if(!query.exec())
        qDebug()<<query.lastError();

    qry.prepare("UPDATE Company Set intake=intake-1 where company_name=:Company");
    qry.bindValue(":Company",company);
    if(!qry.exec())
        qDebug()<<qry.lastError();
    else {
        return true;
    }
    return false;
}
QString Db_Class::get_name(QString usn)
{
    QSqlQuery qry;
    QString name;
    qry.prepare("SELECT name from Student where usn=:Usn");
    qry.bindValue(":Usn",usn);
    if(qry.exec())
    {
        while(qry.next())
        {
            name=qry.value("name").toString();
        }
        return name;
    }
    else {
        qDebug()<<qry.lastError();
    }
    return NULL;
}
QString Db_Class::get_dept(QString usn)
{
    QSqlQuery qry;
    QString dept;
    qry.prepare("SELECT dept from Student where usn=:Usn");
    qry.bindValue(":Usn",usn);
    if(qry.exec())
    {
        while(qry.next())
        {
              dept=qry.value("dept").toString();
        }
        return dept;
    }
    else{
        qDebug()<<qry.lastError();
    }
    return NULL;
}

int Db_Class::get_usn_placed_count(QString usn)
{
    QSqlQuery qry;
//    int i=0;
    qry.prepare("Select count(:Usn) from Placed");
    qry.bindValue("Usn",usn);
    if(qry.exec())
    {
        while (qry.next()) {
            return (qry.value(0).toInt());
        }
    }
    else {
        qDebug()<<qry.lastError()<<"At getting count";
        return 0;
    }
    return 0;
}
void Db_Class::get_placed_companies(Company_Object companies[],QString usn)
{
    QSqlQuery query;
    int i=0;
    query.prepare("Select * from Placed where usn=:Usn");
    query.bindValue(":Usn",usn);
    query.exec();

    if(query.exec())
    {
        while(query.next())
        {
            companies[i].company_name=query.value("company_name").toString();
            i++;
        }
    }
    else {
        qDebug()<<query.lastError();
    }

}

bool Db_Class::add_paper_to_db(Paper paper)
{

    QSqlQuery query;

    query.prepare("INSERT INTO Papers (name,data) values (:Name,:Data)");
    query.bindValue(":Name",paper.name);
    query.bindValue(":Data",paper.file);

    if(query.exec())
    {
        return true;
    }
    else {
        qDebug()<<query.lastError()<<"Db error\n";
        return false;
    }
}
int Db_Class::getpapersCount()
{
    QSqlQuery qry;
    qry.prepare("Select count(*) from Papers;");
    qry.exec();
    while (qry.next()) {
        return (qry.value(0).toInt());
    }
    return 0;
}
void Db_Class::getPaperDetail(Paper papers[])
{
    QSqlQuery query;
    int i=0;
    query.prepare("SELECT * from Papers");
    if(query.exec())
    {
        while(query.next())
        {
            papers[i].name=query.value("name").toString();
//            papers[i].file=query.value("data").toString();
            QString str=query.value("data").toString();
            papers[i].file=NULL;
            papers[i].id=query.value("id").toInt();
            i++;
        }
    }
    else {
        qDebug()<<query.lastError();
    }
}
bool Db_Class::delete_papers(int id)
{
    QSqlQuery query;
    query.prepare("Delete from Papers where id=:Id");
    query.bindValue(":Id",id);
    if(query.exec())
        return true;
    else {
        qDebug()<<query.lastError();
        return false;
    }
}

Paper Db_Class::getBlob(int id)
{
    QSqlQuery qry;
    Paper paper;
    qry.prepare("Select * from Papers where id=:Id");
    qry.bindValue(":Id",id);
    if(qry.exec())
    {
        while(qry.next())
        {
            paper.name=qry.value("name").toString();
            QString data=qry.value("data").toString();
            paper.file=NULL;
            paper.file+=data;
            return paper;
        }
    }
    else {
        qDebug()<<qry.lastError();
    }
}

bool Db_Class::add_contact_to_db(Contact_Object contact)
{
    QSqlQuery query;

    qDebug()<<contact.name<<contact.email<<contact.contact1<<contact.contact2<<contact.designation;


    if(contact.contact2=="")
    {
        query.prepare("INSERT INTO Contact (name,designation,contact1,email) values (:Name,:Designation,:Contact1,:Email)");
        query.bindValue(":Name",contact.name);
        query.bindValue(":Designation",contact.designation);
        query.bindValue(":Contact1",contact.contact1);
        query.bindValue(":Email",contact.email);
    }
    else {
        query.prepare("INSERT INTO Contact (name,designation,contact1,contact2,email) values (:Name,:Designation,:Contact1,:Contact2,:Email)");
        query.bindValue(":Name",contact.name);
        query.bindValue(":Designation",contact.designation);
        query.bindValue(":Contact1",contact.contact1);
        query.bindValue(":Contact2",contact.contact2);
        query.bindValue(":Email",contact.email);
    }
    if(query.exec())
    {
        return true;
    }
    else {
        qDebug()<<query.lastError()<<"Db error\n";
        return false;
    }
}
bool Db_Class::delete_contact(int id)
{
    QSqlQuery query;
    query.prepare("Delete from Contact where id=:Id");
    query.bindValue(":Id",id);
    if(query.exec())
        return true;
    else {
        qDebug()<<query.lastError();
        return false;
    }
}
bool Db_Class::update_contact(Contact_Object contact)
{
    QSqlQuery query;
    if(contact.contact2==NULL)
    {
        query.prepare("UPDATE Contact SET name=:Name,email=:Email,contact1=:Contact1  Where id=:Id");
        query.bindValue(":Id",contact.id);
        query.bindValue(":Name",contact.name);
        query.bindValue(":Email",contact.email);
        query.bindValue(":Contact1",contact.contact1);
        query.bindValue(":Designation",contact.designation);
    }
    else {
        query.prepare("UPDATE Contact SET name=:Name,email=:Email,contact1=:Contact1,contact2=:Contact2  Where id=:Id");
        query.bindValue("Id",contact.id);
        query.bindValue(":Name",contact.name);
        query.bindValue(":Email",contact.email);
        query.bindValue(":Contact1",contact.contact1);
        query.bindValue(":Designation",contact.designation);
        query.bindValue(":Contact2",contact.contact2);
    }
    if(query.exec())
    {
        return true;
    }
    else {
        qDebug()<<query.lastError()<<" DB Error\n";

        return false;
    }
}
int Db_Class::getContactCount()
{
    QSqlQuery qry;
    qry.prepare("Select count(*) from Contact;");
    qry.exec();
    while (qry.next()) {
        return (qry.value(0).toInt());
    }
    return 0;
}
Contact_Object Db_Class::getContact(int id)
{
    QSqlQuery qry;
    qry.prepare("Select * from Contact where id=:Id");
    qry.bindValue(":Id",id);
    if(qry.exec())
    {
       Contact_Object contact;
       while(qry.next())
       {
           contact.id=qry.value("id").toInt();
           contact.name=qry.value("name").toString();
           contact.designation=qry.value("designation").toString();
           contact.contact1=qry.value("contact1").toString();
           contact.contact2=qry.value("contact2").toString();
           contact.email=qry.value("email").toString();
       }
       return contact;
    }
    else {
       qDebug()<<qry.lastError();
    }
}
void Db_Class::getContactDetail(Contact_Object contacts[])
{
    QSqlQuery query;
    int i=0;
    query.prepare("SELECT * from Contact");
    if(query.exec())
    {
        while(query.next())
        {
            contacts[i].name=query.value("name").toString();
            contacts[i].designation=query.value("designation").toString();
            contacts[i].email=query.value("email").toString();
            contacts[i].contact1=query.value("contact1").toString();
            contacts[i].contact2=query.value("contact2").toString();
            contacts[i].id=query.value("id").toInt();
            i++;

        }
    }
    else {
        qDebug()<<query.lastError();
    }
}
int Db_Class::get_count(Criteria_object criteria)
{
    QSqlQuery query;
    if(criteria.combo=="All" && criteria.placed_status=="All")
    {
        query.prepare("Select * from Student");
        if(query.exec())
        {
            qDebug()<<query.size();
            return query.size();
        }
    }
    else if(criteria.combo=="All" && criteria.placed_status=="Unplaced")
    {
        query.prepare("Select * from Student where offer=0");
        if(query.exec())
        {
            qDebug()<<query.size();
            return query.size();
        }

    }
    else if(criteria.combo=="All" && criteria.placed_status=="Placed" && criteria.company=="All"){
        query.prepare("Select * from Student s where exists (Select company_name from Placed p where s.usn=p.USN)");
        query.bindValue(":Company",criteria.company);
        if(query.exec())
        {
            qDebug()<<query.size();
            return query.size();
        }
    }
    else if(criteria.combo=="All" && criteria.placed_status=="Placed" ){
        query.prepare("Select * from Student s where exists (Select company_name from Placed p where s.usn=p.USN and p.company_name=:Company)");
        query.bindValue(":Company",criteria.company);
        if(query.exec())
        {
            qDebug()<<query.size();
            return query.size();
        }
    }

    else if(criteria.combo=="Department wise" && criteria.placed_status=="All"){
        if(criteria.cgpa==0 && criteria.ten==0 && criteria.twelve==0)
        {
            query.prepare("Select * from Student where dept=:Dept");
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.cgpa==0 && criteria.ten==0) {
            query.prepare("Select * from Student where dept=:Dept and twelve>=:Twelve");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.cgpa==0 && criteria.twelve==0) {
            query.prepare("Select * from Student where dept=:Dept and ten>=:Ten");
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }

        }
        else if (criteria.ten==0&&criteria.twelve==0) {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.cgpa==0) {
            query.prepare("Select * from Student where dept=:Dept and ten>=:Ten and twelve>=:Twelve");
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.ten==0) {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa and twelve>=:Twelve");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.twelve==0) {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa and ten>=:Ten");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }
        }
        else {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa and ten>=:Ten and twelve>=:Twelve");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }

        }
    }


    else if(criteria.combo=="Department wise" && criteria.placed_status=="Unplaced"){
        if(criteria.cgpa==0 && criteria.ten==0 && criteria.twelve==0)
        {
            query.prepare("Select * from Student where dept=:Dept");
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.cgpa==0 && criteria.ten==0) {
            query.prepare("Select * from Student where dept=:Dept and twelve>=:Twelve and offer=0");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }        }
        else if (criteria.cgpa==0 && criteria.twelve==0) {
            query.prepare("Select * from Student where dept=:Dept and ten>=:Ten and offer=0");
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.ten==0&&criteria.twelve==0) {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa and offer=0");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }        }
        else if (criteria.cgpa==0) {
            query.prepare("Select * from Student where dept=:Dept and ten>=:Ten and twelve>=:Twelve and offer=0");
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Twelve",criteria.twelve);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.ten==0) {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa and twelve>=:Twelve and offer=0");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.twelve==0) {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa and ten>=:Ten and offer=0");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Ten",criteria.ten);
            if(query.exec())
            {
                return query.size();
            }
        }
        else {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa and ten>=:Ten and twelve>=:Twelve and offer=0");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Ten",criteria.ten);
            if(query.exec())
            {
                return query.size();
            }
        }
    }

    else if(criteria.combo=="Department wise" && criteria.placed_status=="Placed" && criteria.company=="All"){
        if(criteria.cgpa==0 && criteria.ten==0 && criteria.twelve==0)
        {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept)");
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.cgpa==0 && criteria.ten==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.twelve>=:Twelve)");
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Twelve",criteria.twelve);
            if(query.exec())
            {
                return query.size();
            }        }
        else if (criteria.cgpa==0 && criteria.twelve==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.ten>=:Ten)");
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Ten",criteria.ten);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.ten==0&&criteria.twelve==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa)");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }        }
        else if (criteria.cgpa==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and  s.ten>=:Ten and s.twelve>=:Twelve)");
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Twelve",criteria.twelve);
            if(query.exec())
            {
                return query.size();
            }        }
        else if (criteria.ten==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa and s.twelve>=:Twelve)");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Twelve",criteria.twelve);
            if(query.exec())
            {
                return query.size();
            }        }
        else if (criteria.twelve==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa and s.ten>=:Ten)");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }
        }
        else {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa and s.ten>=:Ten and s.twelve>=:Twelve)");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }
        }
    }


    else if(criteria.combo=="Department wise" && criteria.placed_status=="Placed"){
        if(criteria.cgpa==0 && criteria.ten==0 && criteria.twelve==0)
        {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and p.company_name=:Company)");
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.cgpa==0 && criteria.ten==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.twelve>=:Twelve and p.company_name=:Company)");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Company",criteria.company);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }        }
        else if (criteria.cgpa==0 && criteria.twelve==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.ten>=:Ten and p.company_name=:Company)");
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.ten==0&&criteria.twelve==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa and p.company_name=:Company)");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {
                return query.size();
            }        }
        else if (criteria.cgpa==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.ten>=:Ten and s.twelve>=:Twelve and p.company_name=:Company)");
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.ten==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa and s.twelve>=:Twelve and p.company_name=:Company)");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.twelve==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa and s.ten>=:Ten and p.company_name=:Company)");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {
                return query.size();
            }
        }
        else {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa and s.ten>=:Ten and s.twelve>=:Twelve and p.company_name=:Company)");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {
                return query.size();
            }
        }
    }

}
bool Db_Class::get_list(Criteria_object criteria,Student students[])
{
    QSqlQuery query;
    int i=0;

    if(criteria.combo=="All" && criteria.placed_status=="All")
    {
        query.prepare("Select * from Student");
        if(query.exec())
        {
            while(query.next())
            {
                students[i].usn=query.value("usn").toString();
                students[i].name=query.value("name").toString();
                students[i].dept=query.value("dept").toString();
                students[i].email=query.value("email").toString();
                students[i].contact=query.value("contact").toString();
                i++;
            }
        }
    }
    else if(criteria.combo=="All" && criteria.placed_status=="Unplaced")
    {
        query.prepare("Select * from Student where offer=0");
        if(query.exec())
        {
            while(query.next())
            {
                students[i].usn=query.value("usn").toString();
                students[i].name=query.value("name").toString();
                students[i].dept=query.value("dept").toString();
                students[i].email=query.value("email").toString();
                students[i].contact=query.value("contact").toString();
                i++;
            }
        }

    }
    else if(criteria.combo=="All" && criteria.placed_status=="Placed" && criteria.company=="All"){
        query.prepare("Select * from Student s where exists (Select company_name from Placed p where s.usn=p.USN)");
        query.bindValue(":Company",criteria.company);
        if(query.exec())
        {
            while(query.next())
            {
                students[i].usn=query.value("usn").toString();
                students[i].name=query.value("name").toString();
                students[i].dept=query.value("dept").toString();
                students[i].email=query.value("email").toString();
                students[i].contact=query.value("contact").toString();
                i++;
            }
        }
    }
    else if(criteria.combo=="All" && criteria.placed_status=="Placed" ){
        query.prepare("Select * from Student s where exists (Select company_name from Placed p where s.usn=p.USN and p.company_name=:Company)");
        query.bindValue(":Company",criteria.company);
        if(query.exec())
        {
            while(query.next())
            {
                students[i].usn=query.value("usn").toString();
                students[i].name=query.value("name").toString();
                students[i].dept=query.value("dept").toString();
                students[i].email=query.value("email").toString();
                students[i].contact=query.value("contact").toString();
                i++;
            }
        }
    }

    else if(criteria.combo=="Department wise" && criteria.placed_status=="All"){
        if(criteria.cgpa==0 && criteria.ten==0 && criteria.twelve==0)
        {
            query.prepare("Select * from Student where dept=:Dept");
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
        else if (criteria.cgpa==0 && criteria.ten==0) {
            query.prepare("Select * from Student where dept=:Dept and twelve>=:Twelve");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }

            }
        }
        else if (criteria.cgpa==0 && criteria.twelve==0) {
            query.prepare("Select * from Student dept=:Dept and where ten>=:Ten");
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Ten",criteria.ten);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }

            }

        }
        else if (criteria.ten==0&&criteria.twelve==0) {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }

            }
        }
        else if (criteria.cgpa==0) {
            query.prepare("Select * from Student where dept=:Dept and ten>=:Ten and twelve>=:Twelve");
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }

            }
        }
        else if (criteria.ten==0) {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa and twelve>=:Twelve");
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Twelve",criteria.twelve);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }

            }
        }
        else if (criteria.twelve==0) {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa and ten>=:Ten");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Ten",criteria.ten);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }

            }
        }

        else {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa and ten>=:Ten and twelve>=:Twelve");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }

        }
    }


    else if(criteria.combo=="Department wise" && criteria.placed_status=="Unplaced"){
        if(criteria.cgpa==0 && criteria.ten==0 && criteria.twelve==0)
        {
            query.prepare("Select * from Student where dept=:Dept and offer=0");
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                return query.size();
            }
        }
        else if (criteria.cgpa==0 && criteria.ten==0) {
            query.prepare("Select * from Student where dept=:Dept and twelve>=:Twelve and offer=0");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }

            }
        }
        else if (criteria.cgpa==0 && criteria.twelve==0) {
            query.prepare("Select * from Student where dept=:Dept and ten>=:Ten and offer=0");
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }

            }

        }
        else if (criteria.ten==0&&criteria.twelve==0) {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa and offer=0");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }

            }
        }
        else if (criteria.cgpa==0) {
            query.prepare("Select * from Student where dept=:Dept ten>=:Ten and twelve>=:Twelve and offer=0");
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Twelve",criteria.twelve);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }

            }
        }
        else if (criteria.ten==0) {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa and twelve>=:Twelve and offer=0");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }

            }
        }
        else if (criteria.twelve==0) {
            query.prepare("Select * from Student where dept=:Dept cgpa>=:Cgpa and ten>=:Ten and offer=0");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Ten",criteria.ten);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }

            }
        }

        else {
            query.prepare("Select * from Student where dept=:Dept and cgpa>=:Cgpa and ten>=:Ten and twelve>=:Twelve and offer=0");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Ten",criteria.ten);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
    }


    else if(criteria.combo=="Department wise" && criteria.placed_status=="Placed" && criteria.company=="All"){
        if(criteria.cgpa==0 && criteria.ten==0 && criteria.twelve==0)
        {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept)");
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
        else if (criteria.cgpa==0 && criteria.ten==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.ten>=:Ten)");
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Twelve",criteria.twelve);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
        else if (criteria.cgpa==0 && criteria.twelve==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.ten>=:Ten)");
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Ten",criteria.ten);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
        else if (criteria.ten==0&&criteria.twelve==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa)");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
        else if (criteria.cgpa==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and  s.ten>=:Ten and s.twelve>=:Twelve)");
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Twelve",criteria.twelve);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
        else if (criteria.ten==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa and s.twelve>=:Twelve)");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Twelve",criteria.twelve);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
        else if (criteria.twelve==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa and s.ten>=:Ten)");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }

        else {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa and s.ten>=:Ten and s.twelve>=:Twelve)");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
    }


    else if(criteria.combo=="Department wise" && criteria.placed_status=="Placed"){
        if(criteria.cgpa==0 && criteria.ten==0 && criteria.twelve==0)
        {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and p.company_name=:Company)");
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
        else if (criteria.cgpa==0 && criteria.ten==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.twelve>=:Twelve and p.company_name=:Company)");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
        else if (criteria.cgpa==0 && criteria.twelve==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.ten>=:Ten and p.company_name=:Company)");
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
        else if (criteria.ten==0&&criteria.twelve==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept>=:Dept and s.cgpa>=:Cgpa and p.company_name=:Company)");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
        else if (criteria.cgpa==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.ten>=:Ten and s.twelve>=:Twelve and p.company_name=:Company)");
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
        else if (criteria.ten==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa and s.twelve>=:Twelve and p.company_name=:Company)");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
        else if (criteria.twelve==0) {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa and s.ten>=:Ten and p.company_name=:Company)");
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {
                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }

        else {
            query.prepare("Select * from Student s where s.usn IN(Select p.USN from Placed p where s.dept=:Dept and s.cgpa>=:Cgpa and s.ten>=:Ten and s.twelve>=:Twelve and p.company_name=:Company)");
            query.bindValue(":Twelve",criteria.twelve);
            query.bindValue(":Cgpa",criteria.cgpa);
            query.bindValue(":Dept",criteria.dept);
            query.bindValue(":Ten",criteria.ten);
            query.bindValue(":Company",criteria.company);
            if(query.exec())
            {

                while(query.next())
                {
                    students[i].usn=query.value("usn").toString();
                    students[i].name=query.value("name").toString();
                    students[i].dept=query.value("dept").toString();
                    students[i].email=query.value("email").toString();
                    students[i].contact=query.value("contact").toString();
                    i++;
                }
            }
        }
    }

}

Db_Class::~Db_Class()
{

}
