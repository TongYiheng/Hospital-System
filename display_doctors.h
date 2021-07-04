#ifndef DISPLAY_DOCTORS_H
#define DISPLAY_DOCTORS_H

#include <QMainWindow>

namespace Ui {
class display_doctors;
}

class display_doctors : public QMainWindow
{
    Q_OBJECT

public:
    explicit display_doctors(QWidget *parent = nullptr);
    ~display_doctors();

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void receiveDepartment_name(QString data);      //接收科室名

    void on_search_doctor_id_clicked();

    void on_search_doctor_name_clicked();

    void on_reset_clicked();

signals:
    void sendDoctor_id(QString);   //用来传递数据的信号

private:
    Ui::display_doctors *ui;
    QString department_id;
    QString department_name;
    QString doctor_id;
    QString doctor_name;
};

#endif // DISPLAY_DOCTORS_H
