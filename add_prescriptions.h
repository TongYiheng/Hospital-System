#ifndef ADD_PRESCRIPTIONS_H
#define ADD_PRESCRIPTIONS_H

#include <QSqlQuery>
#include <QSqlError>

class add_prescriptions
{
public:
    add_prescriptions();
    void setPrescription_id(const QString& id);
    void setPrescription_content(const QString& content);
    void setDoctor_id(const QString& id);
    void setPatient_id(const QString& id);
    void setCost(const double& thecost);
    bool insertDataToPrescription();
    bool insertDataToPatient_prescription();
    bool updatePatient();
    QSqlQuery sql_query;
private:
    QString prescription_id;
    QString prescription_content;
    QString doctor_id;
    QString patient_id;
    double cost;
};

#endif // ADD_PRESCRIPTIONS_H
