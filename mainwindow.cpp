#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize your pages
    registerPage = new Register();
    homepage = new HomePage();
    singer = new Singer();
    premium = new Premium();

    // Add pages to the QStackedWidget
    ui->stackedWidget->addWidget(registerPage);
    ui->stackedWidget->addWidget(homepage);
    ui->stackedWidget->addWidget(premium);
    ui->stackedWidget->addWidget(singer);

    // Connect the signal to the slot
    connect(registerPage, &Register::loginSuccessful, this, &MainWindow::showHomePage);
    connect(homepage, &HomePage::logoutSuccessful, this, &MainWindow::showRegister);
    connect(registerPage, &Register::loginPSuccessful, this, &MainWindow::showPremium);
    connect(registerPage, &Register::loginSSuccessful, this, &MainWindow::showSinger);
    // Initially show the register page
    ui->stackedWidget->setCurrentWidget(registerPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showHomePage()
{
    ui->stackedWidget->setCurrentWidget(homepage);
}
void MainWindow::showRegister(){
    ui->stackedWidget->setCurrentWidget(registerPage);
}

void MainWindow::showSinger(){
    ui->stackedWidget->setCurrentWidget(singer);
}
void MainWindow::showPremium(){
    ui->stackedWidget->setCurrentWidget(premium);
}
