#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Register; }
QT_END_NAMESPACE

class Register : public QMainWindow
{
    Q_OBJECT

public:
    Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_Sign_up_clicked();

    void on_Sign_in_2_clicked();

private:
    Ui::Register *ui;
};
#endif // REGISTER_H
