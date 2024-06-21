#ifndef VOITURE_H
#define VOITURE_H
#include <QString>
#include <QDialog>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QDateTimeEdit>
class voiture
{
public:
    void setId(QString n);
    void setModel(QString n);
    void setLicensePlate(QString n);
    void setBatteryLvl(QString n);
    void setBatterCap(QString n);
    void setEtat(QString n);
    void setQuantite(QString n);
    QString get_id();
    QString get_model();
    QString get_licensePlate();
    QString get_batteryLvl();
    QString get_BatterCap();
    QString get_Etat();
    QString get_Quantite();
    voiture();
    voiture(QString,QString,QString,QString,QString,QString,QString);
    void setvoiture(voiture v);
    bool insert();
    bool delete_voiture(int id1);
    QSqlQueryModel* afficher_voiture();
    bool update(QString);
    bool idExists(int id);







private:

    QString id,model,license,batteryLvl,batteryCap,etat,quantite ;

    QSqlQueryModel *m_voitureModel;

};




#endif // VOITURE_H


