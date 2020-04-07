#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTime>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->setReadOnly(true);

    start_init();

    QRegExp ONE_STRING("[a-zA-ZА-Яа-я.,]{1,}");
    QValidator *validator = new QRegExpValidator(ONE_STRING, this);
    ui->addresEdit->setValidator(validator);
    ui->name_courier->setValidator(validator);

    connect(ui->Courier_button, SIGNAL(clicked()), this, SLOT(addCourier()));
    connect(ui->order_button, SIGNAL(clicked()), this, SLOT(addOrder()));
    connect(ui->update_button, SIGNAL(clicked()), this, SLOT(update_button_clicked()));
    connect(ui->init_button, SIGNAL(clicked()), this, SLOT(init_button_clicked()));
    connect(ui->deleteOrder_button, SIGNAL(clicked()), this, SLOT(delete_order()));
    connect(ui->deleteCourier_button, SIGNAL(clicked()), this, SLOT(delete_courier()));
    connect(ui->load_file, SIGNAL(clicked()), this, SLOT(choose_file()));

}


void MainWindow::initialization(){

    CourierCounter = 0;
    OrderCounter = 0;


    QFile fileOrder1(fileName_Open_Order);
    QFile fileCourier1(fileName_Open_Courier);

    if (!fileOrder1.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Inicialization order list error\n";
        return;
    }

    if (!fileCourier1.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Inicialization courier list error\n";
        return;
    }

    QTextStream streamOrder1(&fileOrder1);
    QTextStream streamCourier1(&fileCourier1);
    QString buffer1;

    while(!streamOrder1.atEnd()){
        buffer1 = streamOrder1.readLine();
        OrderCounter ++;

    }

    while(!streamCourier1.atEnd()){
        buffer1 = streamCourier1.readLine();
        CourierCounter ++;

    }


    fileOrder1.close();
    fileCourier1.close();

    QFile fileOrder(fileName_Open_Order);
    QFile fileCourier(fileName_Open_Courier);

    if (!fileOrder.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Inicialization order list error\n";
        return;
    }

    if (!fileCourier.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Inicialization courier list error\n";
        return;
    }

    QTextStream streamOrder(&fileOrder);
    QTextStream streamCourier(&fileCourier);

    unsigned int i = VectorOrders.size();
    VectorOrders.resize(VectorOrders.size() +  ulong(OrderCounter));

    QString buffer;
    while(!streamOrder.atEnd()){



        streamOrder >> buffer;
        if (buffer == ""){
            break;
        }
        VectorOrders[i].set_number(QString::number(i+1));
        streamOrder >> buffer;
        VectorOrders[i].set_addres(buffer);
        streamOrder >> buffer;
        VectorOrders[i].set_date(buffer);
        streamOrder >> buffer;
        VectorOrders[i].set_weight(buffer);
        streamOrder >> buffer;
        VectorOrders[i].set_timeStart(buffer);
        streamOrder >> buffer;
        VectorOrders[i].set_timeEnd(buffer);



//        while (buffer != ""){
//            streamOrder >> buffer;
//            continue;
//        }
        ui->comboBox_orders->addItem(QString::number(VectorOrders[i].get_number()));
        Orders::numberCommon++;
        i++;


    }


    i = VectorCourier.size();

    VectorCourier.resize(VectorCourier.size() +  ulong(CourierCounter));
    buffer = "Courier time";
    while(!streamCourier.atEnd()){

        streamCourier >> buffer;

        if (buffer == ""){
            break;
        }
        VectorCourier[i].set_number(QString::number(i+1));
        streamCourier >> buffer;
        VectorCourier[i].set_name(buffer);
        streamCourier >> buffer;
        VectorCourier[i].set_timeStart(buffer);
        streamCourier >> buffer;
        VectorCourier[i].set_timeEnd(buffer);
        streamCourier >> buffer;
        VectorCourier[i].set_weight(buffer);

//        while (buffer != ""){
//            streamOrder >> buffer;
//            continue;
//        }
        ui->comboBox_courier->addItem(QString::number(VectorCourier[i].get_number()));
        Courier::numberCommon++;
        i++;

    }

    fileOrder.close();
    fileCourier.close();


}


void MainWindow::reorder(){

    ui->textEdit->clear();

    for(unsigned i = 0; i < VectorOrders.size() - 1; i++){
        for(unsigned j = 0; j < VectorOrders.size() - i - 1; j++){
            if (VectorOrders[j].get_date() > VectorOrders[j+1].get_date()){
                Orders temp = VectorOrders[j+1];
                VectorOrders[j+1] = VectorOrders[j];
                VectorOrders[j] = temp;

            }
        }
    }

    std::vector<Orders> uncompleted;

    for(unsigned i = 0; i < VectorOrders.size(); i++){
        bool bln = true;
        for(unsigned j = 0; j < VectorCourier.size(); j++){
            if (bln)
            {
                if (VectorOrders[i].get_timeStart() >= VectorCourier[j].get_timeStart() &&
                        VectorOrders[i].get_timeEnd() <= VectorCourier[j].get_timeEnd() &&
                        VectorOrders[i].get_weight() <= VectorCourier[j].get_weight())
                {
                    ui->textEdit->append("Курьер " + VectorCourier[j].get_name() + " ( №" + QString::number(VectorCourier[j].get_number()) +
                                         " - МАКС: " + QString::number(VectorCourier[j].get_weight()) + " кг)\n"  +
                                         "С графиком работы: " + VectorCourier[j].get_timeStart().toString("HH:mm") + " - " +
                                         VectorCourier[j].get_timeEnd().toString("HH:mm") + "\nБерет заказ №" +
                                         QString::number(VectorOrders[i].get_number()) + "\nГруз массой: " +
                                         QString::number(VectorOrders[i].get_weight()) + "кг\nПо адресу: " +
                                         VectorOrders[i].get_addres() + "\nГде заявленное время: " +
                                         VectorOrders[i].get_timeStart().toString("HH:mm") + " - " + VectorOrders[i].get_timeEnd().toString("HH:mm") +
                                         "\nДата доставки: " + VectorOrders[i].get_date().toString("dd.MM.yyyy") + "\n\n");
                    bln = false;
                    continue;

                }
                if (j == VectorCourier.size() - 1)
                    uncompleted.push_back(VectorOrders[i]);
            }
        }
    }

    ui->textEdit->append("\nЗаказы, которые не могут быть исполнены в срок: \n");

    for(unsigned i = 0; i < uncompleted.size(); i++){
        ui->textEdit->append("Заказ номер: " + QString::number(uncompleted[i].get_number()) + ". " +
                             "Адрес: " + uncompleted[i].get_addres() + "\nМасса груза: " +
                             QString::number(VectorOrders[i].get_weight()) + "кг\nВремя ожидания: " +
                             uncompleted[i].get_timeStart().toString("HH:mm") + " - " +
                             uncompleted[i].get_timeEnd().toString("HH:mm") + "\nДата: " +
                             uncompleted[i].get_date().toString("dd.MM.yyyy") + "\n");
    }
}

void MainWindow::addCourier(){

    if(ui->name_courier->text() == "" | ui->spinBox_courier->value()  == 0){
        QMessageBox::warning(this, "ERROR adding", "Вы не ввели все данные о курьере!\nДополните или измините!");
        return;
    }

    VectorCourier.push_back(Courier(ui->name_courier->text(), ui->spinBox_courier->value(),
                                    ui->timeStart_courier->time(), ui->timeEnd_courier->time()));
    //VectorCourier.back().saveCourier();
    ui->comboBox_courier->addItem(QString::number(VectorCourier.back().get_number()));
    ui->spinBox_courier->setValue(0);
    ui->name_courier->clear();
    ui->timeStart_courier->setTime(QTime::fromString("07:00:00", "HH:mm:ss"));
    ui->timeEnd_courier->setTime(QTime::fromString("23:00:00", "HH:mm:ss"));
}


void MainWindow::addOrder(){

    if(ui->addresEdit->text() == "" | ui->spinBox_courier->value()  == 0){
        QMessageBox::warning(this, "ERROR adding", "Вы не ввели все данные о заказе!\nДополните или измините!");
        return;
    }

    VectorOrders.push_back(Orders(ui->addresEdit->text(), ui->dateEdit->date(), ui->timeStart_order->time(),
                                  ui->timeEnd_Order->time(), ui->spinBox_order->value()));
    //VectorOrders.back().saveOrder();
    ui->comboBox_orders->addItem(QString::number(VectorOrders.back().get_number()));

    ui->spinBox_order->setValue(0);
    ui->addresEdit->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeStart_order->setTime(QTime::fromString("08:00:00", "HH:mm:ss"));
    ui->timeEnd_Order->setTime(QTime::fromString("22:00:00", "HH:mm:ss"));
}


void MainWindow::showAllOrders(){

    ui->textEdit->append("\t  Список всех заказов: \n\n");

    std::vector<Orders>::iterator iter;
    for(iter = VectorOrders.begin(); iter != VectorOrders.end(); iter++){

        ui->textEdit->insertPlainText(QString::number(iter->get_number()) + ". ");
        ui->textEdit->insertPlainText("Адрес доставки: " + iter->get_addres() + "\n");
        ui->textEdit->insertPlainText("Дата доставки: " + iter->get_date().toString("dd.MM.yyyy") + "\n");
        ui->textEdit->insertPlainText("Масса груза: " + QString::number(iter->get_weight()) + " кг\n");
        ui->textEdit->insertPlainText("Удобное время доставки:\n\tС: " + iter->get_timeStart().toString("HH:mm:ss") + "\n\t");
        ui->textEdit->insertPlainText("До: " + iter->get_timeEnd().toString("HH.mm.ss") + "\n\n");

    }
}


void MainWindow::showAllCouriers(){

    ui->textEdit->append("\tСписок всех работающих курьеров:\n\n");

    std::vector<Courier>::iterator iter;
    for(iter = VectorCourier.begin(); iter != VectorCourier.end(); iter++){

        ui->textEdit->insertPlainText(QString::number(iter->get_number()) + ". ");
        ui->textEdit->insertPlainText("Имя: " + iter->get_name() + "\n");
        ui->textEdit->insertPlainText("Грузоподъемность авто: " + QString::number(iter->get_weight()) + " кг\n");
        ui->textEdit->insertPlainText("Время работы: \n\tНачало: " + iter->get_timeStart().toString("HH:mm:ss") + "\n\t");
        ui->textEdit->insertPlainText("Конец: " + iter->get_timeEnd().toString("HH.mm.ss") + "\n\n");
    }
}


void MainWindow::update_button_clicked(){

    ui->textEdit->clear();

    if (ui->menu_box->currentIndex() == 0){
        showAllOrders();
    }
    else if (ui->menu_box->currentIndex() == 1){
        showAllCouriers();
    }
    else if (ui->menu_box->currentIndex() == 2){
        reorder();
    }
}


void MainWindow::init_button_clicked(){
    initialization();
    ui->init_button->setEnabled(false);
}


void MainWindow::start_init(){

    ui->deleteOrder_button->setEnabled(false);
    ui->deleteCourier_button->setEnabled(false);
    ui->init_button->setEnabled(true);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate::currentDate());

    ui->timeStart_order->setTime(QTime::fromString("08:00:00", "HH:mm:ss"));
    ui->timeStart_order->setMinimumTime(QTime::fromString("08:00:00", "HH:mm:ss"));
    ui->timeStart_order->setMaximumTime(QTime::fromString("22:55:00", "HH:mm:ss"));

    ui->timeEnd_Order->setTime(QTime::fromString("22:00:00", "HH:mm:ss"));
    ui->timeEnd_Order->setMinimumTime(QTime::fromString("08:05:00", "HH:mm:ss"));
    ui->timeEnd_Order->setMaximumTime(QTime::fromString("23:00:00", "HH:mm:ss"));

    ui->timeStart_courier->setTime(QTime::fromString("07:00:00", "HH:mm:ss"));
    ui->timeStart_courier->setMinimumTime(QTime::fromString("07:00:00", "HH:mm:ss"));
    ui->timeStart_courier->setMaximumTime(QTime::fromString("22::55", "HH:mm:ss"));

    ui->timeEnd_courier->setTime(QTime::fromString("23:00:00", "HH:mm:ss"));
    ui->timeEnd_courier->setMinimumTime(QTime::fromString("08:00:00", "HH:mm:ss"));
    ui->timeEnd_courier->setMaximumTime(QTime::fromString("23:59:00", "HH:mm:ss"));




}

MainWindow::~MainWindow()
{

    if (ui->checkBox_save->isChecked()){

        QMessageBox::information(this, "SAVE YOUR DATA", "Перед тем, как выйти из приложения, \n"
                                                     "необходимо сохранить занесенную информацию!\n\n"
                                                     "Выберите два файла, чтобы занести туда\n"
                                                     "внесенную инфорормацию\n"
                                                     "(.txt) только поддерживается!\n\n"
                                                     "CHOOSE two files for SAVE:\n1. Order_FileName(.txt)\n2. Courier_FileName(.txt)\n ");


        int num = 2;
        while(num){


            num = 2;
            QMessageBox::information(this, "READ", "Выберите файл для сохранения информации\nо сохраненных заявках:\n\n\Example:\tOrders.txt");
            fileName_Save_Order = QFileDialog::getOpenFileName(this, "OPEN ORDER FILE", QDir::homePath(), "Text File (*.txt)");
            QFile fileOrder(fileName_Save_Order);

            if (!fileOrder.open(QIODevice::ReadOnly | QIODevice::Text)){
                QMessageBox::warning(this, "File Order ERROR", "PATH isn't correct!");

            }
            else{
                num--;
            }

            QMessageBox::information(this, "READ", "Выберите файл, для сохранения информации\nо работающих курьерах:\n\nExample:\tCourier.txt\n ");
            fileName_Save_Courier = QFileDialog::getOpenFileName(this, "OPEN COURIER FILE", QDir::homePath(), "Text File (*.txt)");
            QFile fileCourier(fileName_Save_Courier);

            if (!fileCourier.open(QIODevice::ReadOnly | QIODevice::Text)){
                QMessageBox::warning(this, "File Courier ERROR", "PATH isn't correct!");
            }
            else{
                num--;
            }

            fileOrder.close();
            fileCourier.close();
        }



        QFile fileOrder(fileName_Save_Order);
        QFile fileCourier(fileName_Save_Courier);

        fileOrder.open(QIODevice::WriteOnly | QIODevice::Text);
        fileCourier.open(QIODevice::WriteOnly | QIODevice::Text);

        fileOrder.close();
        fileCourier.close();

        std::vector<Orders>::iterator iterOrder;
        std::vector<Courier>::iterator iterCourier;

        for(iterOrder = VectorOrders.begin(); iterOrder != VectorOrders.end(); iterOrder++){
            iterOrder->saveOrder(fileName_Save_Order);
        }

        for(iterCourier = VectorCourier.begin(); iterCourier != VectorCourier.end(); iterCourier++){
            iterCourier->saveCourier(fileName_Save_Courier);
        }

    }

    delete ui;
}


void MainWindow::activate_buttons_order(bool bln){

    ui->spinBox_order->setEnabled(bln);
    ui->addresEdit->setEnabled(bln);
    ui->dateEdit->setEnabled(bln);
    ui->timeStart_order->setEnabled(bln);
    ui->timeEnd_Order->setEnabled(bln);
    ui->order_button->setEnabled(bln);

    ui->deleteOrder_button->setEnabled(!bln);


}


void MainWindow::activate_buttons_courier(bool bln){

    ui->spinBox_courier->setEnabled(bln);
    ui->name_courier->setEnabled(bln);
    ui->timeStart_courier->setEnabled(bln);
    ui->timeEnd_courier->setEnabled(bln);
    ui->Courier_button->setEnabled(bln);

    ui->deleteCourier_button->setEnabled(!bln);


}


void MainWindow::on_comboBox_orders_currentIndexChanged(int index)
{
    if (ui->comboBox_orders->currentIndex() == 0){
        activate_buttons_order(true);


        ui->spinBox_order->setValue(0);
        ui->addresEdit->clear();
        ui->dateEdit->setDate(QDate::currentDate());
        ui->timeStart_order->setTime(QTime::fromString("08:00:00", "HH:mm:ss"));
        ui->timeEnd_Order->setTime(QTime::fromString("22:00:00", "HH:mm:ss"));

    }

    else{

        activate_buttons_order(false);

        unsigned int j;
        int index = ui->comboBox_orders->currentIndex();
        for(j = 0; index != VectorOrders[j].get_number(); j++);

        ui->spinBox_order->setValue(VectorOrders[j].get_weight());
        ui->addresEdit->setText(VectorOrders[j].get_addres());
        ui->dateEdit->setDate(VectorOrders[j].get_date());
        ui->timeStart_order->setTime(VectorOrders[j].get_timeStart());
        ui->timeEnd_Order->setTime(VectorOrders[j].get_timeEnd());
    }
}


void MainWindow::on_comboBox_courier_currentIndexChanged(int index)
{
    if (ui->comboBox_courier->currentIndex() == 0){
        activate_buttons_courier(true);

        ui->spinBox_courier->setValue(0);
        ui->name_courier->clear();
        ui->timeStart_courier->setTime(QTime::fromString("07:00:00", "HH:mm:ss"));
        ui->timeEnd_courier->setTime(QTime::fromString("23:00:00", "HH:mm:ss"));

    }
    else{


        activate_buttons_courier(false);
        unsigned int j;
        int index = ui->comboBox_courier->currentIndex();



        //for(j = 0; index != VectorCourier[j].get_number(); j++);

        j = --index;


        ui->spinBox_courier->setValue(VectorCourier[j].get_weight());
        ui->name_courier->setText(VectorCourier[j].get_name());

        ui->timeStart_courier->setTime(VectorCourier[j].get_timeStart());
        ui->timeEnd_courier->setTime(VectorCourier[j].get_timeEnd());
    }
}


void MainWindow::delete_order(){
    int i = ui->comboBox_orders->currentIndex() - 1;
    ui->comboBox_orders->removeItem(i+1);

    std::vector<Orders>::iterator iter = VectorOrders.begin();

    iter += i;

    VectorOrders.erase(iter);
    ui->comboBox_orders->setCurrentIndex(0);


}


void MainWindow::delete_courier(){
    int i = ui->comboBox_courier->currentIndex() - 1;
    ui->comboBox_courier->removeItem(i+1);

    std::vector<Courier>::iterator iter = VectorCourier.begin();

    iter += i;

    VectorCourier.erase(iter);
    ui->comboBox_courier->setCurrentIndex(0);
}


void MainWindow::choose_file(){
    int num = 2;

    while(num){
        num = 2;
        QMessageBox::information(this, "READ", "Open two files:\n1. Order(.txt)\n2. Courier(.txt)\n\nОни должны содеражать ранее сохраненную информацию!!");
        fileName_Open_Order = QFileDialog::getOpenFileName(this, "OPEN ORDER FILE", QDir::homePath(), "Text File (*.txt)");
        QFile fileOrder(fileName_Open_Order);
        if (!fileOrder.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::warning(this, "File Order ERROR", "PATH isn't correct!");

        }
        else{
            num--;
        }

        fileName_Open_Courier = QFileDialog::getOpenFileName(this, "OPEN COURIER FILE", QDir::homePath(), "Text File (*.txt)");
        QFile fileCourier(fileName_Open_Courier);

        if (!fileCourier.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::warning(this, "File Courier ERROR", "PATH isn't correct!");
        }
        else{
            num--;
        }

        fileOrder.close();
        fileCourier.close();
    }


    ui->load_file->setEnabled(false);
    ui->init_button->setEnabled(true);


    ui->ordername_label->setText(fileName_Open_Order);
    ui->couriername_label->setText(fileName_Open_Courier);
}
