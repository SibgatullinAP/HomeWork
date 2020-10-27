#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include "tree.h"
#include "command.h"

class hash {
	private:
		int size = 0;
		tree *arr = nullptr;

		int h_func(const record &) const;

    public:
		hash() = default;
		~hash();

		int getSize() const { return size; }
		int setSize(int);

		list_node * search(const command &x, data_type, int identity) const;
		int insert(list_node *);
		int remove(const list_node *);
		void destroy();
		int isCorrect() const;

		void print(FILE *fp = stdout) const;
};

#endif // HASH_H
