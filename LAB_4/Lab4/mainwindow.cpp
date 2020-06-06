#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{



	ui->setupUi(this);
	ui->polishNotation->setReadOnly(true);
	ui->resultEdit->setReadOnly(true);

	QRegExp regex("[\\-]{0,1}[0-9]{1,10}|[\\-]{0,1}[0-9]{1,5}[\\.{0,1}][0-9]{1,5}");
	QRegExpValidator *validator = new QRegExpValidator(regex, this);
	ui->aEdit->setValidator(validator);
	ui->bEdit->setValidator(validator);
	ui->cEdit->setValidator(validator);
	ui->dEdit->setValidator(validator);
	ui->eEdit->setValidator(validator);

	ui->aEdit->setText("7.4");
	ui->bEdit->setText("3.6");
	ui->cEdit->setText("2.8");
	ui->dEdit->setText("9.5");
	ui->eEdit->setText("0.9");
	ui->inputEdit->setText("(a+b)*(c-d)/e");


	QRegExp regexInput("[a-zA-Z\\+\\-\\*\\/\\(\\)]{1,40}![0-9]");
	QRegExpValidator *validator2 = new QRegExpValidator(regexInput, this);
	ui->inputEdit->setValidator(validator2);


	connect(ui->runButton, &QPushButton::clicked, this, &MainWindow::runBtnClicked);
	connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetBtnClicked);


}


MainWindow::~MainWindow()
{
	delete ui;
}


QString MainWindow::toRPolishNot(QString input){

	Stack<char>* oprtnStack = new Stack<char>();
	QString postfix;

	for(int i = 0; i < input.length(); i++){
		char crnt = input[i].toLatin1();

		if(isOperand(crnt))
			postfix.append(crnt);

		else if(isOperation(crnt)){
			if(oprtnStack->isEmpty() || hasHighierPreor(crnt, oprtnStack->peek())){
				oprtnStack->push(crnt);
			}
			else{
				while(!oprtnStack->isEmpty() && priority(crnt) <= priority(oprtnStack->peek())){
					postfix.append(oprtnStack->pop());
				}
				oprtnStack->push(crnt);
			}
		}
		else if(crnt == '(')
			oprtnStack->push(crnt);
		else if(crnt == ')'){
			char popped = oprtnStack->pop();
			while(popped != '('){
				postfix.append(popped);
				popped = oprtnStack->pop();
			}

		}
	}

	while(!oprtnStack->isEmpty()){
		postfix.append(oprtnStack->pop());
	}

	return postfix;
}


bool MainWindow::hasHighierPreor(char a, char b){
	return priority(a) > priority(b) ? true : false;
}


bool MainWindow::isOperand(char ch){
	if(ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '^' && ch != '(' && ch != ')')
		return true;

	return false;
}


bool MainWindow::isOperation(char operation){
	if (operation == '+' || operation == '-' || operation == '*' || operation == '/' || operation == '^')
		return true;

	return false;
}


int MainWindow::priority(char oprtn){
	if (oprtn == '(')
		return 1;
	else if(oprtn == '^')
		return 4;
	else if(oprtn == '*' || oprtn == '/')
		return 3;
	else if(oprtn == '+' || oprtn == '-')
		return 2;

	return 0;
}


void MainWindow::runBtnClicked(){
	if (ui->aEdit->text().isEmpty() || ui->bEdit->text().isEmpty() || ui->cEdit->text().isEmpty()
			|| ui->dEdit->text().isEmpty() || ui->eEdit->text().isEmpty() || ui->inputEdit->text().isEmpty()){

		QMessageBox::warning(this, "Input Error", "Fill all missed fields!");
		return;
	}

	QString input = ui->inputEdit->text();
	input = input.remove(" ");
	QString polishNtshn = toRPolishNot(input);
	ui->polishNotation->setText(polishNtshn);


	Stack<double> *polishStack = new Stack<double>();

	for(int i = 0; i < polishNtshn.length(); i++){
		char crnt = polishNtshn[i].toLatin1();
		if (isOperation(crnt)){

			double result;
			double second = polishStack->pop();
			double first = polishStack->pop();

			switch (crnt) {
			case '+':
				result = first + second;
				break;
			case '-':
				result = first - second;
				break;
			case '*':
				result = first * second;
				break;
			case '/':
				result = first / second;
				break;
			/*case '^':
				break*/;
			}

			polishStack->push(result);
		}
		else{
			polishStack->push(getValue(crnt));
		}
	}

	double resultValue = polishStack->pop();

	ui->resultEdit->setText(QString::number(resultValue));
}


void MainWindow::resetBtnClicked(){
	ui->aEdit->setText("");
	ui->bEdit->setText("");
	ui->cEdit->setText("");
	ui->dEdit->setText("");
	ui->eEdit->setText("");
	ui->inputEdit->setText("");
	ui->polishNotation->setText("");
	ui->resultEdit->setText("");
}


double MainWindow::getValue(char fromCh){
	switch (fromCh) {
	case 'a':
		return ui->aEdit->text().toDouble();
	case 'b':
		return ui->bEdit->text().toDouble();
	case 'c':
		return ui->cEdit->text().toDouble();
	case 'd':
		return ui->dEdit->text().toDouble();
	case 'e':
		return ui->eEdit->text().toDouble();
	}
	QMessageBox::warning(this, "ERROR", "Error with getting value from A/B/C/D/E numbers");
	return 0;
}
