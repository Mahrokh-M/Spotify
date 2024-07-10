#include "comment_like.h"
#include "ui_comment_like.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QInputDialog>

Comment_Like::Comment_Like(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Comment_Like)
{
    ui->setupUi(this);

    // Hide the widgets initially
    ui->question_label->hide();
    ui->playlists_scrollBar->hide();

    // Connect the add_playlist button to its slot
    connect(ui->add_playlist, &QPushButton::clicked, this, &Comment_Like::on_add_playlist_clicked);
    setstyle();
}

Comment_Like::~Comment_Like()
{
    delete ui;
}

void Comment_Like::setCommentDetails(const QString &songID)
{
    // Fetch and set the song details based on the songID
    ui->Song_name->setText("Song name for ID: " + songID);

    // Create a widget to hold the content of the scroll area
    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);

    // Example comments
    for (int i = 1; i <= 100; ++i)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();

        // Create label for the name of the person who wrote the comment
        QLabel *nameLabel = new QLabel("User " + QString::number(i), contentWidget);
        hLayout->addWidget(nameLabel);

        // Create label for the comment text
        QLabel *commentLabel = new QLabel("This is comment number " + QString::number(i), contentWidget);
        hLayout->addWidget(commentLabel);

        layout->addLayout(hLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->Comment_section->setWidget(contentWidget);
}

void Comment_Like::on_Back_clicked()
{
    emit goBack();
}

void Comment_Like::on_add_playlist_clicked()
{
    // Show the question label and the playlists scroll area
    ui->question_label->show();
    ui->playlists_scrollBar->show();

    // Fill the playlists scroll area with playlist buttons
    fillPlaylists();
}

void Comment_Like::fillPlaylists()
{
    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);

    // Example playlists
    QStringList playlists = {"Playlist 1", "Playlist 2", "Playlist 3"};

    for (const QString &playlistName : playlists)
    {
        QPushButton *playlistButton = new QPushButton(playlistName, contentWidget);
        connect(playlistButton, &QPushButton::clicked, this, &Comment_Like::on_playlistButtonClicked);
        layout->addWidget(playlistButton);
    }

    // Add the "Add New Playlist" button
    QPushButton *addNewPlaylistButton = new QPushButton("Add New Playlist", contentWidget);
    connect(addNewPlaylistButton, &QPushButton::clicked, this, &Comment_Like::on_addNewPlaylist_clicked);
    layout->addWidget(addNewPlaylistButton);

    ui->playlists_scrollBar->setWidget(contentWidget);
}

void Comment_Like::on_playlistButtonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton)
    {
        QString playlistName = clickedButton->text();
        // Logic to add the current song to the selected playlist
        // Example:
        qDebug() << "Adding song to " << playlistName;
    }
    ui->question_label->hide();
    ui->playlists_scrollBar->hide();
}

void Comment_Like::on_addNewPlaylist_clicked()
{
    bool ok;
    QString newPlaylistName = QInputDialog::getText(this, tr("New Playlist"),tr("Playlist name:"), QLineEdit::Normal,"", &ok);
    if (ok && !newPlaylistName.isEmpty())
    {
        // Logic to create a new playlist
        // Example:
        qDebug() << "Creating new playlist: " << newPlaylistName;

        // You can also update the playlists_scrollBar to show the new playlist
        fillPlaylists();
        ui->question_label->hide();
        ui->playlists_scrollBar->hide();
    }
}

void Comment_Like::setstyle(){
    QString styleSheet = R"(
        /* Global font style */
        * {
            font: 700 12pt "UD Digi Kyokasho NK-B";
        }

    )";

    // Apply the stylesheet to all child widgets of this widget
    this->setStyleSheet(styleSheet);
}
