#ifndef LIST_H
#define LIST_H

#include <stdio.h>

class command;
class list_node;

class list {
	private:
		list_node *head = nullptr;

	public:
		list() = default;
		~list();

		list_node * getHead() const { return head; }

		list_node * search(const command &x);
		int insert(list_node *);
		int remove(list_node *);
		void destroy();
		int isCorrect() const;

		void print(FILE *fp = stdout) const;
};

#endif // LIST_H
