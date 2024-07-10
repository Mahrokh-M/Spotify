#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>
#include <QGraphicsDropShadowEffect>
#include <QDateTime>
#include <QTimer>
#include <QRegularExpression>
#include <QCoreApplication>
#include<QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class Register; }
QT_END_NAMESPACE

class Register : public QMainWindow
{
    Q_OBJECT

public:
    Register(QWidget *parent = nullptr);
    ~Register();
     void onTimeout();


private slots:
    void on_Sign_up_clicked();

    void on_Sign_in_2_clicked();

    void on_forgetPass_clicked();

    void on_Back_clicked();

    void on_Verify_clicked();

    void on_Submit_clicked();

    void on_sign_button_3_clicked();

    void on_sign_button_clicked();
signals:
    void loginSuccessful();  // Add this signal
    void loginPSuccessful();
    void loginSSuccessful();

private:
    Ui::Register *ui;
        QTimer *timer;  // Declare the QTimer pointer
};
#endif // REGISTER_H
bool isValidEmail(const QString &email);
bool isValidPassword(const QString &password);
