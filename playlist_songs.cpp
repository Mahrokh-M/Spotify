#include "playlist_songs.h"
#include "mainwindow.h"
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
    ui->Like_button->setStyleSheet("");
    emit goBack();
}

void playlist_songs::fillPlaylist(const QString &listID)
{
    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);
    ui->playlist_name->setText(listID);

    // Prepare and execute the SQL query
    QSqlQuery query(db);
    query.prepare("EXEC GetSongsInPlaylist @playlist_name = :playlist_name");
    query.bindValue(":playlist_name", listID);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve songs for the playlist: " + query.lastError().text());
        return;
    }

    // Set the playlist picture (example, replace with actual logic)
    QString playlistImagePath = ":/new/prefix1/spotify logo.png";
    QLabel *playlistPicLabel = this->findChild<QLabel*>("playlist_pic");
    if (playlistPicLabel) {
        playlistPicLabel->setPixmap(QPixmap(playlistImagePath).scaled(100, 100, Qt::KeepAspectRatio));
    }

    // Process each song from the query result
    while (query.next()) {
        QString songTitle = query.value("Song_Title").toString();
        QString songID=query.value("ID").toString();
        QString picturePath = query.value("addr").toString();  // Replace with actual picture path logic if available
        QString imagePath = (picturePath.isEmpty() || !QFile::exists(picturePath)) ? ":/new/prefix1/spotify logo.png" : picturePath;

        QHBoxLayout *hLayout = new QHBoxLayout();

        // Create label for song image
        QLabel *label = new QLabel(contentWidget);
        label->setPixmap(QPixmap(imagePath).scaled(50, 50, Qt::KeepAspectRatio));
        hLayout->addWidget(label);

        // Create button for song name
        QPushButton *songButton = new QPushButton(songTitle, contentWidget);
        songButton->setProperty("ID", songID); // Use song title as ID for this example
        songButton->setProperty("name", songTitle);
        songButton->setProperty("pic_path", imagePath);
        connect(songButton, &QPushButton::clicked, this, &playlist_songs::onSongButtonClicked);
        hLayout->addWidget(songButton);

        layout->addLayout(hLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->scrollArea->setWidget(contentWidget);
    setstyle();
    updateLikeButtonStyle(ui->playlist_name->text());
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

void playlist_songs::on_Like_button_clicked()
{
    updateLikeButtonStyle(ui->playlist_name->text());
    // Replace with actual user ID logic
    int userId = ID;

    // Get the playlist name from UI element (assuming ui->playlist_name is a QLabel or similar)
    QString playlistName = ui->playlist_name->text();

    // Check if the playlist exists in Play_list
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT 1 FROM Play_list WHERE [name] = :playlist_name");
    checkQuery.bindValue(":playlist_name", playlistName);

    if (!checkQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to check playlist existence: " + checkQuery.lastError().text());
        return;
    }

    if (!checkQuery.next()) {
        QMessageBox::critical(this, "Error", "Playlist does not exist.");
        return;
    }

    // Prepare and execute the SQL query to like the playlist
    QSqlQuery query(db);
    query.prepare("EXEC LikePlaylist @user_id = :user_id, @playlist_name = :playlist_name");
    query.bindValue(":user_id", userId);
    query.bindValue(":playlist_name", playlistName);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to like the playlist: " + query.lastError().text());
        return;
    }

    // Check if the playlist was liked or already liked
    QSqlQuery likeCheckQuery(db);
    likeCheckQuery.prepare("SELECT 1 FROM Like_Play_list WHERE user_id = :user_id AND [name] = :playlist_name");
    likeCheckQuery.bindValue(":user_id", userId);
    likeCheckQuery.bindValue(":playlist_name", playlistName);

    if (!likeCheckQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to verify like status: " + likeCheckQuery.lastError().text());
        return;
    }

    if (likeCheckQuery.next()) {
        // If the entry is found, it means the playlist was already liked
        QMessageBox::information(this, "Info", "You have already liked this playlist.");
    } else {
        // If the entry is not found, it means the playlist was liked just now
        QMessageBox::information(this, "Success", "Playlist liked successfully.");

        // Change the button color to a gradient of red
        QPushButton *likeButton = qobject_cast<QPushButton *>(sender());
        if (likeButton) {
            likeButton->setStyleSheet(
                        "QPushButton {"
                        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 red, stop:1 darkred);"
                        "color: white;"
                        "border: none;"
                        "padding: 10px;"
                        "border-radius: 5px;"
                        "}"
                        "QPushButton:hover {"
                        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 lightcoral, stop:1 indianred);"
                        "}"
                        "QPushButton:pressed {"
                        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 darkred, stop:1 red);"
                        "}"
                        );
        }
    }
}

void playlist_songs::updateLikeButtonStyle(const QString &playlistName)
{
    // User ID - replace with actual user ID logic
    int userId = ID;

    // Check if the playlist is already liked
    QSqlQuery query(db);
    query.prepare("SELECT 1 FROM Like_Play_list WHERE user_id = :user_id AND [name] = :playlist_name");
    query.bindValue(":user_id", userId);
    query.bindValue(":playlist_name", playlistName);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to check like status: " + query.lastError().text());
        return;
    }

    QPushButton *likeButton = ui->Like_button;

    if (query.next()) {
        // If the entry is found, it means the playlist is already liked
        likeButton->setStyleSheet(
                    "QPushButton {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 red, stop:1 darkred);"
                    "color: white;"
                    "border: none;"
                    "padding: 10px;"
                    "border-radius: 5px;"
                    "}"
                    "QPushButton:hover {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 lightcoral, stop:1 indianred);"
                    "}"
                    "QPushButton:pressed {"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 darkred, stop:1 red);"
                    "}"
                    );
    } else {
        // Reset to default style if not liked
        likeButton->setStyleSheet("");
    }
}

void playlist_songs::fillAlbum(const QString &AlbumID){

}

