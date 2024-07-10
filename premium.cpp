#include "premium.h"
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


    // Example songs
    for (int i = 0; i < 100; ++i) {
        addSongItem("1", "Song 1", ":/new/prefix1/spotify logo.png");
        addSongItem("2", "Song 2", ":/new/prefix1/spotify logo.png");
        addSongItem("3", "Song 3", ":/new/prefix1/spotify logo.png");
    }

    // Add more songs as needed
    fill_favorites();
    fill_playlists();
    fill_friends();
    fill_follow();
    fill_concerts();
    fill_wallet();
    fillFriendshipRequests();
    fillAllUsers();
    //if is premium
//        ui->tabWidget->removeTab(7);
//         ui->tabWidget->removeTab(7);
    //if is simple user
//    while (ui->tabWidget->count() > 1) {
//        ui->tabWidget->removeTab(1);
//    }
    // Define the stylesheet
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
    QPushButton *songButton = new QPushButton(songName, this);
    songButton->setProperty("ID", songID);
    songButton->setProperty("name", songName);
    songButton->setProperty("pic_path", imagePath);
    connect(songButton, &QPushButton::clicked, this, &::Premium::addComment_like);
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

void Premium::fill_follow(){
    // Example content: add several QLabel with images or text
    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);
    for (int i = 1; i <= 100; ++i)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();

        QLabel *label = new QLabel("Friend " + QString::number(i), contentWidget);
        hLayout->addWidget(label);
        layout->addLayout(hLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->followin_scrollBar->setWidget(contentWidget);
    // Example content: add several QLabel with images or text
    QWidget *contentWidget_2 = new QWidget(this);
    QVBoxLayout *layout_2 = new QVBoxLayout(contentWidget_2);
    for (int i = 1; i <= 100; ++i)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();

        QLabel *label = new QLabel("Friend " + QString::number(i), contentWidget_2);
        hLayout->addWidget(label);
        layout_2->addLayout(hLayout);
    }

    // Set the content widget as the scroll area's widget
    ui->follower_scrollBar->setWidget(contentWidget_2);


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

void Premium::fillAllUsers()
{
    // Assuming you have a list of all users available
    QStringList allUsers;
    for (int i = 1; i <= 100; ++i) {
        allUsers.append("User" + QString::number(i));
    }

    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);

    for (const QString &userName : allUsers) {
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

        // Add row layout to main vertical layout
        layout->addLayout(rowLayout);
    }

    // Set the content widget for the scroll area
    ui->allUsers_scrollBar->setWidget(contentWidget);
}

void Premium::acceptFriendshipRequest(const QString &userName)
{
    // Logic to accept friendship request for userName
}

void Premium::declineFriendshipRequest(const QString &userName)
{
    // Logic to decline friendship request for userName
}

void Premium::sendFriendshipRequest(const QString &userName)
{
    // Logic to send friendship request to userName
}
