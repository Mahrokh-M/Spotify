#include "register.h"
#include "ui_register.h"
#include <QPropertyAnimation>
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
    ui->forgetPass->setStyleSheet(
                "QPushButton {"
                "    background-color: transparent;"
                "    border: none;"
                "    font: 700 14pt 'UD Digi Kyokasho NP-B';"
                "    color: rgb(99, 100, 103); /* Default text color */"
                "}"
                "QPushButton:hover {"
                "    color: rgb(119, 120, 123); /* Slightly lighter text color on hover */"
                "}"
                "QPushButton:pressed {"
                "    color: rgb(79, 80, 83); /* Slightly darker text color when pressed */"
                "}"
                );
    ui->password->setEchoMode(QLineEdit::Password);
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
    ui->sign_button_3->setStyleSheet(
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
    int currentYear = QDate::currentDate().year();

    // Populate combo box with years from 1900 to current year
    for (int year = 1900; year <= currentYear; ++year) {
        ui->year->addItem(QString::number(year));
    }
    // Populate months
    QStringList months = {"January", "February", "March", "April", "May", "June",
                          "July", "August", "September", "October", "November", "December"};

    ui->month->addItems(months);
    QStringList days;
    for (int i = 1; i <= 31; ++i) {
        days << QString::number(i);
    }

    ui->day->addItems(days);
    ui->password_2->setEchoMode(QLineEdit::Password);
    ui->wrong_email->hide();
    ui->wrong_pass->hide();
    ui->message_succ->hide();



}

// Function to validate email format
bool isValidEmail(const QString &email) {
    QRegularExpression emailRegex(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
    return emailRegex.match(email).hasMatch();
}

// Function to validate password strength
bool isValidPassword(const QString &password) {
    // At least 8 characters
    QRegularExpression passwordRegex("^.{8,}$");
    return passwordRegex.match(password).hasMatch();
}

void Register::on_Sign_in_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);


}


void Register::on_forgetPass_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->Back->setStyleSheet(
                "QPushButton {"
                "    background-color: transparent;"
                "    border: none;"
                "    font: 700 14pt 'UD Digi Kyokasho NP-B';"
                "    color: rgb(99, 100, 103); /* Default text color */"
                "}"
                "QPushButton:hover {"
                "    color: rgb(119, 120, 123); /* Slightly lighter text color on hover */"
                "}"
                "QPushButton:pressed {"
                "    color: rgb(79, 80, 83); /* Slightly darker text color when pressed */"
                "}"
                );
    ui->Verify->setStyleSheet(
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
}


void Register::on_Back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Register::on_Verify_clicked()
{
    //check the verification
    ui->stackedWidget->setCurrentIndex(3);

}








void Register::on_Submit_clicked()
{

    //save new password
    //trigger
    ui->stackedWidget->setCurrentIndex(0);
    ui->Submit->setStyleSheet(
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
    ui->password_3->setEchoMode(QLineEdit::Password);


}





void Register::on_sign_button_3_clicked()
{

QString email = ui->email->text();
QString password = ui->password_2->text();

if (!isValidEmail(email)) {
     ui->wrong_email->show();
}

if (!isValidPassword(password)) {
    ui->wrong_pass->show();
}
if(isValidPassword(password)&&isValidEmail(email)){
    timer = new QTimer(this);  // Initialize the QTimer
    connect(timer, &QTimer::timeout, this, &Register::onTimeout);
    ui->message_succ->show();
    ui->sign_button_3->hide();
    ui->wrong_email->hide();
     ui->wrong_pass->hide();
    // Start the timer with a 3-second timeout (3000 milliseconds)
    timer->start(3000);
}
}

void Register::onTimeout()
{
ui->stackedWidget->setCurrentIndex(0);
ui->message_succ->hide();
ui->sign_button_3->show();

if (timer) {
    timer->stop();
    delete timer;
    timer = nullptr;
}
}

