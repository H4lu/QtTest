#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QSslSocket>
#include <QSsl>
#include "mainwindow.h"


class Jsonparser : public QObject
{
    Q_OBJECT

private:

    QString findAdr;

    QNetworkAccessManager *manager;
public:
    explicit Jsonparser(QObject *parent = nullptr);

    void getTXR(QString findAddress, MainWindow *window);
    void getTXS(QString findAddress, MainWindow *window);
    void getTA(QString findAddress, QString trans, MainWindow *window);


public slots:
    void onResultTXR(QNetworkReply *reply);
    void onResultTXS(QNetworkReply *reply);
    void onResultTA(QNetworkReply *reply);

signals:
    void sigTXR(QVector<QString> *temp);
    void sigTXS(QVector<QString> *temp);
    void sigTA(QVector<QString> *tempMyWallet, QVector<QString> *adr, bool inout, QVector<qulonglong> *sum, int date);

};


#endif // JSONPARSER_H
