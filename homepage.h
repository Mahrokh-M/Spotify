#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

private slots:
    void playSong();

    void on_pushButton_clicked();

private:
    Ui::HomePage *ui;
    QGridLayout *gridLayout;
    QWidget *contentWidget;
    QScrollArea *scrollArea;
    int songCount;

    void addSongItem(const QString &songName, const QString &imagePath);
signals:
    void logoutSuccessful();  // Add this signal
};

#endif // HOMEPAGE_H
