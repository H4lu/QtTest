#include "jsonparser.h"
#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>


Jsonparser::Jsonparser(QObject *parent) : QObject (parent)
{
    this->manager = new QNetworkAccessManager();
}
void Jsonparser::getTXR(QString findAddress, MainWindow *window)
{
    QString url ="https://chain.so/api/v2/get_tx_received/BTC/";
    connect(this->manager, &QNetworkAccessManager::finished, this, &Jsonparser::onResultTXR);
    connect(this, &Jsonparser::sigTXR, window, &MainWindow::onTXR);
    QNetworkRequest req = QNetworkRequest(QUrl(url.append(findAddress)));
    qDebug() << "Use this url: " + req.url().toString();
    this->manager->get(req);
}

void Jsonparser::getTXS(QString findAddress, MainWindow *window)
{
    QString url ="https://chain.so/api/v2/get_tx_spent/BTC/";
    connect(this->manager, &QNetworkAccessManager::finished, this, &Jsonparser::onResultTXS);
    connect(this, &Jsonparser::sigTXS, window, &MainWindow::onTXS);
    QNetworkRequest req = QNetworkRequest(QUrl(url.append(findAddress)));
    qDebug() << "Use this url: " + req.url().toString();
    this->manager->get(req);
}

void Jsonparser::onResultTXR(QNetworkReply *reply)
{
    qDebug()<<"on jsonparser result!";
    QVector<QString> temp;// = new QVector<QString>;

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

    QJsonObject root = document.object();

    QJsonValue jz = root.value("data");

    QJsonObject jv = jz.toObject();


    QJsonArray ja= jv["txs"].toArray();

    for(int i = 0; i < ja.count(); i++)
    {
        QJsonObject subtree = ja.at(i).toObject();

        QString next;

        next=subtree.value("txid").toString();

        temp.append(next);

    }
    qDebug()<<"Emit signal";
    sigTXR(&temp);

    disconnect(this->manager, &QNetworkAccessManager::finished, this, &Jsonparser::onResultTXR);
    reply->deleteLater();
}

void Jsonparser::onResultTXS(QNetworkReply *reply)
{
    qDebug()<<"on jsonparser result!";
    QVector<QString> temp;// = new QVector<QString>;

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

    QJsonObject root = document.object();

    QJsonValue jz = root.value("data");

    QJsonObject jv = jz.toObject();


    QJsonArray ja= jv["txs"].toArray();

    for(int i = 0; i < ja.count(); i++)
    {
        QJsonObject subtree = ja.at(i).toObject();

        QString next;

        next=subtree.value("txid").toString();

        temp.append(next);

    }
    qDebug()<<"Emit signal";
    sigTXS(&temp);

    disconnect(this->manager, &QNetworkAccessManager::finished, this, &Jsonparser::onResultTXS);
    reply->deleteLater();
}

void Jsonparser::getTA(QString findAddress, QString trans, MainWindow *window)
{
    findAdr = findAddress;
    QString url ="https://chain.so/api/v2/get_tx/BTC/";
    connect(this->manager, &QNetworkAccessManager::finished, this, &Jsonparser::onResultTA);
    connect(this, &Jsonparser::sigTA, window, &MainWindow::onTA);
    QNetworkRequest req = QNetworkRequest(QUrl(url.append(trans)));
    this->manager->get(req);
}

void Jsonparser::onResultTA(QNetworkReply *reply)
{
    QVector<QString> tempMyWallet;// = new QVector<QString>;

    QVector<QString> adr;// = new QVector<QString>;
    bool inout = false;
    QVector<qulonglong> sum;
    int date=0;

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject root = document.object();
    QJsonValue jz = root.value("data");
    QJsonObject jv = jz.toObject();
    int dateTr= jv["time"].toInt();
    QJsonArray ji= jv["inputs"].toArray();
    QJsonArray jo= jv["outputs"].toArray();
    int adrIn=0;
    for(int i = 0; i < ji.count(); i++)
    {
        QJsonObject subtree = ji.at(i).toObject();
        if(findAdr ==  subtree.value("address").toString())
        {
            adrIn=1;
        }
    }
    if (adrIn == 1)
    {
        for(int i = 0; i < ji.count(); i++)
        {
            QJsonObject subtree = ji.at(i).toObject();
            tempMyWallet.append(subtree.value("address").toString());
        }
        for(int i = 0; i < jo.count(); i++)
        {
            QJsonObject subtree = jo.at(i).toObject();
            if(subtree.value("address").toString()!=findAdr)
            {
                adr.append(subtree.value("address").toString());
                QString sumStr=(subtree.value("value").toString());
                sum.append((qulonglong)(sumStr.toDouble(nullptr)*100000000));
                inout = false;
                date=dateTr;
            }
        }
    }else
    {
        for(int i = 0; i < ji.count(); i++)
        {
            QJsonObject subtree = ji.at(i).toObject();
            tempMyWallet.append(subtree.value("address").toString());
        }
        for(int i = 0; i < jo.count(); i++)
        {
            QJsonObject subtree = jo.at(i).toObject();
            if(subtree.value("address").toString()==findAdr)
            {
                adr.append(subtree.value("address").toString());
                QString sumStr=(subtree.value("value").toString());
                sum.append((qulonglong)(sumStr.toDouble(nullptr)*100000000));
                inout = true;
                date=dateTr;
            }
        }
    }


    sigTA(&tempMyWallet, &adr, inout, &sum, date);
    disconnect(this->manager, &QNetworkAccessManager::finished, this, &Jsonparser::onResultTA);
    reply->deleteLater();
}
