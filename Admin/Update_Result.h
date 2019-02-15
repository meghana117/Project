#ifndef UPDATE_RESULT_H
#define UPDATE_RESULT_H

#include <QWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QLineEdit>

class Update_Result : public QWidget
{
    Q_OBJECT
public:
    explicit Update_Result(QWidget *parent = nullptr);

private:
    QFormLayout *form1;
    QPushButton *update,*update1,*cancel,*choose;
    QLineEdit *usn;
    QLabel *USN,*Sem,*sgpa,*sem,*selected,*error1,*error2,*error3,*OrLabel;
    QComboBox *Sems,*sems;
    QDoubleSpinBox *Sgpa;


signals:

public slots:
};

#endif // UPDATE_RESULT_H
