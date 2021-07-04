#ifndef CHANGE_DEPARTMENT_H
#define CHANGE_DEPARTMENT_H

#include <QSqlQuery>
#include <QSqlError>


class change_department
{
public:
    change_department();

    void setPatient_id(const QString& id);
    void setPatient_name(const QString& name);
    void setPatient_sex(const QString& sex);
    void setPatient_age(const int& age);

    void setPatient_sickroom_cur(const QString& id);
    void setPatient_bed_cur(const int& bed);
    void setDoctor_id_cur(const QString& id);
    void setDoctor_name_cur(const QString& name);
    void setDepartment_name_cur(const QString& name);
    void setDepartment_id_cur(const QString& id);

    void setDepartment_name_tar(const QString& name);
    void setPatient_sickroom_tar(const QString& id);
    void setPatient_bed_tar(const int& bed);
    void setDoctor_id_tar(const QString& id);

    //更新数据库中相关表
    bool updatePatient();
    bool updatePatient_doctor();
    bool updateSickroom_cur();
    bool updateSickroom_tar();

    QSqlQuery update_query;

private:
    QString patient_id;
    QString patient_name;
    QString patient_sex;
    int patient_age;

    QString patient_sickroom_cur;
    int patient_bed_cur;
    QString doctor_id_cur;
    QString doctor_name_cur;
    QString department_id_cur;
    QString department_name_cur;

    QString department_name_tar;
    QString department_id_tar;
    QString patient_sickroom_tar;
    int patient_bed_tar;
    QString doctor_id_tar;
};

#endif // CHANGE_DEPARTMENT_H
