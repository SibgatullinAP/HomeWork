#include <string.h>
#include "command.h"
#include "errors.h"

#define WIDTH 10

int command::parse(const char *str, const char *space){
	int i = 0;
	int ret;

	name = 0;
	phone = -1;
	group = -1;

	type = CMD_NONE;
	c_name = COND_NONE;
	c_phone = COND_NONE;
	c_group = COND_NONE;
	oper = OP_NONE;
	order[0] = order[1] = DATA_NONE;

	while(space[(unsigned char)str[i]]) i++;

	if(!strncmp(str + i, "quit", 4)){
		type = QUIT;
		i += 4;
	}
	else if(!strncmp(str + i, "stop", 4)){
		type = STOP;
		i += 4;
	}
	else if(!strncmp(str + i, "select", 6) || !(strncmp(str + i, "delete", 6))){
		if(str[i] == 's'){
			type = SELECT;
			i += 6;

			if(!space[(unsigned char)str[i]]) return ERR_PARSE_SPACE;
			while(space[(unsigned char)str[i]]) i++;

			if(str[i] != '*') return ERR_PARSE_WORD;
			i++;
		}
		else{
			type = DELETE;
			i += 6;
		}

		if(!space[(unsigned char)str[i]]){
			return (str[i] == ';')? 0 : ERR_PARSE_SPACE;
		}
		while(space[(unsigned char)str[i]]) i++;

		if(str[i] == ';') return 0;
		if(strncmp(str + i, "where", 5)) return ERR_PARSE_WORD;
		i += 5;

		if(!space[(unsigned char)str[i]]) return ERR_PARSE_SPACE;
		while(space[(unsigned char)str[i]]) i++;

		ret = read_arg(str + i, space, order[0]);
		if(ret <= 0) return ret ? ret : ERR_PARSE_ARGUMENT;
		i += ret;

		if(!space[(unsigned char)str[i]]){
			return (str[i] == ';')? 0 : ERR_PARSE_SPACE;
		}
		while(space[(unsigned char)str[i]]) i++;

		if(str[i] == ';') return 0;

		if(!strncmp(str + i, "and", 3)){
			oper = AND;
			i += 3;
		}
		else if(!strncmp(str + i, "or", 2)){
			oper = OR;
			i += 2;
		}
		else return ERR_PARSE_WORD;

		if(!space[(unsigned char)str[i]]) return ERR_PARSE_SPACE;
		while(space[(unsigned char)str[i]]) i++;

		ret = read_arg(str + i, space, order[1]);
		if(ret <= 0) return ret ? ret : ERR_PARSE_ARGUMENT;
		i += ret;
	}
	else if(!strncmp(str + i, "insert", 6)){
		type = INSERT;
		i += 6;

		while(space[(unsigned char)str[i]]) i++;

		if(str[i] != '(') return ERR_PARSE_BRACKET;
		i++;

		while(space[(unsigned char)str[i]]) i++;

		int j = 0;
		while(str[i + j] && str[i + j] != ',' && !space[(unsigned char)str[i + j]]) j++;

		name = std::make_unique<char[]>(j + 1);
		if(!name) return ERR_PARSE_NAME;
		strncpy(name.get(), str + i, j);
		name[j] = 0;
		i += j;

		while(space[(unsigned char)str[i]]) i++;

		if(str[i] != ',') return ERR_PARSE_SEPARATOR;
		i++;

		while(space[(unsigned char)str[i]]) i++;

		if(sscanf(str + i, "%d", &phone) != 1) return ERR_PARSE_PHONE;
		i++;
		while(str[i] >= '0' && str[i] <= '9') i++;

		while(space[(unsigned char)str[i]]) i++;

		if(str[i] != ',') return ERR_PARSE_SEPARATOR;
		i++;

		while(space[(unsigned char)str[i]]) i++;

		if(sscanf(str + i, "%d", &group) != 1) return ERR_PARSE_GROUP;
		i++;
		while(str[i] >= '0' && str[i] <= '9') i++;

		while(space[(unsigned char)str[i]]) i++;

		if(str[i] != ')') return ERR_PARSE_BRACKET;
		i++;
	}
	else return ERR_PARSE_COMMAND;
	
	while(space[(unsigned char)str[i]]) i++;

	return (str[i] == ';')? 0 : ERR_PARSE_SEPARATOR;
}

void command::print(FILE *out) const {
	switch(type){
		case CMD_NONE: break;
		case QUIT: fprintf(out, "quit;\n"); break;
		case STOP: fprintf(out, "stop;\n"); break;

		case INSERT:
			fprintf(out, "insert (%s, %d, %d);\n", name.get(), phone, group);
			break;

		case SELECT:
		case DELETE:
			if(type == SELECT) fprintf(out, "select *");
			else fprintf(out, "delete");

			if(order[0] != DATA_NONE) fprintf(out, " where ");

			print_arg(out, order[0]);

			switch(oper){
				case OP_NONE:
					fprintf(out, ";\n");
					return;
				case AND: fprintf(out, " and "); break;
				case OR:  fprintf(out, " or ");  break;
			}

			print_arg(out, order[1]);
			fprintf(out, ";\n");
	}
}

void command::print_table(FILE *out) const {
	fprintf(out, "│ %*s | %*d | %*d | ", WIDTH, name.get(), WIDTH, phone, WIDTH, group);

	switch(type){
		case CMD_NONE: fprintf(out, "%*s | ", WIDTH, "CMD_NONE"); break;
		case QUIT:     fprintf(out, "%*s | ", WIDTH, "QUIT");     break;
		case STOP:     fprintf(out, "%*s | ", WIDTH, "STOP");     break;
		case SELECT:   fprintf(out, "%*s | ", WIDTH, "SELECT");   break;
		case INSERT:   fprintf(out, "%*s | ", WIDTH, "INSERT");   break;
		case DELETE:   fprintf(out, "%*s | ", WIDTH, "DELETE");   break;
	}

	print_table_cond(out, c_name);
	fprintf(out, " | ");
	print_table_cond(out, c_phone);
	fprintf(out, " | ");
	print_table_cond(out, c_group);
	fprintf(out, " | ");

	switch(oper){
		case OP_NONE: fprintf(out, "%*s │\n", WIDTH, "OP_NONE"); break;
		case AND: fprintf(out, "%*s │\n", WIDTH, "AND"); break;
		case OR:  fprintf(out, "%*s │\n", WIDTH, "OR");  break;
	}

	//fprintf(out, "├");
	//for(int i = 1; i < 8 * (WIDTH + 3); i++) fprintf(out, "─");
	//fprintf(out, "┤\n");
}

void command::print_table_top(FILE *out){
	fprintf(out, "┌");
	for(int i = 1; i < 8 * (WIDTH + 3); i++) fprintf(out, "─");
	fprintf(out, "┐\n");

	fprintf(out, "│ %*s | %*s | %*s | %*s | ", WIDTH, "name", WIDTH, "phone", WIDTH, "group", WIDTH, "type");
	fprintf(out, "%*s | %*s | %*s | %*s │\n", WIDTH, "c_name", WIDTH, "c_phone", WIDTH, "c_group", WIDTH, "oper");

	fprintf(out, "├");
	for(int i = 1; i < 8 * (WIDTH + 3); i++) fprintf(out, "─");
	fprintf(out, "┤\n");
}

void command::print_table_bottom(FILE *out){
	fprintf(out, "└");
	for(int i = 1; i < 8 * (WIDTH + 3); i++) fprintf(out, "─");
	fprintf(out, "┘\n");
}

void command::print_table_cond(FILE *out, cond_type c){
	switch(c){
		case COND_NONE: fprintf(out, "%*s", WIDTH, "COND_NONE"); break;
		case LIKE: fprintf(out, "%*s", WIDTH, "LIKE"); break;
		case EQ: fprintf(out, "%*s", WIDTH, "EQ"); break;
		case NE: fprintf(out, "%*s", WIDTH, "NE"); break;
		case LE: fprintf(out, "%*s", WIDTH, "LE"); break;
		case GE: fprintf(out, "%*s", WIDTH, "GE"); break;
		case LT: fprintf(out, "%*s", WIDTH, "LT"); break;
		case GT: fprintf(out, "%*s", WIDTH, "GT"); break;
	}
}

int command::read_cond(const char *str, cond_type &c){
	int i = 0;

	if(str[0] == '='){
		c = EQ;
		i++;
	}
	else if(str[0] == '<'){
		c = LT;
		i++;

		if(str[1] == '='){
			c = LE;
			i++;
		}
		else if(str[1] == '>'){
			c = NE;
			i++;
		}
	}
	else if(str[0] == '>'){
		c = GT;
		i++;

		if(str[1] == '='){
			c = GE;
			i++;
		}
	}

	return i;
}

int command::read_arg(const char *str, const char *space, data_type &data){
	int i = 0;
	int ret;

	if(!strncmp(str + i, "name", 4)){
		i += 4;
		data = NAME;

		if(!space[(unsigned char)str[i]]) return ERR_PARSE_SPACE;
		while(space[(unsigned char)str[i]]) i++;

		if(!strncmp(str + i, "like", 4)){
			c_name = LIKE;
			i += 4;
		}
		else{
			ret = read_cond(str + i, c_name);
			if(!ret) return ERR_PARSE_CONDITION;
			i += ret;
		}

		if(!space[(unsigned char)str[i]]) return ERR_PARSE_SPACE;
		while(space[(unsigned char)str[i]]) i++;

		int j = 0;
		while(str[i + j] && str[i + j] != ';' && !space[(unsigned char)str[i + j]]) j++;

		name = std::make_unique<char[]>(j + 1);
		if(!name) return ERR_PARSE_NAME;
		strncpy(name.get(), str + i, j);
		name[j] = 0;
		i += j;
	}
	else if(!strncmp(str + i, "phone", 5)){
		i += 5;
		data = PHONE;

		if(!space[(unsigned char)str[i]]) return ERR_PARSE_SPACE;
		while(space[(unsigned char)str[i]]) i++;

		ret = read_cond(str + i, c_phone);
		if(!ret) return ERR_PARSE_CONDITION;
		i += ret;

		if(!space[(unsigned char)str[i]]) return ERR_PARSE_SPACE;
		while(space[(unsigned char)str[i]]) i++;

		if(sscanf(str + i, "%d", &phone) != 1) return ERR_PARSE_PHONE;
		i++; // signed
		while(str[i] >= '0' && str[i] <= '9') i++;
	}
	else if(!strncmp(str + i, "group", 5)){
		i += 5;
		data = GROUP;

		if(!space[(unsigned char)str[i]]) return ERR_PARSE_SPACE;
		while(space[(unsigned char)str[i]]) i++;

		ret = read_cond(str + i, c_group);
		if(!ret) return ERR_PARSE_CONDITION;
		i += ret;

		if(!space[(unsigned char)str[i]]) return ERR_PARSE_SPACE;
		while(space[(unsigned char)str[i]]) i++;

		if(sscanf(str + i, "%d", &group) != 1) return ERR_PARSE_GROUP;
		i++; // signed
		while(str[i] >= '0' && str[i] <= '9') i++;
	}

	return i;
}

void command::print_cond(FILE *out, cond_type c){
	switch(c){
		case COND_NONE:
		case LIKE: fprintf(out, "ERROR"); break;
		case EQ: fprintf(out, "="); break;
		case NE: fprintf(out, "<>"); break;
		case LE: fprintf(out, "<="); break;
		case GE: fprintf(out, ">="); break;
		case LT: fprintf(out, "<"); break;
		case GT: fprintf(out, ">"); break;
	}
}

void command::print_arg(FILE *out, data_type data) const {
	switch(data){
		case DATA_NONE:
			break;

		case NAME:
			fprintf(out, "name ");

			if(c_name == LIKE) fprintf(out, "like");
			else print_cond(out, c_name);

			fprintf(out, " %s", name.get());
			break;

		case PHONE:
			fprintf(out, "phone ");
			print_cond(out, c_phone);
			fprintf(out, " %d", phone);
			break;

		case GROUP:
			fprintf(out, "group ");
			print_cond(out, c_group);
			fprintf(out, " %d", group);
			break;
	}
}

int command::check_cond(const record *x) const {
	int ret, ind;

	ind = (order[0] == NAME) ? 1 : 0;

	switch(oper){
		case OP_NONE:
			return check_single_cond(x, order[0]);

		case AND:
			ret = check_single_cond(x, order[ind]);
			return (ret <= 0)? ret : check_single_cond(x, order[1 - ind]);

		case OR:
			ret = check_single_cond(x, order[ind]);
			return ret ? ret : check_single_cond(x, order[1 - ind]);
	}

	return -1;
}

int command::check_single_cond(const record *x, data_type data) const {
	if(!x) return ERR_NULL_ARG;

	switch(data){
		case DATA_NONE: return 1;
		case NAME:
			switch(c_name){
				case COND_NONE: break;
				case EQ: return !strcmp(x->name.get(), name.get());
				case NE: return strcmp(x->name.get(), name.get());
				case LE: return strcmp(x->name.get(), name.get()) <= 0;
				case GE: return strcmp(x->name.get(), name.get()) >= 0;
				case LT: return strcmp(x->name.get(), name.get()) < 0;
				case GT: return strcmp(x->name.get(), name.get()) > 0;
				case LIKE: return check_like(x->name.get(), name.get());
			}
			break;

		case PHONE:
			switch(c_phone){
				case COND_NONE:
				case LIKE: break;
				case EQ: return x->phone == phone;
				case NE: return x->phone != phone;
				case LE: return x->phone <= phone;
				case GE: return x->phone >= phone;
				case LT: return x->phone < phone;
				case GT: return x->phone > phone;
			}
			break;

		case GROUP:
			switch(c_group){
				case COND_NONE:
				case LIKE: break;
				case EQ: return x->group == group;
				case NE: return x->group != group;
				case LE: return x->group <= group;
				case GE: return x->group >= group;
				case LT: return x->group < group;
				case GT: return x->group > group;
			}
	}

	return 0;
}

int command::check_like(const char *str, const char *pattern){
	char buf[2][LEN + 1];
	int i, j = 0, id;

	for(i = 0; pattern[i]; i++){
		if(pattern[i] == '%') break;
	}
	if(!pattern[i]){
		for(i = 0; pattern[i] && str[i]; i++){
			if(pattern[i] != '_' && pattern[i] != str[i]) break;
		}
		return !pattern[i] && !str[i];
	}

	if(!pattern[0]) return !str[0];

	buf[0][0] = 1;
	for(i = 0; pattern[i] == '%'; i++) buf[0][i + 1] = 1;
	for(; pattern[i]; i++) buf[0][i + 1] = 0;

	id = 1;
	for(i = 0; str[i]; i++){
		buf[id][0] = 0;
		for(j = 0; pattern[j]; j++){
			if(pattern[j] == '%'){
				buf[id][j + 1] = buf[1 - id][j + 1] || buf[id][j];
			}
			else if(pattern[j] == '_' || pattern[j] == str[i]){
				buf[id][j + 1] = buf[1 - id][j];
			}
			else buf[id][j + 1] = 0;
		}

		id = 1 - id;
	}

	return buf[1 - id][j];
}
