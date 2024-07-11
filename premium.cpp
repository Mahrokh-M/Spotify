#include "premium.h"
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


    fillSongs();

    // Add more songs as needed
    fill_favorites();
    fill_playlists();
    fill_friends();
    fill_follow();
    fillAllUsers();
    fill_concerts();
    fill_wallet();
    fillFriendshipRequests();
    fill_my_belongings();
    //if is premium
    //        ui->tabWidget->removeTab(7);
    //         ui->tabWidget->removeTab(7);
    //if is simple user
    //    while (ui->tabWidget->count() > 1) {
    //        ui->tabWidget->removeTab(1);
    //    }
    // Define the stylesheet
    setstyle();
    if (!initializeDatabase(db)) {
       QMessageBox::critical(this, "Database Connection Error", "Failed to connect to the database");
    }

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
//**
void Premium::addSongItem(const QString &songID, const QString &songName, const QString &imagePath)
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

void Premium::addComment_like()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        QString songID = button->property("ID").toString();
        emit open_comment(songID); // Emit signal with songID
    }
}
//**
void Premium::fillSongs()
{
    QSqlQuery query("SELECT song_id, address_of_picture, title FROM Songs");
    while (query.next()) {
        QString songID = query.value(0).toString();
        QString picturePath = query.value(1).toString();
        QString songName = query.value(2).toString();
        QString imagePath = picturePath.isEmpty() ? ":/new/prefix1/spotify logo.png" : picturePath;
        addSongItem(songID, songName, imagePath);  // Pass songID, songName, and imagePath
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

void Premium::myPlaylist(){
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
        connect(songButton, &QPushButton::clicked, this, &Premium::showPlaylist);
        vLayout->addWidget(songButton);

        // Add the vertical layout to the horizontal layout
        layout->addLayout(vLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->your_playlist_scrollbar->setWidget(contentWidget);
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
    QWidget *contentWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(contentWidget);
    for (int i = 1; i <= 100; ++i)
    {
        QVBoxLayout *vLayout = new QVBoxLayout();

        QLabel *label = new QLabel(contentWidget);
        label->setPixmap(QPixmap(":/new/prefix1/spotify logo.png").scaled(100, 100, Qt::KeepAspectRatio));
        vLayout->addWidget(label);

        QPushButton *songButton = new QPushButton("Song " + QString::number(i), contentWidget);
        songButton->setProperty("ID", QString::number(i));
        songButton->setProperty("name", "Song " + QString::number(i));
        songButton->setProperty("pic_path", ":/new/prefix1/spotify logo.png");
        connect(songButton, &QPushButton::clicked, this, &Premium::showPlaylist);
        vLayout->addWidget(songButton);

        layout->addLayout(vLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->friend_playlist_scrollbar->setWidget(contentWidget);
}

void Premium::publicPlaylist(){
    // Example content: add several QLabel with images or text
    QWidget *contentWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(contentWidget);
    for (int i = 1; i <= 100; ++i)
    {
        QVBoxLayout *vLayout = new QVBoxLayout();

        QLabel *label = new QLabel(contentWidget);
        label->setPixmap(QPixmap(":/new/prefix1/spotify logo.png").scaled(100, 100, Qt::KeepAspectRatio));
        vLayout->addWidget(label);

        QPushButton *songButton = new QPushButton("Song " + QString::number(i), contentWidget);
        songButton->setProperty("ID", QString::number(i));
        songButton->setProperty("name", "Song " + QString::number(i));
        songButton->setProperty("pic_path", ":/new/prefix1/spotify logo.png");
        connect(songButton, &QPushButton::clicked, this, &Premium::showPlaylist);
        vLayout->addWidget(songButton);

        layout->addLayout(vLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->publicPlaylist_scrollbar->setWidget(contentWidget);
}

void Premium::fill_friends(){

    // Example content: add several QLabel with images or text
    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);
    for (int i = 1; i <= 100; ++i)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();

        QLabel *label = new QLabel("Friend " + QString::number(i), contentWidget);
        hLayout->addWidget(label);

        QPushButton *chatButton = new QPushButton("Start Chat", contentWidget);
        chatButton->setProperty("ID", QString::number(i));
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
        QString friendID = button->property("ID").toString();
        emit startChat(friendID); // Emit signal with friendID
    }
}

void Premium::fill_follow() {
    int user_id = getCurrentUserId(); // Replace with your logic to get current user's ID

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

void Premium::fillFriendshipRequests()
{
    // Assuming you have a list of users who sent friendship requests
    QStringList requests = {"User1", "User2", "User3"};

    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);

    for (const QString &userName : requests) {
        // Create a horizontal layout for each row
        QHBoxLayout *rowLayout = new QHBoxLayout();

        // Label to display user name
        QLabel *nameLabel = new QLabel(userName, this);
        rowLayout->addWidget(nameLabel);

        // Button to accept friendship request
        QPushButton *acceptButton = new QPushButton("Accept", this);
        // Connect acceptButton clicked signal to slot
        connect(acceptButton, &QPushButton::clicked, this, [=]() {
            acceptFriendshipRequest(userName);
        });
        rowLayout->addWidget(acceptButton);

        // Button to decline friendship request
        QPushButton *declineButton = new QPushButton("Decline", this);
        // Connect declineButton clicked signal to slot
        connect(declineButton, &QPushButton::clicked, this, [=]() {
            declineFriendshipRequest(userName);
        });
        rowLayout->addWidget(declineButton);

        // Add row layout to main vertical layout
        layout->addLayout(rowLayout);
    }

    // Set the content widget for the scroll area
    ui->friendship_requests->setWidget(contentWidget);
}

void Premium::fillAllUsers() {
    // Replace this with your logic to get the current user's ID
    int currentUserId = getCurrentUserId();

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

void Premium::sendFriendshipRequest(const QString &userName) {
    // Your logic to send a friendship request to the user
    QMessageBox::information(this, "Friendship Request", "Friendship request sent to " + userName);
}

void Premium::followUser(int userId, const QString &userName) {
    // Your logic to follow the user
    int currentUserId = getCurrentUserId(); // Replace this with your logic to get the current user's ID

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
    // Logic to accept friendship request for userName
}

void Premium::declineFriendshipRequest(const QString &userName)
{
    // Logic to decline friendship request for userName
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
    int songCount = 0;
    for (const QVariantMap &result : results) {
        QString type = result["Type"].toString();
        QString title = result["Title"].toString();
        QString address_of_picture = result["address_of_picture"].toString();
        QString labelText = QString("%1: %2").arg(type == "Song" ? "Song" : "Album").arg(title);

        int row = songCount / 8;
        int col = songCount % 8;

        // Create label for song/album image
        QLabel *imageLabel = new QLabel(this);
        QPixmap pixmap;
        if (!address_of_picture.isEmpty() && pixmap.load(address_of_picture)) {
            imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
        } else {
            imageLabel->setPixmap(QPixmap(":/new/prefix1/spotify logo.png").scaled(100, 100, Qt::KeepAspectRatio));
        }
        gridLayout->addWidget(imageLabel, row * 2, col);

        // Create button for song/album name
        QPushButton *button = new QPushButton(labelText, this);
        button->setProperty("ID", result["ID"]);
        button->setProperty("Type", type);
        connect(button, &QPushButton::clicked, this, &Premium::addComment_like);
        gridLayout->addWidget(button, row * 2 + 1, col);

        songCount++;
    }
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

void Premium::on_Search_pushButton_clicked()
{
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
    QLayoutItem *item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}
