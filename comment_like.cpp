#include "comment_like.h"
#include "ui_comment_like.h"

Comment_Like::Comment_Like(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Comment_Like)
{
    ui->setupUi(this);
}

Comment_Like::~Comment_Like()
{
    delete ui;
}

void Comment_Like::setCommentDetails(const QString &songID)
{
    // Fetch and set the song details based on the songID
    // For example:
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
        QLabel *commentLabel = new QLabel("This is comment number ................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................" + QString::number(i), contentWidget);
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
