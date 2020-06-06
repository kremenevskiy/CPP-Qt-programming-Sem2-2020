#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <QString>
#include <QObject>
#include <QDebug>

struct Order{
	QString prodType;
	QString date;
	QString model;
	bool ready;

	Order *next;

	Order(QString prodType_, QString date_, QString model_, bool ready_);
};


class LinkedList : public QObject
{
	Q_OBJECT
public:

	Order * head;
	Order * tail;

	LinkedList();
	void add(Order *newOrder);
	void remove(int index);
	Order* search(int index);
	void change(int index, QString prodType_, QString date_, QString model_, bool ready_);
	void print();

signals:
	void createdOrder();


};

#endif // LINKEDLIST_H
