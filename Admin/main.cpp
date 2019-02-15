#include "MainWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.show();
    QString filePath = ":/StyleSheet.qss";
    QFile f(filePath);
    f.open(QIODevice::ReadOnly);
    QString data = f.readAll();

    a.setStyleSheet(data);

    return a.exec();
}
void control_widget()
{

}
