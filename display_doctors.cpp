#include "display_doctors.h"
#include "ui_display_doctors.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>

display_doctors::display_doctors(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::display_doctors)
{
    ui->setupUi(this);
}

display_doctors::~display_doctors()
{
    delete ui;
}

void display_doctors::receiveDepartment_name(QString data)
{
    department_name=data;

    //查询该科室的id
    QSqlQuery query;
    QString select_str = QString("select id from department where name='%1' ").arg(department_name);
    query.exec(select_str);
    while(query.next())
        department_id=query.value(0).toString();

    //从数据库中获取当前科室下的医生
    QString sql_doctor;
    sql_doctor=QString("select * from doctor where department='%1';").arg(department_id);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_doctor);
    ui->tableView->setModel(model);

    ui->LINE_ID->setText(department_id);
    ui->LINE_NAME->setText(department_name);
}

void display_doctors::on_tableView_clicked(const QModelIndex &index)
{
    emit sendDoctor_id(index.data().toString());            //获取被点击的医生的id并且传递出去
}

void display_doctors::on_pushButton_clicked()
{
    this->close();
}

void display_doctors::on_search_doctor_id_clicked()
{
    //根据医生ID查询医生
    doctor_id=ui->LINE_DOCTOR_ID->text();
    QString sql_doctor;
    sql_doctor=QString("select * from doctor where id like '%%1%' and department='%2' ").arg(doctor_id,department_id);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_doctor);
    ui->tableView->setModel(model);
}

void display_doctors::on_search_doctor_name_clicked()
{
    //根据医生name查询医生
    doctor_name=ui->LINE_DOCTOR_NAME->text();
    QString sql_doctor;
    sql_doctor=QString("select * from doctor where name like '%%1%' and department='%2' ").arg(doctor_name,department_id);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_doctor);
    ui->tableView->setModel(model);
}

void display_doctors::on_reset_clicked()
{
    //从数据库中获取该科室下的所有医生
    QString sql_doctor;
    sql_doctor=QString("select * from doctor where department='%1';").arg(department_id);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_doctor);
    ui->tableView->setModel(model);

    ui->LINE_DOCTOR_ID->clear();
    ui->LINE_DOCTOR_NAME->clear();
}
