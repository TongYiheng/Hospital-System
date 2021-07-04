#include "mainwindow.h"
#include "loginwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow L;
    L.show();

    return a.exec();
}
