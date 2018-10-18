#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QSslSocket>
#include <QSsl>
#include <QVector>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>


//#include "jsonparser.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QVector<QString> myWallet;

    struct wallet{
        QVector<QString> adr;
        bool inout; //true - in, false - out;
        qulonglong sum;
        int date;
        QGraphicsRectItem *rectangle;
    };
    QVector<wallet> inoutWallet;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
public slots:
    void onTXR(QVector<QString> *temp);
    void onTXS(QVector<QString> *temp);
    void onTA(QVector<QString> *tempMyWallet, QVector<QString> *adr, bool inout, QVector<qulonglong> *sum, int date);
protected:
   virtual void mousePressEvent(QMouseEvent *event);
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    QVector<QString> txData;
    QString adrText;
    int numTX;
    int curTX;
    void selected();
    void ris();


};



#endif // MAINWINDOW_H
