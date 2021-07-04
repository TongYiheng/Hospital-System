#ifndef ADD_DOCTORS_H
#define ADD_DOCTORS_H

#include <QSqlQuery>
#include <QSqlError>

class add_doctors
{
public:
    add_doctors();
    void setDoctor_id(const QString& id);
    void setDoctor_name(const QString& name);
    void setDoctor_sex(const QString& sex);
    void setDoctor_age(const int& age);
    void setDoctor_phone(const QString& phone);
    void setDoctor_department(const QString& department);
    void setDoctor_professional(const QString& professional);
    bool insertDataToDoctor();
    QSqlQuery sql_query;
private:
    QString doctor_id;
    QString doctor_name;
    QString doctor_sex;
    int doctor_age;
    QString doctor_phone;
    QString department_id;
    QString department_name;
    QString doctor_professional;
};

#endif // ADD_DOCTORS_H
