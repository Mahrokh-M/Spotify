#include "register.h"
#include "ui_register.h"
#include"signup.h"
#include <QGraphicsDropShadowEffect>
Register::Register(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->sign_button->setStyleSheet(
                "QPushButton {"
                "    font: 15pt 'Segoe UI Historic';"
                "    background-color: rgb(46, 189, 89);"
                "    border-radius: 30px;"
                "    color: rgb(255, 255, 255);"
                "}"
                "QPushButton:hover {"
                "    background-color: rgb(56, 199, 99);"
                "}"
                "QPushButton:pressed {"
                "    background-color: rgb(36, 179, 79);"
                "}"
                );

    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(10);
    effect->setXOffset(2);
    effect->setYOffset(2);
    effect->setColor(QColor(0, 0, 0, 160));
    ui->sign_button->setGraphicsEffect(effect);
    ui->Sign_in->setStyleSheet(
                "QPushButton {"
                "    border-radius: 20px;"
                "    font: 15pt 'Segoe UI Historic';"
                "    color: rgb(255, 255, 255);"  // Default text color
                "    background-color: transparent;"
                "    border: none;"
                "    border-bottom: 2px solid rgb(46, 189, 89);"  // Green underline
                "    cursor: pointer;"  // Pointer cursor
                "}"
                "QPushButton:hover {"
                "    color: rgb(56, 199, 99);"  // Text color on hover
                "    border-bottom: 2px solid rgb(56, 199, 99);"  // Hover effect for underline
                "}"
                "QPushButton:pressed {"
                "    color: rgb(36, 179, 79);"  // Text color on press
                "    border-bottom: 2px solid rgb(36, 179, 79);"  // Pressed effect for underline
                "}"
                );
    ui->Sign_up->setStyleSheet(
                "QPushButton {"
                "    border-radius: 20px;"
                "    font: 15pt 'Segoe UI Historic';"
                "    color: rgb(255, 255, 255);"  // Default text color
                "    background-color: transparent;"
                "    border: none;"

                "    cursor: pointer;"  // Pointer cursor
                "}"
                "QPushButton:hover {"
                "    color: rgb(56, 199, 99);"  // Text color on hover

                "}"
                "QPushButton:pressed {"
                "    color: rgb(36, 179, 79);"  // Text color on press

                "}"
                );
    ui->stackedWidget->setCurrentIndex(0);

}

Register::~Register()
{
    delete ui;
}


void Register::on_Sign_up_clicked()
{
ui->stackedWidget->setCurrentIndex(1);
ui->Sign_up_2->setStyleSheet(
            "QPushButton {"
            "    border-radius: 20px;"
            "    font: 15pt 'Segoe UI Historic';"
            "    color: rgb(255, 255, 255);"  // Default text color
            "    background-color: transparent;"
            "    border: none;"
            "    border-bottom: 2px solid rgb(46, 189, 89);"  // Green underline
            "    cursor: pointer;"  // Pointer cursor
            "}"
            "QPushButton:hover {"
            "    color: rgb(56, 199, 99);"  // Text color on hover
            "    border-bottom: 2px solid rgb(56, 199, 99);"  // Hover effect for underline
            "}"
            "QPushButton:pressed {"
            "    color: rgb(36, 179, 79);"  // Text color on press
            "    border-bottom: 2px solid rgb(36, 179, 79);"  // Pressed effect for underline
            "}"
            );
ui->Sign_in_2->setStyleSheet(
            "QPushButton {"
            "    border-radius: 20px;"
            "    font: 15pt 'Segoe UI Historic';"
            "    color: rgb(255, 255, 255);"  // Default text color
            "    background-color: transparent;"
            "    border: none;"

            "    cursor: pointer;"  // Pointer cursor
            "}"
            "QPushButton:hover {"
            "    color: rgb(56, 199, 99);"  // Text color on hover

            "}"
            "QPushButton:pressed {"
            "    color: rgb(36, 179, 79);"  // Text color on press

            "}"
            );


}

void Register::on_Sign_in_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

