#include "connexion.h"

connexion::connexion()
{

}
bool connexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("BASEE");
db.setUserName("fares1");//inserer nom de l'utilisateur
db.setPassword("fares");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void connexion::closeConnection(){db.close();}

