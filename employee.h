#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<QString>
#include<QDate>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QTableWidget>


class employee
{
public:


    void setnom(const QString n);
    void setprenom(const QString n);
    void setcin(const QString n);
    void setemail(const QString n);
    void setmdp(const QString n);
    void setrole(QString n);
    void setsalaire(float n);
    void setdatedInscription(const QDate n);
    void setgenre(const QString n);
    void setemployee(employee e);

    QString get_nom();
    QString get_prenom();
    QString get_cin();
    QString get_email();
    QString get_mdp();
    QString get_role();
    float get_salaire();
    QDate get_datedInscription();
    QString get_genre();

    employee(){}
    employee(QString,QString,QString,QString,QString,QString,float,QDate,QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficherTriNom();
    QSqlQueryModel * afficherTriCin();
    QSqlQueryModel * afficherTriNomd();
    QSqlQueryModel * afficherTrisalaire();
    QSqlQueryModel * afficherTrisalaired();

    bool supprimer(QString);
    bool modifier();
    bool recherche(QString cin);
    bool pdf();
    employee recherchee(QString id_employe);

    private:
    QString nom;
    QString prenom;
    QString cin;
    QString email;
    QString mdp;
    QString role;
    float salaire;
    QDate datedInscription;
    QString genre;



};

#endif // EMPLOYEE_H
