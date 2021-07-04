#include "change_department.h"

#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

change_department::change_department() {}

void change_department::setPatient_id(const QString& id) {patient_id=id;}

void change_department::setPatient_name(const QString& name) {patient_name=name;}
void change_department::setPatient_sex(const QString& sex) {patient_sex=sex;}
void change_department::setPatient_age(const int& age) {patient_age=age;}

void change_department::setPatient_sickroom_cur(const QString& id) {patient_sickroom_cur=id;}
void change_department::setPatient_bed_cur(const int& bed) {patient_bed_cur=bed;}
void change_department::setDoctor_id_cur(const QString& id) {doctor_id_cur=id;}
void change_department::setDoctor_name_cur(const QString& name) {doctor_name_cur=name;}
void change_department::setDepartment_name_cur(const QString& name) {department_name_cur=name;}
void change_department::setDepartment_id_cur(const QString& id) {department_id_cur=id;}

void change_department::setDepartment_name_tar(const QString& name) {department_name_tar=name;}
void change_department::setPatient_sickroom_tar(const QString& id) {patient_sickroom_tar=id;}
void change_department::setPatient_bed_tar(const int &bed) {patient_bed_tar=bed;}
void change_department::setDoctor_id_tar(const QString& id) {doctor_id_tar=id;}

bool change_department::updatePatient()
{
    // sql update有参数写法参考
    QString update_sql=QString("update patient set sickroom_id=?,bed_id=? where id='%1' ").arg(patient_id);
    update_query.prepare(update_sql);

    //补全sql中的占位符
    update_query.addBindValue(patient_sickroom_tar);
    update_query.addBindValue(patient_bed_tar);

    return update_query.exec();
}

bool change_department::updatePatient_doctor()
{
    // sql update有参数写法参考
    QString update_sql=QString("update patient_doctor set doctor_id=? where patient_id='%1' ").arg(patient_id);
    update_query.prepare(update_sql);

    //补全sql中的占位符
    update_query.addBindValue(doctor_id_tar);

    return update_query.exec();
}

bool change_department::updateSickroom_cur()
{
    // sql update有参数写法参考
    QString update_sql=QString("update sickroom set patient_number=patient_number-1 where id='%1' ").arg(patient_sickroom_cur);

    return update_query.exec(update_sql);
}

bool change_department::updateSickroom_tar()
{
    // sql update有参数写法参考
    QString update_sql=QString("update sickroom set patient_number=patient_number+1 where id='%1' ").arg(patient_sickroom_tar);

    return update_query.exec(update_sql);
}
