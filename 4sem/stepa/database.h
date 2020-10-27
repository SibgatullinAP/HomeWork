#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include "list.h"
#include "tree.h"
#include "hash.h"
#include "record.h"

class command;
class list_node;

class database {
	private:
		list list_base;
		tree phone_search;
		hash name_search;

	public:
		database(int size = 0){
			phone_search.setCmp(&record::phone_cmp);
			name_search.setSize(size);
		}

		~database() = default;

		int insert(list_node *);
		int remove(list_node *);
		void destroy();

		int read(FILE *);
		int execute(command &);
		void task();
};

#endif // DATABASE_H
