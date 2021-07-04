#ifndef DISPLAY_SICKROOMS_H
#define DISPLAY_SICKROOMS_H

#include <QMainWindow>

namespace Ui {
class display_sickrooms;
}

class display_sickrooms : public QMainWindow
{
    Q_OBJECT

public:
    explicit display_sickrooms(QWidget *parent = nullptr);
    ~display_sickrooms();

signals:
    void sendSickroom_id(QString);   //传递选择的病房号

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_search_sickroom_id_clicked();

    void on_pushButton_reset_clicked();

    void receiveDepartment_nameFromMainwindow(QString data);    //接收主窗口传过来的科室名

private:
    Ui::display_sickrooms *ui;
    QString department_id;
    QString department_name;
    QString sickroom_id;
};

#endif // DISPLAY_SICKROOMS_H
