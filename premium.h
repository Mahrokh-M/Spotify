#ifndef PREMIUM_H
#define PREMIUM_H

#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>

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
signals:
    void open_comment(const QString);
    void open_playlist(const QString);
    void startChat(const QString);

private slots:
    void addComment_like();
    void showPlaylist();


};

#endif // PREMIUM_H
