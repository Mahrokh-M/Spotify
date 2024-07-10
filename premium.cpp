#include "premium.h"
#include "ui_premium.h"


Premium::Premium(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Premium),
    songCount(0)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

    //    // Initialize media player
    //    player = new QMediaPlayer(this);

    // Initialize scroll area and content widget
    scrollArea = ui->scrollArea;
    contentWidget = new QWidget(this);
    gridLayout = new QGridLayout(contentWidget);

    contentWidget->setLayout(gridLayout);
    scrollArea->setWidget(contentWidget);
    // scrollArea->setWidgetResizable(true);

    // Set layout of HomePage to include the scroll area


    // Example songs
    addSongItem("1","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("2","Song 2", ":/new/prefix1/spotify logo.png");
    addSongItem("3","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("1","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("2","Song 2", ":/new/prefix1/spotify logo.png");
    addSongItem("3","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("1","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("2","Song 2", ":/new/prefix1/spotify logo.png");
    addSongItem("3","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("1","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("2","Song 2", ":/new/prefix1/spotify logo.png");
    addSongItem("3","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("1","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("2","Song 2", ":/new/prefix1/spotify logo.png");
    addSongItem("3","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("1","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("2","Song 2", ":/new/prefix1/spotify logo.png");
    addSongItem("3","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("1","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("2","Song 2", ":/new/prefix1/spotify logo.png");
    addSongItem("3","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("1","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("2","Song 2", ":/new/prefix1/spotify logo.png");
    addSongItem("3","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("1","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("2","Song 2", ":/new/prefix1/spotify logo.png");
    addSongItem("3","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("1","Song 1", ":/new/prefix1/spotify logo.png");
    addSongItem("2","Song 2", ":/new/prefix1/spotify logo.png");
    addSongItem("3","Song 1", ":/new/prefix1/spotify logo.png");
    // Add more songs as needed
    fill_favorites();
    fill_playlists();
    fill_friends();
}

Premium::~Premium()
{
    delete ui;
}

void Premium::addSongItem(const QString &songID,const QString &songName, const QString &imagePath)
{
    int row = songCount / 8;
    int col = songCount % 8;

    // Create label for song image
    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap(imagePath);
    imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
    gridLayout->addWidget(imageLabel, row * 2, col);

    // Create button for song name
    QPushButton *songButton = new QPushButton(songName, this);
    songButton->setProperty("ID", songID);
    songButton->setProperty("name", songName);
    songButton->setProperty("pic_path", imagePath);
    connect(songButton, &QPushButton::clicked, this, &::Premium::addComment_like);
    gridLayout->addWidget(songButton, row * 2 + 1, col);

    songCount++;
}
void Premium::addComment_like()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        QString songID = button->property("ID").toString();
        emit open_comment(songID); // Emit signal with songID
    }
}

void Premium::fill_favorites()
{
    QWidget *contentWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(contentWidget);

    // Example content: add several QLabel with images and QPushButton for song names
    for (int i = 1; i <= 100; ++i)
    {
        // Create a vertical layout to hold image and song name
        QVBoxLayout *vLayout = new QVBoxLayout();

        // Create label for song image
        QLabel *label = new QLabel(contentWidget);
        label->setPixmap(QPixmap(":/new/prefix1/spotify logo.png").scaled(100, 100, Qt::KeepAspectRatio));
        vLayout->addWidget(label);

        // Create button for song name
        QPushButton *songButton = new QPushButton("Song " + QString::number(i), contentWidget);
        songButton->setProperty("ID", QString::number(i)); // Assuming songID is the same as i for this example
        songButton->setProperty("name", "Song " + QString::number(i));
        songButton->setProperty("pic_path", ":/new/prefix1/spotify logo.png");
        connect(songButton, &QPushButton::clicked, this, &Premium::addComment_like);
        vLayout->addWidget(songButton);

        // Add the vertical layout to the horizontal layout
        layout->addLayout(vLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->scrollArea_2->setWidget(contentWidget);

    // Example content: add several QLabel with images or text
    QWidget *contentWidget_2 = new QWidget(this);
    QHBoxLayout *layout_2 = new QHBoxLayout(contentWidget_2);
    for (int i = 1; i <= 100; ++i)
    {
        QVBoxLayout *vLayout_2 = new QVBoxLayout();

        QLabel *label = new QLabel(contentWidget_2);
        label->setPixmap(QPixmap(":/new/prefix1/spotify logo.png").scaled(100, 100, Qt::KeepAspectRatio));
        vLayout_2->addWidget(label);

        QPushButton *songButton = new QPushButton("Song " + QString::number(i), contentWidget_2);
        songButton->setProperty("ID", QString::number(i));
        songButton->setProperty("name", "Song " + QString::number(i));
        songButton->setProperty("pic_path", ":/new/prefix1/spotify logo.png");
        connect(songButton, &QPushButton::clicked, this, &Premium::addComment_like);
        vLayout_2->addWidget(songButton);

        layout_2->addLayout(vLayout_2);
    }

    // Set the content widget as the scroll area's widget
    ui->scrollArea_3->setWidget(contentWidget_2);
}

void Premium::fill_playlists()
{
    myPlaylist();
    friendPlaylist();
    publicPlaylist();

}
void Premium::myPlaylist(){
    QWidget *contentWidget_3 = new QWidget(this);
    QHBoxLayout *layout_3 = new QHBoxLayout(contentWidget_3);

    // Example content: add several QLabel with images and QPushButton for song names
    for (int i = 1; i <= 100; ++i)
    {
        // Create a vertical layout to hold image and song name
        QVBoxLayout *vLayout = new QVBoxLayout();

        // Create label for song image
        QLabel *label = new QLabel(contentWidget_3);
        label->setPixmap(QPixmap(":/new/prefix1/spotify logo.png").scaled(100, 100, Qt::KeepAspectRatio));
        vLayout->addWidget(label);

        // Create button for song name
        QPushButton *songButton = new QPushButton("Song " + QString::number(i), contentWidget_3);
        songButton->setProperty("ID", QString::number(i)); // Assuming songID is the same as i for this example
        songButton->setProperty("name", "Song " + QString::number(i));
        songButton->setProperty("pic_path", ":/new/prefix1/spotify logo.png");
        connect(songButton, &QPushButton::clicked, this, &Premium::showPlaylist);
        vLayout->addWidget(songButton);

        // Add the vertical layout to the horizontal layout
        layout_3->addLayout(vLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->your_playlist_scrollbar->setWidget(contentWidget_3);
}

void Premium::showPlaylist(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        QString songID = button->property("ID").toString();
        emit open_playlist(songID); // Emit signal with songID
    }
}

void Premium::friendPlaylist(){

    // Example content: add several QLabel with images or text
    QWidget *contentWidget_4 = new QWidget(this);
    QHBoxLayout *layout_4 = new QHBoxLayout(contentWidget_4);
    for (int i = 1; i <= 100; ++i)
    {
        QVBoxLayout *vLayout_2 = new QVBoxLayout();

        QLabel *label = new QLabel(contentWidget_4);
        label->setPixmap(QPixmap(":/new/prefix1/spotify logo.png").scaled(100, 100, Qt::KeepAspectRatio));
        vLayout_2->addWidget(label);

        QPushButton *songButton = new QPushButton("Song " + QString::number(i), contentWidget_4);
        songButton->setProperty("ID", QString::number(i));
        songButton->setProperty("name", "Song " + QString::number(i));
        songButton->setProperty("pic_path", ":/new/prefix1/spotify logo.png");
        connect(songButton, &QPushButton::clicked, this, &Premium::showPlaylist);
        vLayout_2->addWidget(songButton);

        layout_4->addLayout(vLayout_2);
    }

    // Set the content widget as the scroll area's widget
    ui->friend_playlist_scrollbar->setWidget(contentWidget_4);
}

void Premium::publicPlaylist(){
    // Example content: add several QLabel with images or text
    QWidget *contentWidget_5 = new QWidget(this);
    QHBoxLayout *layout_5 = new QHBoxLayout(contentWidget_5);
    for (int i = 1; i <= 100; ++i)
    {
        QVBoxLayout *vLayout = new QVBoxLayout();

        QLabel *label = new QLabel(contentWidget_5);
        label->setPixmap(QPixmap(":/new/prefix1/spotify logo.png").scaled(100, 100, Qt::KeepAspectRatio));
        vLayout->addWidget(label);

        QPushButton *songButton = new QPushButton("Song " + QString::number(i), contentWidget_5);
        songButton->setProperty("ID", QString::number(i));
        songButton->setProperty("name", "Song " + QString::number(i));
        songButton->setProperty("pic_path", ":/new/prefix1/spotify logo.png");
        connect(songButton, &QPushButton::clicked, this, &Premium::showPlaylist);
        vLayout->addWidget(songButton);

        layout_5->addLayout(vLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->publicPlaylist_scrollbar->setWidget(contentWidget_5);
}

void Premium::fill_friends(){

    // Example content: add several QLabel with images or text
    QWidget *contentWidget_6 = new QWidget(this);
    QVBoxLayout *layout_6 = new QVBoxLayout(contentWidget_6);
    for (int i = 1; i <= 100; ++i)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();

        QLabel *label = new QLabel("Friend " + QString::number(i), contentWidget_6);
        hLayout->addWidget(label);

        QPushButton *chatButton = new QPushButton("Start Chat", contentWidget_6);
        chatButton->setProperty("ID", QString::number(i));
        connect(chatButton, &QPushButton::clicked, this, &Premium::onStartChatClicked);
        hLayout->addWidget(chatButton);

        layout_6->addLayout(hLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->friends_scrollArea->setWidget(contentWidget_6);



}

void Premium::onStartChatClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        QString friendID = button->property("ID").toString();
        emit startChat(friendID); // Emit signal with friendID
    }
}
