#include "leavestree.h"

void LeavesTree::getLeavesCount(Node *root, int *storage){
	if (root){
		getLeavesCount(root->left, storage);
		if(!root->left && !root->right){
			(*storage)++;
		}
		getLeavesCount(root->right, storage);
	}
}
