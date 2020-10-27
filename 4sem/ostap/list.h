#ifndef LIST_H
#define LIST_H
#include "list_node.h"


class list
{
private:
	list_node *head = nullptr;
	list_node *curr = nullptr;
	friend class megabase;
public:
	list() = default;
	~list() {delete_list();}
	void delete_list();
	int print (FILE *fout = stdout);
	int insert (char *n, int &p, int &g);
	int search (char *n, int &p, int &g, list_node **run);
	list_node *find_name_a(ccmp comp, char *n);
	list_node *find_phone_a(icmp comp, int p);
	list_node *find_group_a(icmp comp, int g);
	list_node *find_norp_a(ccmp ccomp, char *n, icmp icomp, int p);
	list_node *find_norg_a(ccmp ccomp, char *n, icmp icomp, int g);
	list_node *find_porg_a(icmp icomp1, int p, icmp icomp2, int g);
	void go_to_head() {curr = head;}
	list_node * get_head() {return head;}
	void delete_node (list_node *x);
	void put_node (list_node *x);
	list_node * search_ne(list_node *x, ratio (record::*comp)(record *), list_node *nhead = nullptr);
	list_node * search_like(list_node *x, int (*comp)(char *, char *), list_node *nhead = nullptr);
};

#endif // LIST_H
