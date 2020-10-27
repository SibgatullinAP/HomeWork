#ifndef COMMAND_H
#define COMMAND_H
#include "record.h"
#include "megabase.h"
#include "defenitions.h"
#include "solve.h"

class megabase;

class command: public record
{
private:
	cor_type flag = UNDEF;
	cmd_type type = CMD_NONE;
	int s_ord = 0;
	cond_type c_name = COND_NONE;
	cond_type c_phone = COND_NONE;
	cond_type c_group = COND_NONE;
	int c_ord = 0;
	op_type oper = OP_NONE;
	order_by c_order = NONE_ORDER;

	const char * select_arguments ();
	const char * print_flag();
	const char * print_type();
	const char * print_cond(cond_type &run);
	const char * print_oper();
	const char * print_argument_order();
	int make_cond (cond_type &run, const char *let, int *tab);
	int parse_where (const char *let, int *tab, char *buf2);
	int find_order (const char *let, int *tab);
	void obnulis ();
public:
	command () = default;
	~command() = default;
	int parse (const char *string, int *tab, char *buf2);
	int print(FILE *fp = stdout);
	int print_table(int i, FILE *fp = stdout); //есть ли?
	int make_command (megabase &A, list_node *puf);
	list_node * creat_list(megabase &A, list_node *puf);
	list_node * search_phone(megabase &A, list_node *puf, list_node *nhead = nullptr);
	list_node * search_name(megabase &A, list_node *puf, list_node *nhead = nullptr);
	list_node * search_group(megabase &A, list_node *puf, list_node *nhead = nullptr);
	list_node * search_and(megabase &A, list_node *puf, list_node *nhead = nullptr);
	list_node * search_or(megabase &A, list_node *puf, list_node *nhead = nullptr);
};





#endif // COMMAND_H
