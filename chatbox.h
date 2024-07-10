#ifndef CHATBOX_H
#define CHATBOX_H

#include <QWidget>

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
signals:
    void goBack();
};

#endif // CHATBOX_H