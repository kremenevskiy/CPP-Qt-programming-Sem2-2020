#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	tree = new BinaryTree();


	ui->treeWidget->setColumnCount(2);

	model = new QStandardItemModel(7,2);
	QStringList list;
	list << "key" << "value";
	model->setHorizontalHeaderLabels(list);
	ui->tableView->setModel(model);




	QRegExp regex("[0-9]{1,10}");
	QRegExpValidator *validator = new QRegExpValidator(regex, this);
	ui->insertKeyEdit->setValidator(validator);
	ui->removeKeyEdit->setValidator(validator);
	ui->searchKeyEdit->setValidator(validator);


	connect(ui->insertButton, &QPushButton::clicked, this, &MainWindow::insertBtn);
	connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::removeBtn);
	connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchBtn);
	connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::updateBtn);
	connect(ui->getLeavesButton, &QPushButton::clicked, this, &MainWindow::getLeavesBtn);
	connect(ui->cleanButton, &QPushButton::clicked, this, &MainWindow::cleanBtn);

	connect(tree, &BinaryTree::inserted, [&](){
		reDrawTree();
	});


	connect(tree, &BinaryTree::removed, [&](){
		reDrawTree();
	});

	connect(tree, &BinaryTree::cleaned, [&](){
		reDrawTree();
	});

	initialize();

}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::drawTree(QTreeWidgetItem *parent, Node *root){
	if (!root)
		return;
	if(root == tree->root){
		QTreeWidgetItem *parent = new QTreeWidgetItem(ui->treeWidget);
		parent->setText(0, QString::number(root->id));
		parent->setText(1, root->name);
		drawTree(parent, root->left);
		drawTree(parent, root->right);
	}


	QTreeWidgetItem *newChild = new QTreeWidgetItem(parent);
	newChild->setText(0, QString::number(root->id));
	newChild->setText(1, root->name);

	drawTree(newChild, root->left);
	drawTree(newChild, root->right);
}


void MainWindow::reDrawTree(){
	ui->treeWidget->clear();
	drawTree(nullptr, tree->root);
}


void MainWindow::insertBtn(){
	if(ui->insertKeyEdit->text().isEmpty() || ui->insertValueEdit->text().isEmpty()){
		QMessageBox::warning(this, "Empty lines!", "Set key and value for insert");
		return;
	}
	tree->insert(&tree->root, ui->insertKeyEdit->text().toInt(), ui->insertValueEdit->text());


}


void MainWindow::removeBtn(){
	if(ui->removeKeyEdit->text().isEmpty()){
		QMessageBox::warning(this, "Empty lines!", "Set key for remove");
		return;
	}

	tree->remove(&tree->root, ui->removeKeyEdit->text().toInt());
}


void MainWindow::searchBtn(){
	if(ui->searchKeyEdit->text().isEmpty()){
		QMessageBox::warning(this, "Empty lines!", "Set key for search");
		return;
	}

	Node *searched = tree->search(tree->root, ui->searchKeyEdit->text().toInt());

	if (!searched){
		QMessageBox::warning(this, "Search Failed!", "No value with such key!");
		return;
	}

	QString value = searched->name;
	ui->searchValueEdit->setText(value);
}


void MainWindow::updateBtn(){
	QString preOrder;
	QString postOrder;
	QString inOrder;

	tree->preOrder(tree->root, &preOrder);
	tree->postOrder(tree->root, &postOrder);
	tree->inOrder(tree->root, &inOrder);

	ui->InOrderEdit->setText(inOrder);
	ui->PreOrderEdit->setText(preOrder);
	ui->PostOrderEdit->setText(postOrder);
}


void MainWindow::cleanBtn(){
	tree->clean(&tree->root);
}


void MainWindow::getLeavesBtn(){
	int leaves = 0;
	LeavesTree::getLeavesCount(tree->root, &leaves);

	ui->leavesEdit->setText(QString::number(leaves));
}


void MainWindow::initialize(){


	int key1 = 20;
	int key2 = 10;
	int key3 = 5;
	int key4 = 15;
	int key5 = 30;
	int key6 = 25;
	int key7 = 40;
	QString value1 = "Vlad";
	QString value2 = "Maksim";
	QString value3 = "Polina";
	QString value4 = "Kristina";
	QString value5 = "ALina";
	QString value6 = "Maria";
	QString value7 = "Sofia";

	tree->insert(&tree->root, key1, value1);
	tree->insert(&tree->root, key2, value2);
	tree->insert(&tree->root, key3, value3);
	tree->insert(&tree->root, key4, value4);
	tree->insert(&tree->root, key5, value5);
	tree->insert(&tree->root, key6, value6);
	tree->insert(&tree->root, key7, value7);


	QModelIndex index;
	index = model->index(0,0);
	model->setData(index, QString::number(key1));
	index = model->index(0,1);
	model->setData(index, value1);
	index = model->index(1,0);
	model->setData(index, QString::number(key2));
	index = model->index(1,1);
	model->setData(index, value2);
	index = model->index(2,0);
	model->setData(index, QString::number(key3));
	index = model->index(2,1);
	model->setData(index, value3);
	index = model->index(3,0);
	model->setData(index, QString::number(key4));
	index = model->index(3,1);
	model->setData(index, value4);
	index = model->index(4,0);
	model->setData(index, QString::number(key5));
	index = model->index(4,1);
	model->setData(index, value5);
	index = model->index(5,0);
	model->setData(index, QString::number(key6));
	index = model->index(5,1);
	model->setData(index, value6);
	index = model->index(6,0);
	model->setData(index, QString::number(key7));
	index = model->index(6,1);
	model->setData(index, value7);

	int rows = model->rowCount();
	model->insertRow(model->index(++rows,0).row());


}



