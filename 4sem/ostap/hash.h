#ifndef HASH_H
#define HASH_H
#include "redblacktree.h"

class hash
{
private:
	RBTree <point_list_node> **Array = nullptr;
	int module = 1000;
public:
	hash() = default;
	hash(int m);
	~hash () {delete_array();}
	int insert (list_node *x, ratio (*comp)(list_node *, RBTree_node <point_list_node> *), int (*total_comp)(list_node *, RBTree_node <point_list_node> *));
	void delete_array();
	void print_hash(FILE *fp = stdout);
	int check_RB();
	list_node *search_eq(list_node *x, ratio (*comp)(list_node *, RBTree_node<point_list_node> *), list_node *nhead = nullptr);
	list_node *search_lt(list_node *x, ratio (*comp)(list_node *, RBTree_node<point_list_node> *), list_node *nhead = nullptr);
	list_node *search_le(list_node *x, ratio (*comp)(list_node *, RBTree_node<point_list_node> *), list_node *nhead = nullptr);
	list_node *search_gt(list_node *x, ratio (*comp)(list_node *, RBTree_node<point_list_node> *), list_node *nhead = nullptr);
	list_node *search_ge(list_node *x, ratio (*comp)(list_node *, RBTree_node<point_list_node> *), list_node *nhead = nullptr);
	void delete_node(list_node *x, ratio (*comp)(list_node *, RBTree_node <point_list_node> *), int (*total_comp)(list_node *, RBTree_node <point_list_node> *));
	void delete_all();
};

#endif // HASH_H
