#ifndef PREMIUM_H
#define PREMIUM_H

#include "chatbox.h"
#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include<QFileDialog>
#include<QLineEdit>
#include<QVector>
#include<QFormLayout>
#include<QGroupBox>
#include<QMessageBox>
#include <QSqlError>
#include<QSqlQuery>
#include <QFile>
#include<QCalendarWidget>
#include<QTimeEdit>
#include<QTextEdit>
extern int songId;
extern int albumid;
extern QDate concertDate;

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
    int songCount;
    QString Type;
    QVector<QLineEdit*> titleEdits;
    QVector<QLineEdit*> albumEdits;
    QVector<QLineEdit*> genreEdits;
    QVector<QLineEdit*> releaseDateEdits;
    QVector<QLineEdit*> ageCategoryEdits;
    QVector<QLineEdit*> countryEdits;
    QVector<QTextEdit*> lyricsEdits;  // Add this line
    QPushButton *submitSongsButton;
    QGridLayout *gridLayout;
    QWidget *contentWidget;
    QScrollArea *scrollArea;
    void addSongItem(const QString &songID, const QString &songName, const QString &imagePath);
    void fill_favorites();
    void fillSongs();
    void fill_friends();
    void myPlaylist();
    void friendPlaylist();
    void publicPlaylist();
    void onStartChatClicked();
    void fill_follow();
    void fill_concerts();
    void addConcertItem(QVBoxLayout *layout, const QString &concertName, int artistId, const QDateTime &date, const QString &imagePath);
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
    void acceptFriendshipRequest(const QString &name);
    void declineFriendshipRequest(const QString &userName);
    void sendFriendshipRequest(const QString &userName);
    void fillAllUsers();
    void clearScrollArea();
    void on_SubmitSongs_clicked();
    void fill_my_belongings();
    void onDeleteButtonClicked(const QString& type, const QString& itemName);
    void onNameButtonClicked(const QString& type, const QString& itemName);
    void fillScrollArea(QScrollArea* scrollArea, const QString& type);
    QList<QVariantMap> searchMusicAndAlbum(const QString &name, const QString &artistName, const QString &genre, const QString &country, const QString &ageCategory);
    void displaySearchResults(const QList<QVariantMap> &results);
    void clearScrollAreaSearch();
    bool initializeDatabase(QSqlDatabase &db);
    void followUser(int userId, const QString &userName);
    void show_album_page();
    void clearScrollArea(QScrollArea *scrollArea);
    void clearTickets(QScrollArea* scrollArea);
    void updateBalanceLabel();
    bool areTicketsAvailable(int artistId, const QDateTime &date);
    void fill_playlists();
    void setupDateTimePicker();
    void setupDateTimePicker2();
    void clearScrollArea2();
    void setupDateTimePicker3();
    void fillAlbums();

signals:
    void open_comment(const QString);
    void open_playlist(const QString);
    void startChat(const QString);
    void open_album(const QString);
    void Logout();

private slots:
    void addComment_like();
    void showPlaylist();
    void on_UploadPhoto_clicked();
    void on_submit_song_clicked();
    void on_OK_clicked();

    void on_Search_pushButton_clicked();
    void on_charge_clicked();

    void on_withdraw_clicked();

    void on_premiumBuy_clicked();

    void on_submit_song_2_clicked();

    void on_UploadPhoto_2_clicked();

public slots:
    void setUserID(const QString &userType);
    void fillPlayListAfterNew();


};

#endif // PREMIUM_H
