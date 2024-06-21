#include "login.h"
#include "mainwindow.h"
#include "mainwindow_voiture.h"
#include "mainwindow_maintenance.h"
#include "voiture.h"
#include "maintenance.h"
#include "ui_login.h"
#include <QSqlQuery>
#include <QMainWindow>
#include <QMessageBox>
#include "smtp.h"
#include "employee.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &login::sendMailmdp);

    ui->lineEdit_cinlogin->setValidator(new QRegExpValidator(QRegExp("\\d{8}"), this));

}

login::~login()
{
    delete ui;
}

void login::on_pushButton_login_clicked()
{
    QString id_employe = ui->lineEdit_cinlogin->text();
       QString mdp = ui->lineEdit_mdplogin->text();

       // Vérifier que les champs d'identification ne sont pas vides
       if (id_employe.isEmpty() || mdp.isEmpty()) {
           QMessageBox::warning(this, "Avertissement", "Veuillez remplir tous les champs.");
           return;
       }

       // Vérifier que le cin existe dans la base de données
       employee emp;
       emp = emp.recherchee(id_employe);
       if (emp.get_cin().isEmpty()) {
           QMessageBox::warning(this, "Avertissement", "l'mployée n'existe pas.");
           return;
       }

       // Vérifier que le mot de passe correspond au cin
       if (emp.get_mdp() == mdp) {
           QString role = emp.get_role();

           if (role == "Admin") {
               // Afficher la fenêtre MainWindow
               MainWindow *mainWindow = new MainWindow();
               mainWindow->show();
               this->hide(); // cacher la fenêtre de login
               connect(mainWindow, &QMainWindow::destroyed, this, &login::show);
           } else if (role == "Agent de voiture") {
               // Afficher la fenêtre AgentVoiture
               mainwindow_voiture *agentVoiture = new mainwindow_voiture();
               agentVoiture->show();
               this->hide();
               connect(agentVoiture, &QMainWindow::destroyed, this, &login::show);
           } else if (role == "Agent de maintenance") {
               // Afficher la fenêtre AgentMaintenance
               mainwindow_maintenance *agentMaintenance = new mainwindow_maintenance();
               agentMaintenance->show();
               this->hide();
               connect(agentMaintenance, &QMainWindow::destroyed, this, &login::show);
           } else {
               QMessageBox::warning(this, "Avertissement", "Le rôle de cet employé n'est pas reconnu.");
           }
       } else {
           QMessageBox::warning(this, "Avertissement", "Mot de passe incorect.");
       }
   }


void login::sendMailmdp()
{
    QString id_employe = ui->lineEdit_cinlogin->text();
    if (id_employe.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer votre CIN.");
        return;
    }
    employee emp = emp.recherchee(id_employe);
    if (emp.get_nom().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun employé trouvé avec ce CIN.\n\nATTENTION : Votre Cin doit comporter 8 chiffres");
        return;
    }
      /* employee emp;
       emp=emp.recherchee(id_employe);*/
       QString emailtr = emp.get_email();
        QString mdp = emp.get_mdp();
        QString prenom = emp.get_prenom();
QString nom=emp.get_nom();
    Smtp* smtp = new Smtp("benammar.fares@esprit.tn", "211JFT9154", "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSentmdp(QString)));
    smtp->sendMail("benammar.fares@esprit.tn", emailtr, " Mot de passe", "Notre société TCHARGI vous souhaite la bienvenue Monsieur/Madame :   " + QString(nom.at(0)).toUpper() + nom.mid(1) + " " + QString(prenom.at(0)).toUpper() + prenom.mid(1) + "\n\nVotre mot de passe est : " + mdp + "\n\nNous vous conseillons de le changer immédiatement après votre première connexion.");



}



void login::mailSentmdp(QString status)
{

    if (status == "Message sent") {
        QMessageBox::warning(nullptr, tr("Qt Simple SMTP client"), tr("Vérifiez votre courrier !\n\n"));
    }
}

