#ifndef PREMIUM_H
#define PREMIUM_H

#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include<QFileDialog>
namespace Ui {
class Premium;
}

class Premium : public QWidget
{
    Q_OBJECT

public:
    explicit Premium(QWidget *parent = nullptr);
    ~Premium();

private:
    Ui::Premium *ui;
    QString m_imagePath;
private:
    QGridLayout *gridLayout;
    QWidget *contentWidget;
    QScrollArea *scrollArea;
    int songCount;
    void addSongItem(const QString &songID,const QString &songName, const QString &imagePath);
    void fill_favorites();
    void fill_playlists();
    void fill_friends();
    void myPlaylist();
    void friendPlaylist();
    void publicPlaylist();
    void onStartChatClicked();
    void fill_follow();
    void fill_concerts();
    void addConcertItem(QHBoxLayout *layout, const QString &concertName, const QString &imagePath);
    void showTicketOptions();
    void buyTicket();
    double getUserBalance();
    void toggleTicketOptions();
    void fill_wallet();
    double calculateTotalBalance(const QList<QPair<QString, double>>& validTickets);
    void updateBalanceLabel(double balance);
    void populateTickets(const QList<QPair<QString, double>>& tickets, QScrollArea* scrollArea, bool horizontal);
    void setstyle();
    void fillFriendshipRequests();
    void acceptFriendshipRequest(const QString &);
    void declineFriendshipRequest(const QString &userName);
    void sendFriendshipRequest(const QString &userName);
    void fillAllUsers();;


signals:
    void open_comment(const QString);
    void open_playlist(const QString);
    void startChat(const QString);

private slots:
    void addComment_like();
    void showPlaylist();


    void on_UploadPhoto_clicked();
    void on_submit_song_clicked();
};

#endif // PREMIUM_H
