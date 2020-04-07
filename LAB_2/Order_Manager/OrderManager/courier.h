#ifndef COURIER_H
#define COURIER_H

#include <QString>
#include <QTime>
#include <QFile>
#include <QDebug>


class Courier
{
public:
    Courier(QString _name, int _weight, QTime _timeStart, QTime _timeEnd);
    Courier();

    void saveCourier(QString filePath);
    void showCourier();
    static int numberCommon;


    void set_timeStart(QString timeStart_str);
    void set_timeEnd(QString timeEnd_str);
    void set_weight(QString weight_str);
    void set_number(QString num_str);
    void set_name(QString name_str);

    QString get_name();
    QTime get_timeStart();
    QTime get_timeEnd();
    int get_weight();
    int get_number();


private:

    int number;
    QString name;
    int weight;
    QTime timeStart;
    QTime timeEnd;

};




#endif // COURIER_H
