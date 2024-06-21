#include "mainwindow_voiture.h"
#include "ui_mainwindow_voiture.h"
#include "ui_mainwindow.h"
#include "voiture.h"
#include "mainwindow.h"
#include "client.h"
#include "arduino.h"
#include "client.h"

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

namespace Ui {
class client;
}



namespace Ui {
class voiture;
}

namespace Ui {
class session;
}

mainwindow_voiture::mainwindow_voiture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwindow_voiture)
{
   // arduino a;
    ui->setupUi(this);

//***zyeda taa client***//
    client c;
    QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
    ui->tableView_client->setModel(c.afficher());

    //controle de saisie
   ui->lineEdit_id->setValidator(new QIntValidator(1, 99999999, this));
   ui->lineEdit_telephone->setValidator(new QIntValidator(1, 99999999, this));
   ui->lineEdit_cin->setValidator(new QIntValidator(1, 99999999, this));
   ui->lineEdit_supp_id->setValidator(new QIntValidator(1, 99999999, this));
   ui->lineEdit_nom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));
   ui->lineEdit_prenom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));
   ui->lineEdit_adresse->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));
   ui->lineEdit_email->setValidator(new QRegExpValidator(QRegExp("[A-Za-z._%+-]+@[A-Za-z.-]+(?=\\.[A-Za-z]{2,})(\\.?[A-Za-z])*"),  this));


    //*********zyeda taa session*****//////////

    ui->tableView_3->setModel(Etmp2.afficher_session());
 QTableWidget *tableWidget_2 = findChild<QTableWidget*>("tableWidget_2");
 int row3 = tableWidget_2->rowCount();

 //control de saisir
 ui->ID_SESSION->setValidator(new QIntValidator(1, 99999999, this));
 //ui->MODEE->setValidator(new QIntValidator(0, 1, this));
 ui->NIV_BATTERIE->setValidator(new QIntValidator(0, 100, this));
 ui->VITESSE->setValidator(new QIntValidator(0, 10, this));
 ui->PRIX->setValidator(new QIntValidator(1, 99999999, this));


    //*********************//
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


connect(ui->pushButton_TRI, &QPushButton::clicked, this, &mainwindow_voiture::on_pushButton_TRI_clicked);
}

mainwindow_voiture::~mainwindow_voiture()
{
    delete ui;
}



void mainwindow_voiture::readCard()
{

    QByteArray arduinoMsg = a.read_from_arduino();

    qDebug() << "messs messs:" << arduinoMsg;

       int tagPos = arduinoMsg.indexOf(": ");
             if (tagPos < 0) {
                 qDebug() << "Second line:" << tagPos;

                 return;

             }
             QString uidString = arduinoMsg.mid(tagPos + 2, 1);
                      qDebug() << "Second line:" << uidString;
                      bool ok;
                      int uidInt = uidString.toInt(&ok, 16);

                      if (ok) {
                                   qDebug() << "your id is" <<uidInt;
                               }
                      bool idFound = false;

                      while (!idFound) {
                          QSqlQuery query2;
                          query2.prepare("SELECT MATRICULE FROM VOITURE WHERE ID_VOITURE=:id");
                          query2.bindValue(":id", uidInt);
                          if (query2.exec()) {
                              if (query2.next()) {
                                  qDebug() << "SUCCEDED" << uidInt;
                                  idFound = true;
                              }
                          }

}}

void mainwindow_voiture::on_pushButton_6_clicked()
{



    QByteArray arduinoMsg = a.read_from_arduino();


       int tagPos = arduinoMsg.indexOf("tag :");
             if (tagPos < 0) {
                 qDebug() << "messs:" << tagPos;

                 return;
             }
             QString uidString = arduinoMsg.mid(tagPos + 6, 1);
                      qDebug() << "Second line:" << uidString;
                      bool ok;
                      int uidInt = uidString.toInt(&ok, 16);

                      if (ok) {
                                   qDebug() << "your id is" <<uidInt;
                               }
                      QSqlQuery query2;
                          query2.prepare("SELECT MATRICULE FROM VOITURE WHERE ID_VOITURE=:id");
                          query2.bindValue(":id", uidInt);
                          if (query2.exec()) {
                              if (query2.next()) {

                                  qDebug() << "SUCCEDED" <<uidInt;

                              }}

    int PRICE;
    int id1 = ui->lineEdit_ID_CAR->text().toInt();

    QSqlQuery query1;
    query1.prepare("SELECT PRIX FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE = :id_voiture");
    query1.bindValue(":id_voiture", id1);

     query1.exec();
    while (query1.next()) {
   PRICE=query1.value("PRIX").toInt();
  qDebug() << "TEST PRIX!" <<PRICE ;
     }
     if (!query1.exec()) {
         qDebug() << "Failed to execute query1!";
         return;
     }


     QByteArray priceData = QByteArray::number(PRICE);
  // create an instance of the arduino object
    a.write_to_arduino(priceData);

}


void mainwindow_voiture::on_pushButton_clicked()
{


    //fuction true meloul taa tous les fonctions
    bool isValid = true;


    // Get the input values
   QString id = ui->lineEdit_idvoiture->text();
   QString model = ui->lineEdit_model->text();
   QString license = ui->lineEdit_license->text();
   QString bat_lvl = ui->lineEdit_bat_lvl->text();
   QString batt_cap = ui->lineEdit_batt_cap->text();
   QString etat = ui->comboBox_etat->currentText();
   QString quantite = ui->lineEdit_quantite->text();

//consructeur voiture parametré
   voiture v(id,model,license,bat_lvl,batt_cap,etat,quantite);


    //get the id2 for the checkid fucntion
    int id2 = ui->lineEdit_idvoiture->text().toInt();


//check for the id_voiture if exist and number or not
    if (v.idExists(id2)) {
        QMessageBox::warning(this, "ID EXISTE", "ID already exists, please enter another ID.");
        isValid = false;
    }


   //check if empty or not

   if ((id.isEmpty()) || (model.isEmpty()) || (license.isEmpty()) ||  (bat_lvl.isEmpty()) ||  (batt_cap.isEmpty()) ||  (etat.isEmpty()) ||  (quantite.isEmpty())) {
       QMessageBox::warning(this, "Invalid Inputs", "Vous devez saisir tous les champs pour ajouter ");
       isValid = false;

   }

      //*****************
  QRegExp etatRegex("[a-zA-Z]+");
  QRegExp licenseRegex("[a-zA-Z]{2}\\d{3}[a-zA-Z]{2}");

    //CONVERTING the lvl_batterie and capacité and quantité to entierr

  int batt_cap_int = ui->lineEdit_batt_cap->text().toInt();
  int bat_lvl_int = ui->lineEdit_bat_lvl->text().toInt();
  int quantite_int = ui->lineEdit_quantite->text().toInt();



          //control saisir sur la quantité a charger

            if (quantite_int > batt_cap_int -bat_lvl_int ) {
                QMessageBox::warning(this, "Invalid Input", "la qunatité que vous voullez charger depasse les limites.");

                isValid = false;

            }


          //control saisir sur la matricule


        if ((!licenseRegex.exactMatch(license))  && (!license.isEmpty())) {
            QMessageBox::warning(this, "Invalid Input", "Matricule format is XX999XX.");
            isValid = false;
        }

        //*****************

    if (isValid) {
        v.setId(id);
        v.setLicensePlate(ui->lineEdit_license->text());
        v.setBatteryLvl(ui->lineEdit_bat_lvl->text());
        v.setBatterCap(ui->lineEdit_batt_cap->text());
        v.setModel(ui->lineEdit_model->text());
        v.setEtat(ui->comboBox_etat->currentText());
        v.setQuantite(ui->lineEdit_quantite->text());


        if (v.insert()) {
            //refresh to afficher
            ui->tableView->setModel(Etmp.afficher_voiture());
            ui->tableView_2->setModel(Etmp.afficher_voiture());

            qDebug() << "Voiture inserted successfully";
            QMessageBox::information(nullptr, QObject::tr("OK"),
                          QObject::tr("Ajout effectué\n"
                                      "Click Cancel to exit ."), QMessageBox::Cancel);


            // Add a new row to the QTableWidget and set the item for each column
            QTableWidget *tableWidget = findChild<QTableWidget*>("tableWidget");
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            // Get the current date/time
            QDateTime currentDateTime = QDateTime::currentDateTime();
            tableWidget->setItem(row, 0, new QTableWidgetItem(v.get_model()));
            tableWidget->setItem(row, 1,new QTableWidgetItem(v.get_Etat()));
            tableWidget->setItem(row, 2, new QTableWidgetItem(v.get_licensePlate()));
            tableWidget->setItem(row, 3, new QTableWidgetItem(v.get_Quantite()));
            tableWidget->setItem(row, 4, new QTableWidgetItem(currentDateTime.toString(Qt::ISODate)));

        } else {
            qDebug() << "Failed to insert voiture into database";
        }
    }
}






void mainwindow_voiture::on_pushButton_3_clicked()
{
    int id1 =ui->lineEdit->text().toUInt();

    //QString license = ui->lineEdit->text();
     voiture v; // declare and initialize Etmp

     bool test=Etmp.delete_voiture(id1);

     //get the id2 for the checkid fucntion
     int id2 = ui->lineEdit_idvoiture->text().toInt();


 //check for the id_voiture if exist and number or not


     //get the id2 for the checkid fucntion
     if (!v.idExists(id2)) {


     if (test) {
         ui->tableView->setModel(Etmp.afficher_voiture());
         ui->tableView_2->setModel(Etmp.afficher_voiture());

         QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("Suppression effectue.\n"
                                       "Cancel to exit."), QMessageBox::Cancel);

     }

     }else {
QMessageBox::warning(this, "ID N EXISTE pas", "ID doesn't exists, please enter another ID.");


}

}








void mainwindow_voiture::on_pushButton_4_clicked()
{
    QString id = ui->lineEdit_idvoiture->text();
    QString license = ui->lineEdit_license->text();
    QString bat_lvl = ui->lineEdit_bat_lvl->text();
    QString batt_cap = ui->lineEdit_batt_cap->text();
    QString model = ui->lineEdit_model->text();
    QString etat = ui->comboBox_etat->currentText();
    QString quantite = ui->lineEdit_quantite->text();

    voiture v(id,model,license,bat_lvl,batt_cap,etat,quantite);

    //get the id2 for the checkid fucntion
    int id2 = ui->lineEdit_idvoiture->text().toInt();
    if (v.idExists(id2)) {

     if (v.update(v.get_id())) {
          // Refresh the table view to show the updated data
          ui->tableView->setModel(Etmp.afficher_voiture());
          QMessageBox::information(this, "Update voiture", "Voiture updated successfully.");
      } else {
          QMessageBox::warning(this, "Update voiture", "Failed to update voiture.");
      }}else {

        QMessageBox::warning(this, "ID EXISTE", "ID already exists, please enter another ID.");

    }
  }




void mainwindow_voiture::on_pushButton_PDF_clicked()
{
    // Prepare SQL query
    QSqlQuery query;
    query.prepare("SELECT * FROM VOITURE");

    // Execute query
    if (!query.exec()) {
        qDebug() << "Failed to execute query!";
        return;
    }

    // Create PDF document
    QPdfWriter writer("C:/PDF/output.pdf");
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageMargins(QMarginsF(20, 20, 20, 20));

    // Create PDF painter
    QPainter painter(&writer);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.setFont(QFont("Arial", 5));



    // Define table cell dimensions
    int cellWidth = 150;
    int cellHeight = 40;

    // Set table position
    int tableX = 20;
    int tableY = 20;

    // Draw table header
    painter.drawText(tableX + cellWidth , tableY, "ID_VOITURE");
    painter.drawText(tableX + cellWidth * 6, tableY , "ID_CLIENT");
    painter.drawText(tableX + cellWidth * 11, tableY , "ID_MAINTENANCE");
    painter.drawText(tableX + cellWidth * 18, tableY, "MATRICULE");
    painter.drawText(tableX + cellWidth * 24, tableY, "BATTERIE_LVL");
    painter.drawText(tableX + cellWidth * 30, tableY, "BATTERIE_CAP");
    painter.drawText(tableX + cellWidth * 36, tableY, "MODEL");
    painter.drawText(tableX + cellWidth * 40, tableY, "ETAT");
    painter.drawText(tableX + cellWidth * 45, tableY, "QUANTITE");
    painter.drawText(tableX + cellWidth * 50, tableY, "ID_SESSION");

    tableY += cellHeight;

    // Loop through query results and draw table cells
    int row = 5;
    while (query.next()) {
        // Draw ID_VOITURE value
        painter.drawText(tableX + cellWidth , tableY + row * cellHeight, query.value(0).toString());
        // Draw ID_CLIENT value
        painter.drawText(tableX + cellWidth * 6, tableY + row * cellHeight, query.value(1).toString());
        // Draw ID_MAINTENANCE value
        painter.drawText(tableX + cellWidth * 11, tableY + row * cellHeight, query.value(2).toString());
        // Draw MATRICULE value
        painter.drawText(tableX + cellWidth * 18, tableY + row * cellHeight, query.value(3).toString());
        // Draw BATTERIE_LVL value
        painter.drawText(tableX + cellWidth * 24, tableY + row * cellHeight, query.value(4).toString());
        // Draw BATTERIE_CAP value
        painter.drawText(tableX + cellWidth * 30, tableY + row * cellHeight, query.value(5).toString());
        // Draw MODEL value
        painter.drawText(tableX + cellWidth * 36, tableY + row * cellHeight, query.value(6).toString());
        // Draw ETAT value
        painter.drawText(tableX + cellWidth * 40, tableY + row * cellHeight, query.value(7).toString());
        // Draw QUANTITE value
        painter.drawText(tableX + cellWidth * 45, tableY + row * cellHeight, query.value(8).toString());
        // Draw ID_SESSION value
        painter.drawText(tableX + cellWidth * 50, tableY + row * cellHeight, query.value(9).toString());

        row++;
        row++;
        row++;
        row++;
    }

    // Clean up
    painter.end();

    qDebug() << "PDF generated!";
}


void mainwindow_voiture::on_pushButton_TRI_clicked()
{
    // khdhit el table View mel ui
      QAbstractItemModel *model = ui->tableView->model();

      // Create a QSortFilterProxyModel  lel tri
      QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
      proxyModel->setSourceModel(model);

      // Sort by id
      proxyModel->setSortRole(Qt::EditRole);
      proxyModel->sort(0, Qt::AscendingOrder);

      //update lel table view
      ui->tableView->setModel(proxyModel);
}




void mainwindow_voiture::on_lineEdit_recherche_textChanged(const QString &searchString)
{

    QSqlQueryModel *model = new QSqlQueryModel(this);
       model->setQuery(QString("SELECT * FROM VOITURE WHERE MODEL LIKE '%%1%'").arg(searchString));
       model->setHeaderData(0, Qt::Horizontal, "ID_VOITURE");
       model->setHeaderData(1, Qt::Horizontal, "ID_CLIENT");
       model->setHeaderData(2, Qt::Horizontal, "ID_MAINTENANCE");
       model->setHeaderData(3, Qt::Horizontal, "MATRICULE");
       model->setHeaderData(4, Qt::Horizontal, "BATTERIE_LVL");
       model->setHeaderData(5, Qt::Horizontal, "BATTERIE_CAP");
       model->setHeaderData(6, Qt::Horizontal, "MODEL");
       model->setHeaderData(7, Qt::Horizontal, "ETAT");
       model->setHeaderData(8, Qt::Horizontal, "QUANTITE");
       model->setHeaderData(9, Qt::Horizontal, "ID_SESSION");
       ui->tableView_2->setModel(model);
       ui->tableView_2->show();
}







void mainwindow_voiture::on_pushButton_STAT_clicked()
{
    QSqlQuery query;
    QGraphicsScene *scene = new QGraphicsScene(this);

    QPieSeries *series = new QPieSeries();




    if (!query.exec("SELECT COUNT(*) FROM VOITURE")) {
        // Handle the error if the query fails to execute
        qDebug() << "Failed to execute query: " << query.lastError().text();
        return;
    }

    // Fetch the result of the query
    if (query.next()) {
        // Get the total count of cars from the first column of the result
        int totalCount = query.value(0).toInt();
        qDebug() << "Total count of cars: " << totalCount;

        //
        QSqlQuery query("SELECT COUNT(*) FROM VOITURE WHERE ETAT='Maintenance '");
        query.next();
        int maintenanceCount = query.value(0).toInt();
        qDebug() << "Total count of cars: " << maintenanceCount;
        //
        QSqlQuery query2("SELECT COUNT(*) FROM VOITURE WHERE ETAT='Non Maintenance'");
        query2.next();
        int nonMaintenanceCount = query2.value(0).toInt();
        qDebug() << "Total count of cars: " << nonMaintenanceCount;

        // Calculate the percentage of cars in maintenance and non-maintenance status
        double maintenancePercent = 100.0 * maintenanceCount / totalCount;
        double nonMaintenancePercent = 100.0 * nonMaintenanceCount / totalCount;

        qDebug() << "PERCENTAGE: " << maintenancePercent;
        qDebug() << "PERCENTAGE: " << nonMaintenancePercent;

        // Add the data to the series
        QPieSlice *maintenanceSlice = new QPieSlice();
        series->setPieSize(80);
        maintenanceSlice->setLabel(QString("Maintenance\n%1%\n(%2)").arg(maintenancePercent, 0, 'f', 2).arg(maintenanceCount));
        maintenanceSlice->setValue(maintenancePercent);
       maintenanceSlice->setBrush(QColor(50, 205, 50)); // green
       QFont font;
       font.setPointSize(8); //
       maintenanceSlice->setLabelFont(font);
       series->append(maintenanceSlice);



        QPieSlice *nonMaintenanceSlice = new QPieSlice();
        nonMaintenanceSlice->setLabel(QString("Non-Maintenance\n%1%\n(%2)").arg(nonMaintenancePercent, 0, 'f', 2).arg(nonMaintenanceCount));
        nonMaintenanceSlice->setValue(nonMaintenancePercent);
       nonMaintenanceSlice->setBrush(QColor(255, 0, 0)); // red
      nonMaintenanceSlice->setLabelFont(font);
        series->append(nonMaintenanceSlice);




        // format to show the percentage and the value
        series->setLabelsVisible();
        series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

        // legend
        QChart *chart = new QChart();
        chart->setGeometry(QRectF(0, 0, 600, 400));

        chart->addSeries(series);
        chart->setTitle("Etat Voiture");
        QFont titleFont;
        titleFont.setPointSize(30);
        chart->setTitleFont(titleFont);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);

        // Set the chart theme and other properties
        chart->setTheme(QChart::ChartThemeLight);
        chart->setAnimationOptions(QChart::AllAnimations);

        // Create a new QChartView widget and set the chart as its chart
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Add the QChartView widget to the QGraphicsScene
        QGraphicsProxyWidget *proxy = scene->addWidget(chartView);
        proxy->setPos(0, 0);

        // Set the QGraphicsScene as the scene of the QGraphicsView widget
        ui->graphicsView->setScene(scene);
               ui->graphicsView->fitInView(proxy, Qt::KeepAspectRatio);
    }

}




void mainwindow_voiture::on_pushButton_5_clicked()
{

    //******************* SELECTING MEL VOITURE ******************//

       QSqlQuery query;
       query.prepare("SELECT ID_VOITURE, ID_CLIENT, MATRICULE, MODEL, ID_SESSION, DATE_VOITURE FROM VOITURE");

       // Execute query
       if (!query.exec()) {
           qDebug() << "Failed to execute query!";
           return;
       }


       //******************* SELECTING MEL SESSION ******************//


       int PRICE;
       QSqlQuery query1;
       query1.prepare("SELECT PRIX FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION");
        query1.exec();
       while (query1.next()) {
      PRICE=query1.value("PRIX").toInt();
     qDebug() << "TEST PRIX!" <<PRICE ;
        }
        if (!query1.exec()) {
            qDebug() << "Failed to execute query1!";
            return;
        }


        //******************* SELECTING MEL CLIENT ******************//


        int prenom;
        int telephone;
        QSqlQuery query2;
        query2.prepare("SELECT PRENOM, TELEPHONE FROM CLIENT JOIN VOITURE ON VOITURE.ID_CLIENT=CLIENT.ID_CLIENT");

         query2.exec();
        while (query2.next()) {

       prenom=query2.value("PRENOM").toInt();
       telephone=query2.value("TELEPHONE").toInt();

      qDebug() << "TEST PRENOM!" <<prenom ;
      qDebug() << "TEST TELEPHONE!" <<telephone ;

         }
        if (!query2.exec()) {
            qDebug() << "Failed to execute query2!";
            return;
        }


        //************************** PDF *************************//

       QPdfWriter writer("C:/PDF/historique.pdf");
       writer.setPageSize(QPageSize(QPageSize::A4));
       writer.setPageMargins(QMarginsF(20, 20, 20, 20));
       // Create PDF painter
       QPainter painter(&writer);
       painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
       painter.setFont(QFont("Arial", 5));

       // Define table cell dimensions
       int cellWidth = 150;
       int cellHeight = 40;

       // Set table position
       int tableX = 20;
       int tableY = 20;

       // Draw table header
       painter.drawText(tableX + cellWidth , tableY, "ID_VOITURE");
       painter.drawText(tableX + cellWidth * 6, tableY , "MATRICULE");
       painter.drawText(tableX + cellWidth * 11, tableY , "MODEL");
       painter.drawText(tableX + cellWidth * 18, tableY, "SESSION");
      painter.drawText(tableX + cellWidth * 24, tableY, "PRIX");
      painter.drawText(tableX + cellWidth * 30, tableY, "CLIENT");
      painter.drawText(tableX + cellWidth * 38, tableY, "TELEPHONE_CLIENT");
      painter.drawText(tableX + cellWidth * 47, tableY, "TIME");



       tableY += cellHeight;

       // Loop through query results and draw table cells
       int row = 5;
       while (query.next() && query2.next() && query1.next()) {
           painter.drawText(tableX + cellWidth , tableY + row * cellHeight, query.value(0).toString());
           painter.drawText(tableX + cellWidth * 6, tableY + row * cellHeight, query.value(2).toString());
          painter.drawText(tableX + cellWidth * 11, tableY + row * cellHeight, query.value(3).toString());
          painter.drawText(tableX + cellWidth * 18, tableY + row * cellHeight, query.value(4).toString());
          painter.drawText(tableX + cellWidth * 24, tableY + row * cellHeight, query1.value(0).toString());
           painter.drawText(tableX + cellWidth * 30, tableY + row * cellHeight, query2.value(0).toString());
          painter.drawText(tableX + cellWidth * 38, tableY + row * cellHeight, query2.value(1).toString());
          painter.drawText(tableX + cellWidth * 46, tableY + row * cellHeight, query.value(5).toString());


           row++;
           row++;
           row++;
           row++;
       }

       // Clean up
       painter.end();

       qDebug() << "PDF generated!";

  }



void mainwindow_voiture::on_pushButton_charge_clicked()
{


    if (ui->pushButton_charge->isEnabled()) {



        int PRICE;
        int id1 = ui->lineEdit_ID_CAR->text().toInt();

        QSqlQuery query1;
        query1.prepare("SELECT PRIX FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE = :id_voiture");
        query1.bindValue(":id_voiture", id1);

         query1.exec();
        while (query1.next()) {
       PRICE=query1.value("PRIX").toInt();
      qDebug() << "TEST PRIX!" <<PRICE ;
         }
         if (!query1.exec()) {
             qDebug() << "Failed to execute query1!";
             return;
         }


         QByteArray priceData = QByteArray::number(PRICE);
      // create an instance of the arduino object
        a.write_to_arduino(priceData);




       int VITESSE;
       QSqlQuery query2;
       query2.prepare("SELECT VITESSE FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE=:idv");
       query2.bindValue(":idv", id1);

        query2.exec();
       while (query2.next()) {

      VITESSE=query2.value("VITESSE").toInt();

     qDebug() << "TEST VITESSE!" <<VITESSE ;


        }
       if (!query2.exec()) {
           qDebug() << "Failed to execute query2!";
           return;
       }



       int QUANT;
       QSqlQuery query3;
       query3.prepare("SELECT QUANTITE FROM VOITURE WHERE ID_VOITURE=:idv");
       query3.bindValue(":idv", id1);

        query3.exec();
       while (query3.next()) {

      QUANT=query3.value("QUANTITE").toInt();

     qDebug() << "TEST QUANTITE!" <<QUANT ;}


int duree;
  if (VITESSE >= 20) {
  double temp = VITESSE * QUANT  / 60;
  duree = static_cast<int>(temp);
       }
  else if (VITESSE<20) {
    double temp = VITESSE * QUANT / 30;
    temp=temp+15;
    duree = static_cast<int>(temp);

  }




  QLCDNumber *lcdNumber = ui->lcdNumber_2;
  lcdNumber->display(duree);



          // Get battery level and max battery level from database using car ID
          QSqlQuery query;
          query.prepare("SELECT BATTERIE_LVL, BATTERIE_CAP ,QUANTITE FROM VOITURE WHERE ID_VOITURE = :id");
         query.bindValue(":id", id1);
          if (!query.exec()) {
              qDebug() << "Failed to retrieve car data from database: " << query.lastError().text();


              return;
          }

          // If car ID not found in database
          if (!query.next()) {
              qDebug() << "Car not found in database.";
              return;
          }

          // Get battery level and max battery level
          int batteryLevel = query.value(0).toInt();
          int batteryCap = query.value(1).toInt();
          int chargeQuantity = query.value(2).toInt();

          currentBatteryLevel = batteryLevel;
          maxBatteryLevel = batteryCap;

          qDebug() << "Battery level before charging: " << currentBatteryLevel;


          // Update progress bar
          ui->progressBar_charging->setRange(0, maxBatteryLevel);
          ui->progressBar_charging->setValue(currentBatteryLevel);


          ui->lcdNumber->setDigitCount(2);
          ui->lcdNumber->display("0");
          int count = 1;
          for (int i = 0; i < chargeQuantity; i++) {
              QThread::sleep(1); // sleep for 1 second
              currentBatteryLevel++;
              ui->progressBar_charging->setValue(currentBatteryLevel);
              ui->lcdNumber->display(QString("%1").arg(count, 2, 10, QChar('0')));
              if (count == duree) { // stop the loop when count reaches duree
                  break;
              }
              count++;
          }

          for (int i = 0; i < chargeQuantity - duree; i++) {
              // Set the range and initial value of the QLabel

                  currentBatteryLevel++;
                  ui->progressBar_charging->setValue(currentBatteryLevel);
              }

          // Update car's battery level in database
          QSqlQuery updateQuery;
          updateQuery.prepare("UPDATE VOITURE SET BATTERIE_LVL= :batteryLevel WHERE ID_VOITURE = :id3");
          updateQuery.bindValue(":batteryLevel", currentBatteryLevel);
          updateQuery.bindValue(":id3", id1);
          if (!updateQuery.exec()) {
              qDebug() << "Failed to update car's battery level in database: " << updateQuery.lastError().text();
              return;
          }
          ui->tableView->setModel(Etmp.afficher_voiture());
          ui->tableView_2->setModel(Etmp.afficher_voiture());


             qDebug() << "Battery level after charging: " << currentBatteryLevel;




}

    else {
            // show an error message
            QMessageBox::warning(this, "Error", "Swipe your Card .");

}}




void mainwindow_voiture::update_card()
{




    QByteArray arduinoMsg = a.read_from_arduino();

   qDebug() << "messs messs:" << arduinoMsg;


             if (arduinoMsg.contains("ca")) {
                 QMessageBox::information(nullptr, "Car Detected", "A car has been detected!");
             }

      int tagPos = arduinoMsg.indexOf(": ");


            if (tagPos < 0) {
                 qDebug() << "Second line:" << tagPos;

                return;

           }
            QString uidString = arduinoMsg.mid(tagPos + 2, 1);

                     qDebug() << "Second line:" << uidString;
                     bool ok;
                     int uidInt = uidString.toInt(&ok, 16);
                     bool idFound = false;


                     QString mode;

                     QSqlQuery query5;
                     query5.prepare("SELECT MODEE FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE = :id_voiture");
                     query5.bindValue(":id_voiture", uidInt);

                      query5.exec();
                     if (query5.next()) {
                    mode=query5.value("MODEE").toString();
                   qDebug() << "MODEEE!" <<mode ;
                      }
                      if (!query5.exec()) {
                          qDebug() << "Failed to execute query1!";
                          return;
                      }

if (mode=="repos"){
    QMessageBox::warning(this, "repos", "wait until session is charged");

    QByteArray myByteArray = mode.toUtf8();

                     a.write_to_arduino(myByteArray);
                     ok=false;
}




                     if (ok){
                                 qDebug() << "your id is" <<uidInt;


                    if (!idFound) {
                        QSqlQuery query2;
                        query2.prepare("SELECT MATRICULE FROM VOITURE WHERE ID_VOITURE=:id");
                        query2.bindValue(":id", uidInt);
                        if (query2.exec()) {
                            if (query2.next()){
if(uidInt==8){
    QMessageBox::information(this, "admin is connected", "droit d'acces permi");

    ui->pushButton_charge->setEnabled(true);
}
if(uidInt!=8){

                                qDebug() << "SUCCEDED" << uidInt;

                                QMessageBox::information(this, "Login", "Charge your car now!");

                                int PRICE;

                                QSqlQuery query1;
                                query1.prepare("SELECT PRIX FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE = :id_voiture");
                                query1.bindValue(":id_voiture", uidInt);

                                 query1.exec();
                                if (query1.next()) {
                               PRICE=query1.value("PRIX").toInt();
                              qDebug() << "TEST PRIX!" <<PRICE ;
                                 }
                                 if (!query1.exec()) {
                                     qDebug() << "Failed to execute query1!";
                                     return;
                                 }


                                 QByteArray priceData = QByteArray::number(PRICE);
                              // create an instance of the arduino object
                                a.write_to_arduino(priceData);




                               int VITESSE;
                               QSqlQuery query4;
                               query4.prepare("SELECT VITESSE FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE=:idv");
                               query4.bindValue(":idv", uidInt);

                                query4.exec();
                               if (query4.next()) {

                              VITESSE=query4.value("VITESSE").toInt();

                             qDebug() << "TEST VITESSE!" <<VITESSE ;


                                }
                               if (!query4.exec()) {
                                   qDebug() << "Failed to execute query2!";
                                   return;
                               }



                               int QUANT;
                               QSqlQuery query3;
                               query3.prepare("SELECT QUANTITE FROM VOITURE WHERE ID_VOITURE=:idv");
                               query3.bindValue(":idv", uidInt);

                                query3.exec();
                               if (query3.next()) {

                              QUANT=query3.value("QUANTITE").toInt();

                             qDebug() << "TEST QUANTITE!" <<QUANT ;}


                        int duree;
                          if (VITESSE >= 20) {
                          double temp = VITESSE * QUANT  / 60;
                          duree = static_cast<int>(temp);
                               }
                          else if (VITESSE<20) {
                            double temp = VITESSE * QUANT / 30;
                            temp=temp+15;
                            duree = static_cast<int>(temp);

                          }




                          QLCDNumber *lcdNumber = ui->lcdNumber_2;
                          lcdNumber->display(duree);



                                  // Get battery level and max battery level from database using car ID
                                  QSqlQuery query;
                                  query.prepare("SELECT BATTERIE_LVL, BATTERIE_CAP ,QUANTITE FROM VOITURE WHERE ID_VOITURE = :id");
                                 query.bindValue(":id", uidInt);
                                  if (!query.exec()) {
                                      qDebug() << "Failed to retrieve car data from database: " << query.lastError().text();


                                      return;
                                  }

                                  if (!query.next()) {
                                      qDebug() << "Car not found in database.";
                                      return;
                                  }

                                  int batteryLevel = query.value(0).toInt();
                                  int batteryCap = query.value(1).toInt();
                                  int chargeQuantity = query.value(2).toInt();

                                  currentBatteryLevel = batteryLevel;
                                  maxBatteryLevel = batteryCap;

                                  qDebug() << "Battery level before charging: " << currentBatteryLevel;


                                  // Update progress bar
                                  ui->progressBar_charging->setRange(0, maxBatteryLevel);
                                  ui->progressBar_charging->setValue(currentBatteryLevel);


                                  ui->lcdNumber->setDigitCount(2);
                                  ui->lcdNumber->display("0");
                                  int count = 1;
                                  for (int i = 0; i < chargeQuantity; i++) {
                                      QThread::sleep(1); // sleep for 1 second
                                      currentBatteryLevel++;
                                      ui->progressBar_charging->setValue(currentBatteryLevel);
                                      ui->lcdNumber->display(QString("%1").arg(count, 2, 10, QChar('0')));
                                      if (count == duree) { // stop the loop when count reaches duree
                                          break;
                                      }
                                      count++;
                                  }

                                  for (int i = 0; i < chargeQuantity - duree; i++) {
                                      // Set the range and initial value of the QLabel

                                          currentBatteryLevel++;
                                          ui->progressBar_charging->setValue(currentBatteryLevel);
                                      }

                                  // Update car's battery level in database
                                  QSqlQuery updateQuery;
                                  updateQuery.prepare("UPDATE VOITURE SET BATTERIE_LVL= :batteryLevel WHERE ID_VOITURE = :id3");
                                  updateQuery.bindValue(":batteryLevel", currentBatteryLevel);
                                  updateQuery.bindValue(":id3", uidInt);
                                  if (!updateQuery.exec()) {
                                      qDebug() << "Failed to update car's battery level in database: " << updateQuery.lastError().text();
                                      return;
                                  }
                                  ui->tableView->setModel(Etmp.afficher_voiture());
                                  ui->tableView_2->setModel(Etmp.afficher_voiture());


                                     qDebug() << "Battery level after charging: " << currentBatteryLevel;

 idFound = true;


                        }


                         }  else {

                                QMessageBox::warning(this, "Error", "Your car is no longer registered.");

                            } }}
                         }



}


    //QByteArray buffer;
   //QByteArray data = a.read_from_arduino();
  //buffer += data;
 //while (buffer.contains('\n')) {
     // int newline_pos = buffer.indexOf('\n');
      // QByteArray message = buffer.left(newline_pos);
     // buffer.remove(0, newline_pos + 1);

     // qDebug() << "Received message from Arduino:" << message;
        //if (message.startsWith("\r")) {

       //ui->pushButton_charge->setEnabled(true);
      //      QMessageBox::information(this, "Login", "You have successfully logged in!");
       //}

//}


                            //******************************************SESSION RASLEN **********************************///

void mainwindow_voiture::on_pushButton_ajouter_session_clicked()
{


    //fuction true meloul taa tous les fonctions
    bool isValid = true;


    // Get the input values
   QString ID_SESSION = ui->ID_SESSION->text();
   QString MODEE = ui->MODEE->currentText();
   QString NIV_BATTERIE = ui->NIV_BATTERIE->text();
   QString VITESSE = ui->VITESSE->text();
   QString HAPPY_HOUR = ui->HAPPY_HOUR->currentText();
   QString PRIX = ui->PRIX->text();

//consructeur voiture parametré
session s(ID_SESSION,MODEE,NIV_BATTERIE,VITESSE,HAPPY_HOUR,PRIX );


    //get the id2 for the checkid fucntion
    int id2 = ui->ID_SESSION->text().toInt();


//check for the id_voiture if exist and number or not
    if (s.idExists(id2)) {
        QMessageBox::warning(this, "ID EXISTE", "ID already exists, please enter another ID.");
        isValid = false;
    }


   //check if empty or not

   if ((ID_SESSION.isEmpty()) || (MODEE.isEmpty()) || (NIV_BATTERIE.isEmpty()) ||  (VITESSE.isEmpty()) ||  (HAPPY_HOUR.isEmpty()) ||  (PRIX.isEmpty()))
   {
       QMessageBox::warning(this, "Invalid Inputs", "Vous devez saisir tous les champs pour ajouter ");
       isValid = false;

   }

        //*****************

    if (isValid) {
        s.setID_SESION(ui->ID_SESSION->text());
        s.setMODEE(ui->MODEE->currentText());
        s.setNIV_BATTERIE(ui->NIV_BATTERIE->text());
        s.setVITESSE(ui->VITESSE->text());
        s.setHAPPY_HOUR(ui->HAPPY_HOUR->currentText());
        s.setPRIX(ui->PRIX->text());


        if (s.insert()) {
            //refresh to afficher
            ui->tableView_3->setModel(Etmp2.afficher_session());
            qDebug() << "session inserted successfully";
            QMessageBox::information(nullptr, QObject::tr("OK"),
                          QObject::tr("Ajout effectué\n"
                                      "Click Cancel to exit ."), QMessageBox::Cancel);

            // Add a new row to the QTableWidget and set the item for each column
            QTableWidget *tableWidget_2 = findChild<QTableWidget*>("tableWidget_2");
            int row3 = tableWidget_2->rowCount();
            tableWidget_2->insertRow(row3);
            tableWidget_2->setItem(row3, 0, new QTableWidgetItem(s.get_MODEE()));
            tableWidget_2->setItem(row3, 1,new QTableWidgetItem(s.get_NIV_BATTERIE()));
            tableWidget_2->setItem(row3, 2, new QTableWidgetItem(s.get_VITESSE()));
            tableWidget_2->setItem(row3, 3, new QTableWidgetItem(s.get_HAPPY_HOUR()));
            tableWidget_2->setItem(row3, 4, new QTableWidgetItem(s.get_PRIX()));
        } else {
            qDebug() << "Failed to insert session into database";
        }
    }

}
void mainwindow_voiture::on_pushButton_effacer_session_clicked(){

    int id1 =ui->lineEdit_test_session->text().toUInt();

    //QString license = ui->lineEdit->text();
     session s; // declare and initialize Etmp

     bool test=Etmp2.delete_session(id1);

     if (test) {
         ui->tableView_3->setModel(Etmp2.afficher_session());

         QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("Suppression effectue.\n"
                                       "Cancel to exit."), QMessageBox::Cancel);

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                           QObject::tr("Suppression NON effectue.\n"
                                       "Cancel to exit."), QMessageBox::Cancel);
}









void mainwindow_voiture::on_pushButton_modif_session_clicked()
{
    QString ID_SESSION = ui->ID_SESSION->text();
    QString MODEE = ui->MODEE->currentText();
    QString NIV_BATTERIE = ui->NIV_BATTERIE->text();
    QString VITESSE = ui->VITESSE->text();
    QString HAPPY_HOUR = ui->HAPPY_HOUR->currentText();
    QString PRIX = ui->PRIX->text();


    session s(ID_SESSION,MODEE,NIV_BATTERIE,VITESSE,HAPPY_HOUR,PRIX);

    //get the id2 for the checkid fucntion
    int id2 = ui->ID_SESSION->text().toInt();
    s.update(s.get_ID_SESION());
    ui->tableView_3->setModel(Etmp2.afficher_session());
   /* if (s.idExists(id2)) {

     if (s.update(s.get_ID_SESSION())) {
          // Refresh the table view to show the updated data
          ui->tableView->setModel(Etmp.afficher_session());
          QMessageBox::information(this, "Update session", "session updated successfully.");
      } else {
          QMessageBox::warning(this, "Update session", "Failed to update session.");
      }}else {

        QMessageBox::warning(this, "ID EXISTE", "ID already exists, please enter another ID.");

    }*/
  }





void mainwindow_voiture::on_pushButton_PDF_session_clicked()
{
    // Prepare SQL query
        QSqlQuery query;
        query.prepare("SELECT * FROM SESION");

        // Execute query
        if (!query.exec()) {
            qDebug() << "Failed to execute query!";
            return;
        }

        // Create PDF document
        QPdfWriter writer("C:/PDF/output.pdf");
        writer.setPageSize(QPageSize(QPageSize::A4));
        writer.setPageMargins(QMarginsF(20, 20, 20, 20));

        // Create PDF painter
        QPainter painter(&writer);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        painter.setFont(QFont("Arial", 5));



        // Define table cell dimensions
        int cellWidth = 150;
        int cellHeight = 40;

        // Set table position
        int tableX = 20;
        int tableY = 20;

        // Draw table header
        painter.drawText(tableX + cellWidth , tableY, "ID_SESSION");
        painter.drawText(tableX + cellWidth * 6, tableY , "MODEE");
        painter.drawText(tableX + cellWidth * 11, tableY , "NIV_BATTERIE");
        painter.drawText(tableX + cellWidth * 18, tableY, "VITESSE");
        painter.drawText(tableX + cellWidth * 24, tableY, "HAPPY_HOUR");
        painter.drawText(tableX + cellWidth * 30, tableY, "PRIX");


        tableY += cellHeight;

        // Loop through query results and draw table cells
        int row = 5;
        while (query.next()) {
            // Draw ID_VOITURE value
            painter.drawText(tableX + cellWidth , tableY + row * cellHeight, query.value(0).toString());
            // Draw ID_CLIENT value
            painter.drawText(tableX + cellWidth * 6, tableY + row * cellHeight, query.value(1).toString());
            // Draw ID_MAINTENANCE value
            painter.drawText(tableX + cellWidth * 11, tableY + row * cellHeight, query.value(2).toString());
            // Draw MATRICULE value
            painter.drawText(tableX + cellWidth * 18, tableY + row * cellHeight, query.value(3).toString());
            // Draw BATTERIE_LVL value
            painter.drawText(tableX + cellWidth * 24, tableY + row * cellHeight, query.value(4).toString());
            // Draw BATTERIE_CAP value
            painter.drawText(tableX + cellWidth * 30, tableY + row * cellHeight, query.value(5).toString());


            row++;
            row++;
            row++;
            row++;
        }

        // Clean up
        painter.end();

        qDebug() << "PDF generated!";
    }

void mainwindow_voiture::on_pushButton_tri_session_2_clicked()
{
    // khdhit el table View mel ui
          QAbstractItemModel *model = ui->tableView_3->model();

          // Create a QSortFilterProxyModel  lel tri
          QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
          proxyModel->setSourceModel(model);

          // Sort by id
          proxyModel->setSortRole(Qt::EditRole);
          proxyModel->sort(0, Qt::AscendingOrder);

          //update lel table view
          ui->tableView_3->setModel(proxyModel);
}

void mainwindow_voiture::on_lineEdit_2_textChanged(const QString &arg1)
{

    QSqlQueryModel *model = new QSqlQueryModel(this);
       model->setQuery(QString("SELECT * FROM SESION WHERE MODEL LIKE '%%1%'").arg(arg1));
       model->setHeaderData(0, Qt::Horizontal, "ID_SESSION");
       model->setHeaderData(1, Qt::Horizontal, "MODEE");
       model->setHeaderData(2, Qt::Horizontal, "NIV_BATTERIE");
       model->setHeaderData(3, Qt::Horizontal, "VITESSE");
       model->setHeaderData(4, Qt::Horizontal, "BATTERIE_LVL");
       model->setHeaderData(5, Qt::Horizontal, "HAPPY_HOUR");
       model->setHeaderData(6, Qt::Horizontal, "PRIX");
       ui->tableView_4->setModel(model);
       ui->tableView_4->show();
}




void mainwindow_voiture::on_mode_charge_session_clicked()
{

    int quantity;
    int niv;
    int niv_batt;

        int v=ui->lineEdit_3->text().toInt();
        int id_s=ui->lineEdit_4->text().toInt();
        QSqlQuery query;
        query.prepare("SELECT QUNATITE FROM VOITURE WHERE ID_VOITURE=:idVoi");
        query.bindValue(":idVoi",v );
        if (query.exec() && query.next()) {
             quantity = query.value(0).toInt(); // Get the quantity from Voiture table
            qDebug() << "Quantity: " << quantity;
        } else {
            qDebug() << "Failed to get quantity from Voiture table!";
        }


        query.prepare("SELECT NIV_BATTERIE FROM SESION WHERE ID_SESSION=:id");
        query.bindValue(":id",id_s );
        if (query.exec() && query.next()) {
             niv = query.value(0).toInt(); // Get the NIV_BATTERIE from SESION table
            qDebug() << "NIVEAU: " << niv;
        } else {
            qDebug() << "Failed to get NIV_BATTERIE from SESION table!";
        }



        double niv_quantity = quantity*100/1000;
        int new_niv = static_cast<int>(niv - niv_quantity);

if(query.exec() && query.next()){

        if (new_niv <= 20) {
            QSqlQuery query3;

            query3.prepare("UPDATE SESION SET MODEE = 'repos' WHERE ID_SESSION = :id");
            query3.bindValue(":id", id_s);
            if (query3.exec()) {
                QMessageBox::warning(this, "REPOS MODE", "la session est en mode repos");
            } else {
                qDebug() << "Failed to update MODEE column in SESSION tableeeeeeeeeeeeeeeeeeeee!";
            }
 }
else {



QSqlQuery query2;
query2.prepare("UPDATE SESION SET NIV_BATTERIE=:new_niv WHERE ID_SESSION=:id");
query2.bindValue(":id", id_s);
query2.bindValue(":new_niv", new_niv);
if (query2.exec()) {
    qDebug() << "Updated NIV_BATTERIE in SESION table";
    QMessageBox::warning(this, "Charging", "Mise a jour de la session complete");
}
else {
    qDebug() << "Failed to update NIV_BATTERIE in SESION table!";
    return;
}

        }}




}

void mainwindow_voiture::on_pushButton_arduino_session_clicked()
{

    int PRICE;
    int id=ui->lineEdit_5->text().toInt();

                                   QSqlQuery query1;
                                   query1.prepare("SELECT PRIX FROM SESION JOIN VOITURE ON VOITURE.ID_SESSION=SESION.ID_SESSION WHERE VOITURE.ID_VOITURE = :id_voiture");
                                   query1.bindValue(":id_voiture", id);

                                    query1.exec();
                                   if (query1.next()) {
                                  PRICE=query1.value("PRIX").toInt();
                                 qDebug() << "TEST PRIX!" <<PRICE ;
                                    }
                                    if (!query1.exec()) {
                                        qDebug() << "Failed to execute query1!";
                                        return;
                                    }


                                    QByteArray priceData = QByteArray::number(PRICE);
                                 // create an instance of the arduino object
                                   a.write_to_arduino(priceData);
}
void mainwindow_voiture::on_pushButton_stat_session_clicked()
{
    session s  ;
        QSqlQuery q1,q2,q3;
               qreal tot=0,c1=0,c2=0;
               q1.prepare("SELECT ID_SESSION FROM SESION");
               q1.exec();
               q2.prepare("SELECT ID_SESSION FROM SESION WHERE MODEE='repos'");
               q2.exec();
               q3.prepare("SELECT ID_SESSION FROM SESION WHERE MODEE='actif'");
               q3.exec();
               while (q1.next()){tot++;}
               while (q2.next()){c1++;}
               while (q3.next()){c2++;}
               c1=(c1 * 100)/tot;
               c2=(c2 * 100)/tot;
               QString c3= QString::number(c1) ;
               c3="="+c3+"%";
            QString c4= QString::number(c2) ;
            c4="="+c4+"%";
             QString etat1="L" ;
             etat1=etat1+c3 ;
             QString etat2="P" ;
             etat2=etat2+c4 ;
               //Création des pie series
               QPieSeries *series = new QPieSeries();
               series->append(etat1,c1);
               series->append(etat2,c2);
               //Creation d'un charte
               QChart *chart  =new QChart();
               chart->setTitle("Les résultats:");
               chart->addSeries(series);
               chart->legend()->show();
                chart->setBackgroundBrush(QColor(252, 236, 218, 0));
               QChartView *chartView;
               chartView = new QChartView(chart,ui->graphicsView_statistic);
               chartView->setRenderHint(QPainter::Antialiasing);
               chartView->setMinimumSize(280,200);
               chartView->show();
}

void mainwindow_voiture::on_pushButton_effacer_tout_sess_clicked()
{
    session s;
        s.delete_all();
        ui->tableView_3->setModel(s.afficher_session());
}




void mainwindow_voiture::on_pushButton_chercher_session_clicked()
{
    session s;
        ui->tableView_4->setModel(s.afficher_search(ui->lineEdit_2->text()));
}





//***************************CLIENT YOUSSEF**********************************//


void mainwindow_voiture::on_pb_ajouter_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    int cin=ui->lineEdit_cin->text().toInt();
    QString adresse=ui->lineEdit_adresse->text();
    int telephone=ui->lineEdit_telephone->text().toInt();
    QString email=ui->lineEdit_email->text();
    int bonus=0;
    int reclamation=0;
    client c(id,nom,prenom,cin,adresse,telephone,email,bonus,reclamation);
    // Add a new row to the QTableWidget and set the item for each column
   // c.ajouter_client();
    if ((ui->lineEdit_id->text().isEmpty()) || (ui->lineEdit_nom->text().isEmpty()) || (ui->lineEdit_prenom->text().isEmpty()) || (ui->lineEdit_cin->text().isEmpty()) || (ui->lineEdit_adresse->text().isEmpty()) || (ui->lineEdit_telephone->text().isEmpty()) || (ui->lineEdit_email->text().isEmpty()))
    {
        QMessageBox::warning(this,"Invalide input    ","Saisie invalide!");
    }
    if ((c.ajouter_client()==false) && (!ui->lineEdit_id->text().isEmpty() )) {
            QMessageBox::warning(this,"Invalide input    ","Id existe deja!");
            }
        ui->tableView_client->setModel(c.afficher());


     // QTableWidget *tableWidget = findChild<QTableWidget*>("tableWidget");
    //  int row = tableWidget->rowCount();
     // tableWidget->insertRow(row);
    /*  tableWidget->setItem(row, 0, new QTableWidgetItem(c.get_nom()));
      tableWidget->setItem(row, 1, new QTableWidgetItem(c.get_prenom()));
      tableWidget->setItem(row, 2, new QTableWidgetItem(c.get_cin()));
      tableWidget->setItem(row, 3, new QTableWidgetItem(c.get_adresse()));
      tableWidget->setItem(row, 4, new QTableWidgetItem(c.get_telephone()));
      tableWidget->setItem(row, 5, new QTableWidgetItem(c.get_email()));
      tableWidget->setItem(row, 6, new QTableWidgetItem(c.get_bonus()));
      tableWidget->setItem(row, 7, new QTableWidgetItem(c.get_reclamation()));*/
}





void mainwindow_voiture::on_pb_supprimer_clicked()
{
    client c;
    c.setID(ui->lineEdit_supp_id->text().toInt());
    bool test=c.supprimer_client(c.get_id());
    ui->tableView_client->setModel(c.afficher());
    /*QMessageBox msgbox;
    if (test)
            msgbox.setText("Supprission avec succées!");
    else
            msgbox.setText("Echec de supprission!");
            msgbox.exec();*/
}

void mainwindow_voiture::on_pb_update_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    int cin=ui->lineEdit_cin->text().toInt();
    QString adresse=ui->lineEdit_adresse->text();
    int telephone=ui->lineEdit_telephone->text().toInt();
    QString email=ui->lineEdit_email->text();
    client c(id,nom,prenom,cin,adresse,telephone,email,0,0);
    c.modifier_client(c.get_id());
    ui->tableView_client->setModel(c.afficher());
}

void mainwindow_voiture::on_pb_avertissement_clicked()
{
    int id=ui->lineEdit_id2->text().toInt();
    int recl=ui->spinBox_averti->text().toInt();
    client c;
    c.ajouter_averti(id,recl);
    c.reduction_averti(id,recl);
    ui->tableView_client->setModel(c.afficher());
}

void mainwindow_voiture::on_pb_avertissement_2_clicked()
{
    int id=ui->lineEdit_id2->text().toInt();
    //int recl=ui->spinBox_averti->text().toInt();
    client c;
    c.update_bonus(id);
    ui->tableView_client->setModel(c.afficher());
    if (c.happy_hour(id)==false)
    {
        QMessageBox::warning(this,"Invalide!    ","Happy Hour n'est pas valide pour ce client !     ");
    }
}


void mainwindow_voiture::on_pushButton_pdf_client_clicked()
{
    client c;
    c.pdf();
    {QMessageBox::information(nullptr, QObject::tr("database is open"),
    QObject::tr("PDF exported successfully!\n"
    "Click Cancel to exit."), QMessageBox::Cancel);}
}

void mainwindow_voiture::on_pushButton_dec_tri_clicked()
{
    client c;
    ui->tableView_client->setModel(c.afficher_d());
}

void mainwindow_voiture::on_pushButton_croiss_tri_clicked()
{
    client c;
    ui->tableView_client->setModel(c.afficher_c());
}

void mainwindow_voiture::on_pushButton_search_client_clicked()
{
    client c;
    ui->tableView_client->setModel(c.afficher_search(ui->lineEdit_search->text()));
}

void mainwindow_voiture::on_pushButton_effacertout_clie_clicked()
{
    client c;
    c.delete_all();
    ui->tableView_client->setModel(c.afficher_c());
}

void mainwindow_voiture::on_pushButton_stat_client_clicked()
{

    QSqlQuery q1,q2,q3;
               qreal tot=0,c1=0,c2=0;
               q1.prepare("SELECT ID_CLIENT FROM CLIENT");
               q1.exec();
               q2.prepare("SELECT ID_CLIENT FROM CLIENT WHERE BONUS > 200");
               q2.exec();
               q3.prepare("SELECT ID_CLIENT FROM CLIENT WHERE BONUS < 200");
               q3.exec();
               while (q1.next()){tot++;}
               while (q2.next()){c1++;}
               while (q3.next()){c2++;}
               c1=(c1 * 100)/tot;
               c2=(c2 * 100)/tot;
               QString c3= QString::number(c1) ;
               c3="="+c3+"%";
            QString c4= QString::number(c2) ;
            c4="="+c4+"%";
             QString etat1="Fidele" ;
             etat1=etat1+c3 ;
             QString etat2="Non Fidele" ;
             etat2=etat2+c4 ;
               //Création des pie series
               QPieSeries *series = new QPieSeries();
               series->append(etat1,c1);
               series->append(etat2,c2);
               //Creation d'un charte
               QChart *chart  =new QChart();
               chart->setTitle("Les résultats des cartes fidelitées:");
               chart->addSeries(series);
               chart->legend()->show();
               chart->setBackgroundBrush(QColor(31, 86, 62, 1));
               QChartView *chartView;
               chartView = new QChartView(chart,ui->graphicsView_client);
               chartView->setRenderHint(QPainter::Antialiasing);
               chartView->setMinimumSize(280,200);
               chartView->show();
}

void mainwindow_voiture::on_pushButton_tester_clientclicked()
{
    QByteArray data = a.getserial()->readAll();
               // qDebug() << "Received data from Arduino:" << data;
                           QString strData(data);
                         //  qDebug() << "Received data:" << strData;
                           int startIndex = strData.indexOf("Card UID:");
                              if (startIndex != -1) {
                                  QString uid = strData.mid(startIndex + 10, 11);
                                  qDebug() << "Card UID:" << uid;
                                  uid.remove(" ");
                                  bool ok;
                                      int decimalValue = uid.toInt(&ok, 16);
                                      qDebug() <<decimalValue ;
                                      QSqlQuery query;
                                        client cc;
                                      if (cc.test_maintenance(decimalValue)==true)
                                      {
                                          qDebug() << "Id valide";
                                          query.prepare("SELECT * FROM MAINTENANCE  WHERE DATE >= NOW() AND DATE <= DATE_ADD(NOW(), INTERVAL 5 MINUTE)");
                                                                                   query.bindValue(":id", decimalValue);
                                                                                   query.exec();
                                                                               //    if (query.next())
                                                                               //    {
                                                                                       qDebug() << "Resa valide";
                                                                                       QDateTime currentDateTime = QDateTime::currentDateTime();
                                                                                       QString dateTimeStr = currentDateTime.toString("yyyy-MM-dd hh:mm");
                                                                                       qDebug() << dateTimeStr;
                                                                                       //test type panne
                                                                                       query.prepare("SELECT* FROM MAINTENANCE WHERE ID_MAINTENANCE=:id");
                                                                                       query.bindValue(":id", decimalValue);
                                                                                       query.exec();
                                                                                       while (query.next()) {
                                                                                            QString tp=query.value("TYPEE").toString();
                                                                                            qDebug()<<"Type"<<tp;
                                                                                            if (tp=="Panne")
                                                                                            {
                                                                                                a.write_to_arduino("1");
                                                                                                query.prepare("UPDATE MAINTENANCE SET COUT=:prix WHERE ID_MAINTENANCE=:id");
                                                                                                query.bindValue(":prix", 0);
                                                                                                query.bindValue(":id", decimalValue);
                                                                                                query.exec();

                                                                                              //  A.write_to_arduino(data);
                                                                                            }
                                                                                            else if (tp=="Lavage")
                                                                                            {
                                                                                                a.write_to_arduino("2");
                                                                                                query.prepare("UPDATE MAINTENANCE SET COUT=:prix WHERE ID_MAINTENANCE=:id");
                                                                                                query.bindValue(":prix", 0);
                                                                                                query.bindValue(":id", decimalValue);
                                                                                                query.exec();
                                                                                            }
                                                                                            //qDebug()<<"hello"<<recl;
                                                                                       }


                                                                              /*     }
                                                                                   else
                                                                                   {
                                                                                       qDebug() << "Resa invalide";
                                                                                   }*/

                                      }
                              else {
                                /*  query.prepare("SELECT* FROM MAINTENANCE WHERE ID_MAINTENANCE=:id");
                                  query.bindValue(":id", decimalValue);
                                  query.exec();
                                  while (query.next()) {*/
                                    //   QDateTime date=query.value("DATE_HR");
                                     //  qDebug()<<"hello"<<date;
                                      qDebug() << "Resa invalide";
                                  //}
                                  a.write_to_arduino("3");
                              }
                              }

        data = a.read_from_arduino();
  //  qDebug() << "Received data from Arduino:" << data;
}


