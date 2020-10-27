#ifndef DATABASE_H
#define DATABASE_H
#include "redblacktree.h"
#include "hash.h"
#include "defenitions.h"
#include "solve.h"



class database
{
private:
	RBTree <point_list_node> Tree_phone;
	hash *Hash_RBT = nullptr;
	int check_RB_Tree_Phone_ ();
	int check_order_Tree_Phone_ ();
public:
	database(int m = 100);
	~database() {delete Hash_RBT;}
	void print_record(FILE *fp = stdout);
	void print_Tree_phone (FILE *fp = stdout);
	void printf_Hash_RBT (FILE *fp = stdout);
	void check_RB_Tree_Phone ();
	void check_order_Tree_Phone ();
	void check_RB_Hash ();
	void insert(std::unique_ptr <char[]> &n, int p, int g);
	int insert(list_node *nuxt);
	list_node *creat_nlist(list_node *nhead = nullptr);
	void delete_node (list_node *x);
};


class point_database
{
private:
	database *key = nullptr;
	int group = 0;
public:
	~point_database() {delete key;}
	database * get_key() {return key;}
	void print_record(FILE *fp = stdout) {key->print_record(fp);}
	int init (list_node *x, int m)
	{
		if (!key)
		{
			//printf("\nBusu\n");
			key = new database(m);
			group = x->get_group();
		}
		return key->insert(x);
	}
	location check(){return DATABASE;}
	void print_location() {printf("\nYou are in DATABSE\n");}
	int get_group() {return group;}
	list_node * get_list (list_node *nhead = nullptr) {return key->creat_nlist(nhead);}
	void change_node(point_database *x)
	{
		database *t;
		t = key;
		key = x->key;
		x->key = t;
		int g;
		g = group;
		group = x->group;
		x->group = g;
	}
	void delete_key (list_node *x)
	{
		key->delete_node(x);
	}
};

#endif // DATABASE_H
