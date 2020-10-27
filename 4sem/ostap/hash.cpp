#include "hash.h"

hash::hash(int m)
{
	Array = new RBTree <point_list_node>* [m];
	if (!Array)
		printf("\nCannot not allocate memmory for Hash\n\n");
	for (int i = 0; i < m; Array[i] = new RBTree <point_list_node>, i++);
	module = m;
}


int hash::insert(list_node *x, ratio (*comp)(list_node *, RBTree_node <point_list_node> *), int (*total_comp)(list_node *, RBTree_node <point_list_node> *))
{
	int value = x->hash_name(module);
	/*
	x->print_record();
	printf(" hash = %d\n\n", value);
	*/
	Array[value]->insert(x, comp, total_comp);
	return WORK_DONE;
}

void hash::delete_all()
{
	for (int i = 0; i < module; Array[i]->delete_all(), i++);
}

void hash::delete_array()
{
	for (int i = 0; i < module; delete Array[i], i++);
	module = 0;
	delete [] Array;
}


void hash::print_hash(FILE *fp)
{
	int counter = 0;
	for (int i = 0; i < module && counter < MAX_LEN; i++)
	{
		if (Array[i]->get_root())
		{
			fprintf(fp, "\nARRAY[%d]:\n", i);
			Array[i]->print_tree(fp);
			counter++;
		}
	}
}


int hash::check_RB()
{
	for (int i = 0; i < module; i++)
	{
		if (!Array[i]->check_RB(Array[i]->get_root()))
			return 0;
	}
	return 1;
}


list_node * hash::search_eq(list_node *x, ratio (*comp)(list_node *, RBTree_node<point_list_node> *), list_node *nhead)
{
	int number = x->hash_name(module);
	return Array[number]->search_eq(x, comp, nhead);
}

list_node * hash::search_lt(list_node *x, ratio (*comp)(list_node *, RBTree_node<point_list_node> *), list_node *nhead)
{
	for (int i = 0; i < module; i++)
		nhead = Array[i]->search_lt(x, comp, nhead);
	return nhead;
}

list_node * hash::search_le(list_node *x, ratio (*comp)(list_node *, RBTree_node<point_list_node> *), list_node *nhead)
{
	for (int i = 0; i < module; i++)
		nhead = Array[i]->search_le(x, comp, nhead);
	return nhead;
}

list_node * hash::search_gt(list_node *x, ratio (*comp)(list_node *, RBTree_node<point_list_node> *), list_node *nhead)
{
	for (int i = 0; i < module; i++)
		nhead = Array[i]->search_gt(x, comp, nhead);
	return nhead;
}

list_node * hash::search_ge(list_node *x, ratio (*comp)(list_node *, RBTree_node<point_list_node> *), list_node *nhead)
{
	for (int i = 0; i < module; i++)
		nhead = Array[i]->search_ge(x, comp, nhead);
	return nhead;
}

void hash::delete_node(list_node *x, ratio (*comp)(list_node *, RBTree_node<point_list_node> *), int (*total_comp)(list_node *, RBTree_node<point_list_node> *))
{
	//printf("\ndeleting list_node from hash "); x->print_record(); printf("\n");
	int res = x->hash_name(module);
	Array[res]->delete_node(x, comp, total_comp);
}
