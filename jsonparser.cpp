#include "jsonparser.h"
#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
Jsonparser::Jsonparser(QObject *parent) : QObject (parent)
{
   this->manager = new QNetworkAccessManager();
}
void Jsonparser::getTX(QString findAddress, MainWindow *window)
{
    QString url ="https://chain.so/api/v2/get_tx_received/BTC/";  

    connect(this->manager, &QNetworkAccessManager::finished, this, &Jsonparser::onResultTX);
    connect(this, &Jsonparser::sigTX, window, &MainWindow::onTX);
    QNetworkRequest req = QNetworkRequest(QUrl(url.append(findAddress)));
    qDebug() << "Use this url: " + req.url().toString();
   this->manager->get(req);

}

void Jsonparser::onResultTX(QNetworkReply *reply)
{
    qDebug()<<"on jsonparser result!";
    QVector<Address> *temp = new QVector<Address>();

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

    QJsonObject root = document.object();

    QJsonValue jz = root.value("data");

    QJsonObject jv = jz.toObject();


    QJsonArray ja= jv["txs"].toArray();

    for(int i = 0; i < ja.count(); i++)
    {
        QJsonObject subtree = ja.at(i).toObject();

        Address next;

        next.tx=subtree.value("txid").toString();
        next.val=subtree.value("value").toString();
        next.time=subtree.value("time").toInt();
        next.inout = true;

        temp->append(next);

    }
    qDebug()<<"Emit signal";
    sigTX(temp);

    disconnect(this->manager, &QNetworkAccessManager::finished, this, &Jsonparser::onResultTX);
    reply->deleteLater();
}

