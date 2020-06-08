#ifndef QUEUE_H
#define QUEUE_H

#include "doublylist.h"
#include <QObject>

class Queue : public QObject, public DoublyList
{
	Q_OBJECT
public:
	Queue();

	void add(int data);
	int extract();
	QString printAll();
	bool isEmpty();
	void clear();

signals:
	void removeSgnl(int data);
	void added(int data);

};

#endif // QUEUE_H
