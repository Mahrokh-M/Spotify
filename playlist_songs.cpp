#include "playlist_songs.h"
#include "ui_playlist_songs.h"

playlist_songs::playlist_songs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::playlist_songs)
{
    ui->setupUi(this);
    setstyle();
}

playlist_songs::~playlist_songs()
{
    delete ui;
}

void playlist_songs::on_Back_clicked()
{
    emit goBack();
}

void playlist_songs::fillPlaylist(const QString &listID)
{
    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);

    // Example songs
    for (int i = 1; i <= 100; ++i)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();

        // Create label for song image
        QLabel *label = new QLabel(contentWidget);
        label->setPixmap(QPixmap(":/new/prefix1/spotify logo.png").scaled(50, 50, Qt::KeepAspectRatio));
        hLayout->addWidget(label);

        // Create button for song name
        QPushButton *songButton = new QPushButton("Song " + QString::number(i), contentWidget);
        songButton->setProperty("ID", QString::number(i)); // Assuming songID is the same as i for this example
        songButton->setProperty("name", "Song " + QString::number(i));
        songButton->setProperty("pic_path", ":/new/prefix1/spotify logo.png");
        connect(songButton, &QPushButton::clicked, this, &playlist_songs::onSongButtonClicked);
        hLayout->addWidget(songButton);

        layout->addLayout(hLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->scrollArea->setWidget(contentWidget);
    setstyle();
}

void playlist_songs::onSongButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        QString songID = button->property("ID").toString();
        emit open_comment(songID);
    }
}

void playlist_songs::setstyle(){
    QString styleSheet = R"(
        /* Global font style */
        * {
            font: 700 12pt "UD Digi Kyokasho NK-B";
        }

    )";

    // Apply the stylesheet to all child widgets of this widget
    this->setStyleSheet(styleSheet);
}
