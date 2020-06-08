#include "twoqueues.h"

TwoQueues::TwoQueues(Queue *first, Queue *second)
{
	first->clear();
	second->clear();
}


void TwoQueues::fillRand(Queue *first, Queue *second, int Count1, int Count2){
	srand(time(0));

	for(int i = 0; i < Count1; i++){
		first->add(rand() % 1000);
	}

	for(int i = 0; i < Count2; i++){
		second->add(rand() % 1000);
	}
}


void TwoQueues::connectTwoQueues(Queue *first, Queue *second){
	int max = 0;

	int position = 1;
	int positionMax = 0;

	Node *current = first->head;

	while(current){
		if (current->data > max){
			max = current->data;
			positionMax = position;
		}

		current = current->next;
		position++;
	}

	qDebug() << "max: " << max;


	qDebug() << first->printAll();



	Node *current2 = second->head;
	while(current2){
		int value = current2->data;

		first->insert(++positionMax, value);
		current2 = current2->next;
	}

	qDebug() << first->printAll();
}
