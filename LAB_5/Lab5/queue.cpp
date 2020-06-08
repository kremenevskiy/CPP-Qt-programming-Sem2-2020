#include "queue.h"

Queue::Queue() : DoublyList()
{

}

void Queue::add(int data){
	emit added(data);
	this->pushBack(data);
}


int Queue::extract(){
	int data = head->data;
	emit removeSgnl(data);
	this->remove(1);
	return data;
}


QString Queue::printAll(){
	return DoublyList::printAll();
}


bool Queue::isEmpty(){
	return DoublyList::isEmpty();
}


void Queue::clear(){
	DoublyList::clear();
}
