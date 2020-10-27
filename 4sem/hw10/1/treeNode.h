#ifndef TREE_NODE_H
#define TREE_NODE_H 

#include "student.h"

class TreeNode;
class Tree;

class TreeNode
{
	private:
		TreeNode **Children = nullptr;
		Student **Values = nullptr;
		int Size = 0;

	public:
		TreeNode (int size = 0);
		~TreeNode() = default;

		void deleteNode();
		void clear(int n);
		void fullClear();
		int findInsert(Student *src);
		void print(int ord, FILE *out = stdout);

		friend class Tree;
};

#endif