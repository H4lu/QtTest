#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QSslSocket>
#include <QSsl>
#include <QVector>
#include "address.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void onResult(QNetworkReply *reply);
    void on_pushButton_2_clicked();
public slots:
    void onTXR(QVector<Address> *temp);
    void onTXS(QVector<Address> *temp);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    QVector<Address> AData;
    QVector<Address> *txData;
    QString adrText;
};

#endif // MAINWINDOW_H
