#ifndef LEAVESTREE_H
#define LEAVESTREE_H

#include "binarytree.h"

class LeavesTree : public BinaryTree
{
public:
	static void getLeavesCount(Node * root, int *storage);
};

#endif // LEAVESTREE_H
