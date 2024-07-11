#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "comment_like.h"
#include "register.h"
#include"premium.h"
#include"comment_like.h"
#include"playlist_songs.h"
#include"chatbox.h"
QT_BEGIN_NAMESPACE
extern QSqlDatabase db;
extern int ID;
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
    Premium* premium;
    Comment_Like*comment_like;
    playlist_songs*playlist;
    ChatBox*chatbox;

private slots:
    void showRegister();
    void showPremium(const QString &);
    void showComment(const QString &);
    void goBacktoHome();
    void showPlaylist(const QString &);
    void startChat(const QString &);
    void OpenAlbum(const QString &songID);

};

#endif // MAINWINDOW_H
