#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QSslSocket>
#include <QSsl>
#include "mainwindow.h"

#include "address.h"

class Jsonparser : public QObject
{
    Q_OBJECT
public:
    explicit Jsonparser(QObject *parent = nullptr);

    void getTXR(QString findAddress, MainWindow *window);
    void getTXS(QString findAddress, MainWindow *window);
 //   void getTA(Address *tx, MainWindow *window);


public slots:
    void onResultTXR(QNetworkReply *reply);
    void onResultTXS(QNetworkReply *reply);
  //  void onResultTA(QNetworkReply *reply);

signals:
    void sigTXR(QVector<Address> *temp);
    void sigTXS(QVector<Address> *temp);
 //   void sigTA(QVector<Address> *temp);
private:
    QNetworkAccessManager *manager;
};


#endif // JSONPARSER_H
