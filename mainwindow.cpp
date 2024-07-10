#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize your pages
    registerPage = new Register();
    premium = new Premium();
    comment_like= new Comment_Like();
    playlist= new playlist_songs();
    chatbox= new ChatBox();
    // Add pages to the QStackedWidget
    ui->stackedWidget->addWidget(registerPage);
    ui->stackedWidget->addWidget(premium);
    ui->stackedWidget->addWidget(comment_like); // Add the Comment_Like page
    ui->stackedWidget->addWidget(playlist);
    ui->stackedWidget->addWidget(chatbox);
    // Connect the signal to the slot
    connect(registerPage, &Register::loginPSuccessful, this, &MainWindow::showPremium);
    connect(premium, &Premium::open_comment, this, &MainWindow::showComment);
    connect(comment_like, &Comment_Like::goBack, this, &::MainWindow::goBacktoHome);
    connect(premium, &Premium::open_playlist, this, &::MainWindow::showPlaylist);
    connect(playlist, &playlist_songs::goBack, this, &::MainWindow::goBacktoHome);
    connect(playlist, &playlist_songs::open_comment, this, &MainWindow::showComment);
    connect(comment_like, &Comment_Like::open_comment, this, &MainWindow::showComment);
    connect(premium, &Premium::startChat, this, &MainWindow::startChat);
    connect(chatbox, &ChatBox::goBack, this, &MainWindow::goBacktoHome);
    // Initially show the register page
    ui->stackedWidget->setCurrentWidget(registerPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showRegister(){
    ui->stackedWidget->setCurrentWidget(registerPage);
}

void MainWindow::showPremium(){
    ui->stackedWidget->setCurrentWidget(premium);
}
void MainWindow::showComment(const QString &songID){
    //fill the lable, name and comment section based on ID
    comment_like->setCommentDetails(songID);
    ui->stackedWidget->setCurrentWidget(comment_like);
}
void MainWindow::goBacktoHome(){
    ui->stackedWidget->setCurrentWidget(premium);
}
void MainWindow::showPlaylist(const QString &songID){
    //fill the table with songs
    playlist->fillPlaylist(songID);
    ui->stackedWidget->setCurrentWidget(playlist);
}
void MainWindow::startChat(const QString &personID){
    chatbox->fillChat(personID);
    ui->stackedWidget->setCurrentWidget(chatbox);
}
