#ifndef PREMIUM_H
#define PREMIUM_H

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
    int ID;
    QString Type;
    QVector<QLineEdit*> titleEdits;
    QVector<QLineEdit*> albumEdits;
    QVector<QLineEdit*> genreEdits;
    QVector<QLineEdit*> releaseDateEdits;
    QVector<QLineEdit*> ageCategoryEdits;
    QVector<QLineEdit*> countryEdits;
    QPushButton *submitSongsButton;
    QGridLayout *gridLayout;
    QWidget *contentWidget;
    QScrollArea *scrollArea;
    void addSongItem(const QString &songID, const QString &songName, const QString &imagePath);
    void fill_favorites();
    void fill_playlists();
    void fillSongs();
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
    int getCurrentUserId();
    bool initializeDatabase(QSqlDatabase &db);
    void followUser(int userId, const QString &userName);


signals:
    void open_comment(const QString);
    void open_playlist(const QString);
    void startChat(const QString);

private slots:
    void addComment_like();
    void showPlaylist();
    void on_UploadPhoto_clicked();
    void on_submit_song_clicked();
    void on_OK_clicked();

    void on_Search_pushButton_clicked();
public slots:
    void setUserID(const int &userId,const QString &userType);
};

#endif // PREMIUM_H
