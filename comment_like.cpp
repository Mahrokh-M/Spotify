#include "comment_like.h"
#include "mainwindow.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "qurlquery.h"
#include "ui_comment_like.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QInputDialog>
int ID_Song;
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
    commentSection = findChild<QScrollArea*>("Comment_section");

    // Create a layout to hold the comments
    commentsLayout = new QVBoxLayout();
    QWidget *scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setLayout(commentsLayout);
    commentSection->setWidget(scrollAreaWidgetContents);
    commentSection->setWidgetResizable(true);
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
    clearScrollArea(ui->Comment_section);//**
    loadCommentsForSong(songID.toInt());//**
    ID_Song=songID.toInt();
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
    clearScrollArea(ui->Comment_section);
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


void Comment_Like::on_Add_comment_clicked()
{
    QString commentText = ui->write_comment->text();
    if (commentText.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Comment text cannot be empty.");
        return;
    }

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("EXEC AddCommentToSong @user_id = :user_id, @song_id = :song_id, @text = :text");
        query.bindValue(":user_id", ID);
        query.bindValue(":song_id", ID_Song);
        query.bindValue(":text", commentText);

        if (!query.exec()) {
            qDebug() << "Failed to execute stored procedure:" << query.lastError();
            QMessageBox::critical(this, "Database Error", "Failed to add comment to song.");
        } else {
            qDebug() << "Comment added successfully!";
            clearScrollArea(ui->Comment_section);
             loadCommentsForSong(ID_Song);
            //QMessageBox::information(this, "Success", "Comment added successfully to song.");
            ui->write_comment->clear();
        }
    } else {
        qDebug() << "Database is not open!";
        QMessageBox::critical(this, "Database Error", "Database is not open.");
    }
}
void Comment_Like::loadCommentsForSong(int ID_Song) {
    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("EXEC GetCommentsForSong @song_id = :song_id");
        query.bindValue(":song_id", ID_Song);

        if (!query.exec()) {
            qDebug() << "Failed to execute stored procedure:" << query.lastError();
            QMessageBox::critical(this, "Database Error", "Failed to retrieve comments for song.");
        } else {
            while (query.next()) {
                QString text = query.value(0).toString();
                int userId = query.value(1).toInt();
                QString date = query.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss");

                // Create a horizontal layout for each comment
                QHBoxLayout *hLayout = new QHBoxLayout();

                // Create label for the name of the person who wrote the comment
                QLabel *nameLabel = new QLabel(QString("User %1").arg(userId), this);
                hLayout->addWidget(nameLabel);

                // Create label for the comment text
                QLabel *commentLabel = new QLabel(text, this);
                hLayout->addWidget(commentLabel);

                // Create label for the comment date
                QLabel *dateLabel = new QLabel(date, this);
                hLayout->addWidget(dateLabel);

                // Add the horizontal layout to the vertical layout of the scroll area
                commentsLayout->addLayout(hLayout);
            }
        }
    } else {
        qDebug() << "Database is not open!";
        QMessageBox::critical(this, "Database Error", "Database is not open.");
    }
}
void Comment_Like::clearScrollArea(QScrollArea *scrollArea) {

    // Retrieve the widget from the scroll area
    QWidget *widget = scrollArea->widget();

    // Check if the widget exists
    if (widget) {
        // Get the layout of the widget
        QLayout *layout = widget->layout();

        // Remove all widgets from the layout
        if (layout) {
            QLayoutItem *item;
            while ((item = layout->takeAt(0)) != nullptr) {
                QWidget *widget = item->widget();
                if (widget) {
                    widget->deleteLater(); // Safely delete the widget
                } else {
                    delete item->layout(); // Delete any child layouts
                }
            }
        }
    }

    // Reset the scroll area with a new widget to keep the layout
    QWidget *newWidget = new QWidget();
    commentsLayout = new QVBoxLayout(newWidget);
    newWidget->setLayout(commentsLayout);
    scrollArea->setWidget(newWidget);


}
