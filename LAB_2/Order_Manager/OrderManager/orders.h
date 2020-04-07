#ifndef ORDERS_H
#define ORDERS_H

#include <QString>
#include <QFile>
#include <QDate>
#include <QTime>
#include <QDebug>



class Orders
{
public:
    Orders();
    Orders(QString _addres, QDate _date, QTime _timeStart, QTime _timeEnd, int _weight);

    void saveOrder(QString filePath);
    void readOrders();
    void readOrder();
    static int numberCommon;

    void set_addres(QString addres_str);
    void set_date(QString date_str);
    void set_timeStart(QString timeStart_str);
    void set_timeEnd(QString timeEnd_str);
    void set_weight(QString weight_str);
    void set_number(QString num_str);

    QString get_addres();
    QDate get_date();
    QTime get_timeStart();
    QTime get_timeEnd();
    int get_weight();
    int get_number();

private:

    QString addres;
    QDate date;
    QTime timeStart;
    QTime timeEnd;
    int weight;
    int number;

};



#endif // ORDERS_H
