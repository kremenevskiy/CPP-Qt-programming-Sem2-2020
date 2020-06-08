#ifndef TWOQUEUES_H
#define TWOQUEUES_H

#include "queue.h"
#include <ctime>
#include <QDebug>


class TwoQueues : public Queue
{
	Q_OBJECT
public:
	TwoQueues(Queue *first, Queue *second);
	void connectTwoQueues(Queue *first, Queue *second);

//public slots:
	void fillRand(Queue *first, Queue *second, int Count1, int Count2);


};

#endif // TWOQUEUES_H
