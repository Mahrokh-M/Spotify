#ifndef PLAYLIST_SONGS_H
#define PLAYLIST_SONGS_H

#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QFile>
namespace Ui {
class playlist_songs;
}

class playlist_songs : public QWidget
{
    Q_OBJECT

public:
    explicit playlist_songs(QWidget *parent = nullptr);
    ~playlist_songs();
    int albumid;

private slots:
    void on_Back_clicked();
    void setstyle();

    void on_Like_button_clicked();

private:
    Ui::playlist_songs *ui;
    void onSongButtonClicked();
    void updateLikeButtonStyle(const QString &playlistName);
public slots:
    void fillPlaylist(const QString &listID);
    void fillAlbum(const QString &AlbumID);
signals:
    void goBack();
    void open_comment(const QString);
};

#endif // PLAYLIST_SONGS_H
