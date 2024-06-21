#include "mainwindow_maint.h"
#include "ui_mainwindow_maint.h"
#include "maintenance.h"
#include "arduino.h"
#include <QtWidgets>
#include <QTabWidget>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QString>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QValidator>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QtPrintSupport>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QMessageBox>
#include <QSound>
#include <vector>
#include <QDebug>
#include <stdlib.h>

mainwindow_maint::mainwindow_maint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwindow_maint)
{
    ui->setupUi(this);

    arduino a;
    if (QObject::connect(a.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()))) {
            qDebug() << "Connected to the readyRead() signal";
        } else {
            qDebug() << "Failed to connect to the readyRead() signal";
        }
qDebug() << "Connecting to readyRead() signal...";

     QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
     ui->setupUi(this);
  ui->tableView->setModel(Etmp.afficher_maintenance());
  // Find the QTableWidget using its object name
     QTableWidget *tableWidget = findChild<QTableWidget*>("tableWidget");
     // Use the QTableWidget object as needed
      int row = tableWidget->rowCount();
      ui->lineEdit_idmaintenance->setValidator(new QIntValidator(1,999, this));
      ui->combobox_type->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z]+(?:\\s+[a-zA-Z]+)*$"),  this));
      ui->lineEdit_Cout->setValidator(new QRegExpValidator(QRegExp("^[\\d]+(\\.[\\d]{1,2})?$"),  this));
      ui->lineEdit_Dure->setValidator(new QRegExpValidator(QRegExp("^([01]?[0-9]|2[0-3]):[0-5][0-9]$"),  this));

}

mainwindow_maint::~mainwindow_maint()
{
    delete ui;
}



void mainwindow_maint::update_label()
{
   // qDebug() << "update_label() called";
    // Read the data from the serial port




    //qDebug() << "Data received from Arduino:" << data;

    // Handle the data as needed
    // Convert the data to a string and parse the RFID UID
   // QString uidString = QString(data).trimmed(); // Trim whitespace from the data
   /* if (uidString.length() == 0) {
        // No UID was read
        return;
    }*/
   // qDebug() << "RFID UID:" << uidString;

    // Update the UI with the RFID UID
   // ui->rfidLabel->setText(uidString);
}

/*void MainWindow::onReadyRead()
{
    // Read the data from the serial port
    QByteArray data = A.read_from_arduino();
    qDebug() << "Data received from Arduino:" << data;

    // Handle the data as needed
    // Convert the data to a string and parse the RFID UID
    QString uidString = QString(data).trimmed(); // Trim whitespace from the data
    if (uidString.length() == 0) {
        // No UID was read
        return;
    }
    qDebug() << "RFID UID:" << uidString;

    // Update the UI with the RFID UID
    ui->rfidLabel->setText(uidString);
}
*/


void mainwindow_maint::on_pushButton_ajout_maint_clicked()
{
    maintenance m;



    //function true
    bool isValid = true ;
//id number or not
QString  id = ui->lineEdit_idmaintenance->text();

int  id2 = ui->lineEdit_idmaintenance->text().toInt();

if (m.id_exist(id2)) {
    QMessageBox::warning(this, "ID EXISTE", "id existe deja !! .");
isValid=false;
}

QString id_maintenance = ui->lineEdit_idmaintenance->text();
QString type = ui->combobox_type->currentText();
QString description = ui->plainTextEdit->toPlainText();
QString cout = ui->lineEdit_Cout->text();
QString duree = ui->lineEdit_Dure->text();
QString date_hr = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
QDateTime dateTime = QDateTime::fromString(date_hr, "yyyy-MM-dd hh:mm:ss");
if (id_maintenance.isEmpty() || type.isEmpty() || description.isEmpty() || cout.isEmpty() || duree.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields.");
      isValid=false;
    }
QRegExp dateRegex("^\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}$");
QRegExp typeRegex("^[a-zA-Z]+(?:\\s+[a-zA-Z]+)*$");
QRegExp descriptionRegex("^[a-zA-Z0-9 ]{0,100}$");
QRegExp coutRegex("^[\\d]+(\\.[\\d]{1,2})?$");
QRegExp dureeRegex("^([0-9]|[01][0-9]|2[0-3]):[0-5][0-9]$");
if (!dateRegex.exactMatch(date_hr)){
    QMessageBox::warning(this, "Invalid Input", "Date must be in the format YYYY-MM-DD HH:MM:SS.");
    isValid = false;
}
if (!dureeRegex.exactMatch(duree)) {
    QMessageBox::warning(this, "Invalid Input", "Duration must be in the format HH:MM.");
    isValid = false;
}

if (!descriptionRegex.exactMatch(description)) {
    QMessageBox::warning(this, "Invalid Input", "Description reached 100 caracters .");
    isValid = false;
}
 if (isValid) {





    m.setid(ui->lineEdit_idmaintenance->text());
   m.settype(ui->combobox_type->currentText());
    m.setdate(ui->dateTimeEdit->dateTime());
    m.setdescription(ui->plainTextEdit->toPlainText());
    m.setcout(ui->lineEdit_Cout->text());
    m.setduree(ui->lineEdit_Dure->text());


    QDateTime selectedDateTime = ui->dateTimeEdit->dateTime();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString durationText = ui->lineEdit_Dure->text();
    QRegExp durationRegex("^([0-9]|[01][0-9]|2[0-3]):([0-5][0-9])$");
    if (durationRegex.indexIn(durationText) == -1) {
        QMessageBox::warning(nullptr, "Invalid Duration", "Please enter a valid duration in the format \"hh:mm\"");
        return;
    }
    int durationHours = durationRegex.cap(1).toInt();
    int durationMinutes = durationRegex.cap(2).toInt();
    int durationSeconds = durationHours * 3600 + durationMinutes * 60;
   QDateTime previousDateTime;
    if (!m.isValidDT( previousDateTime, selectedDateTime, durationSeconds)) {
        QMessageBox::warning(nullptr, "Invalid Date and Time", "Please select a date and time that is after the previous maintenance record and before the ready time");
        return ;
    }


if (m.insert(m)){
    m.setid(ui->lineEdit_idmaintenance->text());
   m.settype(ui->combobox_type->currentText());
    m.setdate(ui->dateTimeEdit->dateTime());
    m.setdescription(ui->plainTextEdit->toPlainText());
    m.setcout(ui->lineEdit_Cout->text());
    m.setduree(ui->lineEdit_Dure->text());


    QDateTime selectedDateTime = ui->dateTimeEdit->dateTime();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString durationText = ui->lineEdit_Dure->text();
    QRegExp durationRegex("^([0-9]|[01][0-9]|2[0-3]):([0-5][0-9])$");
    if (durationRegex.indexIn(durationText) == -1) {
        QMessageBox::warning(nullptr, "Invalid Duration", "Please enter a valid duration in the format \"hh:mm\"");
        return;
    }
    int durationHours = durationRegex.cap(1).toInt();
    int durationMinutes = durationRegex.cap(2).toInt();
    int durationSeconds = durationHours * 3600 + durationMinutes * 60;
   QDateTime previousDateTime;
    if (!m.isValidDT( previousDateTime, selectedDateTime, durationSeconds)) {
        QMessageBox::warning(nullptr, "Invalid Date and Time", "Please select a date and time that is after the previous maintenance record and before the ready time");
        return ;
    }


    ui->tableView->setModel(Etmp.afficher_maintenance());
            qDebug() << "maintenance inserted successfully";
            QMessageBox::information(nullptr, QObject::tr("OK"),
                          QObject::tr("Ajout effectué🙂\n"
                                      "Click Cancel to exit ."), QMessageBox::Cancel);
           // QSound::play("C:/Users/bouch/qt-things/notif.wav");
      QTableWidget *tableWidget = findChild<QTableWidget*>("tableWidget");
      int row = tableWidget->rowCount();
      tableWidget->insertRow(row);
      tableWidget->setItem(row, 0, new QTableWidgetItem(m.get_type()));
      tableWidget->setItem(row, 1, new QTableWidgetItem(m.get_date().toString("yyyy-MM-dd hh:mm:ss")));
      tableWidget->setItem(row, 2, new QTableWidgetItem(m.get_description()));
      tableWidget->setItem(row, 3, new QTableWidgetItem(m.get_cout()));
      tableWidget->setItem(row, 4, new QTableWidgetItem(m.get_duree()));
      qDebug() << "bouton: 'Ajouter Maintenance'  appuyé";
}
      else {
           qDebug() << "Failed to insert Maintenance !  into database";
      }

 }

 QDateTime now = QDateTime::currentDateTime();
 // Get the selected date and time from the dateTimeEdit widget
 QDateTime selectedDateTime = ui->dateTimeEdit->dateTime();
 // Parse the duration text input into hours and minutes
 QString durationText = ui->lineEdit_Dure->text();
 QRegExp durationRegex("^([0-9]|[01][0-9]|2[0-3]):([0-5][0-9])$");
 if (durationRegex.indexIn(durationText) == -1) {
     QMessageBox::warning(nullptr, "Invalid Duration", "Please enter a valid duration in the format \"hh:mm\"");
     return;
 }
 int durationHours = durationRegex.cap(1).toInt();
 int durationMinutes = durationRegex.cap(2).toInt();
 // Calculate the duration in seconds
 int durationSeconds = durationHours * 3600 + durationMinutes * 60;
 // Calculate the ready time
 QDateTime readyDateTime = selectedDateTime.addSecs(durationSeconds);
 // Format the ready time as "hh:mm"
 QString readyTimeString = readyDateTime.toString("hh:mm");
 int remainingSeconds = durationSeconds;
 QMessageBox remainingTimeMsgBox;
 remainingTimeMsgBox.setWindowTitle("Remaining Time");
 // Create a progress bar to show the remaining time
 QProgressBar *progressBar = new QProgressBar(&remainingTimeMsgBox);
 progressBar->setRange(0, remainingSeconds);
 progressBar->setValue(remainingSeconds);
 remainingTimeMsgBox.layout()->addWidget(progressBar);
 // Create a timer to update the remaining time
 QTimer timer;
 QObject::connect(&timer, &QTimer::timeout, [&]() {
     // Decrement the remaining time by 1 second
     remainingSeconds--;
     progressBar->setValue(remainingSeconds);
     remainingTimeMsgBox.setText("Remaining time: " + QString::number(remainingSeconds) + " seconds");
     // If the remaining time is 0, stop the timer and play a sound
     if (remainingSeconds == 0) {
         QMessageBox messageBox;
         QSound::play("C:/Users/bouch/qt-things/notif.wav"); // replace with path to your sound file
         messageBox.setWindowTitle("Car Ready");
         messageBox.setText("Car ready boi🙂!!");
         messageBox.setIconPixmap(QPixmap("C:/Users/bouch/qt-things/notification-2.png"));
         messageBox.exec();
         timer.stop();
     }
 });
 // Start the timer with a 1-second interval
 timer.start(1000);
 // Show the remaining time message box
 remainingTimeMsgBox.setText("Remaining time: " + QString::number(remainingSeconds) + " seconds");
 remainingTimeMsgBox.exec();


}

void mainwindow_maint::on_pushButton_3_maint_clicked()
{
    int id1 =ui->lineEdit_2->text().toUInt();
     maintenance m ;// declare and initialize Etmp
     bool test=Etmp.delete_maintenance(id1);
     if (test) {
         ui->tableView->setModel(Etmp.afficher_maintenance());
         QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("Suppression effectue🙂.\n"
                                       "Cancel to exit."), QMessageBox::Cancel);
     }
     else
     {
         QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                           QObject::tr("Suppression NON effectue(L'ID n'existe pas dans la base de données!)\n"
                                       "Cancel to exit."), QMessageBox::Cancel);

     }
}
void mainwindow_maint::on_pushButton_9_maint_clicked()
{
     maintenance m ;// declare and initialize Etmp
     bool test=Etmp.delete_allmaintenance();
     if (test) {
         ui->tableView->setModel(Etmp.afficher_maintenance());
         QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("Suppression effectue🙂.\n"
                                       "Cancel to exit."), QMessageBox::Cancel);
     }
}

void mainwindow_maint::on_pushButton_4_modifier_maint_clicked()
{
    QString id = ui->lineEdit_idmaintenance->text();
    QString type = ui->combobox_type->currentText();
    QString description = ui->plainTextEdit->toPlainText();
    QString cout = ui->lineEdit_Cout->text();
    QString duree = ui->lineEdit_Dure->text();
    QString date_hr = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QDateTime dateTime = QDateTime::fromString(date_hr, "yyyy-MM-dd hh:mm:ss");
    maintenance m;
    int  id2 = ui->lineEdit_idmaintenance->text().toInt();
    m.setid(id);
    m.settype(type);
    m.setdescription(description);
    m.setcout(cout);
    m.setduree(duree);
    m.setdate(dateTime);
    if (m.id_exist(id2))
    {
    if (m.update_maintenance(m, ui->tableWidget)) {
        // Refresh the table view to show the updated data
        ui->tableView->setModel(m.afficher_maintenance());
        QMessageBox::information(this, "Update Maintenance", "Maintenance updated successfully🙂.");
    } else {
        QMessageBox::warning(this, "Update Maintenance", "Failed to update Maintenance.");
    }}else{
        QMessageBox::warning(this, "!", " please enter an ID.");

    }
}
void mainwindow_maint::on_recherche_textChanged(const QString &arg1)
{
    ui->tableView->setModel(Etmp.afficher_search_result(ui->recherche->text() ));
}

void mainwindow_maint::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(ui->comboBox->currentText()=="id ↓"){ ui->tableView->setModel(Etmp.afficher_id_decroissant());}
        if(ui->comboBox->currentText()=="id ↑"){ ui->tableView->setModel(Etmp.afficher_id_croissant());}
}

void mainwindow_maint::on_pushButton_7_maint_clicked()
{
maintenance m ;
m.telechargerPDF();
{QMessageBox::information(nullptr, QObject::tr("database is open"),
QObject::tr("PDF exported successfully🙂!\n"
"Click Cancel to exit."), QMessageBox::Cancel);}
}

void mainwindow_maint::on_pushButton_8_maint_clicked()
{
    maintenance m ;
    QSqlQuery q1,q2,q3;
   /* QByteArray data = A.getserial()->readAll();
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
                                        maintenance m;
                                      if (m.test_maintenance(decimalValue)==true)
                                      {
                                          qDebug() << "Id valide";
                                          query.prepare("SELECT * FROM MAINTENANCE  WHERE DATE >= NOW() AND DATE <= DATE_ADD(NOW(), INTERVAL 30 MINUTE)");
                                                                                   query.bindValue(":id", decimalValue);
                                                                                  query.exec();
                                                                               //    if (query.next())
                                                                               //    {
                                                                                       qDebug() << "Resa valide";
                                                                                       QDateTime currentDateTime = QDateTime::currentDateTime();
                                                                                       QString dateTimeStr = currentDateTime.toString("yyyy-MM-dd hh:mm");
                                                                                       qDebug() << dateTimeStr;
                                                                                       //test type panne
                                                                                       int recl;
                                                                                       query.prepare("SELECT* FROM MAINTENANCE WHERE ID_MAINTENANCE=:id");
                                                                                       query.bindValue(":id", decimalValue);
                                                                                       query.exec();
                                                                                       while (query.next()) {
                                                                                            QString tp=query.value("TYPE").toString();
                                                                                            qDebug()<<"Type"<<tp;
                                                                                            if (tp=="Panne")
                                                                                            {
                                                                                                A.write_to_arduino("1");
                                                                                                query.prepare("UPDATE MAINTENANCE SET COUT=:prix WHERE ID_MAINTENANCE=:id");
                                                                                                query.bindValue(":prix", 0);
                                                                                                query.bindValue(":id", decimalValue);
                                                                                                query.exec();

                                                                                              //  A.write_to_arduino(data);
                                                                                            }
                                                                                            else if (tp=="Lavage")
                                                                                            {
                                                                                                A.write_to_arduino("2");
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
                                    //  }
                           //   else {
                                 /* query.prepare("SELECT* FROM MAINTENANCE WHERE ID_MAINTENANCE=:id");
                                  query.bindValue(":id", decimalValue);
                                  query.exec();
                                  while (query.next()) {*/
                                    //   QDateTime date=query.value("DATE_HR");
                                     //  qDebug()<<"hello"<<date;
                                  //    qDebug() << "Resservation invalide";
                                 // }

                                //  A.write_to_arduino("3");
                           //   }
                            //  }
       // data = A.read_from_arduino();
           qreal tot=0,c1=0,c2=0;
           q1.prepare("SELECT ID_MAINTENANCE FROM MAINTENANCE");
           q1.exec();
           q2.prepare("SELECT ID_MAINTENANCE FROM MAINTENANCE WHERE type='Lavage'");
           q2.exec();
           q3.prepare("SELECT ID_MAINTENANCE FROM MAINTENANCE WHERE type='Panne'");
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

}
