#ifndef LEAVE_HOSPITAL_H
#define LEAVE_HOSPITAL_H

#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>

class leave_hospital
{
public:
    leave_hospital();
    void setPatient_id(const QString& id);
    void setAmount(const double& money);
    bool updateSickroom();
    bool deletePatient();
    bool deletePatient_doctor();
    bool deletePatient_inspection();
    bool deletePatient_prescription();
    bool deletePatient_payment();
    bool insertPayback();
    bool dropUser();
    QSqlQuery sql_query;
private:
    QString patient_id;
    QString sickroom_id;
    double amount;
};

#endif // LEAVE_HOSPITAL_H
