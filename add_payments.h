#ifndef ADD_PAYMENTS_H
#define ADD_PAYMENTS_H

#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>

class add_payments
{
public:
    add_payments();
    void setPayment_id(const QString& id);
    void setPatient_id(const QString& id);
    void setMoney(const double& theMoney);
    bool insertPayment();
    bool insertPatient_payment();
    bool updatePatient();
    QSqlQuery sql_query;

private:
    QString payment_id;
    QString patient_id;
    double money;
};

#endif // ADD_PAYMENTS_H
