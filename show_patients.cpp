#include "show_patients.h"
#include "ui_show_patients.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

show_patients::show_patients(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::show_patients)
{
    ui->setupUi(this);

    //获取数据库中所有的病人
    QString sql_patient;
    sql_patient="select id,name,sex,age,sickroom_id,bed_id from patient";
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_patient);
    ui->tableView->setModel(model);
}

show_patients::~show_patients()
{
    delete ui;
}

void show_patients::on_tableView_clicked(const QModelIndex &index)
{
    emit sendPatient_id(index.data().toString());     //获取被点击的病人的id并且传递出去
}

void show_patients::on_select_patient_id_clicked()
{
    patient_id=ui->LINE_PATIENT_ID->text();

    //从数据库中获取该病人的信息
    QString sql_patient;
    sql_patient=QString("select id,name,sex,age,sickroom_id,bed_id from patient where id like '%%1%' ").arg(patient_id);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_patient);
    ui->tableView->setModel(model);
}

void show_patients::on_select_patient_name_clicked()
{
    patient_name=ui->LINE_PATIENT_NAME->text();

    //从数据库中获取该病人的信息
    QString sql_patient;
    sql_patient=QString("select id,name,sex,age,sickroom_id,bed_id from patient where name like '%%1%' ").arg(patient_name);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_patient);
    ui->tableView->setModel(model);
}

void show_patients::on_select_department_name_clicked()
{
    department_name=ui->LINE_DEPARTMENT_NAME->text();

    //查询该科室的id
    QSqlQuery query;
    QString select_str = QString("select id from department where name like '%%1%' ").arg(department_name);
    query.exec(select_str);
    while(query.next())
        department_id=query.value(0).toString();

    //从数据库中获取该病人的信息
    QString sql_patient;
    sql_patient=QString("select patient.id,patient.name,patient.sex,patient.age,patient.sickroom_id,patient.bed_id from patient,department_sickroom "
                        "where department_id='%1' and patient.sickroom_id=department_sickroom.sickroom_id").arg(department_id);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_patient);
    ui->tableView->setModel(model);
}

void show_patients::on_select_sickroom_id_clicked()
{
    sickroom_id=ui->LINE_SICKROOM_ID->text();

    //从数据库中获取该病人的信息
    QString sql_patient;
    sql_patient=QString("select id,name,sex,age,sickroom_id,bed_id from patient where sickroom_id like '%%1%' ").arg(sickroom_id);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_patient);
    ui->tableView->setModel(model);
}

void show_patients::on_reset_clicked()
{
    //获取数据库中所有的病人
    QString sql_patient;
    sql_patient="select id,name,sex,age,sickroom_id,bed_id from patient";
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_patient);
    ui->tableView->setModel(model);

    ui->LINE_PATIENT_ID->clear();
    ui->LINE_PATIENT_NAME->clear();
    ui->LINE_DEPARTMENT_NAME->clear();
    ui->LINE_SICKROOM_ID->clear();
}

void show_patients::on_pushButton_clicked()
{
    this->close();
}
