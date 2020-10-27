#ifndef MEGABASE_H
#define MEGABASE_H
#include "list.h"
#include "redblacktree.h"
#include "solve.h"
#include "defenitions.h"
#include "hash.h"


class point_database;

class megabase
{
private:
	list Container;
	RBTree <point_list_node> Tree_phone;
	hash *Hash_RBT = nullptr;
	RBTree <point_database> *Tree_group;
	friend class command;
public:
	megabase(int m = 1000);
	~megabase() {delete Tree_group; delete Hash_RBT;}
	int read (FILE *fp);
	void print_Tree_group (FILE *fp = stdout);
	void insert(std::unique_ptr <char[]> &n, int p, int g);
	int insert(list_node *);
	void print_Tree_phone(FILE *fp = stdout);
	void delete_node(list_node *x);
	void delete_all() {Container.delete_list(); Tree_group->delete_all(); Hash_RBT->delete_all(); Tree_phone.delete_all();}

};

#endif // MEGABASE_H
