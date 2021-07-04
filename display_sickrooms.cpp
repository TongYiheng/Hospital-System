#include "display_sickrooms.h"
#include "ui_display_sickrooms.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

display_sickrooms::display_sickrooms(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::display_sickrooms)
{
    ui->setupUi(this);
}

display_sickrooms::~display_sickrooms()
{
    delete ui;
}

void display_sickrooms::receiveDepartment_nameFromMainwindow(QString data)
{
    department_name=data;

    //从数据库中获取该科室下的所有病房
    QString sql_sickroom;
    sql_sickroom=QString("select sickroom.id,sickroom.rank from sickroom,department_sickroom,department "
                         "where sickroom_id=sickroom.id and department_id=department.id and department.name='%1' ").arg(department_name);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_sickroom);
    ui->tableView->setModel(model);

    //查询该科室的id
    QSqlQuery query;
    QString select_str = QString("select id from department where name='%1' ").arg(department_name);
    query.exec(select_str);
    while(query.next())
        department_id=query.value(0).toString();

    ui->LINE_DEPARTMENT_ID->setText(department_id);
    ui->LINE_DEPARTMENT_NAME->setText(department_name);
}

void display_sickrooms::on_tableView_clicked(const QModelIndex &index)
{
    emit sendSickroom_id(index.data().toString());            //获取被点击的病房的id并且传递出去
}

void display_sickrooms::on_pushButton_clicked()
{
    this->close();
}

void display_sickrooms::on_pushButton_search_sickroom_id_clicked()
{
    //根据病房号查询病房
    sickroom_id=ui->lineEdit_sickroom_id->text();
    QString sql_sickroom;
    sql_sickroom=QString("select sickroom.id,sickroom.rank from sickroom,department_sickroom,department "
                         "where sickroom_id=sickroom.id and department_id=department.id and department.name='%1' "
                         "and sickroom.id like '%%2%' ").arg(department_name,sickroom_id);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_sickroom);
    ui->tableView->setModel(model);
}

void display_sickrooms::on_pushButton_reset_clicked()
{
    //从数据库中获取该科室下的所有病房
    QString sql_sickroom;
    sql_sickroom=QString("select sickroom.id,sickroom.rank from sickroom,department_sickroom,department "
                         "where sickroom_id=sickroom.id and department_id=department.id and department.name='%1' ").arg(department_name);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_sickroom);
    ui->tableView->setModel(model);

    ui->lineEdit_sickroom_id->clear();
}
