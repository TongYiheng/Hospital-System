#include "add_inspection_items.h"

#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

add_inspection_items::add_inspection_items() {}

void add_inspection_items::setInspection_id(const QString &id) {inspection_id=id;}
void add_inspection_items::setInspection_content(const QString &content) {inspection_content=content;}
void add_inspection_items::setPatient_id(const QString &id) {patient_id=id;}
void add_inspection_items::setPlace(const QString &theplace) {place=theplace;}
void add_inspection_items::setCost(const double &thecost) {cost=thecost;}

bool add_inspection_items::insertDataToInspection_items()
{
    // sql insert 有参数写法参考
    QString insert_sql = "insert into inspection_items(id, content, cost) values (?,?,?)";

    sql_query.prepare(insert_sql);

    //补全sql中的占位符
    sql_query.addBindValue(inspection_id);
    sql_query.addBindValue(inspection_content);
    sql_query.addBindValue(cost);

    return sql_query.exec();
}

bool add_inspection_items::insertDataToPatient_inspection()
{
    // sql insert 有参数写法参考
    QString insert_sql = "insert into patient_inspection(patient_id, inspection_id, place) values (?,?,?)";

    sql_query.prepare(insert_sql);

    //补全sql中的占位符
    sql_query.addBindValue(patient_id);
    sql_query.addBindValue(inspection_id);
    sql_query.addBindValue(place);

    return sql_query.exec();
}

bool add_inspection_items::updatePatient()
{
    // sql update有参数写法参考
    QString update_sql=QString("update patient set account=account-? where id='%1' ").arg(patient_id);
    sql_query.prepare(update_sql);

    //补全sql中的占位符
    sql_query.addBindValue(cost);

    return sql_query.exec();
}
