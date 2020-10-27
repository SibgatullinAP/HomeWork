#ifndef TREE_H
#define TREE_H 

#include "treeNode.h"
#include <math.h>

class Tree
{
	private:
		int Order = 0; 
		TreeNode *Root = nullptr;

	public:
		Tree() = default;
		Tree(int order);
		~Tree()
		{
			deleteTree(Root);
		}

		void deleteTree(TreeNode *root);
		int read(FILE *fp);
		Student* insert(Student *src, TreeNode *current, TreeNode **left, TreeNode **right);
		Student* insertTreeNode(Student *result, TreeNode *current, TreeNode **left, TreeNode **right);
		void print(TreeNode *root, int level = 0, int counter = -1, FILE *out = stdout);

		int getOrder();
		TreeNode* getRoot();
		void testAll(int k = 0);

       	int func1(int k);
       	void solve1(TreeNode* tmp, int k, int &count);

       	int func2(int k);
       	int solve2(TreeNode* tmp, int k, int &counter, int &counter_students);

       	int func3(int k);
       	int solve3(TreeNode * Root, int k, int &counter, int &count_students, int &res);

       	int func4(int k);
		int getHeight(TreeNode * Root);
       	int solve4(TreeNode * Root, int k, int &counter, int h, int &count_students, int &res);

        int func6(int k); 

};

#endif