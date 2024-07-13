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
#include "newplaylistdialog.h"
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

    QString styleSheet = R"(
/* General font and background */
QWidget {
    background-color: #121212; /* Dark background similar to Spotify */
    color: #FFFFFF; /* White text */
    font: 15pt "Segoe UI Historic"; /* Specified font */
}

/* Buttons */
QPushButton {
    background-color: #191414; /* Dark background */
    color: white;
    border: 2px solid #1DB954; /* Darker green border */
    padding: 10px;
    border-radius: 20px;
    font-size: 14px;
}

QPushButton:hover {
    background-color: #1ED760; /* Lighter green for hover */
    border: 2px solid #1DB954;
}

QPushButton:pressed {
    background-color: #1DB954; /* Spotify green for pressed */
    border: 2px solid #1DB954;
}

/* Labels */
QLabel {
    color: white;
    background-color: #1DB954; /* Spotify green */
    padding: 5px;
    border-radius: 25px; /* Fully rounded corners */
    font-size: 14px;
}

/* Scroll areas */
QScrollArea {
    background-color: #191414; /* Dark background */
    color: white; /* White text */
}

/* Scrollbar */
QScrollBar:vertical {
    border: none;
    background: #191414; /* Dark background */
    width: 10px;
    margin: 0px 0px 0px 0px;
}

QScrollBar::handle:vertical {
    background: #1DB954; /* Spotify green */
    min-height: 20px;
    border-radius: 5px;
}

QScrollBar::add-line:vertical {
    background: none;
    height: 0px;
    subcontrol-position: bottom;
    subcontrol-origin: margin;
}

QScrollBar::sub-line:vertical {
    background: none;
    height: 0px;
    subcontrol-position: top;
    subcontrol-origin: margin;
}

/* Text Edit */
QTextEdit {
    background-color: #191414; /* Dark background */
    color: white;
    border: 1px solid #1DB954;
    padding: 10px;
    border-radius: 10px;
    font-size: 14px;
}

/* Line Edit */
QLineEdit {
    background-color: #191414; /* Dark background */
    color: white;
    border: 1px solid #1DB954;
    padding: 10px;
    border-radius: 10px;
    font-size: 14px;
}

/* Specific styling for Like_button */
#Like_button {
    background-color: #191414; /* Dark background */
    color: white;
    border: 2px solid #1DB954;
    padding: 10px;
    border-radius: 20px;
    font-size: 14px;
}


    )";
   this->setStyleSheet(styleSheet);
    //ui->Comment_section->setStyleSheet(scrollAreaStyle);
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
            songDetails["ArtistName"]=query.value("ArtistName").toString();
            songDetails["Genre"] = query.value("Genre").toString();
            songDetails["Country"] = query.value("Country").toString();
            songDetails["AgeCategory"] = query.value("AgeCategory").toString();
            songDetails["Lyrics"] = query.value("Lyrics").toString();
            songDetails["PictureAddress"] = query.value("PictureAddress").toString();
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
//**************************************************************
void Comment_Like::on_Back_clicked()
{
    clearScrollArea(ui->Comment_section);
    emit goBack();
}
//**************************************************************
void Comment_Like::on_add_playlist_clicked()
{
    ui->textEdit_Lyrics->hide();
    // Show the question label and the playlists scroll area
    ui->question_label->show();
    ui->playlists_scrollBar->show();

    // Fill the playlists scroll area with playlist buttons
    fillPlaylists();
}
//*************************************************************
void Comment_Like::fillPlaylists()
{
    QSqlQuery query(db);
    query.prepare("EXEC GetUserPlaylists @user_id = :user_id");
    query.bindValue(":user_id", ID);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);

    while (query.next()) {
        QString playlistName = query.value("name").toString();
        QPushButton *playlistButton = new QPushButton(playlistName, contentWidget);
        playlistButton->setProperty("playlistName", playlistName);
        playlistButton->setProperty("songId", ID_Song);
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
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;

    QString playlistName = button->property("playlistName").toString();
    int songId = button->property("songId").toInt();

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database is not open.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("EXEC AddSongToPlaylist @user_id = :user_id, @playlist_name = :playlist_name, @song_id = :song_id");
    query.bindValue(":user_id", ID);
    query.bindValue(":playlist_name", playlistName);
    query.bindValue(":song_id", songId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    QString resultMessage;
    if (query.next()) {
        resultMessage = query.value(0).toString();
    }

    QMessageBox::information(this, "Add Song to Playlist", resultMessage);
}
void Comment_Like::on_addNewPlaylist_clicked()
{
    NewPlaylistDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        QString newPlaylistName = dialog.playlistName();
        bool isPublic = dialog.isPublic();
        QString imagePath = dialog.imagePath();

        if (!newPlaylistName.isEmpty())
        {
            QSqlQuery query(db);
            query.prepare("EXEC CreatePlaylist @user_id = :user_id, @playlist_name = :playlist_name, @is_public = :is_public, @address_of_picture = :address_of_picture");
            query.bindValue(":user_id", ID);
            query.bindValue(":playlist_name", newPlaylistName);
            query.bindValue(":is_public", isPublic);
            query.bindValue(":address_of_picture", imagePath);

            if (!query.exec()) {
                QMessageBox::critical(this, "Database Error", query.lastError().text());
                return;
            }

            QString resultMessage;
            if (query.next()) {
                resultMessage = query.value(0).toString();
            }

            QMessageBox::information(this, "Create Playlist", resultMessage);

            fillPlaylists();
            ui->question_label->hide();
            ui->playlists_scrollBar->show();
            emit newPlayList();
        }
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

void Comment_Like::on_Like_button_clicked()
{
    // LikeSong
    QSqlQuery likeSongQuery(db);
    likeSongQuery.prepare("EXEC LikeSong @user_id = :user_id, @song_id = :song_id");
    likeSongQuery.bindValue(":user_id", ID);
    likeSongQuery.bindValue(":song_id", ID_Song);

    if (!likeSongQuery.exec()) {
        QMessageBox::critical(this, "Database Error", likeSongQuery.lastError().text());
        return;
    }

    //InsertUserArtistLikes
    QSqlQuery insertArtistLikesQuery(db);
    if (!insertArtistLikesQuery.exec("EXEC InsertUserArtistLikes")) {
        QMessageBox::critical(this, "Database Error", insertArtistLikesQuery.lastError().text());
        return;
    }
    QMessageBox::information(this, "Success", "Song liked and related records updated successfully.");
}


void Comment_Like::on_add_favorite_clicked()
{
    QSqlQuery query(db);
    query.prepare("EXEC ToggleFavoriteSong @user_id = :user_id, @song_id = :song_id");
    query.bindValue(":user_id", ID);
    query.bindValue(":song_id", ID_Song);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    QString resultMessage;
    if (query.next()) {
        resultMessage = query.value(0).toString();
    }

    QMessageBox::information(this, "Add to Favorites", resultMessage);
}






