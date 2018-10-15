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

    void getTX(QString findAddress, MainWindow *window);
    void getTR(QVector<Address> *temp, QVector<Address> *data);


public slots:
    void onResultTX(QNetworkReply *reply);
    //void onResultTA(QNetworkReply *reply);

signals:
    void sigTX(QVector<Address> *temp);
private:
    QNetworkAccessManager *manager;
};


#endif // JSONPARSER_H
