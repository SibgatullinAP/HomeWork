#include "solve.h"



ratio compare_phone (list_node *a, RBTree_node <point_list_node> *b)
{
	return a->compare_phone_(b->get_key());
}

int compare_wo_p (list_node *a, RBTree_node <point_list_node> *b)
{

	if (a->compare_group_(b->get_key()) == EQUAL)
	{
		if (a->compare_name_(b->get_key()) == EQUAL)
			return EQUALITY;
	}
	return 0;
}

ratio compare_name (list_node *a, RBTree_node <point_list_node> *b)
{
	return a->compare_name_(b->get_key());
}

int compare_wo_n (list_node *a, RBTree_node <point_list_node> *b)
{

	if (a->compare_phone_(b->get_key()) == EQUAL)
	{
		if (a->compare_group_(b->get_key()) == EQUAL)
			return EQUALITY;
	}
	return 0;
}

ratio compare_group (list_node *a, RBTree_node <point_database> *b)
{
	if (a->get_group()< b->get_group())
		return LESS;
	if (a->get_group() > b->get_group())
		return MORE;
	return EQUAL;
}

int compare_wo_g (list_node *a, RBTree_node <point_database> *b)
{
	(void) a; (void) b;
	printf("\n\nKOSTЫLINA\n\n");
	return WORK_DONE;
}


int solve (const char *name_a, int M, double &T)
{
	char buf[LEN], buf2[LEN], s[BRAKES] = {' ', '\t', '\n'};
	int tab[SPACES] = {0};
	double t;

	for (int i = 0; i < BRAKES; tab[(int) s[i]] = 1, i++);

	int res = 0;
	megabase A(M);

	if (name_a)
	{
		FILE *fa;
		if(!(fa = fopen(name_a, "r")))
			return CANNOT_OPEN_FILE_A;
		printf("\nStart reading from file '%s'\n", name_a);
		t = clock();
		res = A.read(fa);
		t = (clock()-t)/CLOCKS_PER_SEC;
		printf("End of reading\n\x1b[31mTIME\x1b[0m reading         = %f\n\n", t);
		//printf("\nTuta\n\n");
		if (res < 0)
		{
			fclose(fa);
			return res;
		}
		fclose(fa);
	}

	//FILE *ftest; ftest = fopen ("Start_tree.txt", "w"); A.print_Tree_phone(ftest); fclose(ftest);

	//printf("\nTree_group = \n\n"); A.print_Tree_group();


	printf("\nInput command\n");
	t = clock();

	list_node *puf;
	puf = new list_node;
	command prikaz;
	while(fgets(buf, LEN, stdin))
	{
		printf("\ninput: %s\n", buf);
		if (!prikaz.parse(buf, tab, buf2))
		{
			printf("WRONG command\n");
			continue;
		}

		printf("test : "); prikaz.print(); printf("\n");


#ifdef DEBUG
		printf("command: %sresult:", buf);
#endif
		res = prikaz.make_command(A, puf);
		if (res == EXIT)
		{
#ifdef DEBUG
			printf("\t\t  EXIT\n");
#endif
			break;
		}
		//A.print_Tree_phone(); printf("\n\n");
		}
	if (res != EXIT)
	{
		if (!feof(stdin))
		{
			delete puf;
			return FGETS_ERR;
		}
	}

	t =  (clock()-t)/CLOCKS_PER_SEC;
	printf("End of making command\n\x1b[31mTIME\x1b[0m making commands = %f\n", t);

	delete puf;
	T = clock();
	return WORK_DONE;
}


int like_c (char *a, char *b);


int c_EQ (char *a, char *b) {return (strcmp(a,b)? 0: 1);}
int c_NE (char *a, char *b) {return (strcmp(a,b)? 1: 0);}
int c_LT (char *a, char *b) {return (strcmp(a,b) < 0? 1: 0);}
int c_GT (char *a, char *b) {return (strcmp(a,b) > 0? 1: 0);}
int c_LE (char *a, char *b) {return (strcmp(a,b) <= 0? 1: 0);}
int c_GE (char *a, char *b) {return (strcmp(a,b) >= 0? 1: 0);}
int c_LIKE (char *a, char *b) {return like_c(a, b);}
int rc_LIKE (char *a, char *b) {return !like_c(a, b);}

int i_EQ (int a, int b) {return (a == b? 1 : 0);}
int i_NE (int a, int b) {return (a != b? 1 : 0);}
int i_LT (int a, int b) {return (a < b? 1 : 0);}
int i_GT (int a, int b) {return (a > b? 1 : 0);}
int i_LE (int a, int b) {return (a <= b? 1 : 0);}
int i_GE (int a, int b) {return (a >= b? 1 : 0);}



ccmp return_ccomp(cond_type x)
{
	switch(x)
	{
	case EQ:
		return c_EQ;
	case NE:
		return c_NE;
	case LT:
		return c_LT;
	case GT:
		return c_GT;
	case LE:
		return c_LE;
	case GE:
		return c_GE;
	case LIKE:
		return c_LIKE;
	case COND_NONE:
		return nullptr;
	}
	return nullptr;
}

ccmp return_rccomp(cond_type x)
{
	switch(x)
	{
	case EQ:
		return c_NE;
	case NE:
		return c_EQ;
	case LT:
		return c_GE;
	case GT:
		return c_LE;
	case LE:
		return c_GT;
	case GE:
		return c_LT;
	case LIKE:
		return rc_LIKE;
	case COND_NONE:
		return nullptr;
	}
	return nullptr;
}

icmp return_icomp(cond_type x)
{
	switch(x)
	{
	case EQ:
		return i_EQ;
	case NE:
		return i_NE;
	case LT:
		return i_LT;
	case GT:
		return i_GT;
	case LE:
		return i_LE;
	case GE:
		return i_GE;
	case LIKE:
		return i_EQ;
	case COND_NONE:
		return nullptr;
	}
	return nullptr;
}

icmp return_ricomp(cond_type x)
{
	switch(x)
	{
	case EQ:
		return i_NE;
	case NE:
		return i_EQ;
	case LT:
		return i_GE;
	case GT:
		return i_LE;
	case LE:
		return i_GT;
	case GE:
		return i_LT;
	case LIKE:
		return i_NE;
	case COND_NONE:
		return nullptr;
	}
	return nullptr;
}


int like_c (char *a, char *b)
{
	int i = 0, j = 0;
	while (a[i] && b[j])
	{
		if (a[i] != b[j])
		{
			if (b[j] != '%')
				return 0;
			i++;
			continue;
		}
		i++;
		j++;
	}
	//printf ("was here?\n");
	return 1;
}
