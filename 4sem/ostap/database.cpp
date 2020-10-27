#include "database.h"


list_node * database::creat_nlist(list_node *nhead)
{
	return Tree_phone.making_list(Tree_phone.get_root(), nhead);
}


database::database(int m)
{
	hash *buf;
	buf = new hash(m);
	Hash_RBT = buf;
}


void database::print_record(FILE *fp)
{
	printf("\n\tTree_phone\n");
	print_Tree_phone(fp);
	printf("\n\tHash\n");
	printf_Hash_RBT(fp);
}


void database::insert(std::unique_ptr <char[]> &n, int p, int g)
{
	list_node *nuxt;
	nuxt = new list_node();
	nuxt->init_ptr(n, p, g);
	int res = insert(nuxt);
	if (res == EQUALITY)
		delete nuxt;
}

int database::insert(list_node *nuxt)
{
	int res = Tree_phone.insert(nuxt, compare_phone, compare_wo_p);
	if (res == EQUALITY)
		return EQUALITY;
	Hash_RBT->insert(nuxt, compare_name, compare_wo_n);
	return WORK_DONE;
}


void database::print_Tree_phone(FILE *fp)
{
	Tree_phone.print_tree(fp);
}


void database::printf_Hash_RBT(FILE *fp)
{
	Hash_RBT->print_hash(fp);
}

void database::check_RB_Tree_Phone()
{
	int res = check_RB_Tree_Phone_();
	if (!res)
		printf("\nTree is not RB\n\n");
	else
		printf("\nTree is RB with BLACK_weight = %d\n\n", res);
}


void database::check_order_Tree_Phone()
{
	int res = check_order_Tree_Phone_();
	if (!res)
		printf("\nTree is not ordered\n\n");
	else
		printf("\nTree is OK (ordered)\n\n");
}

void database::check_RB_Hash()
{
	if (!Hash_RBT->check_RB())
		printf("\nProblem with color of HASH\n\n");
	else
		printf("\nHASH'S color is OK\n\n");
}


int database::check_order_Tree_Phone_()
{
	return Tree_phone.check_order(Tree_phone.root, compare_phone);
}

int database::check_RB_Tree_Phone_()
{
	return Tree_phone.check_RB(Tree_phone.root);
}

void database::delete_node(list_node *x)
{
	Tree_phone.delete_node(x, compare_phone, compare_wo_p);
	Hash_RBT->delete_node(x, compare_name, compare_wo_n);
}
