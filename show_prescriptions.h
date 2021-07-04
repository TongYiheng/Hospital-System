#ifndef SHOW_PRESCRIPTIONS_H
#define SHOW_PRESCRIPTIONS_H

#include <QMainWindow>

namespace Ui {
class show_prescriptions;
}

class show_prescriptions : public QMainWindow
{
    Q_OBJECT

public:
    show_prescriptions(QString &id,QWidget *parent = nullptr);
    ~show_prescriptions();

private slots:
    void on_pushButton_clicked();

private:
    Ui::show_prescriptions *ui;
};

#endif // SHOW_PRESCRIPTIONS_H
