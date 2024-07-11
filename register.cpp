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
        QString username = ui->username_3->text();
        QString email = ui->Email_3->text();

        // Open the database connection
        if (initializeDatabase(db)) {
            QSqlQuery query(db);
            query.prepare("{CALL CheckUserByEmailAndUsername(?, ?)}");
            query.addBindValue(username);
            query.addBindValue(email);

            if (query.exec()) {
                if (query.next()) {
                    QString result = query.value(0).toString();
                    if (result == "Valid") {
                        ui->stackedWidget->setCurrentIndex(3); // Move to the next page for verification
                    } else {
                        QMessageBox::warning(this, "Verification Failed", "Invalid username or email.");
                    }
                } else {
                    QMessageBox::warning(this, "Error", "Query did not return any result.");
                }
            } else {
                qDebug() << "Query execution error:" << query.lastError().text();
                QMessageBox::critical(this, "Database Error", "Failed to execute query.");
            }
        } else {
            QMessageBox::critical(this, "Database Connection Error", "Failed to connect to the database.");
        }
    }



void Register::on_Submit_clicked()
{

    //save new password
    //trigger

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
    if (ui->username_3->text().isEmpty() || ui->password_3->text().isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill in both username and password fields.");
            return; // Stop further execution
        }
    else if(ui->password_3->text()==ui->username_4->text()){
        QString password =ui->password_3->text();
        QString username =ui->username_3->text();
        if (initializeDatabase(db)) {
            QSqlQuery query(db);
            query.prepare("{CALL UpdatePassword(?, ?)}");
            query.addBindValue(username);
            query.addBindValue(password);

            if (query.exec()) {
                        if (query.next()) {
                            int affectedRows = query.value("AffectedRows").toInt();
                            if (affectedRows > 0) {
                                QString message = "Password updated successfully for user: " + username;
                                QMessageBox::information(this, "Success", message);
                                // Handle success scenario, e.g., show message to user
                                ui->stackedWidget->setCurrentIndex(0);
                            } else {
                                qDebug() << "No rows updated. User:" << username << "not found or password not changed.";
                                // Handle case where no rows were updated
                            }
                        } else {
                            qDebug() << "Query did not return any result.";
                        }
                    } else {
                        qDebug() << "Query execution error:" << query.lastError().text();
                        // Handle error scenario, e.g., show error message
                    }
                } else {
                    qDebug() << "Database Connection Error: Failed to connect to the database.";
                    // Handle error connecting to the database
                }
            }
    else{
        QMessageBox::critical(this, "Error", "Passwords do not match. Please enter them again.");
        ui->password_3->clear();
        ui->username_4->clear();

    }
}

void Register::on_sign_button_3_clicked() {
    QString email = ui->email->text();
    QString password = ui->password_2->text();
    QString username = ui->username_2->text();
    QString country = ui->country->text();
    int year = ui->year->currentText().toInt();
    int month = ui->month->currentIndex() + 1; // Corrected indexing for month
    int day = ui->day->currentText().toInt();
    QDate birthDate(year, month, day);

    if (!isValidEmail(email)) {
        ui->wrong_email->show();
        return;
    }

    if (!isValidPassword(password)) {
        ui->wrong_pass->show();
        return;
    }


        QSqlQuery query(db);
        query.prepare("{CALL InsertUser(?, ?, ?, ?, ?)}");
        query.addBindValue(username);
        query.addBindValue(password);
        query.addBindValue(birthDate.toString(Qt::ISODate)); // Ensure to pass as string
        query.addBindValue(country);
        query.addBindValue(email);

        if (query.exec()) {
            ui->message_succ->show();
            ui->sign_button_3->hide();
            ui->wrong_email->hide();
            ui->wrong_pass->hide();

            // Start the timer with a 3-second timeout (3000 milliseconds)
            QTimer *timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, &Register::onTimeout);
            timer->start(3000);
        } else {
            qDebug() << "Stored procedure execution error:" << query.lastError().text();
            QMessageBox::critical(this, "Database Error", "Failed to register user");
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

void Register::on_sign_button_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();

    QSqlQuery query(db);

    // Prepare the query to call stored procedure
    query.prepare("{CALL CheckUserType(?, ?)}");
    query.addBindValue(username);
    query.addBindValue(password);

            // Execute the query
            if (query.exec()) {
                // Check the result
                if (query.next()) {
                    QString userType = query.value(0).toString();
                    int userId = query.value(1).toInt();
                    if (userType == "Regular User") {
                        emit loginPSuccessful(userId,userType);  // Signal for regular user
                    } else if (userType == "Premium User") {
                        emit loginPSuccessful(userId,userType); // Signal for premium user
                    }
                } else {
                    qDebug() << "No rows returned.";
                    // Handle case where no rows were returned (user does not exist)
                    QMessageBox::critical(this, "Login Error", "Invalid username or password.");
                }
            } else {
                qDebug() << "Stored procedure execution error:" << query.lastError().text();
                QMessageBox::critical(this, "Database Error", "Failed to execute stored procedure.");
            }
        } else {
            qDebug() << "No rows returned.";
            // Handle case where no rows were returned (user does not exist)
            QMessageBox::critical(this, "Login Error", "Invalid username or password.");
        }
    } else {
        qDebug() << "Stored procedure execution error:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "Failed to execute stored procedure.");
    }
}






