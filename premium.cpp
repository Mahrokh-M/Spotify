#include "premium.h"
#include "ui_premium.h"

Premium::Premium(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Premium)
{
    ui->setupUi(this);
}

Premium::~Premium()
{
    delete ui;
}
