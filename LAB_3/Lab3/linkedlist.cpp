#include "linkedlist.h"

Order::Order(QString prodType_, QString date_, QString model_, bool ready_)
	: prodType(prodType_), date(date_), model(model_), ready(ready_) {

}


LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;
}


void LinkedList::add(Order *newOrder){
	if (!head){
		head = newOrder;
		head->next = nullptr;
	}
	else
		tail->next = newOrder;

	tail = newOrder;
	tail->next = nullptr;

	emit createdOrder();
}


void LinkedList::remove(int index){

	if(!head)
		return;

	Order *prev = head;
	Order *current = head->next;

	if(index == 0){
		head = current->next;
		delete current;
		return;
	}

	for(int i = 1; current; i++){
		if(index == i){
			if(!current->next)
				tail = prev;

			prev->next = current->next;
			delete current;
			return;
		}
		current = current->next;
		prev = prev->next;
	}
}


Order* LinkedList::search(int index){
	Order *current = head;

	int crnt = 0;
	while(current){
		if(crnt == index)
			return current;
		current = current->next;
		crnt ++;
	}

	return nullptr;
}


void LinkedList::change(int index, QString prodType_, QString date_, QString model_, bool ready_){
	Order *current = head;

	int crnt = 0;
	while(current){

		if(crnt == index){
			current->prodType = prodType_;
			current->date = date_;
			current->model = model_;
			current->ready = ready_;
			return;
		}

		current = current->next;
		crnt++;
	}
}









