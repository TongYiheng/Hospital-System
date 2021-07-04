#ifndef DISPLAY_PATIENTS_H
#define DISPLAY_PATIENTS_H

#include <QMainWindow>

namespace Ui {
class display_patients;
}

class display_patients : public QMainWindow
{
    Q_OBJECT

public:
    explicit display_patients(QWidget *parent = nullptr);
    ~display_patients();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void receiveDepartment_name(QString data);      //接收科室名

    void on_search_patient_id_clicked();

    void on_search_patient_name_clicked();

    void on_reset_clicked();

signals:
    void sendPatient_id(QString);   //用来传递数据的信号

private:
    Ui::display_patients *ui;
    QString department_id;
    QString department_name;
    QString patient_id;
    QString patient_name;
};

#endif // DISPLAY_PATIENTS_H
