#include "premium.h"
#include "mainwindow.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "qurlquery.h"
#include "ui_premium.h"

Premium::Premium(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Premium),
    songCount(0)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

    scrollArea = ui->scrollArea;
    contentWidget = new QWidget(this);
    gridLayout = new QGridLayout(contentWidget);

    contentWidget->setLayout(gridLayout);
    scrollArea->setWidget(contentWidget);

    setstyle();

}

Premium::~Premium()
{
    delete ui;
}

void Premium::setstyle(){
    QString styleSheet = R"(
        /* Global font style */
        * {
            font: 700 12pt "UD Digi Kyokasho NK-B";
        }

    )";

    // Apply the stylesheet to all child widgets of this widget
    this->setStyleSheet(styleSheet);
}


void Premium::setUserID(const QString &userType){
    Type=userType;
    //  if is premium
//    if(userType=="Premium User"){
//    ui->tabWidget->removeTab(7);
//    ui->tabWidget->removeTab(7);}
//    // if is simple user
//    if(userType=="Regular User"){
//        while (ui->tabWidget->count() > 2) {
//            ui->tabWidget->removeTab(2);
//        }
//    }

    fillSongs();
    fill_favorites();
    fill_playlists();
    fill_friends();
    fill_follow();
    fillAllUsers();
    fill_concerts();
    fill_wallet();
    fillFriendshipRequests();
    fill_my_belongings();
}

bool Premium::initializeDatabase(QSqlDatabase &db) {
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={ODBC Driver 17 for SQL Server};SERVER=LOCALHOST\\SQLEXPRESS;DATABASE=Spotify;Trusted_Connection=Yes;");

    if (!db.open()) {
        qDebug() << "Database connection error:" << db.lastError().text();
        return false;
    }

    qDebug() << "Database connected!";
    return true;
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
    QPushButton *songButton = new QPushButton(songName, this);  // Use songName as the text of the button
    songButton->setProperty("ID", songID);
    songButton->setProperty("pic_path", imagePath);
    connect(songButton, &QPushButton::clicked, this, &Premium::addComment_like);
    gridLayout->addWidget(songButton, row * 2 + 1, col);

    songCount++;
}

void Premium::fillSongs()
{
    // Create a new content widget for the scroll area
    QWidget *contentWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(contentWidget);
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft); // Align content to the top-left

    QSqlQuery query("SELECT song_id, address_of_picture, title FROM Songs");
    int row = 0, col = 0;
    const int maxColumns = 4; // Adjust this value based on your layout preference

    while (query.next()) {
        QString songID = query.value(0).toString();
        QString picturePath = query.value(1).toString();
        QString songName = query.value(2).toString();
        QString imagePath = picturePath.isEmpty() ? ":/new/prefix1/spotify logo.png" : picturePath;

        // Create a frame with a green border
        QFrame *frame = new QFrame(contentWidget);
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(2);
        frame->setFixedSize(150, 200); // Set fixed size for the frame
        frame->setStyleSheet("border: 2px solid green;");

        // Create a vertical layout to hold image and song name
        QVBoxLayout *vLayout = new QVBoxLayout(frame);

        // Create label for song image
        QLabel *imageLabel = new QLabel(frame);
        QPixmap pixmap;
        if (!imagePath.isEmpty() && pixmap.load(imagePath)) {
            imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
        } else {
            imageLabel->setPixmap(QPixmap(":/new/prefix1/spotify logo.png").scaled(100, 100, Qt::KeepAspectRatio));
        }
        vLayout->addWidget(imageLabel);

        // Create button for song name
        QPushButton *songButton = new QPushButton(songName, frame);
        songButton->setProperty("ID", songID);
        songButton->setProperty("name", songName);
        songButton->setProperty("pic_path", imagePath);
        connect(songButton, &QPushButton::clicked, this, &Premium::addComment_like);
        vLayout->addWidget(songButton);

        // Add frame to the grid layout
        layout->addWidget(frame, row, col);

        // Move to the next column
        col++;
        // If we've reached the maximum number of columns, move to the next row
        if (col >= maxColumns) {
            col = 0;
            row++;
        }
    }

    // Set the content widget as the scroll area's widget
    ui->scrollArea->setWidget(contentWidget);
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

void Premium::show_album_page()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        QString albumID = button->property("ID").toString();
        emit open_album(albumID); // Emit signal with albumID
    }
}

void Premium::fill_favorites() {
    // Get user ID from the current session or context
    int userId = 1; // Replace this with your logic to get the current user's ID

    // Fill favorites
    QWidget *contentWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(contentWidget);
    layout->setAlignment(Qt::AlignLeft); // Align content to the left

    QSqlQuery query(db);
    query.prepare("EXEC GetFavoriteSongsAndAlbums @user_id = :user_id");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve favorite songs and albums: " + query.lastError().text());
        return;
    }

    while (query.next()) {
        int itemId = query.value(0).toInt();
        QString itemName = query.value(1).toString();
        QString itemType = query.value(2).toString();
        QString picPath = query.value(3).toString(); // Get the picture path from the query result
        QString imagePath = (picPath.isEmpty() || !QFile::exists(picPath)) ? ":/new/prefix1/spotify logo.png" : picPath;

        QFrame *frame = new QFrame(contentWidget);
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(2);
        frame->setFixedSize(150, 200); // Set fixed size for the frame
        frame->setStyleSheet("border: 2px solid green;"); // Set green border color
        QVBoxLayout *vLayout = new QVBoxLayout(frame);

        QLabel *label = new QLabel(frame);
        label->setPixmap(QPixmap(imagePath).scaled(100, 100, Qt::KeepAspectRatio));
        vLayout->addWidget(label);

        QPushButton *itemButton = new QPushButton(itemName, frame);
        itemButton->setProperty("ID", itemId);
        itemButton->setProperty("name", itemName);
        itemButton->setProperty("pic_path", imagePath);

        if (itemType == "Song") {
            connect(itemButton, &QPushButton::clicked, this, &Premium::addComment_like);
        } else if (itemType == "Album") {
            connect(itemButton, &QPushButton::clicked, this, &Premium::show_album_page);
        }

        vLayout->addWidget(itemButton);
        layout->addWidget(frame);
    }

    ui->scrollArea_2->setWidget(contentWidget);

    // Fill recommended songs and albums
    QWidget *contentWidget_2 = new QWidget(this);
    QHBoxLayout *layout_2 = new QHBoxLayout(contentWidget_2);
    layout_2->setAlignment(Qt::AlignLeft); // Align content to the left

    // Get recommended albums
    QSqlQuery recAlbumsQuery(db);
    recAlbumsQuery.prepare("EXEC GetRecommendedAlb @user_id = :user_id");
    recAlbumsQuery.bindValue(":user_id", userId);

    if (!recAlbumsQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve recommended albums: " + recAlbumsQuery.lastError().text());
        return;
    }

    while (recAlbumsQuery.next()) {
        int albumId = recAlbumsQuery.value(0).toInt();
        QString albumName = recAlbumsQuery.value(1).toString();
        QString picPath = recAlbumsQuery.value(2).toString(); // Get the picture path from the query result
        QString imagePath = (picPath.isEmpty() || !QFile::exists(picPath)) ? ":/new/prefix1/spotify logo.png" : picPath;

        QFrame *frame = new QFrame(contentWidget_2);
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(2);
        frame->setFixedSize(150, 200); // Set fixed size for the frame
        frame->setStyleSheet("border: 2px solid green;"); // Set green border color
        QVBoxLayout *vLayout = new QVBoxLayout(frame);

        QLabel *label = new QLabel(frame);
        label->setPixmap(QPixmap(imagePath).scaled(100, 100, Qt::KeepAspectRatio));
        vLayout->addWidget(label);

        QPushButton *albumButton = new QPushButton(albumName, frame);
        albumButton->setProperty("ID", albumId);
        albumButton->setProperty("name", albumName);
        albumButton->setProperty("pic_path", imagePath);
        connect(albumButton, &QPushButton::clicked, this, &Premium::show_album_page);
        vLayout->addWidget(albumButton);

        layout_2->addWidget(frame);
    }

    // Get recommended songs
    QSqlQuery recSongsQuery(db);
    recSongsQuery.prepare("EXEC GetRecommendedSongsByArtistLike @user_id = :user_id");
    recSongsQuery.bindValue(":user_id", userId);

    if (!recSongsQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve recommended songs: " + recSongsQuery.lastError().text());
        return;
    }

    while (recSongsQuery.next()) {
        int songId = recSongsQuery.value(0).toInt();
        QString songName = recSongsQuery.value(1).toString();
        QString picPath = recSongsQuery.value(2).toString(); // Get the picture path from the query result
        QString imagePath = (picPath.isEmpty() || !QFile::exists(picPath)) ? ":/new/prefix1/spotify logo.png" : picPath;

        QFrame *frame = new QFrame(contentWidget_2);
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(2);
        frame->setFixedSize(150, 200); // Set fixed size for the frame
        frame->setStyleSheet("border: 2px solid green;"); // Set green border color
        QVBoxLayout *vLayout = new QVBoxLayout(frame);

        QLabel *label = new QLabel(frame);
        label->setPixmap(QPixmap(imagePath).scaled(100, 100, Qt::KeepAspectRatio));
        vLayout->addWidget(label);

        QPushButton *songButton = new QPushButton(songName, frame);
        songButton->setProperty("ID", songId);
        songButton->setProperty("name", songName);
        songButton->setProperty("pic_path", imagePath);
        connect(songButton, &QPushButton::clicked, this, &Premium::addComment_like);
        vLayout->addWidget(songButton);

        layout_2->addWidget(frame);
    }

    ui->scrollArea_3->setWidget(contentWidget_2);
}

void Premium::fill_playlists()
{
    myPlaylist();
    friendPlaylist();
    publicPlaylist();

}

void Premium::myPlaylist() {
    // Get user ID from the current session or context
    int userId = ID; // Replace this with your logic to get the current user's ID

    QWidget *contentWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(contentWidget);
    layout->setAlignment(Qt::AlignLeft); // Align content to the left

    QSqlQuery query(db);
    query.prepare("EXEC GetPlaylistsByUserId @user_id = :user_id");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve user's playlists: " + query.lastError().text());
        return;
    }

    while (query.next()) {
        QString playlistName = query.value(0).toString();
        QString picturePath = query.value(1).toString();
        QString imagePath = (picturePath.isEmpty() || !QFile::exists(picturePath)) ? ":/new/prefix1/spotify logo.png" : picturePath;

        QVBoxLayout *vLayout = new QVBoxLayout();

        QFrame *frame = new QFrame(contentWidget);
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(2);
        frame->setFixedSize(150, 180); // Set fixed size for the frame
        frame->setStyleSheet("border: 2px solid green;"); // Set green border color

        QLabel *label = new QLabel(frame);
        label->setPixmap(QPixmap(imagePath).scaled(100, 100, Qt::KeepAspectRatio));
        vLayout->addWidget(label);

        QPushButton *playlistButton = new QPushButton(playlistName, frame);
        playlistButton->setProperty("name", playlistName);
        playlistButton->setProperty("pic_path", imagePath);
        connect(playlistButton, &QPushButton::clicked, this, &Premium::showPlaylist);
        vLayout->addWidget(playlistButton);

        frame->setLayout(vLayout);
        layout->addWidget(frame);
    }

    ui->your_playlist_scrollbar->setWidget(contentWidget);
}

void Premium::showPlaylist(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        QString songID = button->property("name").toString();
        emit open_playlist(songID); // Emit signal with songID
    }
}

void Premium::friendPlaylist() {
    // Clear previous contents of the scroll area
    clearScrollArea(ui->friend_playlist_scrollbar);

    // Get user ID from the current session or context
    int userId = ID; // Replace this with your logic to get the current user's ID

    // Execute the stored procedure to get friend playlists
    QSqlQuery query;
    query.prepare("EXEC GetFriendPlaylists @user_id = :user_id");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve friend playlists: " + query.lastError().text());
        return;
    }

    // Create a widget to hold all playlist items
    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(contentWidget);

    while (query.next()) {
        QString playlistName = query.value("Playlist_Name").toString();

        // Create layout for each playlist item
        QFrame *frame = new QFrame(contentWidget);
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(2);
        frame->setFixedSize(150, 180); // Set fixed size for the frame
        frame->setStyleSheet("border: 2px solid green;"); // Set green border color
        QVBoxLayout *vLayout = new QVBoxLayout(frame);

        // Get the playlist image address (use address_of_picture or default to Spotify logo)
        QString picPath = query.value("address_of_picture").toString();
        if (picPath.isEmpty() || !QFile::exists(picPath)) {
            picPath = ":/new/prefix1/spotify logo.png"; // Default to Spotify logo if path is empty or invalid
        }

        // Create label for playlist image
        QLabel *label = new QLabel(frame);
        label->setPixmap(QPixmap(picPath).scaled(100, 100, Qt::KeepAspectRatio));
        vLayout->addWidget(label);

        // Create button for playlist name
        QPushButton *playlistButton = new QPushButton(playlistName, frame);
        playlistButton->setProperty("Name", playlistName); // Set playlist name property
        playlistButton->setProperty("pic_path", picPath); // Set playlist image path property
        connect(playlistButton, &QPushButton::clicked, this, &Premium::showPlaylist); // Connect signal
        vLayout->addWidget(playlistButton);

        // Add the frame layout to the main layout
        mainLayout->addWidget(frame);
    }

    // Set the content widget as the scroll area's widget
    ui->friend_playlist_scrollbar->setWidget(contentWidget);
}

void Premium::publicPlaylist() {
    QWidget *contentWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(contentWidget);
    layout->setAlignment(Qt::AlignLeft); // Align content to the left

    QSqlQuery query(db);
    query.prepare("SELECT [name], address_of_picture FROM Play_list WHERE ispublic = 1");

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve public playlists: " + query.lastError().text());
        return;
    }

    while (query.next()) {
        QString playlistName = query.value(0).toString();
        QString picturePath = query.value(1).toString();
        QString imagePath = (picturePath.isEmpty() || !QFile::exists(picturePath)) ? ":/new/prefix1/spotify logo.png" : picturePath;

        QVBoxLayout *vLayout = new QVBoxLayout();

        QFrame *frame = new QFrame(contentWidget);
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(2);
        frame->setFixedSize(150, 180); // Set fixed size for the frame
        frame->setStyleSheet("border: 2px solid green;"); // Set green border color

        QLabel *label = new QLabel(frame);
        label->setPixmap(QPixmap(imagePath).scaled(100, 100, Qt::KeepAspectRatio));
        vLayout->addWidget(label);

        QPushButton *playlistButton = new QPushButton(playlistName, frame);
        playlistButton->setProperty("name", playlistName);
        playlistButton->setProperty("pic_path", imagePath);
        connect(playlistButton, &QPushButton::clicked, this, &Premium::showPlaylist);
        vLayout->addWidget(playlistButton);

        frame->setLayout(vLayout);
        layout->addWidget(frame);
    }

    ui->publicPlaylist_scrollbar->setWidget(contentWidget);
}

void Premium::fill_my_belongings()
{
    fillScrollArea(ui->my_songs_scrollBar, "Song");
    fillScrollArea(ui->my_albums_scrollBar, "Album");
    fillScrollArea(ui->my_concerts_scrollBar, "Concert");
}

void Premium::fillScrollArea(QScrollArea* scrollArea, const QString& type)
{
    // Create a horizontal layout for the scroll area
    QHBoxLayout* scrollLayout = new QHBoxLayout();

    // Example data for demonstration purposes
    // Replace this with your actual data source
    QStringList itemNames;
    if (type == "Song") {
        itemNames << "Song 1" << "Song 2" << "Song 3";
    } else if (type == "Album") {
        itemNames << "Album 1" << "Album 2" << "Album 3";
    } else if (type == "Concert") {
        itemNames << "Concert 1" << "Concert 2" << "Concert 3";
    }

    for (const QString& itemName : itemNames) {
        // Create a vertical layout for each item
        QVBoxLayout* itemLayout = new QVBoxLayout();

        // Create a label for the image
        QLabel* imageLabel = new QLabel();
        QPixmap pixmap(":/new/prefix1/spotify logo.png"); // Use the provided image path
        imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imageLabel->setAlignment(Qt::AlignCenter);

        // Create buttons for the name and delete action
        QPushButton* nameButton = new QPushButton(itemName);
        QPushButton* deleteButton = new QPushButton("Delete");

        // Set styles for buttons
        QString buttonStyle = "font: 12pt 'Segoe UI Historic';"
                              "background-color: rgb(46, 189, 89);"
                              "border-radius: 10px;"
                              "color: rgb(255, 255, 255);";
        nameButton->setStyleSheet(buttonStyle);
        deleteButton->setStyleSheet(buttonStyle);

        // Add widgets to the item layout
        itemLayout->addWidget(imageLabel);
        itemLayout->addWidget(nameButton);
        itemLayout->addWidget(deleteButton);

        // Add the item layout to the scroll layout
        QWidget* itemWidget = new QWidget();
        itemWidget->setLayout(itemLayout);
        scrollLayout->addWidget(itemWidget);

        // Connect the delete button to the appropriate slot
        connect(deleteButton, &QPushButton::clicked, [this, type, itemName]() {
            onDeleteButtonClicked(type, itemName);
        });

        // Connect the name button to the appropriate slot (if needed)
        connect(nameButton, &QPushButton::clicked, [this, type, itemName]() {
            onNameButtonClicked(type, itemName);
        });
    }

    // Set the layout to the scroll area
    QWidget* scrollAreaWidget = new QWidget();
    scrollAreaWidget->setLayout(scrollLayout);
    scrollArea->setWidget(scrollAreaWidget);
}

void Premium::onDeleteButtonClicked(const QString& type, const QString& itemName)
{
    // Handle the deletion of the item (e.g., remove from data source and UI)
    qDebug() << "Delete" << type << ":" << itemName;
}

void Premium::onNameButtonClicked(const QString& type, const QString& itemName)
{
    // Handle the action for the name button (e.g., open details or play the song/album/concert)
    qDebug() << "Clicked on" << type << ":" << itemName;
}

void Premium::fill_friends() {
    // Clear existing content
    qDeleteAll(ui->friends_scrollArea->widget()->children());
    int userid=ID;
    // Prepare and execute the SQL query
    QSqlQuery query;
    query.prepare("EXEC GetFriendsNames @user_id = :user_id");
    query.bindValue(":user_id", userid);  // Assuming currentUserID is defined somewhere

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    // Create a new QWidget and layout for displaying friends
    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);

    // Iterate through the results and populate the layout
    while (query.next()) {
        QString friendName = query.value("friend_name").toString();
        QHBoxLayout *hLayout = new QHBoxLayout();

        QLabel *label = new QLabel(friendName);
                hLayout->addWidget(label);

        QPushButton *chatButton = new QPushButton("Start Chat", contentWidget);
        chatButton->setProperty("FriendName", friendName);  // Setting a property to identify the friend
        connect(chatButton, &QPushButton::clicked, this, &Premium::onStartChatClicked);
        hLayout->addWidget(chatButton);

        layout->addLayout(hLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->friends_scrollArea->setWidget(contentWidget);
}



void Premium::onStartChatClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        QString friendName = button->property("FriendName").toString();
                emit startChat(friendName);
    }
}

void Premium::fill_follow() {
    int user_id = ID; // Replace with your logic to get current user's ID

    // Display followers
    QSqlQuery followersQuery(db);
    followersQuery.prepare("EXEC GetFollowers @user_id = :user_id");
    followersQuery.bindValue(":user_id", user_id);

    if (!followersQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to execute GetFollowers: " + followersQuery.lastError().text());
        return;
    }

    QWidget *contentWidgetFollower = new QWidget(this);
    QVBoxLayout *layoutFollower = new QVBoxLayout(contentWidgetFollower);

    while (followersQuery.next()) {
        int follower_id = followersQuery.value(0).toInt();
        QString follower_username = followersQuery.value(1).toString();

        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *label = new QLabel(follower_username, contentWidgetFollower);
        hLayout->addWidget(label);
        layoutFollower->addLayout(hLayout);
    }

    ui->follower_scrollBar->setWidget(contentWidgetFollower);

    // Display following
    QSqlQuery followingQuery(db);
    followingQuery.prepare("EXEC GetFollowing @user_id = :user_id"); // Corrected binding here
    followingQuery.bindValue(":user_id", user_id);

    if (!followingQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to execute GetFollowing: " + followingQuery.lastError().text());
        return;
    }

    QWidget *contentWidgetFollowing = new QWidget(this);
    QVBoxLayout *layoutFollowing = new QVBoxLayout(contentWidgetFollowing);

    while (followingQuery.next()) {
        int following_id = followingQuery.value(0).toInt();
        QString following_username = followingQuery.value(1).toString();

        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *label = new QLabel(following_username, contentWidgetFollowing);
        hLayout->addWidget(label);
        layoutFollowing->addLayout(hLayout);
    }

    ui->followin_scrollBar->setWidget(contentWidgetFollowing);
}

void Premium::fill_concerts()
{
    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(contentWidget);

    // Example concerts
    QStringList concertNames = {"Concert 1", "Concert 2", "Concert 3", "Concert 4", "Concert 5", "Concert 6", "Concert 7", "Concert 8", "Concert 9", "Concert 10"};
    QString imagePath = ":/new/prefix1/spotify logo.png";

    for (int i = 0; i < concertNames.size(); i += 4)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();

        for (int j = 0; j < 4 && i + j < concertNames.size(); ++j)
        {
            addConcertItem(hLayout, concertNames[i + j], imagePath);
        }

        mainLayout->addLayout(hLayout);
    }

    ui->concerts_scrollBar->setWidget(contentWidget);
}

void Premium::addConcertItem(QHBoxLayout *layout, const QString &concertName, const QString &imagePath)
{
    QWidget *concertWidget = new QWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout(concertWidget);

    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap(imagePath);
    imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
    vLayout->addWidget(imageLabel);

    QPushButton *concertButton = new QPushButton(concertName, this);
    concertButton->setProperty("name", concertName);
    connect(concertButton, &QPushButton::clicked, this, &Premium::toggleTicketOptions);
    vLayout->addWidget(concertButton);

    QWidget *ticketWidget = new QWidget(this);
    QVBoxLayout *ticketLayout = new QVBoxLayout(ticketWidget);
    ticketWidget->setObjectName("ticketWidget");
    ticketWidget->setVisible(false);

    QStringList ticketOptions = {"VIP - $200", "Standard - $100", "Economy - $50"};
    for (const QString &ticketOption : ticketOptions)
    {
        QPushButton *ticketButton = new QPushButton(ticketOption, this);
        ticketButton->setProperty("price", ticketOption.split('-').last().trimmed().mid(1).toDouble());
        ticketButton->setProperty("concert", concertName);
        connect(ticketButton, &QPushButton::clicked, this, &Premium::buyTicket);
        ticketLayout->addWidget(ticketButton);
    }

    vLayout->addWidget(ticketWidget);
    layout->addWidget(concertWidget);
}

void Premium::toggleTicketOptions()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;

    QWidget *concertWidget = qobject_cast<QWidget*>(button->parentWidget());
    if (!concertWidget)
        return;

    QWidget *ticketWidget = concertWidget->findChild<QWidget*>("ticketWidget");
    if (!ticketWidget)
        return;

    bool isVisible = ticketWidget->isVisible();
    ticketWidget->setVisible(!isVisible);
}

void Premium::buyTicket()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;

    double ticketPrice = button->property("price").toDouble();
    QString concertName = button->property("concert").toString();
    double userBalance = getUserBalance();

    if (userBalance >= ticketPrice)
    {
        // Proceed with ticket purchase
        QMessageBox::information(this, "Purchase Successful", QString("You have successfully purchased a ticket for %1!").arg(concertName));
    }
    else
    {
        // Show error message
        QMessageBox::critical(this, "Insufficient Funds", "You do not have enough money to buy this ticket.");
    }
}

double Premium::getUserBalance()
{
    // Example function to return user balance, replace with actual logic
    return 150.0; // User has $150
}

void Premium::fill_wallet()
{
    // Example tickets
    QList<QPair<QString, double>> validTickets = {
        {"Concert 1", 100.0},
        {"Concert 3", 50.0},
        {"Concert 5", 150.0}
    };

    QList<QPair<QString, double>> expiredTickets = {
        {"Concert 2", 100.0},
        {"Concert 4", 50.0}
    };

    double totalBalance = calculateTotalBalance(validTickets);
    updateBalanceLabel(totalBalance);
    populateTickets(validTickets, ui->valid_tickets_scrollArea, true); // horizontal layout
    populateTickets(expiredTickets, ui->expired_tickets_scrollArea, true); // horizontal layout
}

double Premium::calculateTotalBalance(const QList<QPair<QString, double>>& validTickets)
{
    double balance = 0.0;
    for (const auto& ticket : validTickets)
    {
        balance += ticket.second;
    }
    return balance;
}

void Premium::updateBalanceLabel(double balance)
{
    ui->balance->setText(QString("Balance: $%1").arg(balance));
}

void Premium::populateTickets(const QList<QPair<QString, double>>& tickets, QScrollArea* scrollArea, bool horizontal)
{
    QWidget *contentWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(contentWidget);

    for (const auto& ticket : tickets)
    {
        QString concertName = ticket.first;
        double ticketPrice = ticket.second;

        QLabel *ticketLabel = new QLabel(QString("%1 - $%2").arg(concertName).arg(ticketPrice), this);
        layout->addWidget(ticketLabel);
    }

    contentWidget->setLayout(layout);
    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true);
}

void Premium::fillFriendshipRequests() {
    // Clear existing content
    qDeleteAll(ui->friendship_requests->widget()->children());

    // Prepare and execute the SQL query
    QSqlQuery query;
    QString queryString = "EXEC GetFriendSRequest @target_user_id = :user_id";
    query.prepare(queryString);
    query.bindValue(":user_id", ID);  // Assuming currentUserID is defined somewhere

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    // Create a new QWidget and layout for displaying friend requests
    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);

    // Iterate through the results and populate the layout
    while (query.next()) {
        QHBoxLayout *hLayout = new QHBoxLayout();

        QString friendName = query.value("username").toString();

        QLabel *label = new QLabel(friendName, contentWidget);
        hLayout->addWidget(label);

        QPushButton *acceptButton = new QPushButton("Accept", contentWidget);
        connect(acceptButton, &QPushButton::clicked, this, [=]() {
            acceptFriendshipRequest(friendName);  // Call slot function to accept the request
        });
        hLayout->addWidget(acceptButton);

        QPushButton *declineButton = new QPushButton("Decline", contentWidget);
        connect(declineButton, &QPushButton::clicked, this, [=]() {
            declineFriendshipRequest(friendName);  // Call slot function to decline the request
        });
        hLayout->addWidget(declineButton);

        layout->addLayout(hLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->friendship_requests->setWidget(contentWidget);
}

void Premium::fillAllUsers() {
    // Replace this with your logic to get the current user's ID
    int currentUserId = ID;

    // Create a content widget and a vertical layout for it
    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);

    // Create a query object
    QSqlQuery query(db);

    // Prepare the query to select all usernames and their corresponding user IDs
    if (!query.exec("SELECT user_id, username FROM Users")) {
        QMessageBox::critical(this, "Error", "Failed to retrieve users: " + query.lastError().text());
        return;
    }

    // Iterate over the results
    while (query.next()) {
        int userId = query.value(0).toInt();
        QString userName = query.value(1).toString();

        // Skip the current user's information
        if (userId == currentUserId) {
            continue;
        }

        // Create a horizontal layout for each row
        QHBoxLayout *rowLayout = new QHBoxLayout();

        // Label to display user name
        QLabel *nameLabel = new QLabel(userName, this);
        rowLayout->addWidget(nameLabel);

        // Button to send friendship request
        QPushButton *sendRequestButton = new QPushButton("Send Request", this);
        // Connect sendRequestButton clicked signal to slot
        connect(sendRequestButton, &QPushButton::clicked, this, [=]() {
            sendFriendshipRequest(userName);
        });
        rowLayout->addWidget(sendRequestButton);

        // Button to follow the user
        QPushButton *followButton = new QPushButton("Follow", this);
        // Connect followButton clicked signal to slot
        connect(followButton, &QPushButton::clicked, this, [=]() {
            followUser(userId, userName);
        });
        rowLayout->addWidget(followButton);

        // Add row layout to main vertical layout
        layout->addLayout(rowLayout);
    }

    // Set the content widget for the scroll area
    ui->allUsers_scrollBar->setWidget(contentWidget);
}
//---------------------------------------------------------------
void Premium::sendFriendshipRequest(const QString &userName) {
    // Database connection and query execution
    QSqlQuery query;
    query.prepare("EXEC SendFriendRequest1 @user_id1 = :user_id1, @friend_username = :friend_username");
    query.bindValue(":user_id1", ID);  // Assuming currentUserID is defined elsewhere
    query.bindValue(":friend_username", userName);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to send friendship request: " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Friendship Request", "Friendship request sent to " + userName);
    fillFriendshipRequests();
}
//------------------------------------------------------
void Premium::followUser(int userId, const QString &userName) {
    // Your logic to follow the user
    int currentUserId = ID; // Replace this with your logic to get the current user's ID

    QSqlQuery query(db);
    query.prepare("EXEC AddFollower @UserId1 = :userId1, @UserId2 = :userId2");
    query.bindValue(":userId1", currentUserId);
    query.bindValue(":userId2", userId);

    if (!query.exec()) {
        QMessageBox::information(this, "Error", "You are already following "+ userName);
        return;
    }

    QMessageBox::information(this, "Follow User", "You are now following " + userName);
    fill_follow();
}

void Premium::acceptFriendshipRequest(const QString &userName)
{
    int currentUserId = ID;

           // Retrieve the user ID of the requester using their username
           QSqlQuery query;
           query.prepare("EXEC AcceptFriendRequests @target_user_id = :target_user_id, @requester_username = :requester_username");
           query.bindValue(":target_user_id", currentUserId);
           query.bindValue(":requester_username", userName);

           if (!query.exec()) {
               qDebug() << "Error accepting friend request:" << query.lastError().text();
               return;
           }

           QMessageBox::information(this, "Friend Request Accepted",
                                       QString("Friend request from %1 accepted successfully.").arg(userName));
           fill_friends();

           // Optionally, update the UI or perform other actions after accepting the request
           // Example: Refresh the list of friendship requests
           fillFriendshipRequests();

}

void Premium::declineFriendshipRequest(const QString &userName)
{
    QSqlQuery query;
    query.prepare("EXEC DeclineFriendRequest @current_user_id = :user_id, @requester_username = :friend_username");
    query.bindValue(":user_id", ID);
    query.bindValue(":friend_username", userName);


    if (!query.exec()) {

        QMessageBox::critical(this, "Error", "Failed to decline friendship request: " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Friendship Request", "Friend request from " + userName + " declined successfully.");

    fillFriendshipRequests();
}


void Premium::on_UploadPhoto_clicked()
{
    // Example: Ask user to choose a file
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Choose Image"), "", tr("Images (*.png *.jpg *.jpeg)"));

    if (imagePath.isEmpty()) {
        // User canceled the selection
        return;
    }

    // Load the selected image
    QPixmap image(imagePath);

    // Display the image on QLabel named Song_photo
    ui->Song_photo->setPixmap(image.scaled(ui->Song_photo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Store imagePath in a member variable to use it later
    m_imagePath = imagePath;
}

void Premium::on_submit_song_clicked()
{
    if (m_imagePath.isEmpty()) {
        // No image selected, handle the case as needed
        qDebug() << "Error: No image selected";
        return;
    }

    // Load the selected image again (in case it's not already loaded)
    QPixmap image(m_imagePath);

    // Example: Save the image to project directory
    QString projectPath = QCoreApplication::applicationDirPath(); // Get current application directory
    QString newFilePath = QDir::cleanPath(projectPath + "/" + QFileInfo(m_imagePath).fileName());

    if (image.save(newFilePath)) {
        // Image saved successfully
        qDebug() << "Image saved to project directory:" << newFilePath;
    } else {
        // Failed to save image
        qDebug() << "Error: Failed to save image to project directory";
        return; // Optionally handle the error and return
    }

    // Further processing after saving the image, such as submitting the song
    // Example: SubmitSongFunction();

    // Clear the stored imagePath after processing
    m_imagePath.clear();

    // Optionally clear the Song_photo label after submission
    ui->Song_photo->clear();
}

void Premium::on_OK_clicked()
{
    // Clear previous dynamically added widgets
    clearScrollArea();

    // Get the number of songs from num_songs line edit
    int numSongs = ui->num_songs->text().toInt();
    if (numSongs <= 0) {
        qDebug() << "Invalid number of songs";
        return;
    }

    songCount = numSongs;

    // Create a layout to hold the dynamically added widgets
    QVBoxLayout *scrollLayout = new QVBoxLayout();

    QString lineEditStyle = "border-radius: 15px;"
                            "background-color: rgb(255, 255, 255);"
                            "padding: 10px;"
                            "font: 700 12pt 'UD Digi Kyokasho NP-B';";

    QString labelStyle = "color: rgb(255, 255, 255);"
                         "font: 700 12pt 'UD Digi Kyokasho NP-B';";

    for (int i = 0; i < songCount; ++i) {
        QGroupBox *songGroup = new QGroupBox(tr("Song %1").arg(i + 1), this);
        QFormLayout *formLayout = new QFormLayout();

        // Create line edits for each song's properties
        QLineEdit *titleEdit = new QLineEdit();
        QLineEdit *albumEdit = new QLineEdit();
        QLineEdit *genreEdit = new QLineEdit();
        QLineEdit *releaseDateEdit = new QLineEdit();
        QLineEdit *ageCategoryEdit = new QLineEdit();
        QLineEdit *countryEdit = new QLineEdit();

        // Set the stylesheet for line edits
        titleEdit->setStyleSheet(lineEditStyle);
        albumEdit->setStyleSheet(lineEditStyle);
        genreEdit->setStyleSheet(lineEditStyle);
        releaseDateEdit->setStyleSheet(lineEditStyle);
        ageCategoryEdit->setStyleSheet(lineEditStyle);
        countryEdit->setStyleSheet(lineEditStyle);

        // Create custom labels with the specified stylesheet
        QLabel *titleLabel = new QLabel(tr("Title"));
        QLabel *albumLabel = new QLabel(tr("Album"));
        QLabel *genreLabel = new QLabel(tr("Genre"));
        QLabel *releaseDateLabel = new QLabel(tr("Release Date"));
        QLabel *ageCategoryLabel = new QLabel(tr("Age Category"));
        QLabel *countryLabel = new QLabel(tr("Country"));

        // Set the stylesheet for labels
        titleLabel->setStyleSheet(labelStyle);
        albumLabel->setStyleSheet(labelStyle);
        genreLabel->setStyleSheet(labelStyle);
        releaseDateLabel->setStyleSheet(labelStyle);
        ageCategoryLabel->setStyleSheet(labelStyle);
        countryLabel->setStyleSheet(labelStyle);

        // Add line edits and labels to the form layout
        formLayout->addRow(titleLabel, titleEdit);
        formLayout->addRow(albumLabel, albumEdit);
        formLayout->addRow(genreLabel, genreEdit);
        formLayout->addRow(releaseDateLabel, releaseDateEdit);
        formLayout->addRow(ageCategoryLabel, ageCategoryEdit);
        formLayout->addRow(countryLabel, countryEdit);

        // Add the form layout to the group box
        songGroup->setLayout(formLayout);

        // Add the group box to the scroll layout
        scrollLayout->addWidget(songGroup);

        // Store pointers to the line edits for later use
        titleEdits.append(titleEdit);
        albumEdits.append(albumEdit);
        genreEdits.append(genreEdit);
        releaseDateEdits.append(releaseDateEdit);
        ageCategoryEdits.append(ageCategoryEdit);
        countryEdits.append(countryEdit);
    }

    // Create and add the submit button to the layout
    submitSongsButton = new QPushButton(tr("Submit All Songs"));
    QString buttonStyle = "font: 12pt 'Segoe UI Historic';"
                          "background-color: rgb(46, 189, 89);"
                          "border-radius: 30px;"
                          "color: rgb(255, 255, 255);";
    submitSongsButton->setStyleSheet(buttonStyle);
    scrollLayout->addWidget(submitSongsButton);

    // Connect the submit button to the appropriate slot
    connect(submitSongsButton, &QPushButton::clicked, this, &Premium::on_SubmitSongs_clicked);

    // Set the layout to the scroll area
    QWidget *scrollAreaWidget = new QWidget();
    scrollAreaWidget->setLayout(scrollLayout);
    ui->song_scroll_area->setWidget(scrollAreaWidget);
}

void Premium::clearScrollArea()
{
    // Remove all dynamically created widgets from the scroll area
    QWidget *scrollAreaWidget = ui->song_scroll_area->widget();
    if (scrollAreaWidget) {
        delete scrollAreaWidget;
    }

    // Clear the stored pointers to the line edits
    titleEdits.clear();
    albumEdits.clear();
    genreEdits.clear();
    releaseDateEdits.clear();
    ageCategoryEdits.clear();
    countryEdits.clear();
}

void Premium::clearScrollArea(QScrollArea *scrollArea) {
    // Retrieve the widget from the scroll area
    QWidget *contentWidget = scrollArea->widget();
    if (!contentWidget) {
        return;
    }

    // Clear layout and widgets
    QLayout *layout = contentWidget->layout();
    if (!layout) {
        return;
    }

    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        if (QWidget *widget = child->widget()) {
            delete widget; // Delete widget
        }
        delete child; // Delete layout item
    }

    delete layout; // Delete layout itself
    scrollArea->setWidget(nullptr); // Set scroll area's widget to null
}

void Premium::on_SubmitSongs_clicked()
{
    // Collect data from all dynamically created line edits
    for (int i = 0; i < songCount; ++i) {
        QString title = titleEdits[i]->text();
        QString album = albumEdits[i]->text();
        QString genre = genreEdits[i]->text();
        QString releaseDate = releaseDateEdits[i]->text();
        QString ageCategory = ageCategoryEdits[i]->text();
        QString country = countryEdits[i]->text();

        // Process the collected data (e.g., save to file, database, etc.)
        qDebug() << "Song " << i + 1 << ": "
                 << title << ", "
                 << album << ", "
                 << genre << ", "
                 << releaseDate << ", "
                 << ageCategory << ", "
                 << country;
    }

    // Optionally clear the dynamically created widgets after submission
    clearScrollArea();
}

void Premium::displaySearchResults(const QList<QVariantMap> &results) {
    // Create a new content widget for the scroll area
    QWidget *contentWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(contentWidget);
    layout->setAlignment(Qt::AlignLeft); // Align content to the left

    int songCount = 0;
    for (const QVariantMap &result : results) {
        QString type = result["Type"].toString();
        QString title = result["Title"].toString();
        QString address_of_picture = result["address_of_picture"].toString();

        // Create a vertical layout to hold image and title/button
        QVBoxLayout *vLayout = new QVBoxLayout();

        // Create a frame with a green border
        QFrame *frame = new QFrame(contentWidget);
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(2);
        frame->setFixedSize(150, 200); // Set fixed size for the frame
        frame->setStyleSheet("border: 2px solid green;");

        // Create label for song/album image
        QLabel *imageLabel = new QLabel(frame);
        QPixmap pixmap;
        if (!address_of_picture.isEmpty() && pixmap.load(address_of_picture)) {
            imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
        } else {
            imageLabel->setPixmap(QPixmap(":/new/prefix1/spotify logo.png").scaled(100, 100, Qt::KeepAspectRatio));
        }
        vLayout->addWidget(imageLabel);

        // Create button for song/album name
        QString labelText = QString("%1: %2").arg(type == "Song" ? "Song" : "Album").arg(title);
        QPushButton *button = new QPushButton(labelText, frame);
        button->setProperty("ID", result["ID"]);
        button->setProperty("Type", type);
        connect(button, &QPushButton::clicked, this, &Premium::addComment_like);
        vLayout->addWidget(button);

        // Add vertical layout to frame and frame to the horizontal layout
        frame->setLayout(vLayout);
        layout->addWidget(frame);

        songCount++;
    }

    // Set the content widget as the scroll area's widget
    ui->scrollArea->setWidget(contentWidget);
}

QList<QVariantMap> Premium::searchMusicAndAlbum(const QString &name, const QString &artistName, const QString &genre, const QString &country, const QString &ageCategory) {
    QSqlQuery query;
    query.prepare("EXEC SearchMusicAndAlbum :name, :artist_name, :genre, :country, :age_category");
    query.bindValue(":name", name);
    query.bindValue(":artist_name", artistName);
    query.bindValue(":genre", genre);
    query.bindValue(":country", country);
    query.bindValue(":age_category", ageCategory);
    query.exec();

    QList<QVariantMap> results;
    while (query.next()) {
        QVariantMap result;
        result["Type"] = query.value("Type");
        result["ID"] = query.value("ID");
        result["Title"] = query.value("Title");
        result["address_of_picture"] = query.value("address_of_picture");
        results.append(result);
    }

    if (query.lastError().isValid()) {
        qDebug() << "SQL Error: " << query.lastError().text();
    }

    return results;
}

void Premium::on_Search_pushButton_clicked() {
    QString name, artistName, genre, country, ageCategory;

    // Check which radio button is selected
    if (ui->SearchNameMusic->isChecked()) {
        name = ui->SearchLineEdit->text();
    } else if (ui->SearchNameArtist->isChecked()) {
        artistName = ui->SearchLineEdit->text();
    } else if (ui->SearchGenre->isChecked()) {
        genre = ui->SearchLineEdit->text();
    } else if (ui->SearchCountry->isChecked()) {
        country = ui->SearchLineEdit->text();
    } else if (ui->SearchAgeCategory->isChecked()) {
        ageCategory = ui->SearchLineEdit->text();
    }

    QList<QVariantMap> results = searchMusicAndAlbum(name, artistName, genre, country, ageCategory);

    clearScrollAreaSearch();
    displaySearchResults(results);
}

void Premium::clearScrollAreaSearch() {
    // Get the content widget of the scroll area
    QWidget *contentWidget = ui->scrollArea->widget();

    if (contentWidget) {
        // Get the layout of the content widget
        QLayout *layout = contentWidget->layout();

        if (layout) {
            // Remove all widgets from the layout
            QLayoutItem *item;
            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
        }
    }
}

