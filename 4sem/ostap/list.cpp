#include "list.h"

void list::delete_list()
{
	list_node *run = head;
	while(head)
	{
		head = run->next;
		delete run;
		run = head;
	}
	head = nullptr;
	curr = nullptr;
}

#ifdef DEBUG
int list::print(FILE *fout)
{
	list_node *run = head;
	int i = 0;
	while (run)
	{
		if (i < MAX_PRINT)
		{
			fprintf(fout, "\t\t%d)", i + 1);
			run->print_record(fout);
			fprintf(fout, "\n");
		}
		i++;
		run = run->next;
	}
	if (i > MAX_PRINT + 1)
		fprintf(fout, "\t\t...\n");
	fprintf(fout, "\t\tcount = %d\n", i);
	return i;
}
#else
int list::print(FILE *fout)
{
	list_node *run = head;
	int i = 0;
	while (run)
	{
		run->print_record(fout);
		fprintf(fout, "\n");
		i++;
		run = run->next;
	}
	return i;
}
#endif

int list::insert(char *n, int &p, int &g)
{
	int res;
	list_node *nuxt;

	if (!head)
	{
		nuxt = new list_node();
		res = nuxt->init(n, p, g);
		if (res < 0)
		{
			delete nuxt;
			return res;
		}
		curr = head = nuxt;
		return 1;
	}
	list_node *run = curr;		//раскоментить
	res = 1;					//раскоментить
	//list_node *run = nullptr;
	//res = search(n, p, g, &run); //функция ищет есть ли элемент с такими данными в списке и вернет 0 если такой элемент есть, и 1, если его нет
	if (res)
	{
		nuxt = new list_node();
		res = nuxt->init(n, p, g);
		if (res < 0)
		{
			delete nuxt;
			return res;
		}
		if (!run)
		{
			//printf("tut\n");
			nuxt->next = head;
			head->prev = nuxt;
			curr = head = nuxt;
			return 1;
		}
		if (!run->next)
		{
			run->next = nuxt;
			nuxt->prev = run;
			curr = nuxt;
			return 1;
		}
		run->next->prev = nuxt;
		nuxt->next = run->next;
		nuxt->prev = run;
		run->next = nuxt;
		return 1;
	}
	return 0;
}


//вернет 0, если такой элемент уже есть в списке, и вернет 1, если такого нет, а также положит в ans ссылку на элемент, после которого надо вставить наш элемент, если это nullptr
//то надо вставить в head
int list::search(char *n, int &p, int &g, list_node **ans)
{
	list_node *run = head;
	while(run->next)
	{
		if (run->get_phone() < p)
		{
			run = run->next;
			continue;
		}
		if (run->get_phone() == p)
		{
			if ((run->get_group() == g) && (!strcmp(run->get_name(), n)))
				return 0;
			run = run->next;
			continue;
		}
		*ans = run->prev;
		return 1;
	}
	if (run->get_phone() < p)
	{
		*ans = run;
		return 1;
	}
	if ((run->get_phone() == p) && (run->get_group() == g) && (!strcmp(run->get_name(), n)))
		return 0;
	*ans = run->prev;
	return 1;
}


list_node * list::find_name_a(ccmp comp, char *n)
{
	list_node *run = curr;

	while (run)
	{
		curr = run->next;
		if (comp(run->get_name(), n))
			return run;
		run = curr;
	}
	return 0;
}


list_node * list::find_phone_a(icmp comp, int p)
{
	list_node *run = curr;

	while (run)
	{
		curr = run->next;
		if (comp(run->get_phone(), p))
			return run;
		run = curr;
	}
	return 0;
}


list_node * list::find_group_a(icmp comp, int g)
{
	list_node *run = curr;

	while (run)
	{
		curr = run->next;
		if (comp(run->get_group(), g))
			return run;
		run = curr;
	}
	return 0;
}


list_node * list::find_norp_a(ccmp ccomp, char *n, icmp icomp, int p)
{
	list_node *run = curr;
	while (run)
	{
		curr = run->next;
		if (icomp(run->get_phone(), p))
			return run;
		if (ccomp(run->get_name(), n))
			return run;
		run = curr;
	}
	return 0;
}


list_node * list::find_norg_a(ccmp ccomp, char *n, icmp icomp, int g)
{
	list_node *run = curr;
	while (run)
	{
		curr = run->next;
		if (icomp(run->get_group(), g))
			return run;
		if (ccomp(run->get_name(), n))
			return run;
		run = curr;
	}
	return 0;
}


list_node * list::find_porg_a(icmp icomp1, int p, icmp icomp2, int g)
{
	list_node *run = curr;
	while (run)
	{
		curr = run->next;
		if (icomp1(run->get_phone(), p))
			return run;
		if (icomp2(run->get_group(), g))
			return run;
		run = curr;
	}
	return 0;
}


void list::delete_node(list_node *x)
{
	if (x->prev)
		x->prev->next = x->next;
	else
		head = x->next;
	if (x->next)
		x->next->prev = x->prev;
	if (curr == x)
	{
		if (x->next)
			curr = x->next;
		else
			curr = x->prev;
	}
	delete x;
}

void list::put_node(list_node *x)		//функция считает, что x - "чистый узел", то есть next = prev = nullptr
{
	if (!head)
		head = x;
	else
	{
		head->prev = x;
		x->next = head;
		head = x;
	}
}


list_node * list::search_ne(list_node *x, ratio (record :: *comp)(record *), list_node *nhead)
{
	list_node *run = head;
	int res;
	while (run)
	{
		res = (x->*comp)(run);
		if (res != EQUAL)
		{
			if (nhead)
				nhead->put_nnext(run);
			else
			{
				if (!run->get_nlist())
				{
					nhead = run;
					nhead->change_nlist(1);
				}
			}
		}
		run = run->next;
	}
	return nhead;
}

list_node * list::search_like(list_node *x, int (*comp)(char *, char *), list_node *nhead)
{
	list_node *run = head;
	int res;
	//printf("\n\nBBBBBBBBBBBBBBBBBBBABDFASBDNABBDNBNAM\n\n");
	while (run)
	{
		res = comp(run->get_name(), x->get_name());
		if (res)
		{
			if (nhead)
				nhead->put_nnext(run);
			else
			{
				if (!run->get_nlist())
				{
					nhead = run;
					nhead->change_nlist(1);
				}
			}
		}
		run = run->next;
	}
	return nhead;
}

