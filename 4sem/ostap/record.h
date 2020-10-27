#ifndef RECORD_H
#define RECORD_H
#include "defenitions.h"

class record
{
private:
	std::unique_ptr <char[]> name;
	int phone = -1;
	int group = -1;
	friend class command;
	friend class list_node;
public:
	record() = default;
	~record() = default;
	char * get_name (){return name.get();}
	int get_phone () {return phone;}
	int get_group () {return group;}
	int put_name(char *n);
	int put_phone(char *n);
	int put_group(char *n);
	int init (char *n, int &p, int &g);
	int init_ptr (std::unique_ptr <char []> &n, int &p, int &g);
	void print_record(FILE *fp = stdout);
	ratio compare_name_(record *b);
	ratio compare_phone_(record *b);
	ratio compare_group_(record *b);
};

#endif // RECORD_H
