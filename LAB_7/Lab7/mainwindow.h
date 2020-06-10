#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hash.h"
#include "randhash.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void updateHashTables();

public slots:
	void AddBtn();
	void removeBtn();
	void searchBtn();
	void randHashBtn();

private:
	Ui::MainWindow *ui;
	QStandardItemModel *model;
	Hash *hashTable;
};
#endif // MAINWINDOW_H
