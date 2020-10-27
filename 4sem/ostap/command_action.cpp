#include "command.h"

int command::make_command(megabase &A, list_node *puf)
{
	list_node *nhead = nullptr;
	switch(type)
	{
	case QUIT:
		return EXIT;
	case STOP:
		return EXIT;
	case INSERT:
		A.insert(name, phone, group);
		break;
	case SELECT:
		if (!c_name && !c_phone && !c_group)
		{
			A.Container.print();
			return WORK_DONE;
		}
		nhead = creat_list(A, puf);
		if (nhead)
			nhead->print_nlist();
#ifdef DEBUG
		else
			printf("\t\tcount = 0\n");
		//printf("\n");
#endif
		return WORK_DONE;
	case DELETE:
		if (!c_name && !c_phone && !c_group)
		{
			A.delete_all();
			printf("\n");
			return WORK_DONE;
		}
		nhead = creat_list(A, puf);
		//printf("test printf\n");nhead->test_print_nlist();
		if (nhead)
		{
			list_node *run = nhead, *nrun;

			//int i = 1; FILE *ftest; ftest = fopen("tree.txt", "w");
			while (run)
			{
				nrun = run->get_nnext();
				//if (i == 13764) A.print_Tree_phone(ftest);
				//printf("%d)", i++); run->print_record(); printf("\n");

				A.delete_node(run);
				run = nrun;
			}
			//fclose(ftest);

		}
#ifdef DEBUG
		printf("\n");
#endif
		return WORK_DONE;
	case CMD_NONE:
		printf("Something goes wrong\n");
	}
	return 0;
}


list_node * command:: search_phone(megabase &A, list_node *puf, list_node *nhead)
{
	switch (c_phone)
	{
	case EQ:
		nhead = A.Tree_phone.search_eq(puf, compare_phone);
		break;
	case NE:
		nhead = A.Container.search_ne(puf, &record::compare_phone_);
		break;
	case LT:
		nhead = A.Tree_phone.search_lt(puf, compare_phone);
		break;
	case GT:
		nhead = A.Tree_phone.search_gt(puf, compare_phone);
		break;
	case LE:
		nhead = A.Tree_phone.search_le(puf, compare_phone);
		break;
	case GE:
		nhead = A.Tree_phone.search_ge(puf, compare_phone);
		break;
	case LIKE:
		printf("\nLike? in phone\n\n");
		break;
	case COND_NONE:
		printf("\nSomething wrong: search_phone\n\n");
	}
	return nhead;
}

list_node * command:: search_name(megabase &A, list_node *puf, list_node *nhead)
{
	switch (c_name)
	{
	case EQ:
		nhead = A.Hash_RBT->search_eq(puf, compare_name);
		break;
	case NE:
		nhead = A.Container.search_ne(puf, &record::compare_name_);
		break;
	case LT:
		nhead = A.Hash_RBT->search_lt(puf, compare_name);
		break;
	case GT:
		nhead = A.Hash_RBT->search_gt(puf, compare_name);
		break;
	case LE:
		nhead = A.Hash_RBT->search_le(puf, compare_name);
		break;
	case GE:
		nhead = A.Hash_RBT->search_ge(puf, compare_name);
		break;
	case LIKE:
		nhead = A.Container.search_like(puf, like_c);
		break;
	case COND_NONE:
		printf("\nSomething wrong: search_name\n\n");
	}
	return nhead;

}


list_node * command:: search_group(megabase &A, list_node *puf, list_node *nhead)
{
	switch (c_group)
	{
	case EQ:
		nhead = A.Tree_group->search_eq(puf, compare_group);
		break;
	case NE:
		nhead = A.Container.search_ne(puf, &record::compare_group_);
		break;
	case LT:
		nhead = A.Tree_group->search_lt(puf, compare_group);
		break;
	case GT:
		nhead = A.Tree_group->search_gt(puf, compare_group);
		break;
	case LE:
		nhead = A.Tree_group->search_le(puf, compare_group);
		break;
	case GE:
		nhead = A.Tree_group->search_ge(puf, compare_group);
		break;
	case LIKE:
		printf("\nLike? in group\n\n");
		break;
	case COND_NONE:
		printf("\nSomething wrong: search_phone\n\n");
	}
	return nhead;
}


list_node * command:: search_and(megabase &A, list_node *puf, list_node *nhead)
{
	if (!c_name)
	{
		nhead = search_phone(A, puf);
		if (nhead)
		{
			icmp comp = return_icomp(c_group);
			nhead = nhead->calibrate_nlist_g(comp, puf->get_group());
		}
		return nhead;
	}
	if (!c_phone)
	{
		nhead = search_name(A, puf);
		if (nhead)
		{
			icmp comp = return_icomp(c_group);
			nhead = nhead->calibrate_nlist_g(comp, puf->get_group());
		}
		return nhead;
	}
	if (!c_group)
	{
		nhead = search_phone(A, puf);
		if (nhead)
		{
			ccmp comp = return_ccomp(c_name);
			nhead = nhead->calibrate_nlist_n(comp, puf->get_name());
		}
		return nhead;
	}
	return nhead;
}


list_node * command:: search_or(megabase &A, list_node *puf, list_node *nhead)
{
	list_node *nhead_n, *nhead_p, *nhead_g;
	if (!c_name)
	{
		nhead_p = search_phone(A, puf);
		//printf("\n\n:{\n\n");
		//if (nhead_p){printf("\nnhead_p="); nhead_p->test_print_nlist();}
		nhead_g = search_group(A, puf);
		//if (nhead_g) {printf("\nnhead_g=");nhead_g->test_print_nlist();}
		//if (nhead_p) {printf("nhead_p="); nhead_p->test_print_nlist();}
		if (nhead_p)
		{
			//if (nhead_p) nhead_p->test_print_nlist();
			//if (!nhead_g) printf("\n\nPUST???\n");
			nhead_g = nhead_p->qluing_nlist(nhead_g);
			//{printf("nhead_g=");nhead_g->test_print_nlist();}
		}
		if (nhead_g)
			return nhead_g->qluing_nlist(nhead);
		return nhead; //=nullptr;
	}
	if (!c_phone)
	{
		nhead_n = search_name(A, puf);
		nhead_g = search_group(A, puf);
		if (nhead_n)
			nhead_g = nhead_n->qluing_nlist(nhead_g);
		if (nhead_g)
			return nhead_g->qluing_nlist(nhead);
		return nhead; //=nullptr;
	}
	if (!c_group)
	{
		//printf("BUDU TUTA PIU PAU\n");
		nhead_p = search_phone(A, puf);
		nhead_n = search_name(A, puf);
		if (nhead_p)
		{
			//printf("piu pau\n");
			nhead_n = nhead_p->qluing_nlist(nhead_n);
		}
		if (nhead_n)
			return nhead_n->qluing_nlist(nhead);
		return nhead;
	}
	return nhead;

}


list_node * command::creat_list(megabase &A, list_node *puf)
{
	list_node *nhead = nullptr;
	puf->init_ptr(name, phone, group);
	if (oper == OP_NONE)
	{
		if (c_name)
		{
			nhead = search_name(A, puf);
			return nhead;
		}
		if (c_phone)
		{
			nhead = search_phone(A, puf);
			return nhead;
		}
		if (c_group)
		{
			nhead = search_group(A, puf);
			return nhead;
		}
	}
	else
	{
		if (oper == AND)
			nhead = search_and(A, puf);
		else	//oper == OR
			nhead = search_or(A, puf);
	}
	return nhead;
}
