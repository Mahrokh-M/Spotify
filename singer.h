#ifndef SINGER_H
#define SINGER_H

#include <QWidget>

namespace Ui {
class Singer;
}

class Singer : public QWidget
{
    Q_OBJECT

public:
    explicit Singer(QWidget *parent = nullptr);
    ~Singer();

private:
    Ui::Singer *ui;
};

#endif // SINGER_H
