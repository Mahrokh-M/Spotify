#include "homepage.h"
#include "ui_homepage.h"

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage),
    songCount(0)
{
    ui->setupUi(this);

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
    for (int i = 0; i < 100; ++i) {
        addSongItem("1", "Song 1", ":/new/prefix1/spotify logo.png");
        addSongItem("2", "Song 2", ":/new/prefix1/spotify logo.png");
        addSongItem("3", "Song 3", ":/new/prefix1/spotify logo.png");
    }

    // Add more songs as needed
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::addSongItem(const QString &songID,const QString &songName, const QString &imagePath)
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
    connect(songButton, &QPushButton::clicked, this, &HomePage::playSong);
    gridLayout->addWidget(songButton, row * 2 + 1, col);

    songCount++;
}

void HomePage::playSong()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        QString songPath = button->property("songID").toString();
//        player->setMedia(QUrl::fromLocalFile(songPath));
//        player->play();
    }
}

void HomePage::on_pushButton_clicked()
{
    emit logoutSuccessful();  // Emit the signal
}

