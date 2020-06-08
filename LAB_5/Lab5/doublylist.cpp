#include "doublylist.h"

Node::Node(){
	this->next = nullptr;
	this->prev = nullptr;
}

DoublyList::DoublyList() : head(nullptr), tail(nullptr)
{

}


Node* DoublyList::getNewNode(int data){
	Node* newNode = new Node;
	newNode->data = data;
	return newNode;
}


void DoublyList::pushBack(int data){
	Node *newNode = getNewNode(data);

	if(!head){
		head = newNode;
		tail = newNode;
		return;
	}

	Node *current = head;

	while(current->next){
		current = current->next;
	}


	current->next = newNode;
	newNode->prev = current;
	tail = newNode;
}


void DoublyList::insert(int index, int data){

	Node* newNode = getNewNode(data);
	index--;

	if(!head){
		head = newNode;
		tail = head;
		return;
	}

	Node *current = head;

	for(int i = 1; i < index &&	current->next; i++)
		current = current->next;


	if(!index){
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
		return;
	}


	if(current == tail){
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
		return;
	}

	current->next->prev = newNode;
	newNode->next = current->next;
	current->next = newNode;
	newNode->prev = current;
	return;
}


void DoublyList::remove(int index){
	if(isEmpty())
		return;

	index --;


	Node *current = head;
	for(int i = 0; i < index && current->next; i++){
		current = current->next;
	}

	if(current == head){
		if(head == tail)
			tail = nullptr;
		head = head->next;

		if (head)
			head->prev = nullptr;

		delete current;
		return;
	}

	if(current == tail){
		current->prev->next = nullptr;
		tail = current->prev;
		delete current;
		return;
	}


	current->prev->next = current->next;
	current->next->prev = current->prev;
	delete current;
	return;
}


Node* DoublyList::search(int data){

	Node * current = head;

	while(current->next){
		if(current->data == data){
			return current;
		}
		current = current->next;
	}

	return nullptr;
}


QString DoublyList::printAll(){
	QString buffer;
	Node *current = head;

	while(current){
		buffer += QString::number(current->data) + " ";
		current = current->next;
	}

	return buffer;
}


bool DoublyList::isEmpty(){
	if(!head)
		return true;
	return false;
}


void DoublyList::clear(){

	if(!head)
		return;

	Node *current = head;

	while(current->next){
		head = current->next;
		delete current;
		current = current->next;
	}
	delete head;
	head = nullptr;
	tail = nullptr;
}
