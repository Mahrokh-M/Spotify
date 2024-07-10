#include "chatbox.h"
#include "ui_chatbox.h"

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

void ChatBox::fillChat(const QString &){

    //some logic to fill the chatbox
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
