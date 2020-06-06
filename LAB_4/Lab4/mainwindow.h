#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>

#include "stack.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	QString toRPolishNot(QString input);
	int priority(char oprtn);
	bool hasHighierPreor(char a, char lastStack);
	bool isOperand(char ch);

	bool isOperation(char operation);

	double getValue(char fromCh);


public slots:
	void runBtnClicked();
	void resetBtnClicked();


private:
	Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
