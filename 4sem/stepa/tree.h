#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include "command.h"

class list_node;
class tree_node;

class tree {
	private:
		int (*cmp)(const record &, const record &) = nullptr;
		tree_node *root = nullptr;

    public:
		tree() = default;
		~tree();

		tree_node * getRoot() const { return root; }
		void setCmp(int (*cmp)(const record &, const record &)){ this->cmp = cmp; }

		list_node * search(const command &x, data_type, int identity) const;
		int insert(list_node *);
		int remove(const list_node *);
		void destroy();
		int isCorrect() const;

		void print(FILE *fp = stdout) const;
		int blackDepth() const;

	private:
		int recursInsert(tree_node *, tree_node *&);
		int recursRemove(tree_node *, const list_node *, tree_node *&);
		static void recursDestroy(tree_node *);

		static void recursPrint(tree_node *, int *, FILE *, int);
		int recursCorrect(tree_node *) const;
		static void swapData(tree_node *, tree_node *);
};

#endif // TREE_H
