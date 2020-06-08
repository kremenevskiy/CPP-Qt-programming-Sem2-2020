#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

#include <QString>
#include <QObject>

struct Node{
	int data;
	Node *next;
	Node *prev;
	Node();
};


class DoublyList
{
public:
	Node *head;
	Node *tail;

//protected:
	DoublyList();

	Node *getNewNode(int data);
	void insert(int index, int data);
	void pushBack(int data);
	void remove(int index);
	Node *search(int data);
	bool isEmpty();

	QString printAll();

	void clear();

};

#endif // DOUBLYLIST_H
