#include "database.h"
#include "list_node.h"
#include "command.h"
#include "errors.h"

#define PRINT_INFO 0

int database::insert(list_node *x){
	int ret;

	ret = list_base.insert(x);
	if(ret){
		delete x;
		return ret;
	}

	ret = phone_search.insert(x);
	if(ret){
		list_base.remove(x);
		return ret;
	}

	ret = name_search.insert(x);
	if(ret){
		phone_search.remove(x);
		list_base.remove(x);
		return ret;
	}

	return 0;
}

int database::remove(list_node *x){
	if(phone_search.remove(x)){
		return ERR_NOT_FOUND;
	}

	if(name_search.remove(x)){
		return ERR_NOT_FOUND;
	}

	list_base.remove(x);

	return 0;
}

void database::destroy(){
	list_base.destroy();
	phone_search.destroy();
	name_search.destroy();
}

int database::read(FILE *fp){
	destroy();

	int ret;
	list_node *next;

	while(true){
		next = new list_node;
		if(!next) return ERR_MEMORY;

		ret = next->read(fp);
		if(ret < 0){
			delete next;
			return ERR_READ;
		}
		if(ret > 0){
			delete next;
			break;
		}

		ret = insert(next);
		if(ret) return ret;
	}

	return 0;
}

int database::execute(command &x){
	list_node *curr = nullptr, *tmp;
	int ret;

	switch(x.type){
		case CMD_NONE: break;

		case STOP:
		case QUIT: return 1;

		case INSERT:
			curr = new list_node;
			if(!curr) return ERR_MEMORY;

			curr->init(x);

			ret = insert(curr);
			if(PRINT_INFO){
				if(ret){
					printf("Error: ");
					switch(ret){
						case ERR_OVERLAP: printf("doubling data\n"); break;
						case ERR_MEMORY: printf("not enough memory\n"); break;
						default: printf("insert unknown error\n");
					}
				}
				else printf("inserted\n");
			}
			break;

		case SELECT:
			ret = 0;

			switch(x.oper){
				case COND_NONE:
					if(x.c_phone == EQ){
						curr = phone_search.search(x, DATA_NONE, 1);
					}
					else if(x.c_name == EQ){
						curr = name_search.search(x, DATA_NONE, 1);
					}
					else{
						curr = list_base.search(x);
					}
					break;

				case AND:
					if(x.c_phone == EQ){
						curr = phone_search.search(x, (x.c_name == COND_NONE)? GROUP : NAME, 1);
					}
					else if(x.c_name == EQ){
						curr = name_search.search(x, (x.c_phone == COND_NONE)? GROUP : PHONE, 1);
					}
					else{
						curr = list_base.search(x);
					}
					break;

				case OR:
					if(x.c_name == EQ && x.c_phone == EQ){
						curr = name_search.search(x, PHONE, 0);

						while(curr){
							curr->print();
							curr = curr->next_search;
							ret++;
						}

						curr = phone_search.search(x, DATA_NONE, 1);
					}
					else{
						curr = list_base.search(x);
					}
					break;
			}

			while(curr){
				curr->print();
				curr = curr->next_search;
				ret++;
			}
			if(PRINT_INFO) printf("selected: %d\n\n", ret);
			break;

		case DELETE:
			ret = 0;

			switch(x.oper){
				case COND_NONE:
					if(x.c_phone == EQ){
						curr = phone_search.search(x, DATA_NONE, 1);
					}
					else if(x.c_name == EQ){
						curr = name_search.search(x, DATA_NONE, 1);
					}
					else{
						curr = list_base.search(x);
					}
					break;

				case AND:
					if(x.c_phone == EQ){
						curr = phone_search.search(x, (x.c_name == COND_NONE)? GROUP : NAME, 1);
					}
					else if(x.c_name == EQ){
						curr = name_search.search(x, (x.c_phone == COND_NONE)? GROUP : PHONE, 1);
					}
					else{
						curr = list_base.search(x);
					}
					break;

				case OR:
					if(x.c_name == EQ && x.c_phone == EQ){
						curr = name_search.search(x, DATA_NONE, 1);

						while(curr){
							tmp = curr->next_search;
							if(remove(curr)){
								printf("Error: failed to remove ");
								curr->print();
							}
							curr = tmp;
							ret++;
						}

						curr = phone_search.search(x, DATA_NONE, 1);
					}
					else{
						curr = list_base.search(x);
					}
					break;
			}

			while(curr){
				tmp = curr->next_search;
				if(remove(curr)){
					printf("Error: failed to remove ");
					curr->print();
				}
				curr = tmp;
				ret++;
			}
			if(PRINT_INFO) printf("deleted: %d\n\n", ret);
			break;
	}

	//if(!list_base.isCorrect()) printf("Error: incorrect base struct\n");
	/*else{
		printf("--- Base ---\n");
		list_base.print();
		printf("------------\n");
	}*/

	//if(!phone_search.isCorrect()) printf("Error: incorrect phone struct\n");
	/*else{
		printf("--- Phone ---\n");
		phone_search.print();
		printf("-------------\n");
	}*/

	//if(!name_search.isCorrect()) printf("Error: incorrect name struct\n");
	/*else{
		printf("--- Name ---\n");
		name_search.print();
		printf("------------\n");
	}*/

	return 0;
}

void database::task(){
	int ret;
	char space[256] = {};
	char buf[LEN];
	command cmd;

	space[' '] = 1;
	space['\t'] = 1;

	//command::print_table_top();

	while(fgets(buf, LEN, stdin)){
		ret = cmd.parse(buf, space);
		if(ret < 0){
			if(buf[0] != '\n'){
				for(int i = 0; buf[i]; i++){
					if(buf[i] == '\n'){
						buf[i] = 0;
						break;
					}
				}

				printf("Error: ");
				switch(ret){
					case ERR_PARSE_COMMAND:   printf("unknown command"); break;
					case ERR_PARSE_WORD:      printf("misspelled word"); break;
					case ERR_PARSE_SPACE:     printf("missing space"); break;
					case ERR_PARSE_ARGUMENT:  printf("unnown argument"); break;
					case ERR_PARSE_CONDITION: printf("misspelled condition"); break;
					case ERR_PARSE_BRACKET:   printf("missing bracket"); break;
					case ERR_PARSE_SEPARATOR: printf("missing separator"); break;
					case ERR_PARSE_NAME:      printf("not enough memory for name"); break;
					case ERR_PARSE_PHONE:     printf("can not read phone"); break;
					case ERR_PARSE_GROUP:     printf("can not read group"); break;
					default: printf("parse unknown error");
				}
				printf(" in \"%s\"\n", buf);
			}
		}
		else{
			//cmd.print_table();
			//cmd.print();
			ret = execute(cmd);
			if(ret) break;
		}
	}

	//command::print_table_bottom();
}
