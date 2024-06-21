#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QString>
#include <QSqlQueryModel>
#include <QObject>
#include <QPdfWriter>
#include <QPainter>
client::client()
{
    nom="";
    prenom="";
    telephone=0;
    adresse="";
    id=0;
    bonus=0;
    reclamation=0;
    email="";
    cin=0;
}
client::client(int id,QString nom,QString prenom,int cin,QString adresse,int telephone,QString email,int bonus,int reclamation)
{
    this->id=id;
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->adresse=adresse;
    this->bonus=bonus;
    this->telephone=telephone;
    this->reclamation=reclamation;
}

//set
void client::setID(int id){this->id=id;}
void client::setnom(QString nom){this->nom=nom;}
void client::setprenom(QString prenom){this->prenom=prenom;}
void client::setcin(int cin){this->cin=cin;}
void client::setadresse(QString adresse){this->adresse=adresse;}
void client::settelephone(int telephone){this->telephone=telephone;}
void client::setemail(QString email){this->email=email;}
void client::setbonus(int bonus){this->bonus=bonus;}
void client::setreclamation(int reclamation){this->reclamation=reclamation;}



//get
int client::get_id(){return id;}
QString client::get_nom(){return nom;}
QString client::get_prenom(){return prenom;}
int client::get_cin(){return cin;}
QString client::get_adresse(){return adresse;}
int client::get_telephone(){return telephone;}
QString client::get_email(){return email;}
int client::get_bonus(){return bonus;}
int client::get_reclamation(){return reclamation;}


//functions

bool client::ajouter_client()
{
    QString id_string= QString::number(id);
    QString id_cin= QString::number(cin);
    QString id_bonus= QString::number(bonus);
    QString id_reclamation= QString::number(reclamation);
    QString id_telephone= QString::number(telephone);
    QSqlQuery query;
          query.prepare("INSERT INTO client (ID_CLIENT, NOM, PRENOM, CIN, ADRESSE, TELEPHONE, EMAIL, BONUS, RECLAMATION) "
                        "VALUES (:id, :nom, :prenom, :cin, :adresse, :telephone, :email, :bonus, :reclamation)");
          query.bindValue(":id", id_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":cin", cin);
          query.bindValue(":adresse", adresse);
          query.bindValue(":telephone", telephone);
          query.bindValue(":email", email);
          query.bindValue(":bonus", bonus);
          query.bindValue(":reclamation", reclamation);
          return query.exec();
}


QSqlQueryModel* client::afficher()
{
    QSqlQueryModel* Model= new QSqlQueryModel();
          Model->setQuery("SELECT* FROM client");
          Model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          Model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          Model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
          Model->setHeaderData(3, Qt::Horizontal, QObject::tr("Cin"));
          Model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
          Model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
          Model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
          Model->setHeaderData(7, Qt::Horizontal, QObject::tr("Bonus (DT)"));
          Model->setHeaderData(8, Qt::Horizontal, QObject::tr("Reclamation"));
    return Model;
}


QSqlQueryModel* client::afficher_d()
{
    QSqlQueryModel* Model= new QSqlQueryModel();
          Model->setQuery("SELECT* FROM client order by ID_CLIENT DESC");
          Model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          Model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          Model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
          Model->setHeaderData(3, Qt::Horizontal, QObject::tr("Cin"));
          Model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
          Model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
          Model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
          Model->setHeaderData(7, Qt::Horizontal, QObject::tr("Bonus (DT)"));
          Model->setHeaderData(8, Qt::Horizontal, QObject::tr("Reclamation"));
    return Model;
}


QSqlQueryModel* client::afficher_c()
{
    QSqlQueryModel* Model= new QSqlQueryModel();
          Model->setQuery("SELECT* FROM client order by ID_CLIENT ASC");
          Model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          Model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          Model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
          Model->setHeaderData(3, Qt::Horizontal, QObject::tr("Cin"));
          Model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
          Model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
          Model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
          Model->setHeaderData(7, Qt::Horizontal, QObject::tr("Bonus (DT)"));
          Model->setHeaderData(8, Qt::Horizontal, QObject::tr("Reclamation"));
    return Model;
}


bool client::supprimer_client(int id)
{
          QSqlQuery query;
          query.prepare("DELETE FROM CLIENT WHERE ID_CLIENT=:id");
          query.bindValue(0, id);
          return query.exec();
}


bool client::modifier_client(int id)
{
          QSqlQuery query;
          QString id_string= QString::number(id);
          QString id_cin= QString::number(cin);
          QString id_bonus= QString::number(bonus);
          QString id_reclamation= QString::number(reclamation);
          QString id_telephone= QString::number(telephone);
          query.prepare("UPDATE CLIENT SET ID_CLIENT=:id , NOM=:nom , PRENOM=:prenom , CIN=:cin , ADRESSE=:adresse , TELEPHONE=:telephone , EMAIL=:email WHERE ID_CLIENT=:id");
          query.bindValue(":id", id_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":cin", id_cin);
          query.bindValue(":adresse", adresse);
          query.bindValue(":telephone", id_telephone);
          query.bindValue(":email", email);
          return query.exec();

}


bool client::ajouter_averti(int id,int recl)
{
    QSqlQuery query;
    int r;
    QString id_string= QString::number(id);
    //QString id_reclamation= QString::number(recl);
    //QString id_reclamation= QString::number(reclamation);

    //reclamation
    query.prepare("SELECT* FROM client WHERE ID_CLIENT=:id");
    query.bindValue(":id", id);
    query.exec();
    while (query.next()) {
         r=query.value("RECLAMATION").toInt();
    }
    recl=recl+r;
    //update reclamation
    query.prepare("UPDATE CLIENT SET RECLAMATION=:reclamation WHERE ID_CLIENT=:id");
    query.bindValue(":reclamation", recl);
    query.bindValue(":id", id);
    return query.exec();
}


int client::reduction_averti(int id,int recl)
    {
        QSqlQuery query;
       int b=0,r=0;
        QString id_string= QString::number(id);
        //QString id_reclamation= QString::number(recl);
        //QString id_reclamation= QString::number(reclamation);
        query.prepare("SELECT* FROM client WHERE ID_CLIENT=:id");
        query.bindValue(":id", id);
        query.exec();
        while (query.next()) {
             b=query.value("BONUS").toInt();
             //recl = query.value("RECLAMATION").toInt();
             b=b-(recl*2);
        }
        query.prepare("UPDATE CLIENT SET BONUS=:bonus WHERE ID_CLIENT=:id");
        query.bindValue(":bonus", b);
        query.bindValue(":id", id);
        query.exec();
        return r;
    }


bool client::update_bonus(int id)
{
    QSqlQuery query;
    int bon=0,qte=0;
    QString id_string= QString::number(id);
    //QString id_reclamation= QString::number(recl);
    //QString id_reclamation= QString::number(reclamation);
    //quantité
    query.prepare("SELECT * FROM VOITURE JOIN CLIENT ON VOITURE.ID_CLIENT=CLIENT.ID_CLIENT WHERE VOITURE.ID_CLIENT=:id");
    query.bindValue(":id", id);
    query.exec();
    while (query.next()) {
        qte = query.value("QUNATITE").toInt();
    }
    //bonus
    query.prepare("SELECT* FROM client WHERE ID_CLIENT=:id");
    query.bindValue(":id", id);
    query.exec();
    while (query.next()) {
         bon=query.value("BONUS").toInt();
    }
    bon=bon+(qte*3);
    qDebug() << "bon =" << bon;

    //update bonus
    query.prepare("UPDATE CLIENT SET BONUS=:bonus WHERE ID_CLIENT=:id");
    query.bindValue(":bonus", bon);
    query.bindValue(":id", id);
    query.exec();
    //
    query.prepare("UPDATE VOITURE SET QUNATITE=:quantite WHERE ID_CLIENT=:id");
    query.bindValue(":quantite", 0);
    query.bindValue(":id", id);
    query.exec();
}


bool client::happy_hour(int id)
{
    QSqlQuery query;
    int recl;
    query.prepare("SELECT* FROM client WHERE ID_CLIENT=:id");
    query.bindValue(":id", id);
    query.exec();
    while (query.next()) {
         recl=query.value("RECLAMATION").toInt();
         qDebug()<<"hello"<<recl;
    }
    if (recl<15)
    {
       return true;
    }
    else{ return false;}
}


void client::pdf()
{
    QPdfWriter pdf("C:/Users/youss/OneDrive/Documents/Pro/work.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::green);
    painter.setFont(QFont("Arial",30));
    painter.drawText(2400,1600,"GESTION CLIENT");
    painter.setPen(Qt::Key_Blue);
    painter.setFont(QFont("Arial",14));
    painter.drawRect(100,100,9600,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Arial",11));
    painter.drawText(200,3300,"ID");
    painter.drawText(800,3300,"NOM");
    painter.drawText(1600,3300,"PRENOM");
    painter.drawText(2800,3300,"CIN");
    painter.drawText(3500,3300,"ADRESSE");
    painter.drawText(4600,3300,"TELEPHONE");
    painter.drawText(6000,3300,"EMAIL");
    painter.drawText(6900,3300,"BONUS");
    painter.drawText(7800,3300,"RECLAMATION");



    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT");
    query.exec();
    while (query.next())
    {
        painter.drawText(200,i,query.value(0).toString());
        painter.drawText(800,i,query.value(1).toString());
        painter.drawText(1800,i,query.value(2).toString());
        painter.drawText(2800,i,query.value(3).toString());
        painter.drawText(3500,i,query.value(4).toString());
        painter.drawText(4500,i,query.value(5).toString());
        painter.drawText(6000,i,query.value(6).toString());
        painter.drawText(7000,i,query.value(7).toString());
        painter.drawText(7800,i,query.value(8).toString());
        i = i + 500;
    }
}


QSqlQueryModel * client::afficher_search(QString ch)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * from CLIENT WHERE PRENOM LIKE '%"+ch+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Bonus (DT)"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Reclamation"));
    return model;
}


bool client::delete_all(){
    QSqlQuery query;
    query.prepare("Delete from CLIENT");
    return query.exec();
}

bool client::test_maintenance(int id){
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














