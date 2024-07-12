#include "chatbox.h"
#include "qdatetime.h"

#include "ui_chatbox.h"

#include "mainwindow.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "qurlquery.h"

QString friendN;
ChatBox::ChatBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatBox)
{
    ui->setupUi(this);
    setstyle();

}

ChatBox::~ChatBox()
{
    delete ui;
}

void ChatBox::fillChat(const QString &friendName){

    qDebug() << "Filling chat with" << friendName;
       friendN=friendName;
        // Replace the loop with SQL query execution
        QSqlQuery query;

        query.prepare("EXEC GetChatsBetweenUser @sender_id = :sender_id, @receiver_username = :receiver_username");
        query.bindValue(":sender_id", ID);  // Assuming you have currentUserID defined somewhere
        query.bindValue(":receiver_username", friendName);


        if (!query.exec()) {
            QMessageBox::critical(this, "Error", "Failed to retrieve chats: " + query.lastError().text());
            return;
        }
        QWidget *contentWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(contentWidget);
        // Iterate through the results and populate the layout
        while (query.next()) {
            QString messageContent = query.value("message_content").toString();
            QDateTime sentAt = query.value("sent_at").toDateTime();
            QHBoxLayout *hLayout = new QHBoxLayout();
            QLabel *messageLabel = new QLabel(messageContent + " (" + sentAt.toString() + ")", this);
            hLayout->addWidget(messageLabel);
            layout ->addLayout(hLayout);
        }

        // Set the content widget as the scroll area's widget
        //this->setLayout(layout);





    // Set the content widget as the scroll area's widget

    ui->scrollAreachat->setWidget(contentWidget);
}

void ChatBox::on_Back_clicked()
{
    emit goBack();
}

void ChatBox::setstyle(){
    QString styleSheet = R"(
        /* Global font style */
        * {
            font: 700 12pt "UD Digi Kyokasho NK-B";
        }

    )";

    // Apply the stylesheet to all child widgets of this widget
    this->setStyleSheet(styleSheet);
}

void ChatBox::on_send_button_clicked()
{
        QString friendName = friendN;
        QString chatContent = ui->message->toPlainText();


        if (!chatContent.isEmpty() && !friendName.isEmpty()) {
            QSqlQuery query;

            query.prepare("EXEC SendMessageS @SenderID=:SenderID, @ReceiverUsername=:ReceiverUsername, @MessageContent=:MessageContent");
            query.bindValue(":SenderID", ID);
            query.bindValue(":ReceiverUsername", friendName);
            query.bindValue(":MessageContent", chatContent);


            if (query.exec()) {
                QMessageBox::information(this, "Message Sent", "Your message has been sent successfully.");
                ui->message->clear();
            } else {
                QMessageBox::critical(this, "Error", "Failed to send message: " + query.lastError().text());
            }
        } else {
            QMessageBox::warning(this, "Input Error", "Please enter a message and select a friend.");
        }


    fillChat(friendN);
}

