#ifndef RedBlackTreeName_H
#define RedBlackTreeName_H

#include "RedBlackTreeNameNode.h"

class RedBlackTreeName
{
    private:
        RedBlackTreeNameNode * Root = nullptr;
	RedBlackTreeNameNode * NILL = new RedBlackTreeNameNode;

    public:
	RedBlackTreeName();
	~RedBlackTreeName();

	RedBlackTreeNameNode *getRoot();

	int read(FILE *inFile);
	void print(RedBlackTreeNameNode *root, int level = 0, int maxPrint = 0);
	void deleteRedBlackTreeName(RedBlackTreeNameNode *tmp);

	void rotateLeft(RedBlackTreeNameNode *& root, RedBlackTreeNameNode *& tmp);
	void rotateRight(RedBlackTreeNameNode *& root, RedBlackTreeNameNode *& tmp);
	RedBlackTreeNameNode * minValue(RedBlackTreeNameNode *root);
	RedBlackTreeNameNode * search(RedBlackTreeNameNode * reference);

	void insert(char *Name, int Phone, int Group);
	RedBlackTreeNameNode * binaryInsertion(RedBlackTreeNameNode *root, RedBlackTreeNameNode *source);
	void balanceInsert(RedBlackTreeNameNode *&root, RedBlackTreeNameNode *& tmp);

	void deleteValue(char *Name, int Phone, int Group);
	RedBlackTreeNameNode * binaryDeletion(RedBlackTreeNameNode *root, RedBlackTreeNameNode*reference);
	RedBlackTreeNameNode * child(RedBlackTreeNameNode *tmp);
	void balanceDelete(RedBlackTreeNameNode *tmp);
};

#endif // RedBlackTreeName_H
