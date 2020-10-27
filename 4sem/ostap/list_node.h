#ifndef LIST_NODE_H
#define LIST_NODE_H
#include "record.h"

class list_node;

class list_node: public record {
private:
	list_node *next = nullptr;
	list_node *prev = nullptr;
	list_node *nnext = nullptr;
	unsigned int nlist = 0;
	friend class list;
	friend class database;
public:
	list_node() = default;
	~list_node() = default;
	int read (FILE *fp)
	{
		int p, g;
		char n[LEN];
		if (fscanf(fp,"%s%d%d", n, &p, &g) != 3)
		{
			if (feof(fp))
				return EOFile;
			return READING_ERR;
		}
		return init(n, p, g);
	}
	int hash_name (int m)
	{
		unsigned int s = 0;
		for (int i = 0; name.get()[i]; s+= (unsigned int)name.get()[i], i++);
		return s%m;
	}
	void put_nnext(list_node *x)
	{
		if (!x->nlist)
		{
			if (!nnext)
				nnext = x;
			else
			{
				x->nnext = nnext;
				nnext = x;
			}
			x->nlist = 1;
		}
		else
			return;
	}
#ifdef DEBUG
	void print_nlist(FILE *fp = stdout) // this function printing and deleting nnext conection
	{
		list_node *run = this, *t;
		int i = 1;
		while (run)
		{
			if (i < MAX_PRINT + 1)
			//if (run->nlist == 0)
			{
				fprintf(fp, "\t\t%d)", i);
				run->print_record(fp);
				fprintf(fp,"\n");
			}
			t = run->nnext;
			run->nnext = nullptr;
			run->nlist = 0;
			run = t;
			i++;
		}
		if (i > MAX_PRINT + 1)
			fprintf(fp,"\t\t...\n");
		fprintf(fp, "\t\tcount = %d\n", i-1);
	}
#else
	void print_nlist(FILE *fp = stdout) // this function printing and deleting nnext conection
	{
		list_node *run = this, *t;
		while (run)
		{
			run->print_record(fp);
			fprintf(fp,"\n");
			t = run->nnext;
			run->nnext = nullptr;
			run->nlist = 0;
			run = t;
		}
	}
#endif
	list_node * calibrate_nlist_p (icmp comp, int p)
	{
		list_node *first = this, *second, *head;
		while (first && !comp(first->phone, p))
		{
			head = first->nnext;
			first->nnext = nullptr;
			first->nlist = 0;
			first = head;
		}
		head = first;
		if (first)
		{
			second = first->nnext;
			while (second)
			{
				if (!comp(second->phone, p))
				{
					first->nnext = second->nnext;
					second->nnext = nullptr;
					second->nlist = 0;
					second = first->nnext;
				}
				else
				{
					first = second;
					second = second->nnext;
				}
			}
		}
		return head;
	}
	list_node * calibrate_nlist_g (icmp comp, int g)
	{
		list_node *first = this, *second, *head;
		//printf("tut? first->group = %d, g = %d\n", first->group, g);
		while (first && !comp(first->group, g))
		{
			//printf("piu pau\n");
			head = first->nnext;
			first->nnext = nullptr;
			first->nlist = 0;
			first = head;
		}
		head = first;
		if (first)
		{
			second = first->nnext;
			while (second)
			{
				if (!comp(second->group, g))
				{
					//printf("second->group = %d, g = %d\n", second->group, g);
					first->nnext = second->nnext;
					second->nnext = nullptr;
					second->nlist = 0;
					second = first->nnext;
				}
				else
				{
					//printf("pif paf second->group = %d, g = %d\n", second->group, g);
					first = second;
					second = second->nnext;
				}
			}
		}
		return head;
	}

	list_node * calibrate_nlist_n(ccmp comp, char *n)
	{
		list_node *first = this, *second, *head;
		while (first && !comp(first->get_name(), n))
		{
			head = first->nnext;
			first->nnext = nullptr;
			first->nlist = 0;
			first = head;
		}
		head = first;
		if (first)
		{
			second = first->nnext;
			while (second)
			{
				if (!comp(second->get_name(), n))
				{
					first->nnext = second->nnext;
					second->nnext = nullptr;
					second->nlist = 0;
					second = first->nnext;
				}
				else
				{
					first = second;
					second = second->nnext;
				}
			}
		}
		return head;
	}
	list_node * qluing_nlist(list_node *nhead)
	{
		/*
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		printf("this = ");
		print_record();
		printf("\nnhead = ");
		if (nhead)
			nhead->print_record();
		else
			printf("pust\n");
		*/
		if (nhead)
		{
			//printf("\nA TUTA BЫL?\n");
			list_node *run = this;
			while (run->nnext)
			{
				run = run->nnext;
			}
			run->nnext = nhead->nnext;
			nhead->nnext = this;
			return nhead;
		}
		//printf("BBBBBBBBBBBBBBBBBBBBBBB\n");
		return this;
	}

	void test_print_nlist(FILE *fp = stdout) // this function printing and deleting nnext conection
	{
		list_node *run = this, *t;
		int i = 1;
		while (run)
		{
			//if (i < MAX_PRINT + 1)
			{
				fprintf(fp, "\t%d)", i);
				run->print_record(fp);
				fprintf(fp,"\n");
			}
			t = run->nnext;
			run = t;
			i++;
		}
		if (i > MAX_PRINT + 1) fprintf(fp,"\t...\n");
		fprintf(fp, "\tcount = %d\n", i-1);
	}
	void change_nlist(int x) {nlist = x;}
	int get_nlist() {return nlist;}
	list_node *get_nnext() {return nnext;}
};


class point_list_node
{
private:
	list_node *key = nullptr;
public:
	//friend class RBTree_node <T>;
	list_node *get_key() {return key;}
	void print_record(FILE *fp = stdout) {key->print_record(fp);}
	int init (list_node *x, int m = 0) {key = x; (void) m; return WORK_DONE;}
	location check(){return LISTNODE;}
	void print_location() {printf("\nYou are in LISTNODE\n");}
	list_node *get_list(list_node *nhead = nullptr)
	{
		if (!key->get_nlist())
		{
			if (!nhead)
			{
				key->change_nlist(1);
				return key;
			}
			nhead->put_nnext(key);
			return nhead;
		}
		return nhead;
	}
	void change_node(point_list_node *x)
	{
		list_node *t;
		t = key;
		key = x->key;
		x->key = t;
	}
	void delete_key(list_node *x)
	{
		(void) x;
	}
};


#endif // LIST_NODE_H
