#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "homepage.h"
#include "register.h"
#include"premium.h"
#include"singer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Register* registerPage;
    HomePage* homepage;
    Premium* premium;
    Singer* singer;

private slots:
    void showHomePage();  // Add this slot
    void showRegister();
    void showSinger();
    void showPremium();
};

#endif // MAINWINDOW_H
