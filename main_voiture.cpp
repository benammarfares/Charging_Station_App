#include "main_voiture.h"
#include "ui_main_voiture.h"
#include "voiture.h"
#include <QtWidgets>
#include <QTabWidget>
#include <QString>
#include <QSqlQuery>
#include <QRegExpValidator>
#include <QSqlRecord>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGraphicsScene>
#include <QtCharts/QChart>
#include <QDebug>
#include <QtSql>
#include <QPdfWriter>
#include <QPainter>
#include <QRectF>
#include <QList>
#include "mainwindow.h"


main_voiture::main_voiture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::main_voiture)
{
    ui->setupUi(this);
    ui->pushButton_charge->setEnabled(false);

    int ret=a.connect_arduino(); // lancer la connexion à arduino
         switch(ret){
         case(0):qDebug()<< "arduino is available and connected to : "<< a.getarduino_port_name();
             break;
         case(1):qDebug() << "arduino is available but not connected to :" <<a.getarduino_port_name();
            break;
         case(-1):qDebug() << "arduino is not available";
         }
         QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_card()));


       //QObject::connect(a.getserial(), SIGNAL(readyRead()), this, SLOT(readCard()));



    // Initialize progress bar
      ui->progressBar_charging->setRange(0, maxBatteryLevel);
      ui->progressBar_charging->setValue(currentBatteryLevel);
      QSqlQuery query;




    ui->tableView->setModel(Etmp.afficher_voiture());
   ui->tableView_2->setModel(Etmp.afficher_voiture());

    // Find the QTableWidget using its object name
       QTableWidget *tableWidget = findChild<QTableWidget*>("tableWidget");

       // Use the QTableWidget object as needed
       int row = tableWidget->rowCount();


       //control de saisir
       ui->lineEdit_idvoiture->setValidator(new QIntValidator(1, 99999999, this));
       ui->lineEdit_bat_lvl->setValidator(new QIntValidator(1, 99999999, this));
       ui->lineEdit_batt_cap->setValidator(new QIntValidator(1, 99999999, this));
       ui->lineEdit_quantite->setValidator(new QIntValidator(1, 99999999, this));
        ui->lineEdit_model->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));


connect(ui->pushButton_TRI, &QPushButton::clicked, this, &main_voiture::on_pushButton_TRI_clicked);
}

main_voiture::~main_voiture()
{
    delete ui;
}
