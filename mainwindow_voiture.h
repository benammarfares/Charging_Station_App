#ifndef MAINWINDOW_VOITURE_H
#define MAINWINDOW_VOITURE_H
#include <QMainWindow>
#include <QMessageBox>
#include "voiture.h"
#include "arduino.h"
#include "session.h"
#include <QDialog>

namespace Ui {
class mainwindow_voiture;
}

class mainwindow_voiture : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindow_voiture(QWidget *parent = nullptr);
    ~mainwindow_voiture();


private slots:

    //*****client youusef**//

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_update_clicked();

    void on_pb_avertissement_clicked();

    void on_pb_avertissement_2_clicked();

    void on_pushButton_pdf_client_clicked();

    void on_pushButton_dec_tri_clicked();

    void on_pushButton_croiss_tri_clicked();

    void on_pushButton_search_client_clicked();

    void on_pushButton_effacertout_clie_clicked();

    void on_pushButton_stat_client_clicked();

    void on_pushButton_tester_clientclicked();



    //*****************//
    void on_pushButton_clicked();


    void on_pushButton_3_clicked();


    void on_pushButton_4_clicked();


    void on_pushButton_PDF_clicked();

    void on_pushButton_TRI_clicked();

    void on_lineEdit_recherche_textChanged(const QString &arg1);



    void on_pushButton_STAT_clicked();


    void on_pushButton_5_clicked();


    void on_pushButton_charge_clicked();
    void update_card();
    void readCard();



    void on_pushButton_6_clicked();

    //***************SESSION RASLEN **********//


    void on_pushButton_ajouter_session_clicked();


    void on_pushButton_effacer_session_clicked();


    void on_pushButton_modif_session_clicked();

    void on_pushButton_PDF_session_clicked();

    void on_pushButton_tri_session_2_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_mode_charge_session_clicked();

    void on_pushButton_arduino_session_clicked();

    void on_pushButton_stat_session_clicked();

    void on_pushButton_effacer_tout_sess_clicked();

    void on_pushButton_chercher_session_clicked();


    //*********************///
private:


    Ui::mainwindow_voiture *ui;
     voiture Etmp;
     int currentBatteryLevel;
     int maxBatteryLevel;
     QByteArray data;
    arduino a;
    session Etmp2;


};



#endif // MAINWINDOW_VOITURE_H
