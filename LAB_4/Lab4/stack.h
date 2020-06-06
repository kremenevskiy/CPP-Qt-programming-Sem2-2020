#ifndef STACK_H
#define STACK_H

#include <QString>
#include <QDebug>

template<class T>
class Node
{
public:
	Node();
	Node(T data);
	Node *next;
	T data;
};


template<class T>
class Stack
{
public:
	Stack();
	Node<T> *top;

	void push(T newData);
	T pop();
	T peek();
	void clear();
	QString viewAll();
	bool isEmpty();
};



#endif // STACK_H
