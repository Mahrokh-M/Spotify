#ifndef CHATBOX_H
#define CHATBOX_H
#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include<QFileDialog>
#include<QLineEdit>
#include<QVector>
#include<QFormLayout>
#include<QGroupBox>
#include<QMessageBox>
#include <QSqlError>
#include<QSqlQuery>
#include <QFile>
#include <QWidget>
extern QString friendN;
namespace Ui {
class ChatBox;
}

class ChatBox : public QWidget
{
    Q_OBJECT

public:
    explicit ChatBox(QWidget *parent = nullptr);
    ~ChatBox();

private:
    Ui::ChatBox *ui;
public slots:
    void fillChat(const QString &);
private slots:
    void on_Back_clicked();
    void setstyle();
    void on_send_button_clicked();

signals:
    void goBack();
};

#endif // CHATBOX_H
