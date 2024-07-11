#include "mainwindow.h"
#include "register.h"
#include <QtSql>
#include <QApplication>
#include<QSqlQuery>
int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        db.setDatabaseName("DRIVER={ODBC Driver 17 for SQL Server};SERVER=LOCALHOST\\SQLEXPRESS;DATABASE=Spotify;Trusted_Connection=Yes;");

        if (db.open()) {
            qDebug() << "Database connected!";}

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
