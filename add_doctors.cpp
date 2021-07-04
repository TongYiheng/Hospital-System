#include "add_doctors.h"

#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


add_doctors::add_doctors() {}

void add_doctors::setDoctor_id(const QString &id) {doctor_id=id;}
void add_doctors::setDoctor_name(const QString &name) {doctor_name=name;}
void add_doctors::setDoctor_sex(const QString &sex) {doctor_sex=sex;}
void add_doctors::setDoctor_age(const int &age) {doctor_age=age;}
void add_doctors::setDoctor_phone(const QString &phone) {doctor_phone=phone;}
void add_doctors::setDoctor_department(const QString &department) {department_name=department;}
void add_doctors::setDoctor_professional(const QString &professional) {doctor_professional=professional;}

bool add_doctors::insertDataToDoctor()
{
    //查询该科室的id
    QSqlQuery query;
    QString select_str = QString("select id from department where name='%1' ").arg(department_name);
    query.exec(select_str);
    while(query.next())
        department_id=query.value(0).toString();

    // sql insert 有参数写法参考
    QString insert_sql = "insert into doctor(id, name, sex, age, phone, department, professional) values (?,?,?,?,?,?,?)";
    sql_query.prepare(insert_sql);

    //补全sql中的占位符
    sql_query.addBindValue(doctor_id);
    sql_query.addBindValue(doctor_name);
    sql_query.addBindValue(doctor_sex);
    sql_query.addBindValue(doctor_age);
    sql_query.addBindValue(doctor_phone);
    sql_query.addBindValue(department_id);
    sql_query.addBindValue(doctor_professional);

    return sql_query.exec();
}

