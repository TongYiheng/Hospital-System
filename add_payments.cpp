#include "add_payments.h"

#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

add_payments::add_payments() {}

void add_payments::setPayment_id(const QString& id) {payment_id=id;}
void add_payments::setPatient_id(const QString& id) {patient_id=id;}
void add_payments::setMoney(const double& theMoney) {money=theMoney;}

bool add_payments::insertPayment()
{
    // sql insert 有参数写法参考
    QString insert_sql = "insert into payment(id, amount, time) values (?,?,?)";

    sql_query.prepare(insert_sql);

    //补全sql中的占位符
    sql_query.addBindValue(payment_id);
    sql_query.addBindValue(money);
    sql_query.addBindValue(QDateTime::currentDateTime());

    return sql_query.exec();
}

bool add_payments::insertPatient_payment()
{
    // sql insert 有参数写法参考
    QString insert_sql = "insert into patient_payment(patient_id,payment_id) values (?,?)";

    sql_query.prepare(insert_sql);

    //补全sql中的占位符
    sql_query.addBindValue(patient_id);
    sql_query.addBindValue(payment_id);

    return sql_query.exec();
}

bool add_payments::updatePatient()
{
    // sql update有参数写法参考
    QString update_sql=QString("update patient set account=account+? where id='%1' ").arg(patient_id);
    sql_query.prepare(update_sql);

    //补全sql中的占位符
    sql_query.addBindValue(money);

    return sql_query.exec();
}
