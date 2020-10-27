#ifndef COMMAND_H
#define COMMAND_H

#include "record.h"

enum cmd_type {
	CMD_NONE, QUIT, STOP, SELECT, INSERT, DELETE
};

enum cond_type {
	COND_NONE, EQ, NE, LE, GE, LT, GT, LIKE
};

enum op_type {
	OP_NONE, AND, OR
};

enum data_type {
	DATA_NONE, NAME, PHONE, GROUP
};

class command: public record {
	private:
		cmd_type  type    = CMD_NONE;
		cond_type c_name  = COND_NONE;
		cond_type c_phone = COND_NONE;
		cond_type c_group = COND_NONE;
		op_type   oper    = OP_NONE;
		data_type order[2] = {DATA_NONE, DATA_NONE};

	public:
		command() = default;
		~command() = default;

		int parse(const char *str, const char *space);

		void print(FILE *out = stdout) const;
		void print_table(FILE *out = stdout) const;
		static void print_table_top(FILE *out = stdout);
		static void print_table_bottom(FILE *out = stdout);

		int check_cond(const record *) const;
		int check_single_cond(const record *, data_type) const;

	private:
		static int read_cond(const char *, cond_type &);
		int read_arg(const char *, const char *, data_type &);

		static void print_cond(FILE *, cond_type);
		void print_arg(FILE *, data_type) const;
		static void print_table_cond(FILE *out, cond_type);

		static int check_like(const char *, const char *);

	friend class database;
	friend class tree;
};

#endif // COMMAND_H
