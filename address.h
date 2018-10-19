#ifndef ADDRESS_H
#define ADDRESS_H

#include <QString>
#include <QVector>
#include <QObject>


class Address
{

public:
    Address();

public:
    QString adr;
    QString tx;
    QString val;
    int time;
    bool inout; //in - true; out - false;


};

#endif // ADDRESS_H
