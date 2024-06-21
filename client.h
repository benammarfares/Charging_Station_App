#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
class client
{
public:
    client();
    client(int,QString,QString,int,QString,int,QString,int,int);
    //setters
    void setID(int id);
    void setnom(QString nom);
    void setprenom(QString prenom);
    void setcin(int cin);
    void setadresse(QString adresse);
    void settelephone(int telephone);
    void setemail(QString email);
    void setbonus(int bonus);
    void setreclamation(int reclamation);
    //getters
    int get_id();
    QString get_nom();
    QString get_prenom();
    int get_cin();
    QString get_adresse();
    int get_telephone();
    QString get_email();
    int get_bonus();
    int get_reclamation();

    //functions
    bool ajouter_client();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_c();
    QSqlQueryModel* afficher_d();
    QSqlQueryModel* afficher_search(QString);
    bool supprimer_client(int);
    bool modifier_client(int);
    bool update_bonus(int);
    bool ajouter_averti(int,int);
    int reduction_averti(int,int);
    bool happy_hour(int);
    void pdf();
    bool delete_all();
    bool test_maintenance(int);
private:
    QString nom,prenom,adresse,email;
    int id,bonus,reclamation,cin,telephone;
};




#endif // VOITURE_H


