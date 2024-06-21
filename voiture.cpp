#include "voiture.h"
#include <QtWidgets>
#include <QSqlQuery>
#include <QtSql>
#include <QString>
#include <QSqlQueryModel>
#include <QtPrintSupport/QPrinter>
#include <QObject>


voiture::voiture()
{
id="";
model="";
license="";
batteryLvl="";
batteryCap="";
etat="";
quantite="";
}

voiture::voiture(QString id,QString model,QString license,QString batteryLvl,QString batteryCap,QString etat,QString quantite)
{
    this->id=id;
    this->model=model;
    this->license=license;
    this->batteryLvl=batteryLvl;
    this->batteryCap=batteryCap;
    this->etat=etat;
    this->quantite=quantite;

}






void voiture::setId(QString n){this->id=n;}
void voiture::setModel(QString n){this->model=n;}
void voiture::setLicensePlate(QString n){this->license=n;}
void voiture::setBatteryLvl(QString n){this->batteryLvl=n;}
void voiture::setBatterCap(QString n){batteryCap=n;}
void voiture::setEtat(QString n){this->etat=n;}
void voiture::setQuantite(QString n){this->quantite=n;}


QString voiture::get_id(){return id;}
QString voiture::get_model(){return model;}
QString voiture::get_licensePlate(){return license;}
QString voiture::get_batteryLvl(){return batteryLvl;}
QString voiture::get_BatterCap(){return batteryCap;}
QString voiture::get_Etat(){return etat;}
QString voiture::get_Quantite(){return quantite;}



bool voiture::idExists(int id2)
{
    QSqlQuery query;
    query.prepare("SELECT ID_VOITURE FROM VOITURE WHERE ID_VOITURE=:id");
    query.bindValue(":id", id2);
    if (query.exec()) {
        if (query.next()) {
            return true;
        }
    }
    // ID does not exist in the database
    return false;
}


bool voiture::insert()
{
    QSqlQuery query;

    query.prepare("INSERT INTO VOITURE (ID_VOITURE, MATRICULE, BATTERIE_LVL, BATTERIE_CAP, MODEL, ETAT, QUNATITE, DATE_VOITURE) "
      "VALUES (:id_voiture, :matricule, :batteryLvl, :batteryCap, :model, :etat, :quantite, :date_voiture)");
    query.bindValue(":id_voiture", id);
    query.bindValue(":matricule", license);
    query.bindValue(":batteryLvl", batteryLvl);
    query.bindValue(":batteryCap",batteryCap);
    query.bindValue(":model",  model);
    query.bindValue(":etat", etat);
    query.bindValue(":quantite",quantite);
    query.bindValue(":date_voiture",QDateTime::currentDateTime());

    if (query.exec()) {
        qDebug() << "New voiture inserted successfully";
    } else {
        qDebug() << "Failed to insert new voiture";
        qDebug() << "Error:" << query.lastError().text();
    }
}




bool voiture::delete_voiture(int id1) {
    QSqlQuery query;
    QString res = QString::number(id1);
    query.prepare("Delete from VOITURE where ID_VOITURE= :id1");
    query.bindValue(":id1", res);
    return query.exec();
}


QSqlQueryModel * voiture::afficher_voiture(){
QSqlQueryModel *model=new QSqlQueryModel();

model->setQuery("select *from VOITURE");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_VOITURE"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_CLIENT"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("ID_MAINTENANCE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("MATRICULE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("BATTERIE_LVL"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("BATTERIE_CAP"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("MODEL"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("ETAT"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("QUANTITE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("ID_SESSION"));


return model;


}




bool voiture::update(QString id){
    QSqlQuery query;
        query.prepare("UPDATE VOITURE SET MATRICULE=:matricule, BATTERIE_LVL=:batterieLvl, BATTERIE_CAP=:batterieCap, MODEL=:model, ETAT=:etat, QUANTITE=:quantite WHERE ID_VOITURE=:id");
        query.bindValue(":id", id);
        query.bindValue(":matricule", license);
        query.bindValue(":batterieLvl", batteryLvl);
        query.bindValue(":batterieCap", batteryCap);
        query.bindValue(":model", model);
        query.bindValue(":etat", etat);
        query.bindValue(":quantite", quantite);
    if (query.exec()) {
        qDebug() << "Voiture updated successfully";
        return true;
    } else {
        qDebug() << "Failed to update voiture";
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }
}



