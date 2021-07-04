#include "patientwindow.h"
#include "ui_patientwindow.h"

patientwindow::patientwindow(const QString &id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::patientwindow),
    patient_id(id)
{
    ui->setupUi(this);


    QSqlQuery query;

    //查询病人基本信息
    QString select_patient=QString("select * from patient where id='%1';").arg(patient_id);
    query.exec(select_patient);
    while(query.next())
    {
        patient_name=query.value(1).toString();
        patient_sex=query.value(2).toString();
        patient_age=query.value(3).toInt();
        patient_phone=query.value(4).toString();
        patient_address=query.value(5).toString();

        start_time=query.value(6).toDateTime();
        sickroom_id=query.value(7).toString();
        patient_bed=query.value(8).toInt();
        patient_account=query.value(9).toString();
    }

    //查询主治医生信息
    QString select_doctor=QString("select doctor_id from patient_doctor where patient_id='%1';").arg(patient_id);
    query.exec(select_doctor);
    while(query.next())
        doctor_id=query.value(0).toString();

    select_doctor=QString("select * from doctor where id='%1';").arg(doctor_id);
    query.exec(select_doctor);
    while(query.next())
    {
        doctor_name=query.value(1).toString();
        doctor_sex=query.value(2).toString();
        doctor_age=query.value(3).toInt();
        doctor_phone=query.value(4).toString();
        department_id=query.value(5).toString();
        doctor_professional=query.value(6).toString();
    }


    //查询住院相关信息
    QString select_department=QString("select name from department where id='%1';").arg(department_id);
    query.exec(select_department);
    while(query.next())
        department_name=query.value(0).toString();

    select_doctor=QString("select * from doctor where id='%1';").arg(doctor_id);
    query.exec(select_doctor);
    while(query.next())
    {
        doctor_name=query.value(1).toString();
        doctor_sex=query.value(2).toString();
        doctor_age=query.value(3).toInt();
        doctor_phone=query.value(4).toString();
        department_id=query.value(5).toString();
        doctor_professional=query.value(6).toString();
    }


    //从数据库中获取病房信息
    QString select_sickroom=QString("select sickroom.rank,cost_per_day from sickroom where id='%1';").arg(sickroom_id);
    query.exec(select_sickroom);
    while(query.next())
    {
        sickroom_rank=query.value(0).toString();
        sickroom_cost_per_day=query.value(1).toString();
    }


    //在窗口中显示信息
    ui->LINE_PATIENT_ID->setText(patient_id);
    ui->LINE_PATIENT_NAME->setText(patient_name);
    ui->LINE_PATIENT_SEX->setText(patient_sex);
    ui->SPINBOX_PATIENT_AGE->setValue(patient_age);
    ui->LINE_PATIENT_PHONE->setText(patient_phone);
    ui->LINE_PATIENT_ADDRESS->setText(patient_address);

    ui->LINE_DOCTOR_NAME->setText(doctor_name);
    ui->LINE_DOCTOR_SEX->setText(doctor_sex);
    ui->SPINBOX_DOCTOR_AGE->setValue(doctor_age);
    ui->LINE_DOCTOR_PHONE->setText(doctor_phone);
    ui->LINE_DOCTOR_PROFESSIONAL->setText(doctor_professional);

    ui->START_TIME->setDateTime(start_time);
    ui->LINE_DEPARTMENT->setText(department_name);
    ui->LINE_SICKROOM_ID->setText(sickroom_id);
    ui->LINE_SICKROOM_RANK->setText(sickroom_rank);
    ui->LINE_SICKROOM_COST_PER_DAY->setText(sickroom_cost_per_day + "元/天");
    ui->SPINBOX_PATIENT_BED->setValue(patient_bed);
    ui->LINE_ACCOUNT->setText(patient_account + "元");
}

patientwindow::~patientwindow()
{
    delete ui;
}

void patientwindow::on_select_prescription_clicked()
{
    show_prescriptions* SP=new show_prescriptions(patient_id);
    SP->show();
}

void patientwindow::on_select_inspection_clicked()
{
    show_inspection_items* SI=new show_inspection_items(patient_id);
    SI->show();
}

void patientwindow::on_select_list_clicked()
{
    show_list* SL=new show_list(patient_id);
    SL->show();
}

void patientwindow::on_pushButton_clicked()
{
    this->close();
}

void patientwindow::on_change_password_clicked()
{
    change_password* CP=new change_password(patient_id);
    CP->show();
}

void patientwindow::on_pushButton_2_clicked()
{
    this->close();
    LoginWindow* LW=new LoginWindow;
    LW->show();
}
