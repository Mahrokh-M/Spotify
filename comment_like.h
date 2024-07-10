#ifndef COMMENT_LIKE_H
#define COMMENT_LIKE_H
#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class Comment_Like;
}

class Comment_Like : public QWidget
{
    Q_OBJECT

public:
    explicit Comment_Like(QWidget *parent = nullptr);
    ~Comment_Like();

private:
    Ui::Comment_Like *ui;
    void onSongButtonClicked();
public slots:
    void setCommentDetails(const QString &songID);
private slots:
    void on_Back_clicked();
signals:
    void goBack();
     void open_comment(const QString);
};

#endif // COMMENT_LIKE_H
