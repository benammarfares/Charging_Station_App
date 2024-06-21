#include "maintenance.h"
#include "mainwindow.h"
#include <QtWidgets>
#include <QMessageBox>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QtSql>
#include <QString>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <vector>











maintenance::maintenance()
{
    id_maintenance="";
type="";
date_hr =QDateTime::currentDateTime();
description="";
cout="";
duree="";
}
void maintenance::setid(QString n){id_maintenance=n;}
void maintenance::settype(QString n){type=n;}
void maintenance::setdate(QDateTime dt){date_hr=dt;}
void maintenance::setdescription(QString n){description=n;}
void maintenance::setcout(QString n){cout=n;}
void maintenance::setduree(QString n){duree=n;}



bool maintenance::id_exist(int id2)
{
    QSqlQuery query;
    query.prepare("SELECT ID_MAINTENANCE FROM MAINTENANCE WHERE ID_MAINTENANCE=:id_maintenance");
    query.bindValue(":id_maintenance", id2);
        if (query.exec()) {
        if (query.next()) {
            return true;
        }
    }
    // ID does not exist in the database
return false;
}
QString maintenance::get_id(){return id_maintenance;}
QDateTime maintenance::get_date(){return date_hr;}
QString maintenance::get_type(){return type;}
QString maintenance::get_description(){return description;}
QString maintenance::get_cout(){return cout;}
QString maintenance::get_duree(){return duree;}

bool maintenance::insert(maintenance& m)
{
    QSqlQuery query ;
 query.prepare("INSERT INTO MAINTENANCE (ID_MAINTENANCE ,DATE_HR , TYPE , DESCRIPTION ,COUT , DUREE)"
  "VALUES (:id_maintenance , :date_hr, :type , :description , :cout , :duree)");
 query.bindValue(":id_maintenance", m.get_id());
  query.bindValue(":date_hr", m.get_date());
  query.bindValue(":type", m.get_type());
  query.bindValue(":description", m.get_description());
  query.bindValue(":cout", m.get_cout());
  query.bindValue(":duree", m.get_duree());
  if (query.exec())
  {
      qDebug() << "New Maintenance inserted !!";
  }
  else
  {
      qDebug() << "Failed to insert new Maintenance";
              qDebug() << "Error:" << query.lastError().text();
  }
}

bool maintenance::delete_allmaintenance() {
    QSqlQuery query;
    query.prepare("Delete from MAINTENANCE ");
    return query.exec();
}

bool maintenance::delete_maintenance(int id1) {
    if (!id_exist(id1)) {
           return false; // ID does not exist in the database
       }
    QSqlQuery query;
    QString res = QString::number(id1);
    query.prepare("Delete from MAINTENANCE where ID_MAINTENANCE=:id1");
    query.bindValue(":id1", res);
    return query.exec();
}
QSqlQueryModel * maintenance::afficher_maintenance(){
QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select *from MAINTENANCE");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_MAINTENANCE"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_HR"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPEE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("COUT"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DUREE"));
return model;
}

QSqlQueryModel * maintenance::afficher_search_result(QString ch)
{
 // int x=ch.toInt();
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from MAINTENANCE where ID_MAINTENANCE LIKE '%"+ch+"%'");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_MAINTENANCE"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_HR"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPEE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("COUT"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DUREE"));
return model;}

QSqlQueryModel * maintenance::afficher_id_decroissant()
{
  QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from MAINTENANCE order by ID_MAINTENANCE DESC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_MAINTENANCE"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_HR"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("COUT"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DUREE"));
return model;}



QSqlQueryModel * maintenance::afficher_id_croissant()
{
  QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from MAINTENANCE order by ID_MAINTENANCE ASC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_MAINTENANCE"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_HR"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("COUT"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DUREE"));
return model;}



bool maintenance::update_maintenance(maintenance m, QTableWidget *tableWidget)
{
    int id = m.get_id().toInt();
        if (!id_exist(id)) {
            qDebug() << "Failed to update maintenance. Invalid ID.";
            return false;
        }
    QSqlQuery query;
    query.prepare("UPDATE MAINTENANCE SET TYPE=:type,DATE_HR=:date_hr, DESCRIPTION=:description, COUT=:cout, DUREE=:duree  WHERE ID_MAINTENANCE=:id_maintenance");
    query.bindValue(":id_maintenance", m.get_id());
    query.bindValue(":type", m.get_type());
    query.bindValue(":date_hr", m.get_date());
    query.bindValue(":description", m.get_description());
    query.bindValue(":cout", m.get_cout());
    query.bindValue(":duree", m.get_duree());
    if (query.exec()) {
        qDebug() << "Maintenance updated successfully";
        // Update the values in the tableWidget
               int row = tableWidget->rowCount() - 1;
               QTableWidgetItem *item;

               // Update the type
               item = new QTableWidgetItem(m.get_type());
               tableWidget->setItem(row, 1, item);

               // Update the date
               item = new QTableWidgetItem(m.get_date().toString("yyyy-MM-dd hh:mm:ss"));
               tableWidget->setItem(row, 2, item);

               // Update the description
               item = new QTableWidgetItem(m.get_description());
               tableWidget->setItem(row, 3, item);

               // Update the cost
               item = new QTableWidgetItem(m.get_cout());
               tableWidget->setItem(row, 4, item);

               // Update the duration
               item = new QTableWidgetItem(m.get_duree());
               tableWidget->setItem(row, 5, item);
        return true;
    } else {
        qDebug() << "Failed to update maintenance";
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }
}

void maintenance::telechargerPDF()
{
    QPdfWriter pdf("C:/Users/bouch/exporter.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::green);
    painter.setFont(QFont("Arial",30));
    painter.drawText(1100,1200,"GESTION MAINTENANCES");
    painter.setPen(Qt::Key_Green);
    painter.setFont(QFont("Arial",14));
    painter.drawRect(100,100,9600,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Arial",11));
    painter.drawText(200,3300,"ID");
    painter.drawText(800,3300,"Date");
    painter.drawText(2590,3300,"Type");
    painter.drawText(4500,3300,"Description");
    painter.drawText(6600,3300,"Coût");
    painter.drawText(8800,3300,"Durée");

    QSqlQuery query;
    query.prepare("select * from MAINTENANCE");
    query.exec();
    while (query.next())
    {
        painter.drawText(200,i,query.value(0).toString());
        painter.drawText(800,i,query.value(1).toString());
        painter.drawText(2590,i,query.value(2).toString());
        painter.drawText(4500,i,query.value(3).toString());
        painter.drawText(6600,i,query.value(4).toString());
        painter.drawText(8800,i,query.value(5).toString());
        i = i + 500;
    }
}

bool maintenance::isValidDT(QDateTime previousDateTime, QDateTime selectedDateTime, int durationSeconds) {

    QSqlQuery query;
   // query.prepare("SELECT DATE_HR FROM MAINTENANCE ORDER BY DATE_HR DESC LIMIT 1;");
   //query.prepare("SELECT DATE_HR FROM MAINTENANCE ORDER BY date_hr DESC LIMIT 1;");
query.prepare("SELECT DATE_HR FROM (SELECT DATE_HR FROM MAINTENANCE ORDER BY DATE_HR DESC) WHERE ROWNUM = 1;");

    if (!query.exec() || !query.next()) {
           QMessageBox::warning(nullptr, "Error", "Failed to retrieve previous maintenance record");
           return false;
       }
       previousDateTime = query.value(0).toDateTime();

    // Calculate the ready time
    QDateTime readyDateTime = selectedDateTime.addSecs(durationSeconds);

    // Check if the selected date and time is after the ready time
    if (selectedDateTime >= readyDateTime) {
        return false;
    }

    // Check if the selected date and time is after the previous date and time
    if (selectedDateTime <= previousDateTime) {
        return false;
    }

    return false;
}

bool maintenance ::test_maintenance(int id){
    QSqlQuery query;
    query.prepare("SELECT ID_MAINTENANCE FROM MAINTENANCE WHERE ID_MAINTENANCE=:idd");
    query.bindValue(":idd", id);
    query.exec();
        if (query.next()){
            return true;
        }
    else
        {
        return false;
}
}
