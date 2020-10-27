#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "record.h"

class list_node;
class list;
class database;
class tree;

class list_node : public record {
	private:
	    list_node *next = nullptr;
		list_node *prev = nullptr;
		list_node *next_search = nullptr;

	public:
		list_node() = default;
		~list_node() = default;

		list_node * get_next() const { return next; }
		list_node * get_prev() const { return prev; }

	friend class database;
	friend class list;
	friend class tree;
};

#endif // LIST_NODE_H
