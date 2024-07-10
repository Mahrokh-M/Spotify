#ifndef PLAYLIST_SONGS_H
#define PLAYLIST_SONGS_H

#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
namespace Ui {
class playlist_songs;
}

class playlist_songs : public QWidget
{
    Q_OBJECT

public:
    explicit playlist_songs(QWidget *parent = nullptr);
    ~playlist_songs();

private slots:
    void on_Back_clicked();
    void setstyle();

private:
    Ui::playlist_songs *ui;
    void onSongButtonClicked();
public slots:
    void fillPlaylist(const QString &listID);
signals:
    void goBack();
    void open_comment(const QString);
};

#endif // PLAYLIST_SONGS_H
