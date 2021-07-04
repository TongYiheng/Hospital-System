#include "add_prescriptions.h"


#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


add_prescriptions::add_prescriptions() {}

void add_prescriptions::setPrescription_id(const QString &id) {prescription_id=id;}
void add_prescriptions::setPrescription_content(const QString& content) {prescription_content=content;}
void add_prescriptions::setDoctor_id(const QString& id) {doctor_id=id;}
void add_prescriptions::setPatient_id(const QString& id) {patient_id=id;}
void add_prescriptions::setCost(const double& thecost) {cost=thecost;}

bool add_prescriptions::insertDataToPrescription()
{
    // sql insert 有参数写法参考
    QString insert_sql = "insert into prescription(id, content, doctor, cost) values (?,?,?,?)";

    sql_query.prepare(insert_sql);

    //补全sql中的占位符
    sql_query.addBindValue(prescription_id);
    sql_query.addBindValue(prescription_content);
    sql_query.addBindValue(doctor_id);
    sql_query.addBindValue(cost);

    return sql_query.exec();
}

bool add_prescriptions::insertDataToPatient_prescription()
{
    // sql insert 有参数写法参考
    QString insert_sql = "insert into patient_prescription(patient_id, prescription_id) values (?,?)";

    sql_query.prepare(insert_sql);

    //补全sql中的占位符
    sql_query.addBindValue(patient_id);
    sql_query.addBindValue(prescription_id);

    return sql_query.exec();
}

bool add_prescriptions::updatePatient()
{
    // sql update有参数写法参考
    QString update_sql=QString("update patient set account=account-? where id='%1' ").arg(patient_id);
    sql_query.prepare(update_sql);

    //补全sql中的占位符
    sql_query.addBindValue(cost);

    return sql_query.exec();
}
