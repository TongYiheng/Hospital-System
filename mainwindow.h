#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "loginwindow.h"

#include "add_patients.h"
#include "add_doctors.h"
#include "add_prescriptions.h"
#include "add_inspection_items.h"
#include "change_department.h"
#include "add_payments.h"
#include "leave_hospital.h"

#include "display_patients.h"
#include "display_doctors.h"
#include "display_department.h"
#include "display_sickrooms.h"
#include "display_beds.h"
#include "show_patients.h"

#include <QMainWindow>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlResult>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_add_patients_clicked();

    void on_add_doctors_clicked();

    void on_select_department_clicked();

    void receiveDepartment_id(QString data);    //添加医生时接收传递过来的数据的槽

    void receiveDoctor_id(QString data);        //添加病人时接收传递过来的数据的槽

    void receiveDoctor_id_3(QString data);      //处方开立时接收传递过来的数据的槽

    void receiveDoctor_id_5(QString data);      //病人转科室时接收新的主治医生

    void receiveSickroom_id(QString data);      //添加病人时接收传递过来的数据的槽

    void receiveSickroom_id_5(QString data);    //病人转科室时接收要转入的病房号

    void receiveDepartment_name(QString data);  //添加病人时接收传递过来的数据的槽

    void receiveBed(int data);                  //添加病人时接收传递过来的数据的槽

    void receiveBed_5(int data);                //病人转科室时接收要转入的病房号

    void receivePatient_id_3(QString data);     //处方开立时接收传递过来的数据的槽

    void receiveDepartment_name_3(QString data);//处方开立时接收科室名

    void receiveDepartment_name_4(QString data);//检查项目开立时接收科室名

    void receiveDepartment_name_5(QString data);//病人转科室时接收科室名

    void receivePatient_id_4(QString data);     //检查项目开立时接收传递过来的数据的槽

    void receivePatient_id_5(QString data);     //病人转科室时接收病人ID

    void receivePatient_id_6(QString data);     //病人缴费时接收病人ID

    void receivePatient_id_7(QString data);     //病人出院时接收病人ID

    void on_select_doctor_clicked();

    void on_select_sickroom_clicked();

    void on_select_bed_clicked();

    void on_add_prescriptions_clicked();

    void on_select_doctor_3_clicked();

    void on_select_patient_3_clicked();

    void on_add_inspection_items_clicked();

    void on_select_patient_4_clicked();

    void on_select_department_name_clicked();

    void on_select_department_3_clicked();

    void on_select_department_4_clicked();

    void on_select_patient_5_cur_clicked();

    void on_select_department_5_tar_clicked();

    void on_select_sickroom_5_tar_clicked();

    void on_select_bed_5_tar_clicked();

    void on_select_doctor_5_tar_clicked();

    void on_change_department_clicked();

    void on_select_patient_6_clicked();

    void on_pay_clicked();

    void on_select_patient_7_clicked();

    void on_leave_hospital_clicked();

    void on_pushButton_clicked();

    void on_add_patients_2_clicked();

    void on_add_doctors_2_clicked();

    void on_add_prescriptions_2_clicked();

    void on_add_inspection_items_2_clicked();

    void on_change_department_2_clicked();

    void on_pay_2_clicked();

    void on_leave_hospital_2_clicked();

signals:
    void sendSickroom_id(QString);   //用来传递数据的信号

    void sendDepartment_nameToAdd_patients(QString);  //传递科室名

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
