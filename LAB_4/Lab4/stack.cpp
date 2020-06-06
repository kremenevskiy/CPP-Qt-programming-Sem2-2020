#include "stack.h"

template<class T>
Node<T>::Node() : next(nullptr), data()
{

}


template <class T>
Node<T>::Node(T data) : Node()
{
	this->data = data;
}


template<class T>
Stack<T>::Stack() : top(nullptr)
{

}


template<typename T>
void Stack<T>::push(T data){
	Node<T> *newNode = new Node<T>(data);

	newNode->next = top;
	top = newNode;
}


template<typename T>
T Stack<T>::pop()
{
	Node<T>* oldTop = this->top;

	T poppedData = oldTop->data;
	top = top->next;
	delete oldTop;

	return 	poppedData;
}


template <typename T>
T Stack<T>::peek(){
	return top->data;
}


template <typename T>
void Stack<T>::clear(){
	while(top){
		pop();
	}
}


template <typename T>
QString Stack<T>::viewAll(){
	QString datan;
	Node<T> *temp = top;
	while(temp){
		qDebug() << temp->data << " ";
//		datan += temp->data.toString(); + " ";
		temp = temp->next;
	}

	return datan;
}


template <typename T>
bool Stack<T>::isEmpty(){
	return top == nullptr ? true : false;
}


// Прочитать про это
template class Stack<int>;
template class Stack<char>;
template class Stack<double>;







