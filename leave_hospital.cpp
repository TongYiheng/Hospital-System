#include "leave_hospital.h"

#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>


leave_hospital::leave_hospital() {}

void leave_hospital::setPatient_id(const QString& id) {patient_id=id;}
void leave_hospital::setAmount(const double& money) {amount=money;}

bool leave_hospital::updateSickroom()
{
    //查询病人的病房号
    QSqlQuery query;
    QString select_str = QString("select sickroom_id from patient where id='%1' ").arg(patient_id);
    query.exec(select_str);
    while(query.next())
        sickroom_id=query.value(0).toString();

    //更新sickroom表的信息
    QString update_sql=QString("update sickroom set patient_number=patient_number-1 where id='%1' ").arg(sickroom_id);
    return sql_query.exec(update_sql);
}

bool leave_hospital::deletePatient()
{
    //删除patient表的信息
    QString delete_sql=QString("delete from patient where id='%1' ").arg(patient_id);
    return sql_query.exec(delete_sql);
}

bool leave_hospital::deletePatient_doctor()
{
    //删除patient_doctor表的信息
    QString delete_sql=QString("delete from patient_doctor where patient_id='%1' ").arg(patient_id);
    return sql_query.exec(delete_sql);
}

bool leave_hospital::deletePatient_inspection()
{
    //删除patient_inspection表的信息
    QString delete_sql=QString("delete from patient_inspection where patient_id='%1' ").arg(patient_id);
    return sql_query.exec(delete_sql);
}

bool leave_hospital::deletePatient_prescription()
{
    //删除patient_prescription表的信息
    QString delete_sql=QString("delete from patient_prescription where patient_id='%1' ").arg(patient_id);
    return sql_query.exec(delete_sql);
}

bool leave_hospital::deletePatient_payment()
{
    //删除patient_payment表的信息
    QString delete_sql=QString("delete from patient_payment where patient_id='%1' ").arg(patient_id);
    return sql_query.exec(delete_sql);
}

bool leave_hospital::insertPayback()
{
    QString insert_sql = "insert into payback(id, patient_id, amount, time) values (null,?,?,?)";

    sql_query.prepare(insert_sql);

    //补全sql中的占位符
    sql_query.addBindValue(patient_id);
    sql_query.addBindValue(amount);
    sql_query.addBindValue(QDateTime::currentDateTime());

    return sql_query.exec();
}

bool leave_hospital::dropUser()
{
    QString drop_sql=QString("drop user '%1'@'localhost' ").arg(patient_id);
    return sql_query.exec(drop_sql);
}
