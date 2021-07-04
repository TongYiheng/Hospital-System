#include "display_patients.h"
#include "ui_display_patients.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>

display_patients::display_patients(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::display_patients)
{
    ui->setupUi(this);
}

display_patients::~display_patients()
{
    delete ui;
}

void display_patients::receiveDepartment_name(QString data)
{
    department_name=data;

    //查询该科室的id
    QSqlQuery query;
    QString select_str = QString("select id from department where name='%1' ").arg(department_name);
    query.exec(select_str);
    while(query.next())
        department_id=query.value(0).toString();

    //从数据库中获取当前科室下的病人
    QString sql_patient;
    sql_patient=QString("select * from patient,department_sickroom where patient.sickroom_id=department_sickroom.sickroom_id "
                        "and department_sickroom.department_id='%1';").arg(department_id);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_patient);
    ui->tableView->setModel(model);

    ui->LINE_DEPARTMENT_ID->setText(department_id);
    ui->LINE_DEPARTMENT_NAME->setText(department_name);
}

void display_patients::on_tableView_clicked(const QModelIndex &index)
{
    emit sendPatient_id(index.data().toString());            //获取被点击的病人的id并且传递出去
}

void display_patients::on_pushButton_clicked()
{
    this->close();
}

void display_patients::on_search_patient_id_clicked()
{
    //根据病人ID查询病人
    patient_id=ui->LINE_PATIENT_ID->text();
    QString sql_patient;
    /*sql_patient=QString("select * from patient,department_sickroom where patient.sickroom_id=department_sickroom.sickroom_id "
                        "and department_sickroom.department_id='%1' and patient.id='%2' ").arg(department_id,patient_id);*/

    sql_patient=QString("select * from patient,department_sickroom where patient.sickroom_id=department_sickroom.sickroom_id "
                        "and department_sickroom.department_id='%1' and patient.id like '%%2%' ").arg(department_id,patient_id);

    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_patient);
    ui->tableView->setModel(model);
}

void display_patients::on_search_patient_name_clicked()
{
    //根据病人name查询病人
    patient_name=ui->LINE_PATIENT_NAME->text();
    QString sql_patient;
    /*sql_patient=QString("select * from patient,department_sickroom where patient.sickroom_id=department_sickroom.sickroom_id "
                        "and department_sickroom.department_id='%1' and patient.name='%2' ").arg(department_id,patient_name);*/

    sql_patient=QString("select * from patient,department_sickroom where patient.sickroom_id=department_sickroom.sickroom_id "
                        "and department_sickroom.department_id='%1' and patient.name like '%%2%' ").arg(department_id,patient_name);

    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_patient);
    ui->tableView->setModel(model);
}

void display_patients::on_reset_clicked()
{
    //从数据库中获取当前科室下的病人
    QString sql_patient;
    sql_patient=QString("select * from patient,department_sickroom where patient.sickroom_id=department_sickroom.sickroom_id "
                        "and department_sickroom.department_id='%1';").arg(department_id);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_patient);
    ui->tableView->setModel(model);

    ui->LINE_DEPARTMENT_ID->setText(department_id);
    ui->LINE_DEPARTMENT_NAME->setText(department_name);

    ui->LINE_PATIENT_ID->clear();
    ui->LINE_PATIENT_NAME->clear();
}
