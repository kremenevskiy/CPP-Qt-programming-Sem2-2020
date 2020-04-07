    #include "courier.h"

int Courier::numberCommon;

Courier::Courier(){

}


//  Когда сохраняю в файл по очереди добавляется в тот же файл с инициализацией

Courier::Courier(QString _name, int _weight, QTime _timeStart, QTime _timeEnd){
    number = ++numberCommon;
    name = _name;
    weight = _weight;
    timeStart = _timeStart;
    timeEnd = _timeEnd;
}


void Courier::saveCourier(QString filePath){
    QFile file(filePath);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        qDebug() << "Courier writing file isnt't opened";
        return;
    }

    QTextStream stream(&file);

    stream << number << " " << name << " " << timeStart.toString() << ' ' << timeEnd.toString() << ' ' << weight << '\n';

    file.close();

}




void Courier::set_name(QString name_str){
    name = name_str;
}

QString Courier::get_name(){
    return name;
}

void Courier::set_number(QString num_str){
    number = num_str.toInt();
}

int Courier::get_number(){
    return number;
}

void Courier::set_timeStart(QString timeStart_str){
    timeStart = QTime::fromString(timeStart_str, "HH:mm:ss");
}

QTime Courier::get_timeStart(){
    return timeStart;
}

void Courier::set_timeEnd(QString timeEnd_str){
    timeEnd = QTime::fromString(timeEnd_str, "HH:mm:ss");
}

QTime Courier::get_timeEnd(){
    return timeEnd;
}

void Courier::set_weight(QString weight_str){
    weight = weight_str.toInt();
}

int Courier::get_weight(){
    return weight;
}


