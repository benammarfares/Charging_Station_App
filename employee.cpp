#include "employee.h"
#include <QtWidgets>
#include <QTableWidget>
#include <QSqlError>
#include <mainwindow.h>


employee::employee(QString cin,QString nom,QString prenom,QString email,QString mdp,QString role,float salaire,QDate datedInscription,QString genre)
{   this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->mdp=mdp;
    this->role=role;
    this->salaire=salaire;
    this->datedInscription=datedInscription;
    this->genre=genre;
}
bool employee::ajouter(){
    QSqlQuery query;
    QString res = QString::number(salaire);
    query.prepare("INSERT INTO employe (id_employe, nom, prenom, email, mdp, rolee, salaire, datee, genree) VALUES (:cin, :nom, :prenom, :email, :mdp, :role, :salaire, :datedInscription, :genre)");
    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":mdp", mdp);
    query.bindValue(":role", role);
    query.bindValue(":salaire", res);
    query.bindValue(":datedInscription", datedInscription);
    query.bindValue(":genre", genre);
    return query.exec();
}
bool employee::supprimer(QString id_employe){
    QSqlQuery query;
    query.prepare("DELETE FROM employe WHERE id_employe = :id_employe");
    query.bindValue(":id_employe", id_employe);
    return query.exec();
}


void employee::setcin(const QString n){cin=n;}
void employee::setnom(const QString n){nom=n;}
void employee::setprenom(const QString n){prenom=n;}
void employee::setemail(const QString n){email=n;}
void employee::setmdp(const QString n){mdp=n;}
void employee::setgenre(const QString n){genre=n;}
void employee::setsalaire(float n){salaire=n;}
void employee::setrole(QString n){role=n;}
void employee::setdatedInscription(const QDate n){datedInscription=n;}

QSqlQueryModel * employee::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from employe");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("E-mail"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Mot de passe"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Rôle"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Salaire"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Genre"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date d'inscription"));


    return model;

}


employee recherchemodifier(QString cin );

QString employee::get_nom(){return nom;}
QString employee::get_prenom(){return prenom;}
QString employee::get_cin(){return cin;}
QString employee::get_email(){return email;}
QString employee::get_mdp(){return mdp;}
QString employee::get_role(){ return role;}
QDate employee::get_datedInscription(){return datedInscription;}

float employee::get_salaire(){return salaire;}
QString employee::get_genre(){return genre;}


bool employee::recherche(QString id_employe ){
QSqlQuery query;
query.prepare("select * from employe where id_employe= :id_employe");
query.bindValue(":id_employe",id_employe);
query.exec();
    if (query.next()) {
        return true; // Utilisateur trouvé
    } else {
        return false; // Utilisateur non trouvé
    }
}

bool employee::modifier()
{
    QSqlQuery query;
    QString res = QString::number(salaire);
    query.prepare("UPDATE employe SET id_employe = :id_employe, nom = :nom, prenom = :prenom, email = :email, mdp = :mdp, rolee = :rolee, salaire = :salaire, datee = :datee, genree = :genre "
                  "WHERE id_employe = :id_employe");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":mdp", mdp);
    query.bindValue(":rolee", role);
    query.bindValue(":salaire", res);
    query.bindValue(":datee", datedInscription);
    query.bindValue(":genre", genre);
    query.bindValue(":id_employe", cin);
    return query.exec();
}
QSqlQueryModel* employee::afficherTriNom()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe ORDER BY LOWER(nom) ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("E-mail"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Rôle"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'inscription"));
    return model;
}
QSqlQueryModel* employee::afficherTriCin()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe ORDER BY id_employe ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("E-mail"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Rôle"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'inscription"));

    return model;
}
QSqlQueryModel* employee::afficherTriNomd()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe ORDER BY LOWER(nom) DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("E-mail"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Rôle"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'inscription"));
    return model;
}
QSqlQueryModel* employee::afficherTrisalaired()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe ORDER BY salaire ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("E-mail"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Rôle"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'inscription"));

    return model;
}
QSqlQueryModel* employee::afficherTrisalaire()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe ORDER BY salaire DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("E-mail"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Rôle"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'inscription"));

    return model;
}
employee employee::recherchee(QString id_employe){
    QSqlQuery query;
    query.prepare("SELECT * FROM employe WHERE id_employe = :id_employe");
    query.bindValue(":id_employe", id_employe);
    query.exec();
    if (query.next()) {
        // Récupérer les valeurs des champs de la ligne sélectionnée
        QString id_employe = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        QString email = query.value(3).toString();
        QString mdp = query.value(4).toString();
        QDate date = query.value(5).toDate();

        float salaire = query.value(6).toFloat();
        QString role = query.value(7).toString();
        QString genre = query.value(8).toString();

        // Créer un objet Utilisateur avec les valeurs récupérées
        employee emp;
        emp.cin=id_employe;
        emp.nom=nom;
        emp.prenom=prenom;
        emp.email=email;
        emp.mdp=mdp;
        emp.salaire=salaire;
        emp.role=role;
        emp.datedInscription=date;
        emp.genre=genre;
        return emp;
    } else {
        // Aucun utilisateur trouvé avec ce cin
        // Retourner un objet Utilisateur vide ou lever une exception
        employee employe;
        return employe;
    }
}
