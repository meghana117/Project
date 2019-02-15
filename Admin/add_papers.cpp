#include "add_papers.h"

Add_Papers::Add_Papers(QWidget *parent) : QWidget(parent)
{

    table=new QTableView();
    model=new QStandardItemModel(1,3);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Paper description"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Download file"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Delete file"));

//    this->setAttribute(Qt::WA_DeleteOnClose);

    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setGeometry(700,300,700,500);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setDefaultSectionSize(50);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    add=new QPushButton("Add papers");
    cancel2=new QPushButton("Cancel");
    vbox1=new QVBoxLayout();
    vbox2=new QVBoxLayout();
    hbox1=new QHBoxLayout();
    hbox2=new QHBoxLayout();


    vbox1->addWidget(table);
    hbox1->addWidget(add);
    hbox1->addWidget(cancel2);
    vbox1->addLayout(hbox1);

    this->setLayout(vbox1);
    this->setGeometry(700,300,600,600);


    initialize();
    initialize_add();


    connect(add,SIGNAL(clicked(bool)),this,SLOT(add_paper()));
    connect(cancel2,SIGNAL(clicked(bool)),this,SLOT(close()));


}

void Add_Papers::initialize()
{


    int count=db.getpapersCount();
    Paper papers[count];
    db.getPaperDetail(papers);

    QPushButton *download_buttons[count];
    QPushButton *del_buttons[count];

    QSignalMapper *download_mapper=new QSignalMapper(this);
    connect(download_mapper,SIGNAL(mapped(int)),this,SLOT(download_pdf(int)));

    QSignalMapper *delete_mapper=new QSignalMapper(this);
    connect(delete_mapper,SIGNAL(mapped(int)),this,SLOT(delete_paper(int)));

    model->setRowCount(db.getpapersCount());
    model->setColumnCount(3);
    for(int i=0;i<count;i++)
    {
        QStandardItem *item1=new QStandardItem(papers[i].name);
        model->setItem(i,0,item1) ;
        qDebug()<<papers[i].name<<"Name ";
        download_buttons[i]=new QPushButton("Download file");
        table->setIndexWidget(model->index(i,1), download_buttons[i]);
        connect(download_buttons[i],SIGNAL(clicked()),download_mapper,SLOT(map()));
        download_mapper->setMapping(download_buttons[i],papers[i].id);
        del_buttons[i]=new QPushButton("Delete file");
        table->setIndexWidget(model->index(i,2),del_buttons[i]);
        connect(del_buttons[i],SIGNAL(clicked()),delete_mapper,SLOT(map()));
        delete_mapper->setMapping(del_buttons[i],papers[i].id);
    }


}
void Add_Papers::initialize_add()
{

    add_widget=new QWidget();
    desc=new QLabel("Enter file description");
    description=new QLineEdit();
    choose=new QPushButton("Choose file");
    add1=new QPushButton("Add");
    cancel=new QPushButton("Cancel");
//    vb1=new QVBoxLayout();
//    hb1=new QHBoxLayout();
//    hb2=new QHBoxLayout();
//    hb3=new QHBoxLayout();
//    hb1->addWidget(desc);
//    hb1->addWidget(description);
//    hb2->addWidget(choose);
//    hb3->addWidget(add1);
//    hb3->addWidget(cancel);
//    vb1->addLayout(hb1);
//    vb1->addLayout(hb2);
//    vb1->addLayout(hb3);
    form1=new QFormLayout();
    form1->addRow(desc,description);
    form1->addRow(choose);
    form1->addRow(add1,cancel);
    add_widget->setLayout(form1);
    add_widget->setGeometry(700,300,600,600);

}
void Add_Papers::add_paper()
{
    add_widget->show();
    this->setEnabled(false);

    connect(choose,SIGNAL(clicked(bool)),this,SLOT(select_file()));
    connect(add1,SIGNAL(clicked(bool)),this,SLOT(add_paper_to_db()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(cancel_add()));

}
void Add_Papers::select_file()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open file"), "",tr("Pdf(*.pdf);;Doc (*.doc);;All Files (*.pdf | *.doc)"));
    QFile file(fileName);

    QByteArray bytes;
    if (file.exists()) {
              if (file.open(QIODevice::ReadOnly)) {
               bytes = file.readAll();
               paper.file=bytes;
               paper.name=description->text();
              file.close();
            }
        }
        file.close();
}
void Add_Papers::add_paper_to_db()
{
    QMessageBox msgbox;
    if(db.add_paper_to_db(paper))
    {
        msgbox.setText("Inserted paper to db");
        msgbox.exec();
        this->initialize();
    }
    else {
        msgbox.setText("Duplicate description or invalid file!");
        msgbox.exec();
    }
}

void Add_Papers::cancel_add()
{
    add_widget->close();
    this->setEnabled(true);
}
void Add_Papers::download_pdf(int id)
{
    Paper str=db.getBlob(id);

    QPrinter printer(QPrinter::HighResolution);
      printer.setOrientation(QPrinter::Landscape);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setPaperSize(QPrinter::A4);
      QString fileName = QFileDialog::getSaveFileName(0,"file", "c:\\", "pdf (*.pdf)");
      printer.setOutputFileName(fileName);

      QPainter painter;
      painter.begin(&printer);

      qDebug()<<str.file;
      painter.drawText( 200,200, str.file );
      painter.end();
}


void Add_Papers::delete_paper(int id)
{
    QMessageBox msgbx;
    QMessageBox msg;

     msg.setInformativeText("Are you sure you want to delete?");
     msg.setStandardButtons(QMessageBox::Yes |  QMessageBox::Cancel);
     msg.setDefaultButton(QMessageBox::Yes);
     int ret = msg.exec();

     switch (ret) {
       case QMessageBox::Yes:
         if(db.delete_papers(id))
         {
             msgbx.setText("Deleted student successfully");
             msgbx.exec();
             this->initialize();
         }
         else {
             msgbx.setText("Couldn't delete student ");
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
Add_Papers::~Add_Papers()
{
    this->deleteLater();
}
