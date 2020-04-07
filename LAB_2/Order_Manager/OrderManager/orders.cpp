#include "orders.h"

int Orders::numberCommon;

Orders::Orders(){

}

Orders::Orders(QString _addres, QDate _date, QTime _timeStart, QTime _timeEnd, int _weight)
{
    number = ++numberCommon;
    addres = _addres;
    date = _date;
    timeStart = _timeStart;
    timeEnd = _timeEnd;
    weight = _weight;
}

void Orders::saveOrder(QString filePath){
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        qDebug() << "Orders file isnt't opened\n";
    }

    QTextStream stream(&file);

    stream << number << " " << addres << " " << date.toString("dd.MM.yyyy") << " " << weight << " " <<
              timeStart.toString() << " " << timeEnd.toString() << '\n';

    file.close();

}


void Orders::set_date(QString date_str){
    date = QDate::fromString(date_str, "dd.MM.yyyy");
}

QDate Orders::get_date(){
    return date;
}

void Orders::set_addres(QString addres_str){
    addres = addres_str;
}

QString Orders::get_addres(){
    return addres;
}

void Orders::set_number(QString num_str){
    number = num_str.toInt();
}

int Orders::get_number(){
    return number;
}

void Orders::set_timeStart(QString timeStart_str){
    timeStart = QTime::fromString(timeStart_str, "HH:mm:ss");
}

QTime Orders::get_timeStart(){
    return timeStart;
}

void Orders::set_timeEnd(QString timeEnd_str){
    timeEnd = QTime::fromString(timeEnd_str, "HH:mm:ss");
}

QTime Orders::get_timeEnd(){
    return timeEnd;
}

void Orders::set_weight(QString weight_str){
    weight = weight_str.toInt();
}

int Orders::get_weight(){
    return weight;
}
