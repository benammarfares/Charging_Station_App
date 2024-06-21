#ifndef MAIN_VOITURE_H
#define MAIN_VOITURE_H
#include <QMainWindow>
#include <QMessageBox>
#include "voiture.h"
#include <QDialog>
QT_BEGIN_NAMESPACE
namespace Ui {
class main_voiture;
}
QT_END_NAMESPACE

class main_voiture : public QDialog
{
    Q_OBJECT

public:
    explicit main_voiture(QWidget *parent = nullptr);
    ~main_voiture();


private slots:
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



private:
    Ui::main_voiture *ui;
    voiture Etmp;
    int currentBatteryLevel;
    int maxBatteryLevel;
    QByteArray data;
//    arduino a;


};

#endif // MAIN_VOITURE_H
