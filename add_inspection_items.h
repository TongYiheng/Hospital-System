#ifndef ADD_INSPECTION_ITEMS_H
#define ADD_INSPECTION_ITEMS_H

#include <QSqlQuery>
#include <QSqlError>

class add_inspection_items
{
public:
    add_inspection_items();
    void setInspection_id(const QString& id);
    void setInspection_content(const QString& content);
    void setPatient_id(const QString& id);
    void setPlace(const QString& theplace);
    void setCost(const double& thecost);
    bool insertDataToInspection_items();
    bool insertDataToPatient_inspection();
    bool updatePatient();
    QSqlQuery sql_query;
private:
    QString inspection_id;
    QString inspection_content;
    QString patient_id;
    QString place;
    double cost;
};

#endif // ADD_INSPECTION_ITEMS_H
