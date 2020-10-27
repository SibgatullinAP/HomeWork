#include "record.h"

int record::init (char *n, int &p, int &g)
{
	name = std::make_unique<char[]>(strlen(n) + 1);
	if(!name)
		return ERR_MEMORY;
	strcpy(name.get(), n);
	phone = p;
	group = g;
	return WORK_DONE;
}

int record::init_ptr(std::unique_ptr<char[]> &n, int &p, int &g)
{
	name = std::move(n);
	phone = p;
	group = g;
	return WORK_DONE;
}

void record::print_record(FILE *fp)
{
	fprintf(fp, "%-20s %15d %5d", name.get(), phone, group);
}


int record::put_name(char *n)
{
	name = std::make_unique<char[]>(strlen(n) + 1);
	if(!name)
		return ERR_MEMORY;
	strcpy(name.get(), n);
	return 1;
}
int record::put_phone(char *n)
{
	if (sscanf(n,"%d", &phone) != 1)
		return 0;
	return 1;
}
int record::put_group(char *n)
{
	if (sscanf(n,"%d", &group) != 1)
		return 0;
	return 1;
}

ratio record::compare_name_(record *b)
{
	int res = strcmp(name.get(), b->name.get());
	if (res < 0)
		return LESS;
	if (res > 0)
		return MORE;
	return EQUAL;
}

ratio record::compare_phone_(record *b)
{
	if (phone < b->phone)
		return LESS;
	if (phone > b->phone)
		return MORE;
	return EQUAL;
}

ratio record::compare_group_(record *b)
{
	if (group< b->group)
		return LESS;
	if (group > b->group)
		return MORE;
	return EQUAL;
}
