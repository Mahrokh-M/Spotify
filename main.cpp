#include "mainwindow.h"
#include "register.h"
#include <QtSql>
#include <QApplication>
#include<QSqlQuery>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
