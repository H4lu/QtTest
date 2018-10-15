#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QVector>
#include "jsonparser.h"

class Address;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->networkManager = new QNetworkAccessManager();
    this->networkManager->connectToHostEncrypted("https://chain.so/api/v2/");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"on button clicked!";
    QString adrText;
    adrText = ui->lineEdit->text();
    //QString url ="https://chain.so/api/v2/get_address_balance/BTC/";
    QString url ="https://chain.so/api/v2/get_tx_received/BTC/";
    // Connect networkManager response to the handler
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onResult);
    // We get the data, namely JSON file from a site on a particular url
    networkManager->get(QNetworkRequest(QUrl(url.append(adrText))));
}

void MainWindow::onResult(QNetworkReply *reply)
{
    qDebug()<<"on RESUTL!";
    // If there are no errors
    if(!reply->error()){
        qDebug()<<"mo ERRRORS!!";
        // So create an object Json Document, by reading into it all the data from the response
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

        // Taking from the document root object
        QJsonObject root = document.object();

        /* We find the object "departament", which is the very first in the root object.
         * Use the keys() method gets a list of all objects and the first index
         * Take away the name of the object on which we obtain its value
         * */
        for(QString key : root.keys()) {
            ui->textEdit->append(key);
        }
        //ui->textEdit->append(root.keys().at(0) + ": " + root.value(root.keys().at(0)).toString());

        // The second value prescribe line
        QJsonValue jv = root.value("data");

        // If the value is an array, ...

        // ... then pick from an array of properties
        QJsonObject ja = jv.toObject();

        // Taking the values of the properties and last name by adding them to textEdit
        ui->textEdit->append(ja.value("network").toString());
        ui->textEdit->append(ja.value("address").toString());
        ui->textEdit->append(ja.value("confirmed_balance").toString());
        ui->textEdit->append(ja.value("unconfirmed_balance").toString());
    }
    reply->deleteLater();
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"on button2 clicked!";
    QString adrText;
    adrText = ui->lineEdit->text();
    Jsonparser *q1 = new Jsonparser(this);
    q1->getTX(adrText,this);

}
void MainWindow::onTX(QVector<Address> *temp)
{   qDebug()<<"on tX";
    for (int i = 0; i < temp->size(); ++i)
    {
        qDebug()<<temp->at(i).tx;
        qDebug()<<temp->at(i).time;
        qDebug()<<temp->at(i).inout;
        qDebug()<<temp->at(i).val;

    }
}
