#ifndef PATIENTWINDOW_H
#define PATIENTWINDOW_H

#include "loginwindow.h"

#include "show_prescriptions.h"
#include "show_inspection_items.h"
#include "show_list.h"
#include "change_password.h"

#include <QMainWindow>

#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QSqlTableModel>
#include <QTableView>

namespace Ui {
class patientwindow;
}

class patientwindow : public QMainWindow
{
    Q_OBJECT

public:
    patientwindow(const QString &id, QWidget *parent = nullptr);
    ~patientwindow();

private slots:
    void on_select_prescription_clicked();

    void on_select_inspection_clicked();

    void on_select_list_clicked();

    void on_pushButton_clicked();

    void on_change_password_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::patientwindow *ui;

    //病人相关信息
    QString patient_id;
    QString patient_name;
    QString patient_sex;
    int patient_age;
    QString patient_phone;
    QString patient_address;

    //医生相关信息
    QString doctor_id;
    QString doctor_name;
    QString doctor_sex;
    int doctor_age;
    QString doctor_phone;
    QString doctor_professional;

    //住院相关信息
    QDateTime start_time;
    QString department_id;
    QString department_name;
    QString sickroom_id;
    QString sickroom_rank;
    QString sickroom_cost_per_day;
    int patient_bed;
    QString patient_account;
};

#endif // PATIENTWINDOW_H
