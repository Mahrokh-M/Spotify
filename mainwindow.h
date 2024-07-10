#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "comment_like.h"
#include "homepage.h"
#include "register.h"
#include"premium.h"
#include"singer.h"
#include"comment_like.h"
#include"playlist_songs.h"
#include"chatbox.h"
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
    Comment_Like*comment_like;
    playlist_songs*playlist;
    ChatBox*chatbox;

private slots:
    void showHomePage();  // Add this slot
    void showRegister();
    void showSinger();
    void showPremium();
    void showComment(const QString &);
    void goBacktoHome();
    void showPlaylist(const QString &);
    void startChat(const QString &);

};

#endif // MAINWINDOW_H
