#include "show_prescriptions.h"
#include "ui_show_prescriptions.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

show_prescriptions::show_prescriptions(QString &id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::show_prescriptions)
{
    ui->setupUi(this);

    //获取数据库中该病人的所有处方
    QString sql_prescription;
    sql_prescription=QString("select prescription.id,prescription.content,doctor.name,prescription.cost from patient_prescription,prescription,doctor where patient_prescription.patient_id"
                             "='%1' and patient_prescription.prescription_id=prescription.id and doctor.id=prescription.doctor ").arg(id);
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(sql_prescription);
    ui->tableView->setModel(model);
}

show_prescriptions::~show_prescriptions()
{
    delete ui;
}

void show_prescriptions::on_pushButton_clicked()
{
    this->close();
}
