#include "display_department.h"
#include "ui_display_department.h"

#include <QSqlQueryModel>

display_department::display_department(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::display_department)
{
    ui->setupUi(this);

    //从数据库中获取所有可供选择的科室
    QString sql_department;
    sql_department="select id,name from department";
    QSqlQueryModel *modelx=new QSqlQueryModel;
    modelx->setQuery(sql_department);
    ui->tableView->setModel(modelx);
}

display_department::~display_department()
{
    delete ui;
}

void display_department::on_tableView_clicked(const QModelIndex &index)
{
    //QString department_id=index.data().toString();            //使用一个字符串接收这个被点击的科室的id
    //ui->lineEdit->setText(department_id);                     //把这个字符串显示在相应的lineEdit控件上
    emit sendDepartment_nameToAdd_patients(index.data().toString());     //获取被点击的科室的name并且传递出去
    //emit sendDepartment_id(index.data().toString());
}

void display_department::on_pushButton_clicked()
{
    this->close();
}

void display_department::on_select_id_clicked()
{
    department_id=ui->LINE_ID->text();

    //查询科室
    QString sql_department;
    sql_department=QString("select id,name from department where id like '%%1%';").arg(department_id);
    QSqlQueryModel *modelx=new QSqlQueryModel;
    modelx->setQuery(sql_department);
    ui->tableView->setModel(modelx);
}

void display_department::on_select_name_clicked()
{
    department_name=ui->LINE_NAME->text();

    //查询科室
    QString sql_department;
    sql_department=QString("select id,name from department where name like '%%1%';").arg(department_name);
    QSqlQueryModel *modelx=new QSqlQueryModel;
    modelx->setQuery(sql_department);
    ui->tableView->setModel(modelx);
}

void display_department::on_pushButton_2_clicked()
{
    //从数据库中获取科室
    QString sql_department;
    sql_department="select id,name from department";
    QSqlQueryModel *modelx=new QSqlQueryModel;
    modelx->setQuery(sql_department);
    ui->tableView->setModel(modelx);

    ui->LINE_ID->clear();
    ui->LINE_NAME->clear();
}
