#ifndef RedBlackTreeName_H
#define RedBlackTreeName_H

#include "RedBlackTreeNameNode.h"

class RedBlackTree;
class RedBlackTreeNode;

class RedBlackTreeName
{
    private:
        RedBlackTreeNameNode * Root = nullptr;
	RedBlackTreeNameNode * NILL = new RedBlackTreeNameNode;

    public:
	RedBlackTreeName();
	~RedBlackTreeName();

	friend class RedBlackTree;
	friend class RedBlackTreeNode;

	RedBlackTreeNameNode *getRoot();

	void print(RedBlackTreeNameNode *root, int level = 0, int maxPrint = 0);
	void deleteRedBlackTreeName(RedBlackTreeNameNode *tmp);

	void rotateLeft(RedBlackTreeNameNode *& root, RedBlackTreeNameNode *& tmp);
	void rotateRight(RedBlackTreeNameNode *& root, RedBlackTreeNameNode *& tmp);
	RedBlackTreeNameNode * minValue(RedBlackTreeNameNode *root);
	RedBlackTreeNameNode * search(ListNode * reference);
	bool isContain(ListNode * reference);

	bool insert(ListNode * reference);
	RedBlackTreeNameNode * binaryInsertion(RedBlackTreeNameNode *root, RedBlackTreeNameNode *source);
	void balanceInsert(RedBlackTreeNameNode *&root, RedBlackTreeNameNode *& tmp);

	void deleteValue(ListNode * reference);
	RedBlackTreeNameNode * binaryDeletion(RedBlackTreeNameNode*reference);
	RedBlackTreeNameNode * child(RedBlackTreeNameNode *tmp);
	void balanceDelete(RedBlackTreeNameNode *tmp);
};

#endif // RedBlackTreeName_H
