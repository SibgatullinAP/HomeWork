#ifndef RedBlackTree_H
#define RedBlackTree_H

#include "RedBlackTreeNode.h"
#include "command.h"

class DataBase;

class RedBlackTree
{
    private:
        RedBlackTreeNode * Root = nullptr;
	RedBlackTreeNode * NILL = nullptr;
	int HashChar = 0;

    public:
	RedBlackTree() = default;
	RedBlackTree(int HashSize);
	~RedBlackTree();

	friend class DataBase;

	RedBlackTreeNode *getRoot();

	void print(RedBlackTreeNode *root, int level = 0, int maxPrint = 0);
	void deleteRedBlackTree(RedBlackTreeNode *tmp);

	void rotateLeft(RedBlackTreeNode *& root, RedBlackTreeNode *& tmp);
	void rotateRight(RedBlackTreeNode *& root, RedBlackTreeNode *& tmp);
	RedBlackTreeNode * minValue(RedBlackTreeNode *root);
	RedBlackTreeNode * search(ListNode * reference);
	bool isContain(ListNode * reference);

	bool insert(ListNode *tmp); // true - если еще нет такого элемента, false - иначе
	RedBlackTreeNode * binaryInsertion(RedBlackTreeNode *root, RedBlackTreeNode *source);
	void balanceInsert(RedBlackTreeNode *&root, RedBlackTreeNode *& tmp);

	void deleteValue(ListNode *tmp);
	RedBlackTreeNode * binaryDeletion(RedBlackTreeNode*reference);
	RedBlackTreeNode * child(RedBlackTreeNode *tmp);
	void balanceDelete(RedBlackTreeNode *tmp);
};

#endif // RedBlackTree_H
