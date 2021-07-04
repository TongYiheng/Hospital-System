#include "show_inspection_items.h"
#include "ui_show_inspection_items.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

show_inspection_items::show_inspection_items(QString &id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::show_inspection_items)
{
    ui->setupUi(this);

    //获取数据库中该病人的所有检查项目
    QString sql_inspection;
    sql_inspection=QString("select inspection_items.* from patient_inspection,inspection_items where patient_inspection.patient_id='%1'"
                           "and patient_inspection.inspection_id=inspection_items.id").arg(id);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_inspection);
    ui->tableView->setModel(model);
}

show_inspection_items::~show_inspection_items()
{
    delete ui;
}

void show_inspection_items::on_pushButton_clicked()
{
    this->close();
}
