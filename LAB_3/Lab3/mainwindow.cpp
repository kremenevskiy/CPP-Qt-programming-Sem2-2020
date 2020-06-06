#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{

	ui->setupUi(this);

	ui->textEdit->setReadOnly(true);
	ui->prodTypeBox_2->setEnabled(false);
	ui->saveButton->setEnabled(false);

	ui->orderNumBox->addItem("Adding mode");

	ui->prodTypeBox->addItem("Clock");
	ui->prodTypeBox->addItem("Phone");
	ui->prodTypeBox->addItem("Laptop");

	ui->prodTypeBox_2->addItem("Clock");
	ui->prodTypeBox_2->addItem("Phone");
	ui->prodTypeBox_2->addItem("Laptop");

	ui->viewBox->addItem("Show all orders");
	ui->viewBox->addItem("Show completed orders");
	ui->viewBox->addItem("Show today orders");

	ui->dateEdit->setDate(QDate::currentDate());


	connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addNewOrder);
	connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::updateInfo);
	connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveInfo);
	//connect(ui->orderNumBox, &QComboBox::currentIndexChanged, this, &MainWindow::orderNumChanged);
	//connect(ui->viewBox, &QComboBox::currentIndexChanged, this, std::bind(&MainWindow::prodTypeChanged, this));


	timer = new QTimer();
	connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
	timer->start(1000);

	orderList = new LinkedList();
	connect(orderList, &LinkedList::createdOrder, this, &MainWindow::updateNum_Creating);

	initialize();


}


MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::addNewOrder(){
	if(!checkInput())
		return;

	Order * newOrder = new Order(ui->prodTypeBox->currentText(), ui->dateEdit->date().toString("dd-MM-yyyy"),
								 ui->modelEdit->text(), ui->isReadyCheck->isChecked());

	orderList->add(newOrder);
	QMessageBox::information(this, "Notification", "New model added succesfully!");
	ui->modelEdit->setText("");

}


void MainWindow::showAllOrders(){
	Order * currentOrder = orderList->head;

	int i = 1;
	while(currentOrder){
		QString ready = currentOrder->ready?"Yes": "No";
		ui->textEdit->appendPlainText(QString::number(i) + ". " + orderInfo(currentOrder) + "\n");
		currentOrder = currentOrder->next;
		i++;
	}
}


void MainWindow::showCompleted(){
	Order * currentOrder = orderList->head;

	int i = 1;
	while(currentOrder){
		QString ready = currentOrder->ready?"Yes": "No";

		if(currentOrder->ready == true){
			ui->textEdit->appendPlainText(QString::number(i) + ". " + orderInfo(currentOrder) + "\n");
		}
		currentOrder = currentOrder->next;
		i++;

	}
}


void MainWindow::showTodayOrders(QString prodType){
	Order * currentOrder = orderList->head;
	QString todayDate = QDate::currentDate().toString("dd-MM-yyyy");

	int i = 1;
	while(currentOrder){
		QString ready = currentOrder->ready?"Yes": "No";

		if(currentOrder->date == todayDate && currentOrder->prodType == prodType){
			ui->textEdit->appendPlainText(QString::number(i) + ". " + orderInfo(currentOrder) + "\n");
		}
		currentOrder = currentOrder->next;
		i++;
	}
}


QString MainWindow::orderInfo(Order *order){
	QString ready = order->ready?"Yes": "No";
	QString info = "  Product: " + order->prodType + "\n  Model: " + order->model +
					"\n  Date Receipt: " + order->date + "\n  IsReady: " + ready;

	return info;
}


void MainWindow::updateInfo(){
	ui->textEdit->clear();
	if (ui->viewBox->currentIndex() == 0){
		showAllOrders();
		return;
	}
	else if(ui->viewBox->currentIndex() == 1){
		showCompleted();
		return;
	}
	else if(ui->viewBox->currentIndex() == 2){
		QString typeProduct = ui->prodTypeBox_2->currentText();
		showTodayOrders(typeProduct);
		return;
	}
}


//void MainWindow::prodTypeChanged(){
//	if (ui->viewBox->currentIndex() == 2)
//		ui->prodTypeBox_2->setEnabled(true);
//	else
//		ui->prodTypeBox_2->setEditable(false);
//}


void MainWindow::saveInfo(){
	QString prodType = ui->prodTypeBox->currentText();
	QString model = ui->modelEdit->text();
	QString date = ui->dateEdit->date().toString("dd-MM-yyyy");
	bool isReady = ui->isReadyCheck->isChecked();

	orderList->change(ui->orderNumBox->currentIndex() - 1, prodType, date, model, isReady);

	QMessageBox::information(this, "Success", "All changes are confirmed and updated!");

}


bool MainWindow::checkInput(){
	if (ui->modelEdit->text().isEmpty()){
		QMessageBox::warning(this, "INVALID INPUT", "Fill all empty gaps first!");
		return false;
	}

	return true;
}


void MainWindow::updateTime(){
	QString time = QTime::currentTime().toString("hh:mm:ss");
	QString date = QDate::currentDate().toString("dd-MM-yyyy");

	ui->dateLabel->setText(date);
	ui->timeLabel->setText(time);
	timer->start(100);
}

void MainWindow::on_orderNumBox_currentIndexChanged(int index)
{
	if (index == 0){
		ui->saveButton->setEnabled(false);
		ui->addButton->setEnabled(true);
		ui->modelEdit->setText("");
		ui->isReadyCheck->setChecked(false);
		return;
	}

	ui->addButton->setEnabled(false);
	ui->saveButton->setEnabled(true);

	Order * current = orderList->search(index - 1);

	ui->prodTypeBox->setCurrentText(current->prodType);
	ui->modelEdit->setText(current->model);
	ui->dateEdit->setDate(QDate::fromString(current->date));
	ui->isReadyCheck->setChecked(current->ready);

}

void MainWindow::on_viewBox_currentIndexChanged(int index)
{
	if (index == 2)
		ui->prodTypeBox_2->setEnabled(true);
	else
		ui->prodTypeBox_2->setEnabled(false);
}


void MainWindow::updateNum_Creating(){
	items++;
	ui->orderNumBox->addItem(QString::number(items));
}


void MainWindow::initialize(){
	orderList->add(new Order("Clock", "06-06-2020", "Samsung", false));
	orderList->add(new Order("Phone", "06-06-2020", "Iphone Se", false));
	orderList->add(new Order("Laptop", "06-06-2020", "Macbook Pro", false));

}
