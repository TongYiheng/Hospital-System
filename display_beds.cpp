#include "display_beds.h"
#include "ui_display_beds.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QMessageBox>

display_beds::display_beds(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::display_beds)
{
    ui->setupUi(this);
}

display_beds::~display_beds()
{
    delete ui;
}

void display_beds::receiveSickroom_id(QString data)
{
    sickroom_id=data;     //获取传递过来的数据

    /*//从数据库中获取已经使用的床位
    QString sql_bed;
    sql_bed=QString("select bed_id from patient where sickroom_id='%1' order by bed_id;").arg(sickroom_id);
    QSqlQueryModel *modelx=new QSqlQueryModel;
    modelx->setQuery(sql_bed);
    ui->tableView->setModel(modelx);*/


    QSqlQuery query_call;
    QString sql_call = "call bed_loop(?)";
    query_call.prepare(sql_call);

    //补全sql中的占位符
    query_call.addBindValue(sickroom_id);
    query_call.exec();

    //从数据库中获取尚未使用的床位
    QString sql_bed;
    sql_bed=QString("select bed_id from bed_temp where bed_id not in (select bed_id from patient where sickroom_id='%1')").arg(sickroom_id);
    QSqlQueryModel *modelx=new QSqlQueryModel;
    modelx->setQuery(sql_bed);
    ui->tableView->setModel(modelx);


    //清除bed_temp的信息
    QSqlQuery query_delete;
    QString sql_delete=QString("delete from bed_temp where bed_id<1000");   //这里由于mysql的安全机制，如果删除时不加where子句会导致删除失败
    query_delete.exec(sql_delete);


    //从数据库中获取病房信息
    QSqlQuery query;
    QString select_capacity=QString("select sickroom.id,sickroom.rank,department.name,patient_number,capacity from sickroom,department_sickroom,department "
                                    "where sickroom_id=sickroom.id and department_id=department.id and sickroom.id='%1';").arg(sickroom_id);
    query.exec(select_capacity);
    while(query.next())
    {
        sickroom_id=query.value(0).toString();
        sickroom_rank=query.value(1).toString();
        department_name=query.value(2).toString();
        patient_number=query.value(3).toString();
        capacity=query.value(4).toString();
    }

    ui->LINE_SICKROOM_ID->setText(sickroom_id);
    ui->LINE_SICKROOM_RANK->setText(sickroom_rank);
    ui->LINE_DEPARTMENT->setText(department_name);
    ui->LINE_PATIENT_NUMBER->setText(patient_number);
    ui->LINE_CAPACITY->setText(capacity);
}

void display_beds::on_pushButton_clicked()
{
    /*
    if(ui->spinBox->value()>capacity.toInt())
    {
        QMessageBox::information(this,"错误", "所选病房号超出病房容量，请重新选择");
    }
    else if(ui->spinBox->value()==0)
    {
        QMessageBox::information(this,"错误", "所选病房号无效，请重新选择");
    }
    else
    {
        emit sendBed(ui->spinBox->value());            //获取病床号并且传递出去
        this->close();
    }*/
    this->close();
}

void display_beds::judge()
{
    if(patient_number==capacity)
        QMessageBox::information(this,"提示", "当前所选病房已满，请重新选择病房");
    //this->close();
}

void display_beds::on_tableView_clicked(const QModelIndex &index)
{
    emit sendBed(index.data().toInt());
}
