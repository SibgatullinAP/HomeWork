#include "megabase.h"

megabase::megabase(int m)
{
	Tree_group = new RBTree<point_database> (m);
	Hash_RBT = new hash(m);
}


int megabase::read(FILE *fp)
{

	int res;

	list_node *nuxt;
	nuxt = new list_node();
	res = nuxt->read(fp);
	//printf("\nres = %d\n\n", res);
	if (res < 0)
	{
		delete nuxt;
		return res;
	}
	if (res == EOFile)
	{
		delete nuxt;
		return res;
	}

	insert(nuxt);
	//printf("\nJump??\n\n");
	for(;;)
	{
		nuxt = new list_node();
		res = nuxt->read(fp);
		if (res < 0)
		{
			delete nuxt;
			return res;
		}
		if (res == EOFile)
		{
			delete nuxt;
			return res;
		}
		res = insert(nuxt);
		if (res == EQUALITY)
		{
			delete nuxt;
			continue;
		}
	}
	//printf("\n\tSuda prishol\n\n");
	return WORK_DONE;
}

#ifdef DEBUG
void megabase::insert(std::unique_ptr <char[]> &n, int p, int g)
{
	list_node *nuxt;
	nuxt = new list_node();
	nuxt->init_ptr(n, p, g);
	int res = insert(nuxt);
	if (res == EQUALITY)
	{
		printf("\t\tThis elements is also exists\n");
		delete nuxt;
		return;
	}
	printf("\t\tDONE\n");
}
#else
void megabase::insert(std::unique_ptr <char[]> &n, int p, int g)
{
	list_node *nuxt;
	nuxt = new list_node();
	nuxt->init_ptr(n, p, g);
	int res = insert(nuxt);
	if (res == EQUALITY)
		delete nuxt;
}
#endif

int megabase::insert(list_node *nuxt)
{
	int res = Tree_group->insert(nuxt, compare_group, compare_wo_g);
	if (res == EQUALITY)
		return EQUALITY;
	Container.put_node(nuxt);
	Tree_phone.insert(nuxt, compare_phone, compare_wo_p);
	Hash_RBT->insert(nuxt, compare_name, compare_wo_n);
	return WORK_DONE;
}


void megabase::print_Tree_group(FILE *fp)
{
	Tree_group->print_tree(fp);
}

void megabase::print_Tree_phone(FILE *fp)
{
	Tree_phone.print_tree(fp);
}


void megabase::delete_node(list_node *x)
{
	Tree_phone.delete_node(x, compare_phone, compare_wo_p);
	Hash_RBT->delete_node(x, compare_name, compare_wo_n);
	Tree_group->delete_node(x, compare_group, compare_wo_g);
	Container.delete_node(x);
}
