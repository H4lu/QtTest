#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QSslSocket>
#include <QSsl>
#include <QVector>

#include <QListView>
#include <QStringListModel>
#include <QAbstractTableModel>
#include <QDesktopServices>
#include <QGraphicsDropShadowEffect>


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
        uint date;
    };
    QVector<wallet> inoutWallet;
    QVector<wallet> inWallet;
    QVector<wallet> outWallet;
private slots:
    void on_pushButton_clicked();
    void showSelectedItemIN(QModelIndex index);
    void showSelectedItemOUT(QModelIndex index);
    void showSelectedItemAddress(QModelIndex index);
public slots:
    void onTXR(QVector<QString> *temp);
    void onTXS(QVector<QString> *temp);
    void onTA(QVector<QString> *tempMyWallet, QVector<QString> *adr, bool inout, QVector<qulonglong> *sum, int date);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    QVector<QString> txData;
    QString adrText;
    int numTX;
    int curTX;
    int numTrans;
    void paintWallet();
    void removeVector();
};



#endif // MAINWINDOW_H
