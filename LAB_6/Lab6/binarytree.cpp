#include "binarytree.h"

BinaryTree::BinaryTree() : root(nullptr)
{

}


Node* BinaryTree::getNewNode(int id, QString name){
	Node *newNode = new Node;
	newNode->id = id;
	newNode->name = name;
	newNode->left = newNode->right = nullptr;

	return newNode;
}


void BinaryTree::insert(Node **root, int id, QString name){
	Node *newNode = getNewNode(id, name);

	if(!(*root)){
		*root = newNode;
		emit inserted();
		return;
	}

	if(id > (*root)->id)
		insert(&(*root)->right, id, name);
	else
		insert(&(*root)->left, id, name);

	emit inserted();
}


Node* BinaryTree::search(Node *root, int id){
	if(!root)
		return nullptr;

	if(root->id == id)
		return root;

	if(id > root->id)
		return search(root->right, id);
	else
		return search(root->left, id);
}


void BinaryTree::remove(Node **root, int id){
	if(!(*root))
		return;
	else if(id < (*root)->id)
		remove(&(*root)->left, id);
	else if(id > (*root)->id)
		remove(&(*root)->right, id);
	else{
		// no child
		if(!(*root)->left && !(*root)->right){
			delete *root;
			*root = nullptr;
			return;
		} // 1 child
		else if(!(*root)->left){
			Node *temp = *root;
			*root = (*root)->right;
			delete temp;
			return;
		}
		else if(!(*root)->right){
			Node *temp = *root;
			*root = (*root)->left;
			delete temp;
			return;
		}
		else{ // 2 children
			Node *temp = findMin((*root)->right);
			(*root)->id = temp->id;
			(*root)->name = temp->name;


			remove(&(*root)->right, temp->id);
		}

	}
	emit removed();
}


Node *BinaryTree::findMin(Node *root){
	while(root->left){
		return findMin(root->left);
	}
	return root;
}


void BinaryTree::clean(Node ** root){
	if((*root)->right){
		clean(&(*root)->right);
	}
	if((*root)->left)
		clean(&(*root)->left);
	delete *root;
	*root = nullptr;
	emit cleaned();

}


void BinaryTree::preOrder(Node *root, QString *storage){
	if(root){
		*storage += QString::number(root->id) + ": " + root->name + "-->";
		preOrder(root->left, storage);
		preOrder(root->right, storage);
	}
}


void BinaryTree::postOrder(Node *root, QString *storage){
	if(root){
		postOrder(root->left, storage);
		postOrder(root->right, storage);
		*storage += QString::number(root->id) + ": " + root->name +  "-->";
	}
}

void BinaryTree::inOrder(Node *root, QString *storage){
	if(root){
		inOrder(root->left, storage);
		*storage += QString::number(root->id) + ": " + root->name + "-->";
		inOrder(root->right, storage);
	}
}



bool BinaryTree::isEmpty(){
	return !root ? true : false;
}
