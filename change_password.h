#ifndef CHANGE_PASSWORD_H
#define CHANGE_PASSWORD_H

#include <QMainWindow>

namespace Ui {
class change_password;
}

class change_password : public QMainWindow
{
    Q_OBJECT

public:
    change_password(QString &id,QWidget *parent = nullptr);
    ~change_password();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::change_password *ui;
    QString patient_id;
};

#endif // CHANGE_PASSWORD_H
