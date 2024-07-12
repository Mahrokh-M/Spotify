#include "comment_like.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "qurlquery.h"
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
    ui->textEdit_Lyrics->hide();
    // Connect the add_playlist button to its slot
    connect(ui->add_playlist, &QPushButton::clicked, this, &Comment_Like::on_add_playlist_clicked);
    setstyle();
}

Comment_Like::~Comment_Like()
{
    delete ui;
}
//**************************************************************
QMap<QString, QString>Comment_Like:: getSongDetails(int songId) {

    QMap<QString, QString> songDetails;
    QSqlQuery query;

    query.prepare("{CALL GetSongDetails(?)}");
    query.bindValue(0, songId);

    if (query.exec()) {
        // Get the first result set (song details)
        if (query.next()) {
            songDetails["ID"] = query.value("ID").toString();
            songDetails["Title"] = query.value("Title").toString();
            songDetails["AlbumTitle"] = query.value("AlbumTitle").toString();
            songDetails["Genre"] = query.value("Genre").toString();
            songDetails["Country"] = query.value("Country").toString();
            songDetails["AgeCategory"] = query.value("AgeCategory").toString();
            songDetails["Lyrics"] = query.value("Lyrics").toString();
            songDetails["PictureAddress"] = query.value("PictureAddress").toString();
        }

        // Move to the next result set (artists)
        if (query.nextResult()) {
            QStringList artists;
            while (query.next()) {
                artists << query.value("ArtistName").toString();
            }
            songDetails["ArtistName"] = artists.join(", ");
        }
        ui->Song_name->setText("Song Name: " + songDetails["Title"]);
        ui->Song_genr->setText("Genre: " + songDetails["Genre"]);
        ui->Song_Country->setText(songDetails["Country"]);
        ui->Song_AgeCategory->setText(songDetails["AgeCategory"]);
        if(songDetails["AlbumTitle"].isEmpty()){
            ui->Song_Album->setText("Album: Unknown");
        }else
            ui->Song_Album->setText("Album: " + songDetails["AlbumTitle"]);
        if(songDetails["ArtistName"].isEmpty()){
            ui->Song_Artist->setText("Artist: Unknown");
        }else
            ui->Song_Artist->setText("Artist: " + songDetails["ArtistName"]);
        QString pictureAddress = songDetails["PictureAddress"];
        if (!pictureAddress.isEmpty()) {
            // Assuming you have a QLabel named Song_pic in your UI
            QPixmap pixmap(pictureAddress);
            ui->Song_pic->setPixmap(pixmap);
            ui->Song_pic->setScaledContents(true);
        } else {
            // Set default Spotify logo if no picture address
            QPixmap spotifyLogo(":/new/prefix1/spotify logo.png");  // Path to your default Spotify logo
            ui->Song_pic->setPixmap(spotifyLogo);
            ui->Song_pic->setScaledContents(true);
        }
    }
    else {
        qDebug() << "Stored procedure execution error:" << query.lastError();
    }

    return songDetails;
}
//**************************************************************
void Comment_Like::setCommentDetails(const QString &songID)
{
    QMap<QString, QString> songDetails = getSongDetails(songID.toInt()); // Pass the song_id you want to fetch

    QString lyrics = songDetails["Lyrics"];
    if (lyrics.isEmpty()) {
        lyrics = "No lyrics available.";
    }
    ui->textEdit_Lyrics->clear();  // Clear any existing content
    ui->textEdit_Lyrics->append("Lyrics:\n");
    ui->textEdit_Lyrics->setText(lyrics);  // Set the lyrics text
    ui->textEdit_Lyrics->setReadOnly(true);  // Make the text read-only
    ui->textEdit_Lyrics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  // Disable horizontal scrolling
    ui->textEdit_Lyrics->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);  // Enab

    //    // Create a widget to hold the content of the scroll area
    //    QWidget *contentWidget = new QWidget(this);
    //    QVBoxLayout *layout = new QVBoxLayout(contentWidget);

    //    // Example comments
    //    for (int i = 1; i <= 100; ++i)
    //    {
    //        QHBoxLayout *hLayout = new QHBoxLayout();

    //        // Create label for the name of the person who wrote the comment
    //        QLabel *nameLabel = new QLabel("User " + QString::number(i), contentWidget);
    //        hLayout->addWidget(nameLabel);

    //        // Create label for the comment text
    //        QLabel *commentLabel = new QLabel("This is comment number " + QString::number(i), contentWidget);
    //        hLayout->addWidget(commentLabel);

    //        layout->addLayout(hLayout);
    //    }

    //    // Set the content widget as the scroll area's widget
    //    ui->Comment_section->setWidget(contentWidget);
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

void Comment_Like::on_show_lyrics_clicked()
{
  ui->playlists_scrollBar->hide();
  ui->question_label->hide();
  if (ui->textEdit_Lyrics->isVisible()) {
        ui->textEdit_Lyrics->hide();  // Hide the textEdit_Lyrics if it's visible
    } else {
        ui->textEdit_Lyrics->show();  // Show the textEdit_Lyrics if it's hidden
    }
}

