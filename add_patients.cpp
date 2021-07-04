#include "add_patients.h"

#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>


add_patients::add_patients() {}

void add_patients::setPatient_id(const QString &id) {patient_id=id;}
void add_patients::setPatient_name(const QString &name) {patient_name=name;}
void add_patients::setPatient_sex(const QString &sex) {patient_sex=sex;}
void add_patients::setPatient_age(const int &age) {patient_age=age;}
void add_patients::setPatient_phone(const QString &phone) {patient_phone=phone;}
void add_patients::setPatient_address(const QString &address) {patient_address=address;}
void add_patients::setStart_time() {start_time=QDateTime::currentDateTime();}
void add_patients::setPatient_sickroom(const QString &sickroom) {patient_sickroom=sickroom;}
void add_patients::setPatient_bed(const int &bed) {patient_bed=bed;}
void add_patients::setPatient_account(const double &account) {patient_account=account;}
void add_patients::setDoctor_id(const QString &id) {doctor_id=id;}

bool add_patients::createPatient_user()
{//创建用户
    QString password=patient_id.mid(10);
    QString create_sql=QString("create user '%1'@'localhost' identified by '%2' ").arg(patient_id,password);
    return sql_query.exec(create_sql);
}

bool add_patients::grantToUser()
{//授权
    QString grant_sql=QString("grant patient_user to '%1'@'localhost' ").arg(patient_id);
    return sql_query.exec(grant_sql);
}


bool add_patients::setToUser()
{//激活
    QString set_sql=QString("set default role patient_user to '%1'@'localhost' ").arg(patient_id);
    return sql_query.exec(set_sql);
}

bool add_patients::insertDataToPatient()
{
    // sql insert 有参数写法参考
    QString insert_sql = "insert into patient(id, name, sex, age, phone, address, start_time, sickroom_id, bed_id, account) values (?,?,?,?,?,?,?,?,?,?)";

    sql_query.prepare(insert_sql);

    //补全sql中的占位符
    sql_query.addBindValue(patient_id);
    sql_query.addBindValue(patient_name);
    sql_query.addBindValue(patient_sex);
    sql_query.addBindValue(patient_age);
    sql_query.addBindValue(patient_phone);
    sql_query.addBindValue(patient_address);
    sql_query.addBindValue(start_time);
    sql_query.addBindValue(patient_sickroom);
    sql_query.addBindValue(patient_bed);
    sql_query.addBindValue(patient_account);

    return sql_query.exec();
}

bool add_patients::insertDataToPatient_doctor()
{
    // sql insert 有参数写法参考
    QString insert_sql = "insert into patient_doctor(patient_id, doctor_id) values (?,?)";

    sql_query.prepare(insert_sql);

    //补全sql中的占位符
    sql_query.addBindValue(patient_id);
    sql_query.addBindValue(doctor_id);

    return sql_query.exec();
}

bool add_patients::updateSickroom()
{
    // sql update有参数写法参考
    QString update_sql=QString("update sickroom set patient_number=patient_number+1 where id='%1' ").arg(patient_sickroom);

    return sql_query.exec(update_sql);
}
