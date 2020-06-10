#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	hashTable = new Hash();

//	hashTable->addItem("a");
//	hashTable->addItem("k");
//	hashTable->addItem("b");
//	hashTable->addItem("l");
//	hashTable->addItem("v");

//	qDebug() << hashTable->printItemsInIndex(8);




	model = new QStandardItemModel(10, 2);
	ui->hastTableView->setModel(model);


	connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::AddBtn);
	connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::removeBtn);
	connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchBtn);
	connect(ui->randHashButton, &QPushButton::clicked, this, &MainWindow::randHashBtn);

	connect(hashTable, &Hash::addedItem, [&](){
		updateHashTables();
	});

	connect(hashTable, &Hash::removedItem, [&](){
		updateHashTables();
	});

	updateHashTables();
}


MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::updateHashTables(){
	ui->hastTextEdit->clear();
	model->clear();
	model = new QStandardItemModel(10, 2);
	ui->hastTableView->setModel(model);



	for(int i = 0; i < hashTable->hashTableSize; ++i){
		model->setData(model->index(i, 0), hashTable->HashTable[i]->value);
		model->setData(model->index(i, 1), hashTable->numberOfItemsInIndex(i));
	}


	for(int i = 0; i < hashTable->hashTableSize; ++i){
		ui->hastTextEdit->appendPlainText(hashTable->printItemsInIndex(i));
	}
}


void MainWindow::AddBtn(){
	if(ui->addEdit->text().isEmpty()){
		QMessageBox::warning(this, "NO DATA", "Set a value for a new Hash Item");
		return;
	}

	QString value = ui->addEdit->text();
	hashTable->addItem(value);

}


void MainWindow::removeBtn(){
	if(ui->removeEdit->text().isEmpty()){
		QMessageBox::warning(this, "NO DATA", "Set a value for delete Item from HashTable");
		return;
	}

	QString value = ui->removeEdit->text();
	hashTable->removeItem(value);
}


void MainWindow::searchBtn(){
	if(ui->searchEdit->text().isEmpty()){
		QMessageBox::warning(this, "NO DATA", "Set a value for search Item in HashTable");
		return;
	}

	QString value = ui->searchEdit->text();
	Item *searched = hashTable->findItem(value);

	if (!searched){
		QMessageBox::warning(this, "No such data", "There isn't such values in HashTable");
		ui->seatchResultEdit->setText("");
		return;
	}

	QString findVal;
	Item * copySearched = searched;
	while(copySearched){
		findVal += " -> " + copySearched->value;
		copySearched = copySearched->next;
	}

	ui->seatchResultEdit->setText(findVal);
}


void MainWindow::randHashBtn(){

}

