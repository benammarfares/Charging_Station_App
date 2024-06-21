#ifndef MAINTENANCE_H
#define MAINTENANCE_H
#include <QString>
#include <QDialog>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableWidget>


class maintenance
{public:
    void setid(QString n);
 void setdate(QDateTime dt);
    void settype(QString n);
    void setdescription(QString n);
    void setcout(QString n);
    void setduree(QString n);
    QString get_id();
    QDateTime get_date();
    QString get_type();
    QString get_description();
    QString get_cout();
    QString get_duree();
    maintenance();
    void setmaintenance(maintenance m);
bool insert(maintenance& m);
bool delete_allmaintenance();
bool delete_maintenance(int id1);
bool isValidDT(QDateTime previousDateTime, QDateTime selectedDateTime, int durationSeconds);
bool test_maintenance(int id );
QSqlQueryModel* afficher_maintenance();
bool update_maintenance(maintenance m,QTableWidget *tableWidget);
bool id_exist(int id);
void trier_par_id_maintenance();
void telechargerPDF();
QSqlQueryModel * afficher_search_result(QString ch);
QSqlQueryModel * afficher_id_decroissant();
   QSqlQueryModel * afficher_id_croissant();

private:
    QString id_maintenance,type,description,cout,duree;
    QDateTime date_hr ;
};
#endif // MAINTENANCE_H
