#ifndef SOLVE_H
#define SOLVE_H
#include "command.h"
#include "megabase.h"
#include "defenitions.h"
#include "list_node.h"
#include "database.h"


int solve (const char *name_a, int M, double &T);
ratio compare_phone (list_node *a, RBTree_node <point_list_node> *b);
int compare_wo_p (list_node *a, RBTree_node <point_list_node> *b);
ratio compare_name (list_node *a, RBTree_node <point_list_node> *b);
int compare_wo_n (list_node *a, RBTree_node <point_list_node> *b);
ratio compare_group (list_node *a, RBTree_node <point_database> *b);
int compare_wo_g (list_node *a, RBTree_node <point_database> *b);
ratio compare_list_node_n(list_node *a, list_node *b);
ratio compare_list_node_p(list_node *a, list_node *b);
ratio compare_list_node_g(list_node *a, list_node *b);
#endif // SOLVE_H
