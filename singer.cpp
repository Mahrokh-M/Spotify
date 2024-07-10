#include "singer.h"
#include "ui_singer.h"

Singer::Singer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Singer)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
}

Singer::~Singer()
{
    delete ui;
}
