#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QStringListModel>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>

#include "doublylist.h"
#include "queue.h"
#include "twoqueues.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void addBtn();
	void extractBtn();
	void isEmptyBtn();
	void clearBtn();
	void extracted(int data);
	void added(int data);
	void checkTailHead();

	void startTwoQueueTaks();
	void linkQueues();
	void fillRand();
	void added2(int data);
	void stopTask();

private:
	Ui::MainWindow *ui;
	QStringListModel *model;
	QStringListModel *model2;
	Queue *queue;
	Queue *queue2;

	TwoQueues *queuesTask;
};
#endif // MAINWINDOW_H
