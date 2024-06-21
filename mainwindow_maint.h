#ifndef MAINWINDOW_MAINT_H
#define MAINWINDOW_MAINT_H
#include <QDateTime>
#include <QDialog>
#include "maintenance.h"
#include <QDialog>

namespace Ui {
class mainwindow_maint;
}

class mainwindow_maint : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindow_maint(QWidget *parent = nullptr);
    ~mainwindow_maint();

private slots:
    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
        // ce slot est lancé à chaque réception d'un message de Arduino
    void on_pushButton_ajout_maint_clicked();
    void on_pushButton_3_maint_clicked();
    void on_pushButton_4_modifier_maint_clicked();
   // void on_lineEdit_3_textChanged(const QString &arg1);

    void on_recherche_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_7_maint_clicked();

    void on_pushButton_8_maint_clicked();

    void on_pushButton_9_maint_clicked();
   // void onReadyRead();

private:
    QList<maintenance> maintenances;
    Ui::mainwindow_maint *ui;
    maintenance Etmp ;
    void trier_par_id_maintenance();
    QByteArray data; // variable contenant les données reçues

       //Arduino A; // objet temporaire

};

#endif // MAINWINDOW_MAINT_H




