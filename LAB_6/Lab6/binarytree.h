#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <QString>
#include <QObject>



struct Node{
	int id;
	QString name;
	Node *left;
	Node *right;
};


class BinaryTree : public QObject
{
	Q_OBJECT
public:
	BinaryTree();
	Node *root;

	Node *getNewNode(int id, QString name);
	void insert(Node** root, int id, QString name);
	void remove(Node **root, int id);
	Node *findMin(Node *root);
	Node* search(Node *root, int id);
	bool isEmpty();
	void clean(Node **root);
	void preOrder(Node *root, QString *storage);
	void postOrder(Node *root, QString *storage);
	void inOrder(Node *root, QString *storage);

signals:
	void inserted();
	void removed();
	void cleaned();
};

#endif // BINARYTREE_H
