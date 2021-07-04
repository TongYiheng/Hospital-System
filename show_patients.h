#ifndef SHOW_PATIENTS_H
#define SHOW_PATIENTS_H

#include <QMainWindow>

namespace Ui {
class show_patients;
}

class show_patients : public QMainWindow
{
    Q_OBJECT

public:
    explicit show_patients(QWidget *parent = nullptr);
    ~show_patients();

signals:
    void sendPatient_id(QString);   //用来传递数据的信号

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_select_patient_id_clicked();

    void on_select_patient_name_clicked();

    void on_select_department_name_clicked();

    void on_select_sickroom_id_clicked();

    void on_reset_clicked();

    void on_pushButton_clicked();

private:
    Ui::show_patients *ui;
    QString patient_id;
    QString patient_name;
    QString department_id;
    QString department_name;
    QString sickroom_id;
};

#endif // SHOW_PATIENTS_H
