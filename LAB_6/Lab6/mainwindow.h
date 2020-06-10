#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "binarytree.h"
#include "leavestree.h"
#include <QTreeWidgetItem>
#include <QStandardItemModel>
#include <QRegExp>
#include <QRegExpValidator>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void drawTree(QTreeWidgetItem *parent, Node* root);
	void reDrawTree();

	void initialize();

public slots:
	void insertBtn();
	void removeBtn();
	void searchBtn();
	void updateBtn();
	void cleanBtn();
	void getLeavesBtn();


private:
	Ui::MainWindow *ui;

	BinaryTree *tree;
	QStandardItemModel *model;


};
#endif // MAINWINDOW_H
