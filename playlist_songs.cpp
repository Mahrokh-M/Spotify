#include "playlist_songs.h"
#include "mainwindow.h"
#include "ui_playlist_songs.h"
bool flagcheck;//0=playlist //1=album
playlist_songs::playlist_songs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::playlist_songs)
{
    ui->setupUi(this);
    // Set background color
    ui->Backgound->setStyleSheet("background-color: rgb(24, 24, 24);");

    QString scrollAreaStyle = R"(
    QScrollArea {
        border: none;
        background-color: #121212; /* Dark background */
        color: #FFFFFF; /* White text color */
    }

    QScrollBar:vertical {
        border: none;
        background: #2A2A2A; /* Darker background for scrollbar */
        width: 12px;
        margin: 15px 0 15px 0;
    }

    QScrollBar::handle:vertical {
        background: #1DB954; /* Spotify green for the scrollbar handle */
        min-height: 20px;
        border-radius: 6px;
    }

    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
        border: none;
        background: none;
    }

    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
        background: none;
    }

    QScrollBar:horizontal {
        border: none;
        background: #2A2A2A; /* Darker background for scrollbar */
        height: 12px;
        margin: 0px 15px 0px 15px;
    }

    QScrollBar::handle:horizontal {
        background: #1DB954; /* Spotify green for the scrollbar handle */
        min-width: 20px;
        border-radius: 6px;
    }

    QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
        border: none;
        background: none;
    }

    QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
        background: none;
    }

    QWidget {
        background-color: #121212; /* Dark background for inner content */
    }

    QLabel {
        color: #FFFFFF; /* White text color for labels */
    }

    QPushButton {
        background-color: #1DB954; /* Spotify green for buttons */
        border: none;
        color: #FFFFFF; /* White text color */
        padding: 10px;
        border-radius: 5px;
        font-size: 12pt;
    }

    QPushButton:hover {
        background-color: #1ED760; /* Slightly lighter green for hover state */
    }

    QPushButton:pressed {
        background-color: #1AAE48; /* Slightly darker green for pressed state */
    }

    QVBoxLayout, QHBoxLayout {
        margin: 0;
        spacing: 10px;
    }
)";
ui->scrollArea->setStyleSheet(scrollAreaStyle);
    // Set playlist name style
    ui->playlist_name->setStyleSheet(
        "color: white;"
        "font: bold 18pt 'Segoe UI';"
    );

    // Set playlist pic style
    ui->playlist_pic->setStyleSheet(
        "border-radius: 10px;"
        "background-color: rgb(24, 24, 24);"
    );

    // Set Like button style
    ui->Like_button->setIcon(QIcon(":/icons/heart.png"));
    ui->Like_button->setIconSize(QSize(24, 24));
    ui->Like_button->setCheckable(true);
    ui->Like_button->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "}"
        "QPushButton:checked {"
        "    background-color: transparent;"
        "    border: none;"
        "    icon: url(:/icons/heart_filled.png);"
        "}"
    );

    // Set Back button style
    ui->Back->setIcon(QIcon(":/icons/back_arrow.png"));
    ui->Back->setIconSize(QSize(24, 24));
    ui->Back->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: white;"
        "    font: 12pt 'Segoe UI';"
        "}"
        "QPushButton:hover {"
        "    color: rgb(180, 180, 180);"
        "}"
    );

    // Set sizes and alignment
    ui->playlist_name->setAlignment(Qt::AlignCenter);
    ui->playlist_pic->setAlignment(Qt::AlignCenter);
    ui->Like_button->setIconSize(QSize(24, 24));
    ui->Back->setIconSize(QSize(24, 24));
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
    flagcheck=0;
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
    if(flagcheck==0){
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
    else if(flagcheck==1){
         int userId = ID;
        // Check if the user has a valid subscription
        QSqlQuery checkSubscriptionQuery(db);
        checkSubscriptionQuery.prepare("SELECT 1 FROM Premium WHERE user_id = :user_id AND End_time > GETDATE()");
        checkSubscriptionQuery.bindValue(":user_id", userId);

        if (!checkSubscriptionQuery.exec()) {
            QMessageBox::critical(nullptr, "Error", "Failed to check subscription: " + checkSubscriptionQuery.lastError().text());
            return;
        }

        if (!checkSubscriptionQuery.next()) {
            QMessageBox::critical(nullptr, "Error", "User does not have a valid subscription. Liking is not allowed.");
            return;
        }

        // Check if the album is already liked
        QSqlQuery likeCheckQuery(db);
        likeCheckQuery.prepare("SELECT 1 FROM Like_album WHERE user_id = :user_id AND album_id = :album_id");
        likeCheckQuery.bindValue(":user_id", userId);
        likeCheckQuery.bindValue(":album_id", albumid);

        if (!likeCheckQuery.exec()) {
            QMessageBox::critical(nullptr, "Error", "Failed to check if album is already liked: " + likeCheckQuery.lastError().text());
            return;
        }

        if (likeCheckQuery.next()) {
            // The album is already liked
            QMessageBox::information(nullptr, "Info", "You have already liked this album.");
        } else {
            // Like the album
            QSqlQuery likeAlbumQuery(db);
            likeAlbumQuery.prepare("INSERT INTO Like_album (user_id, album_id) VALUES (:user_id, :album_id)");
            likeAlbumQuery.bindValue(":user_id", userId);
            likeAlbumQuery.bindValue(":album_id", albumid);

            if (!likeAlbumQuery.exec()) {
                QMessageBox::critical(nullptr, "Error", "Failed to like the album: " + likeAlbumQuery.lastError().text());
                return;
            }

            // Notify the user that the album was liked successfully
            QMessageBox::information(nullptr, "Success", "Album liked successfully.");

            // Example of changing the button style after liking an album (assuming there is a QPushButton for this action)
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
    flagcheck=1;
    albumid=AlbumID.toInt();
    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);
    // Prepare and execute the SQL query
    QSqlQuery query(db);
    query.prepare("EXEC GetSongsByAlbumID @AlbumID = :albumID");
    query.bindValue(":albumID", AlbumID.toInt());

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve songs for the album: " + query.lastError().text());
        return;
    }

    // Set the album picture (example, replace with actual logic)
    QString albumImagePath = ":/new/prefix1/spotify logo.png";
    QLabel *albumPicLabel = this->findChild<QLabel*>("playlist_pic");
    if (albumPicLabel) {
        albumPicLabel->setPixmap(QPixmap(albumImagePath).scaled(100, 100, Qt::KeepAspectRatio));
    }

    // Process each song from the query result
    while (query.next()) {
        QString songTitle = query.value("Song_Title").toString();
        QString songID=query.value("ID").toString();
        QString picturePath = query.value("addr").toString(); // Replace with actual picture path logic if available
        QString imagePath = (picturePath.isEmpty() || !QFile::exists(picturePath)) ? ":/new/prefix1/spotify logo.png" : picturePath;

        QHBoxLayout *hLayout = new QHBoxLayout();

        // Create label for song image
        QLabel *label = new QLabel(contentWidget);
        label->setPixmap(QPixmap(imagePath).scaled(50, 50, Qt::KeepAspectRatio));
        hLayout->addWidget(label);

        // Create button for song name
        QPushButton *songButton = new QPushButton(songTitle, contentWidget);
        songButton->setProperty("ID", songID); // Use song ID as ID for this example
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



