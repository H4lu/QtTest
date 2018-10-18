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

#include <QTimer>
#include <jsonparser.h>


QGraphicsRectItem *rectangle;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->networkManager = new QNetworkAccessManager();
    this->networkManager->connectToHostEncrypted("https://chain.so/api/v2/");
    // txData = new QVector<QString>;
    numTX=0;
    curTX =0;

    QGraphicsScene *sceneIn = new QGraphicsScene(this);
    sceneIn->setItemIndexMethod(QGraphicsScene::NoIndex);
    sceneIn->setSceneRect(0, 0, 400, 400);
    ui->graphicsViewIN->setScene(sceneIn);
    ui->graphicsViewIN->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsViewIN->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsViewIN->setRenderHint(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Jsonparser *jsp = new Jsonparser();
    qDebug()<<"on button2 clicked!";
    adrText = ui->lineEdit->text();
    jsp->getTXR(adrText,this);

}
void MainWindow::onTXR(QVector<QString> *temp)
{
    Jsonparser *jsp = new Jsonparser();
    qDebug()<<"on tXR";
    for (int i = 0; i < temp->size(); ++i)
    {
        qDebug()<<temp->at(i);

        txData.append(temp->at(i));
    }
    QThread timer;
    timer.sleep(2);
    jsp->getTXS(adrText,this);
}


void MainWindow::onTXS(QVector<QString> *temp)
{
    Jsonparser *jsp = new Jsonparser();
    qDebug()<<"on tXS";
    for (int i = 0; i < temp->size(); ++i)
    {
        qDebug()<<temp->at(i);


        QString next;
        next=temp->at(i);

        int n=0;
        for(int j = 0; j<txData.size(); j++)
        {
            if(txData.at(j) == next)
            {
                n=1;
            }
        }

        if(n==0)
        {
            txData.append(next);
        }
    }
    numTX = txData.size();

    if(numTX > 0)
    {
        QThread timer;
        timer.sleep(2);
        jsp->getTA(adrText, txData.at(curTX), this);
        curTX++;
    }

}


void MainWindow::onTA(QVector<QString> *tempMyWallet, QVector<QString> *adr, bool inout, QVector<qulonglong> *sum, int date)
{

    Jsonparser *jsp = new Jsonparser();
    qDebug()<<"on TA";
    qDebug()<<"MyWallet";
    if(!inout)
    {
        for(int i=0; i<tempMyWallet->size(); i++)
        {
            int inWallet = 0;
            for(int j=0; j<myWallet.size(); j++)
            {
                if(myWallet.at(j) == tempMyWallet->at(i))
                {
                    inWallet =1;
                }
            }
            if(inWallet == 0)
            {
                myWallet.append(tempMyWallet->at(i));
            }
        }
        wallet tempinoutWallet;
        for(int i=0; i<adr->size(); i++)
        {
            tempinoutWallet.adr[0] = adr->at(i);
            tempinoutWallet.sum = sum->at(i);
            tempinoutWallet.date=date;
            tempinoutWallet.inout = false;
         //   tempinoutWallet.rectangle = создать сцены и прямоугольники с подписями в них;
            inoutWallet.append(tempinoutWallet);
        }
    }else
    {
        wallet tempinoutWallet;
        for(int i=0; i<tempMyWallet->size(); i++)
        {
            tempinoutWallet.adr[i] = tempMyWallet->at(i);
            tempinoutWallet.sum = sum->at(0);
            tempinoutWallet.date=date;
            tempinoutWallet.inout = true;
            //tempinoutWallet.rectangle = создать сцены и прямоугольники с подписями в них;
            inoutWallet.append(tempinoutWallet);
        }
    }


    for (int i = 0; i < tempMyWallet->size(); ++i)
    {
        qDebug()<<tempMyWallet->at(i);
    }
    qDebug()<<"adr";
    for (int i = 0; i < adr->size(); ++i)
    {
        qDebug()<<adr->at(i);
    }

    qDebug()<<"inout";
    qDebug()<<inout;
    qDebug()<<"sum";
    qDebug()<<sum;
    qDebug()<<"date";
    qDebug()<<date;



    if(curTX < numTX)
    {
        QThread timer;
        timer.sleep(6);
        jsp->getTA(adrText, txData.at(curTX), this);
        curTX++;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 400, 400);
  //  ui->graphicsView->setScene(scene);
    //ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    //ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    //ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //ui->graphicsView->scale(qreal(0.8), qreal(0.8));
    //ui->graphicsView->setMinimumSize(400, 400);

    QBrush greenBrush(Qt::green);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    rectangle = scene->addRect(100,0,80,100,outlinePen, greenBrush);
    rectangle->setFlag(QGraphicsItem::ItemIsSelectable, true);

}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"double";

    if(rectangle->isSelected())
    {
        qDebug()<<"if";
        rectangle->setOpacity(0.5);
        rectangle->setSelected(false);
    }
}
