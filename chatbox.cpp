#include "chatbox.h"
#include "ui_chatbox.h"

ChatBox::ChatBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatBox)
{
    ui->setupUi(this);

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
