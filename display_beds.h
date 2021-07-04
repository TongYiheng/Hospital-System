#ifndef DISPLAY_BEDS_H
#define DISPLAY_BEDS_H

#include <QMainWindow>

namespace Ui {
class display_beds;
}

class display_beds : public QMainWindow
{
    Q_OBJECT

public:
    explicit display_beds(QWidget *parent = nullptr);
    ~display_beds();

    void judge();

private slots:
    void receiveSickroom_id(QString data);      //接收病房号

    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

signals:
    void sendBed(int);   //传递病床号

private:
    Ui::display_beds *ui;
    QString sickroom_id;
    QString sickroom_rank;
    QString department_name;
    QString capacity;
    QString patient_number;
};

#endif // DISPLAY_BEDS_H
