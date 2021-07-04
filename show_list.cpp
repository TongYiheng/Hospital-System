#include "show_list.h"
#include "ui_show_list.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

show_list::show_list(QString &id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::show_list)
{
    ui->setupUi(this);

    QSqlQuery query;


    //获取数据库中该病人的病床费用
    QString select_bed_cost=QString("select sum_bed_cost from patient where id='%1'").arg(id);
    query.exec(select_bed_cost);
    while(query.next())
        ui->doubleSpinBox_bed_cost->setValue(query.value(0).toDouble());


    //获取数据库中该病人的处方费用
    QString select_pres_cost=QString("select sum(cost) as pres_cost from patient_prescription,prescription where patient_prescription.patient_id='%1' and "
                                     "patient_prescription.prescription_id=prescription.id ").arg(id);
    query.exec(select_pres_cost);
    while(query.next())
        ui->doubleSpinBox_pres_cost->setValue(query.value(0).toDouble());



    //获取数据库中该病人的检查费用
    QString select_ins_cost=QString("select sum(cost) as ins_cost from patient_inspection,inspection_items where patient_inspection.patient_id='%1' and "
                                     "patient_inspection.inspection_id=inspection_items.id ").arg(id);
    query.exec(select_ins_cost);
    while(query.next())
        ui->doubleSpinBox_ins_cost->setValue(query.value(0).toDouble());

    //显示总费用
    ui->doubleSpinBox_sum_cost->setValue(ui->doubleSpinBox_bed_cost->value()+ui->doubleSpinBox_pres_cost->value()+ui->doubleSpinBox_ins_cost->value());
}

show_list::~show_list()
{
    delete ui;
}

void show_list::on_pushButton_clicked()
{
    this->close();
}
