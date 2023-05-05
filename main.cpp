
#include "subwindow.h"
#include "triwindow.h"
#include "form.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase trainDataBase=QSqlDatabase::addDatabase("QPSQL");
    trainDataBase.setHostName("localhost");
    trainDataBase.setDatabaseName("train_ticket");
    trainDataBase.setUserName("postgres");
    trainDataBase.setPassword("123456");
    if(!trainDataBase.open()){
        QMessageBox::warning(0,"错误",trainDataBase.lastError().text());
        return false;
    }
    triwindow w;
    subwindow s;
    Form f(&s,&w);
    f.show();
    return a.exec();
}
