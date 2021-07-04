#ifndef DISPLAY_DEPARTMENT_H
#define DISPLAY_DEPARTMENT_H

#include <QMainWindow>

namespace Ui {
class display_department;
}

class display_department : public QMainWindow
{
    Q_OBJECT

public:
    explicit display_department(QWidget *parent = nullptr);
    ~display_department();

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_select_id_clicked();

    void on_select_name_clicked();

    void on_pushButton_2_clicked();

signals://用来传递数据的信号
    void sendDepartment_id(QString);

    void sendDepartment_nameToAdd_patients(QString);

private:
    Ui::display_department *ui;
    QString department_id;
    QString department_name;
};

#endif // DISPLAY_DEPARTMENT_H
