#ifndef PREMIUM_H
#define PREMIUM_H

#include <QWidget>

namespace Ui {
class Premium;
}

class Premium : public QWidget
{
    Q_OBJECT

public:
    explicit Premium(QWidget *parent = nullptr);
    ~Premium();

private:
    Ui::Premium *ui;
};

#endif // PREMIUM_H
