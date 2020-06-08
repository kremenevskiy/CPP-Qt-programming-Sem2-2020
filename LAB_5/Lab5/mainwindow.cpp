#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->headEdit->setReadOnly(true);
	ui->tailEdit->setReadOnly(true);
	ui->isEmptyEdit->setReadOnly(true);
	ui->extractEdit->setReadOnly(true);
	ui->StopTwoTaskBtn->setEnabled(false);
	ui->fillRandBtn->setEnabled(false);
	ui->linkBtn->setEnabled(false);
	ui->countEdit->setEnabled(false);

	model = new QStringListModel(this);
	ui->queueView->setModel(model);

	queue = new Queue();

	connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addBtn);
	connect(ui->extractButton, &QPushButton::clicked, this, &MainWindow::extractBtn);
	connect(ui->isEmptyButton, &QPushButton::clicked, this, &MainWindow::isEmptyBtn);
	connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearBtn);

	connect(queue, &Queue::removeSgnl, this, &MainWindow::extracted);
	connect(queue, &Queue::added, this, &MainWindow::added);

	QRegExp regex("[0-9]{1,10}");
	QRegExpValidator *validator = new QRegExpValidator(regex, this);
	ui->addEdit->setValidator(validator);
	ui->countEdit->setValidator(validator);


	// Two queues

	model2 = new QStringListModel(this);
	ui->queue2View->setModel(model2);
	queue2 = new Queue();


	connect(ui->startTwoQueuesBtn, &QPushButton::clicked, this, &MainWindow::startTwoQueueTaks);
	//connect(ui->fillRandBtn, &QPushButton::clicked, queuesTask, &TwoQueues::fillRand);
	connect(queue2, &Queue::added, this, &MainWindow::added2);
	connect(ui->linkBtn, &QPushButton::clicked, this, &MainWindow::linkQueues);
	connect(ui->StopTwoTaskBtn, &QPushButton::clicked, this, &MainWindow::stopTask);

	connect(ui->fillRandBtn, &QPushButton::clicked, [&](){

		if (ui->countEdit->text().isEmpty()){
			QMessageBox::warning(this, "Input error", "Enter size of new random queue");
			return;
		}

		int size = ui->countEdit->text().toInt();
		queuesTask->fillRand(queue, queue2, size, size);

		ui->fillRandBtn->setEnabled(false);
		ui->linkBtn->setEnabled(true);
		ui->countEdit->setEnabled(false);
	});
}


MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::addBtn(){

	if (ui->addEdit->text().isEmpty()){
		QMessageBox::warning(this, "Write Data!", "First write number, you want to add to the queue");
		return;
	}
	int newNumber = ui->addEdit->text().toInt();

	queue->add(newNumber);

	checkTailHead();
}


void MainWindow::added(int data){
	int rowCount = model->rowCount();
	model->insertRows(rowCount, 1);

	QModelIndex index = model->index(rowCount);
	model->setData(index, QString::number(data));
}


void MainWindow::extractBtn(){
	if(queue->isEmpty()){
		QMessageBox::warning(this, "Extract error", "Couldn't extract from empty queue");
		return;
	}
	queue->extract();
	checkTailHead();



}


void MainWindow::extracted(int data){
	ui->extractEdit->setText(QString::number(data));


	model->removeRow(model->index(0).row());

}


void MainWindow::isEmptyBtn(){
	if(queue->isEmpty())
		ui->isEmptyEdit->setText("true");
	else
		ui->isEmptyEdit->setText("false");


}


void MainWindow::clearBtn(){
	if (!queue->isEmpty()){
		int rows = model->rowCount();

		model->removeRows(model->index(0).row(), rows);


		queue->clear();
		checkTailHead();
	}
	else{
		QMessageBox::information(this, "Already empty", "Queue is already empty!");
		return;
	}

}


void MainWindow::checkTailHead(){
	if(queue->tail)
		ui->tailEdit->setText(QString::number(queue->tail->data));
	else
		ui->tailEdit->setText("nullptr");

	if(queue->head)
		ui->headEdit->setText(QString::number(queue->head->data));
	else
		ui->headEdit->setText("nullptr");
}



// second task

void MainWindow::startTwoQueueTaks(){
	int rows1 = model->rowCount();
	model->removeRows(model->index(0).row(), rows1);

	int rows2 = model2->rowCount();
	model2->removeRows(model2->index(0).row(), rows2);

	if(!queue->isEmpty() || !queue2->isEmpty()){
		QMessageBox::information(this, "Starting Task 2", "All queues will be cleared!");
	}

	queuesTask = new TwoQueues(queue, queue2);

	ui->startTwoQueuesBtn->setEnabled(false);
	ui->fillRandBtn->setEnabled(true);
	ui->countEdit->setEnabled(true);
	ui->headEdit->setVisible(false);
	ui->tailEdit->setVisible(false);

}


void MainWindow::fillRand(){
	queuesTask->fillRand(queue, queue2, 3, 3);
}


void MainWindow::linkQueues(){
	queuesTask->connectTwoQueues(queue, queue2);

	int countRows = model->rowCount();
	model->removeRows(model->index(0).row(), countRows);


	int index = 0;
	Node *current = queue->head;
	QModelIndex ind;

	while(current){
		model->insertRows(index, 1);
		ind = model->index(index);
		model->setData(ind, QString::number(current->data));

		current = current->next;
		index++;
	}

	ui->StopTwoTaskBtn->setEnabled(true);
	ui->linkBtn->setEnabled(false);
}


void MainWindow::added2(int data){
	int rowCount = model2->rowCount();
	model2->insertRows(rowCount, 1);

	QModelIndex index = model2->index(rowCount);
	model2->setData(index, QString::number(data));
}


void MainWindow::stopTask(){
	ui->StopTwoTaskBtn->setEnabled(false);
	ui->startTwoQueuesBtn->setEnabled(true);
	ui->headEdit->setVisible(true);
	ui->tailEdit->setVisible(true);
}
