#ifndef ADD_PATIENTS_H
#define ADD_PATIENTS_H


#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>


class add_patients
{
public:
    add_patients();
    void setPatient_id(const QString& id);
    void setPatient_name(const QString& name);
    void setPatient_sex(const QString& sex);
    void setPatient_age(const int& age);
    void setPatient_phone(const QString& phone);
    void setPatient_address(const QString& address);
    void setStart_time();
    void setPatient_sickroom(const QString& sickroom);
    void setPatient_bed(const int& bed);
    void setPatient_account(const double& account);
    void setDoctor_id(const QString& id);
    bool createPatient_user();
    bool grantToUser();
    bool setToUser();
    bool insertDataToPatient();
    bool insertDataToPatient_doctor();
    bool updateSickroom();
    QSqlQuery sql_query;
private:
    QString patient_id;
    QString patient_name;
    QString patient_sex;
    int patient_age;
    QString patient_phone;
    QString patient_address;
    QDateTime start_time;
    QString patient_sickroom;
    int patient_bed;
    double patient_account;
    QString doctor_id;
};

#endif // ADD_PATIENTS_H
