#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
#include <QComboBox>

#include "linkedlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void addNewOrder();
	bool checkInput();

	void showAllOrders();
	void showCompleted();
	void showTodayOrders(QString prodType);

	void initialize();





	QString orderInfo(Order *order);

public slots:
	void updateInfo();
	void updateTime();
	void updateNum_Creating();
	//void prodTypeChanged();

	void saveInfo();

	//void orderNumChanged(int index);


private slots:
	void on_orderNumBox_currentIndexChanged(int index);

	void on_viewBox_currentIndexChanged(int index);

private:
	Ui::MainWindow *ui;
	LinkedList *orderList;
	QTimer *timer;
	int items;
};
#endif // MAINWINDOW_H
