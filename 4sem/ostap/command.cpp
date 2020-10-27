#include "command.h"


																								//в случае успешной команды возвращает 1, иначе возвразает 0
																								//бежим по сценариям, как только поняли, что команда плохая - вернули ноль
																								//как только поняли, что команда хорошая - вернули 1
																								//если добежали до конца - вернули 0


int command::parse(const char *string, int *tab, char *buf2)
{
	obnulis();
	int i = 0, j = 0;
	const char *let,  *f = string;
	flag = NONE_COR;



	while(tab[(int) f[i]])
		i++;
	if (!f[i])
		return 0;
	let = f + i;

	if ((let[0] == 's') && (let[1] == 'e') && (let[2] == 'l') && (let[3] == 'e') && (let[4] == 'c') && (let[5] == 't') && (tab[(int) let[6]])) //cценарий select
	{
		type = SELECT; f = let + 6; i = 0;
		while(f[i] && tab[(int) f[i]])
			i++;
		if (!f[i])
			return 0;
		let = f + i;
																															//сценарий аргументов selecet
																															//тут можно реализовать возможность иметь 1,2 аргументов вывода select
																															//также, как и в AND и OR


		if (let[0] == '*')
		{
			s_ord = 63; f = let + 1; i = 0;
			while(f[i] && tab[(int) f[i]])
				i++;
			if (!f[i])
				return 0;
			if (f[i] == ';')
			{
				flag = COR;
				return 1;
			}
			let = f + i;
			return parse_where(let, tab, buf2);
		}
		else
			return 0;
	}

	if ((let[0] == 's') && (let[1] == 't') && (let[2] == 'o') && (let[3] == 'p'))										//сценарий stop
	{
		type = STOP; f = let + 4; i = 0;
		while(f[i] && tab[(int) f[i]])
			i++;
		if (!f[i])
			return 0;
		if (f[i] == ';')
		{
			flag = COR;
			return 1;
		}
		else
			return 0;
	}
	if ((let[0] == 'd') && (let[1] == 'e') && (let[2] == 'l') && (let[3] == 'e') && (let[4] == 't') && (let[5] == 'e')) //сценарий delete
	{
		type = DELETE; f = let + 6; i = 0;

		while(f[i] && tab[(int) f[i]])
			i++;
		if (!f[i])
			return 0;
		if (f[i] == ';')
		{
			flag = COR;
			return 1;
		}
		let = f + i;


		return parse_where(let, tab, buf2);
	}

	if ((let[0] == 'q') && (let[1] == 'u') && (let[2] == 'i') && (let[3] == 't'))										//сценарий quit
	{
		type = QUIT; f = let + 4; i = 0;

		while(f[i] && tab[(int) f[i]])
			i++;
		if (!f[i])
			return 0;
		if (f[i] == ';')
		{
			flag = COR;
			return 1;
		}
	}

	if ((let[0] == 'i') && (let[1] == 'n') && (let[2] == 's') && (let[3] == 'e') && (let[4] == 'r') && (let[5] == 't') && (tab[(int) let[6]])) //сценарий insert
	{
		type = INSERT; f = let + 6; i = 0;
		while(f[i] && tab[(int) f[i]])
			i++;
		if (!f[i])
			return 0;
		if (f[i] != '(') //можно убрать, если считать ( пробельным и вставить её в tab  в функции solve
			return 0;

		i++;
		while(f[i] && tab[(int) f[i]])
			i++;
		if (!f[i])
			return 0;


		for (let = f + i, j = 0; let[j] && (!tab[(int) let[j]]) && (let[j] != ','); j++)
			buf2[j] = let[j];
		buf2[j] = 0;

		if (!let[j])
			return 0;
		if (let[j] == ',')
			j++;
		put_name(buf2);

		f = let + j; i = 0;

		while(f[i] && tab[(int) f[i]])
			i++;
		if (!f[i])
			return 0;
		if (f[i] == ',')
		{
			i++;
			while(f[i] && tab[(int) f[i]])
				i++;
			if (!f[i])
				return 0;
		}
		//printf("f[%d] = '%s'", i, f + i);
		for (let = f + i, j = 0; let[j] && (!tab[(int) let[j]]) && (let[j] != ','); j++)
			buf2[j] = let[j];
		buf2[j] = 0;

		if (!let[j])
			return 0;
		//printf("buf2 = '%s'\t", buf2);
		if (let[j] == ',')
			j++;
		if (!put_phone(buf2))
			return 0;


		f = let + j; i = 0;

		while(f[i] && tab[(int) f[i]])
			i++;
		if (!f[i])
			return 0;
		if (f[i] == ',')
		{
			i++;
			while(f[i] && tab[(int) f[i]])
				i++;
			if (!f[i])
				return 0;
		}
		for (let = f + i, j = 0; let[j] && (!tab[(int) let[j]]) && (let[j] != ')'); j++)
			buf2[j] = let[j];
		buf2[j] = 0;

		if (!let[j])
			return 0;

		if (!put_group(buf2))
			return 0;

		if (let[j] == ')')
		{
			//printf("was here?\n");
			j++;
			f = let + j; i = 0;
			while(f[i] && tab[(int) f[i]])
				i++;
			if (!f[i])
				return 0;
			if (f[i] ==';')
			{
				flag = COR;
				return 1;
			}
			else
				return 0;
		}

		f = let + j; i = 0;

		while(f[i] && tab[(int) f[i]])
			i++;
		if (!f[i])
			return 0;
		if (f[i] == ')')
		{
			i++;
			while(f[i] && tab[(int) f[i]])
				i++;
			if (!f[i])
				return 0;
			if (f[i] ==';')
			{
				flag = COR;
				return 1;
			}
			else
				return 0;
		}
	}

	return 0;
}

int command::print_table(int i, FILE *fp)
{
	//printf("test = %d\n", (1<<3) + (1<<2));
	fprintf(fp, " %2.2d| %-8s | %-16s | %-11d | %-5d | %-6s | %-3s | %-4s | %-4s | %-4s | %-4s | %d |\n", i, print_flag(), name.get(), phone, group, print_type(), select_arguments(),
			print_cond(c_name), print_cond(c_phone), print_cond(c_group), print_oper(), c_ord);
	return 0;
}

const char * command::select_arguments()
{
	switch(s_ord)
	{
	case 0: return "";
	case 1<<4: return "name";
	case 1<<2: return "phone";
	case 1<<0: return "group";
	case (1<<4) + (1<<3): return "name, phone";
	case (1<<4) + (1<<1): return "name, group";
	case (1<<2) + (1<<5): return "phone, name";
	case (1<<2) + (1<<1): return "phone, group";
	case (1<<0) + (1<<5): return "group, name";
	case (1<<0) + (1<<3): return "group, phone";
	case (1<<4) + (1<<3) + (1<<1) + (1<<0): return "name, phone, group";
	case (1<<4) + (1<<3) + (1<<2) + (1<<1): return "name, group, phone";
	case (1<<6) + (1<<2) + (1<<1) + (1<<0): return "phone, name, group";
	case (1<<6) + (1<<5) + (1<<2) + (1<<1): return "phone, group, name";
	case (1<<6) + (1<<4) + (1<<3) + (1<<0): return "group, name, phone";
	case (1<<6) + (1<<5) + (1<<4) + (1<<0): return "group, phone, name";
	case 63: return "* ";
	default: return "!!!";
	}
}
const char * command::print_flag()
{
	switch(flag)
	{
	case UNDEF: return "UNDEF";
	case COR: return "CORRECT";
	case NONE_COR: return "NONE_COR";
	}
	return 0;
}
const char * command::print_type()
{
	switch(type)
	{
	case CMD_NONE: return "";
	case QUIT: return "quit";
	case STOP: return "stop";
	case SELECT: return "select";
	case INSERT: return "insert";
	case DELETE: return "delete";
	}
	return 0;
}
const char * command::print_cond(cond_type &run)
{
	switch(run)
	{
	case COND_NONE: return "";
	case EQ: return "=";
	case NE: return "<>";
	case LT: return "<";
	case GT: return ">";
	case LE: return "<=";
	case GE: return ">=";
	case LIKE: return "like";
	}
	return 0;
}
const char * command::print_oper()
{
	switch(oper)
	{
	case OP_NONE: return "";
	case AND: return "and";
	case OR: return "or";
	}
	return 0;
}
const char * command::print_argument_order()
{
	switch(c_order)
	{
	case NONE_ORDER: return "";
	case NAME: return "name";
	case PHONE: return "phone";
	case GROUP: return "group";
	}
	return 0;
}

int command::print(FILE *fp)
{
	if ((type == SELECT) || (type == DELETE))
	{
		fprintf(fp, "%s %swhere ", print_type(), select_arguments());

		if (c_ord == 1)
		{
			if (c_name)
				fprintf(fp, "name %s %s", print_cond(c_name), name.get());
			if (c_phone)
				fprintf(fp, "phone %s %d", print_cond(c_phone), phone);
			if (c_group)
				fprintf(fp, "group %s %d", print_cond(c_group), group);
			if(c_order)
				fprintf(fp, " order by %s;\n", print_argument_order());
			else
				fprintf(fp,";\n");
			return 1;
		}
		else
		{
			if (c_ord == 2)
			{
				if (c_name)
				{
					fprintf(fp, "name %s %s %s ", print_cond(c_name), name.get(), print_oper());
					if (c_phone)
						fprintf(fp, "phone %s %d", print_cond(c_phone), phone);
					if (c_group)
						fprintf(fp, "group %s %d", print_cond(c_group), group);
					if(c_order)
						fprintf(fp, " order by %s;\n", print_argument_order());
					else
						fprintf(fp,";\n");
					return 1;
				}
				else
				{
					fprintf(fp, "phone %s %d %s group %s %d", print_cond(c_phone), phone, print_oper(), print_cond(c_group), group);
					if(c_order)
						fprintf(fp, " order by %s;\n", print_argument_order());
					else
						fprintf(fp,";\n");
					return 1;
				}
			}
			else
			{
				if (c_group)
				{
					fprintf(fp, "group %s %d %s ", print_cond(c_group), group, print_oper());
					if (c_name)
						fprintf(fp, "name %s %s", print_cond(c_name), name.get());
					if (c_phone)
						fprintf(fp, "phone %s %d", print_cond(c_phone), phone);
					if(c_order)
						fprintf(fp, " order by %s;\n", print_argument_order());
					else
						fprintf(fp,";\n");
					return 1;
				}
				else
				{
					fprintf(fp, "phone %s %d %s name %s %s", print_cond(c_phone), phone, print_oper(), print_cond(c_name), name.get());
					if(c_order)
						fprintf(fp, " order by %s;\n", print_argument_order());
					else
						fprintf(fp,";\n");
					return 1;
				}
			}
		}
	}
	if ((type == QUIT) || (type == STOP))
	{
		fprintf(fp, "%s;\n", print_type());
		return 1;
	}
	if (type == INSERT)
	{
		fprintf(fp, "%s (%s, %d, %d);\n", print_type(), name.get(), phone, group);
		return 1;
	}

	fprintf(fp, "\n");
	return 0;
}
int command::make_cond(cond_type &run, const char *let, int *tab)
{
	if (let[0] == '<')
	{
		if (let[1] == '>')
		{
			run = NE;
			return 2;
		}
		else
		{
			if (let[1] == '=')
			{
				run = LE;
				return 2;
			}
			else
			{
				if (tab[(int) let[1]])
				{
					run = LT;
					return 1;
				}
				else
					return 0;
			}
		}
	}
	else
	{
		if (let[0] == '>')
		{
			if (let[1] == '=')
			{
				run = GE;
				return 2;
			}
			else
			{
				if (tab[(int) let[1]])
				{
					run = GT;
					return 1;
				}
				else
					return 0;
			}
		}
		else
		{
			if (let[0] == '=')
			{
				if (tab[(int) let[1]])
				{
					run = EQ;
					return 1;
				}
				else
					return 0;
			}
			else
			{
				if ((let[0] == 'l') && (let[1] == 'i') && (let[2] == 'k') && (let[3] == 'e') && (tab[(int) let[4]]))
				{
					run = LIKE;
					return 4;
				}
				else
					return 0;
			}

		}
	}
	return 1;
}
int command::parse_where(const char *let, int *tab, char *buf2)
{
	int i = 0, j = 0;
	const char *f;
	if ((let[0] == 'w') && (let[1] == 'h') && (let[2] == 'e') && (let[3] == 'r') && (let[4] == 'e') && (tab[(int) let[5]]))
	{
		f = let + 5; i = 0;
		while(f[i] && tab[(int) f[i]])
			i++;
		if (!f[i])
			return 0;
		let = f + i;
																														//первый name
		if ((let[0] == 'n') && (let[1] == 'a') && (let[2] == 'm') && (let[3] == 'e') && (tab[(int) let[4]]))
		{
			f = let + 4; i = 0;
			while(f[i] && tab[(int) f[i]])
				i++;
			if (!f[i])
				return 0;
			let = f + i;

			if (!(j = make_cond(c_name, let, tab)))
				return 0;


			f = let + j; i = 0;
			while(f[i] && tab[(int) f[i]])
				i++;
			if (!f[i] || f[i] == ';')
				return 0;
			let = f + i;

			j = 0;
			while (!tab[(int) let[j]] && let[j] != ';')
			{
				buf2[j] = let[j];
				j++;
			}
			buf2[j] = 0;
			//printf("buf2 = %s\n", buf2);
			put_name(buf2);

			f = let + j; i = 0;
			while(f[i] && tab[(int) f[i]])
				i++;
			if (!f[i])
				return 0;
			if (f[i] == ';')
			{
				c_ord = 1;
				flag = COR;
				return 1;
			}
			let = f + i;

			if ((let[0] == 'a') && (let[1] == 'n') && (let[2] == 'd') && (tab[(int) let[3]]))
			{
				oper = AND;
				j = 3;
			}
			else
			{
				if ((let[0] == 'o') && (let[1] == 'r') && (tab[(int) let[2]]))
				{
					oper = OR;
					j = 2;
				}
				//тут вставить кусок с order (лучше отдельной функцией, чтобы быстренько его везде вставлять
				else
				{
					c_ord = 1;
					return find_order(let, tab);
				}
			}
			f = let + j; i = 0;
			while(f[i] && tab[(int) f[i]])
				i++;
			if (!f[i])
				return 0;
			let = f + i;


			if ((let[0] == 'p') && (let[1] == 'h') && (let[2] == 'o') && (let[3] == 'n') && (let[4] == 'e') && (tab[(int) let[5]]))
			{
				f = let + 5; i = 0;
				while(f[i] && tab[(int) f[i]])
					i++;
				if (!f[i])
					return 0;
				let = f + i;

				if (!(j = make_cond(c_phone, let, tab)))
					return 0;

				f = let + j; i = 0;
				while(f[i] && tab[(int) f[i]])
					i++;
				if (!f[i] || f[i] == ';')
					return 0;
				let = f + i;

				j = 0;
				while (!tab[(int) let[j]] && let[j] != ';')
				{
					buf2[j] = let[j];
					j++;
				}
				buf2[j] = 0;
				//printf("buf2 = %s\n", buf2);
				if (!put_phone(buf2))
					return 0;

				f = let + j; i = 0;
				while(f[i] && tab[(int) f[i]])
					i++;
				if (!f[i])
					return 0;
				if (f[i] == ';')
				{
					c_ord = 2;
					flag = COR;
					return 1;
				}
				else
				{
					c_ord = 2;
					return find_order(f+1, tab);
				}
			}
			else
			{
				if ((let[0] == 'g') && (let[1] == 'r') && (let[2] == 'o') && (let[3] == 'u') && (let[4] == 'p') && (tab[(int) let[5]]))
				{
					f = let + 5; i = 0;
					while(f[i] && tab[(int) f[i]])
						i++;
					if (!f[i])
						return 0;
					let = f + i;

					if (!(j = make_cond(c_group, let, tab)))
						return 0;

					f = let + j; i = 0;
					while(f[i] && tab[(int) f[i]])
						i++;
					if (!f[i] || f[i] == ';')
						return 0;
					let = f + i;

					j = 0;
					while (!tab[(int) let[j]] && let[j] != ';')
					{
						buf2[j] = let[j];
						j++;
					}
					buf2[j] = 0;
						//printf("buf2 = %s\n", buf2);
					if (!put_group(buf2))
						return 0;

					f = let + j; i = 0;
					while(f[i] && tab[(int) f[i]])
						i++;
					if (!f[i])
						return 0;
					if (f[i] == ';')
					{
						c_ord = 2;
						flag = COR;
						return 1;
					}
					else
					{
						c_ord = 2;
						return find_order(f+1, tab);
					}
				}
				else
					return 0;
			}
		}
		else
		{
																																		//первый phone
			if ((let[0] == 'p') && (let[1] == 'h') && (let[2] == 'o') && (let[3] == 'n') && (let[4] == 'e') && (tab[(int) let[5]]))
			{
				f = let + 5; i = 0;
				while(f[i] && tab[(int) f[i]])
					i++;
				if (!f[i])
					return 0;
				let = f + i;

				if (!(j = make_cond(c_phone, let, tab)))
					return 0;

				f = let + j; i = 0;
				while(f[i] && tab[(int) f[i]])
					i++;
				if (!f[i] || f[i] == ';')
					return 0;
				let = f + i;

				j = 0;
				while (!tab[(int) let[j]] && let[j] != ';')
				{
					buf2[j] = let[j];
					j++;
				}
				buf2[j] = 0;
				//printf("buf2 = %s\n", buf2);
				if (!put_phone(buf2))
					return 0;

				f = let + j; i = 0;
				while(f[i] && tab[(int) f[i]])
					i++;
				if (!f[i])
					return 0;
				if (f[i] == ';')
				{
					c_ord = 1;
					flag = COR;
					return 1;
				}
				let = f + i;

				if ((let[0] == 'a') && (let[1] == 'n') && (let[2] == 'd') && (tab[(int) let[3]]))
				{
					oper = AND;
					j = 3;
				}
				else
				{
					if ((let[0] == 'o') && (let[1] == 'r') && (tab[(int) let[2]]))
					{
						oper = OR;
						j = 2;
					}
					else
					{
						c_ord = 1;
						return find_order(let, tab);
					}
				}
				f = let + j; i = 0;
				while(f[i] && tab[(int) f[i]])
					i++;
				if (!f[i])
					return 0;
				let = f + i;

																																				//PN
				if ((let[0] == 'n') && (let[1] == 'a') && (let[2] == 'm') && (let[3] == 'e') && (tab[(int) let[4]]))
				{
					f = let + 4; i = 0;
					while(f[i] && tab[(int) f[i]])
						i++;
					if (!f[i])
						return 0;
					let = f + i;

					if (!(j = make_cond(c_name, let, tab)))
						return 0;


					f = let + j; i = 0;
					while(f[i] && tab[(int) f[i]])
						i++;
					if (!f[i] || f[i] == ';')
						return 0;
					let = f + i;

					j = 0;
					while (!tab[(int) let[j]] && let[j] != ';')
					{
						buf2[j] = let[j];
						j++;
					}
					buf2[j] = 0;
					//printf("buf2 = %s\n", buf2);
					put_name(buf2);

					f = let + j; i = 0;
					while(f[i] && tab[(int) f[i]])
						i++;
					if (!f[i])
						return 0;
					if (f[i] == ';')
					{
						c_ord = 3;
						flag = COR;
						return 1;
					}
					else
					{
						c_ord = 3;
						return find_order(f+1, tab);
					}
				}
				else
				{
																																				//PG
					if ((let[0] == 'g') && (let[1] == 'r') && (let[2] == 'o') && (let[3] == 'u') && (let[4] == 'p') && (tab[(int) let[5]]))
					{
						f = let + 5; i = 0;
						while(f[i] && tab[(int) f[i]])
							i++;
						if (!f[i])
							return 0;
						let = f + i;

						if (!(j = make_cond(c_group, let, tab)))
							return 0;

						f = let + j; i = 0;
						while(f[i] && tab[(int) f[i]])
							i++;
						if (!f[i] || f[i] == ';')
							return 0;
						let = f + i;

						j = 0;
						while (!tab[(int) let[j]] && let[j] != ';')
						{
							buf2[j] = let[j];
							j++;
						}
						buf2[j] = 0;
							//printf("buf2 = %s\n", buf2);
						if (!put_group(buf2))
							return 0;

						f = let + j; i = 0;
						while(f[i] && tab[(int) f[i]])
							i++;
						if (!f[i])
							return 0;
						if (f[i] == ';')
						{
							c_ord = 2;
							flag = COR;
							return 1;
						}
						else
						{
							c_ord = 2;
							return find_order(f+1, tab);
						}
					}
					else
						return 0;
				}
			}
			else
			{
																																			//group первый
				if ((let[0] == 'g') && (let[1] == 'r') && (let[2] == 'o') && (let[3] == 'u') && (let[4] == 'p') && (tab[(int) let[5]]))
				{
					f = let + 5; i = 0;
					while(f[i] && tab[(int) f[i]])
						i++;
					if (!f[i])
						return 0;
					let = f + i;

					if (!(j = make_cond(c_group, let, tab)))
						return 0;

					f = let + j; i = 0;
					while(f[i] && tab[(int) f[i]])
						i++;
					if (!f[i] || f[i] == ';')
						return 0;
					let = f + i;

					j = 0;
					while (!tab[(int) let[j]] && let[j] != ';')
					{
						buf2[j] = let[j];
						j++;
					}
					buf2[j] = 0;
						//printf("buf2 = %s\n", buf2);
					if (!put_group(buf2))
						return 0;

					f = let + j; i = 0;
					while(f[i] && tab[(int) f[i]])
						i++;
					if (!f[i])
						return 0;
					if (f[i] == ';')
					{
						c_ord = 1;
						flag = COR;
						return 1;
					}
					let = f + i;

					if ((let[0] == 'a') && (let[1] == 'n') && (let[2] == 'd') && (tab[(int) let[3]]))
					{
						oper = AND;
						j = 3;
					}
					else
					{
						if ((let[0] == 'o') && (let[1] == 'r') && (tab[(int) let[2]]))
						{
							oper = OR;
							j = 2;
						}
						else
						{
							c_ord = 1;
							return find_order(let, tab);
						}
					}
					f = let + j; i = 0;
					while(f[i] && tab[(int) f[i]])
						i++;
					if (!f[i])
						return 0;
					let = f + i;

																																	//GN

					if ((let[0] == 'n') && (let[1] == 'a') && (let[2] == 'm') && (let[3] == 'e') && (tab[(int) let[4]]))
					{

						f = let + 4; i = 0;
						while(f[i] && tab[(int) f[i]])
							i++;
						if (!f[i])
							return 0;
						let = f + i;

						if (!(j = make_cond(c_name, let, tab)))
							return 0;


						f = let + j; i = 0;
						while(f[i] && tab[(int) f[i]])
							i++;
						if (!f[i] || f[i] == ';')
							return 0;
						let = f + i;

						j = 0;
						while (!tab[(int) let[j]] && let[j] != ';')
						{
							buf2[j] = let[j];
							j++;
						}
						buf2[j] = 0;
						//printf("buf2 = %s\n", buf2);
						put_name(buf2);

						f = let + j; i = 0;
						while(f[i] && tab[(int) f[i]])
							i++;
						if (!f[i])
							return 0;
						if (f[i] == ';')
						{
							c_ord = 3;
							flag = COR;
							return 1;
						}
						else
						{
							//printf("\n\nPRIVEEEEEET f = '%s'\n\n", f);
							c_ord = 3;
							return find_order(f+1, tab);
						}
					}
																																	//GP
					else
					{
						if ((let[0] == 'p') && (let[1] == 'h') && (let[2] == 'o') && (let[3] == 'n') && (let[4] == 'e') && (tab[(int) let[5]]))
						{
							f = let + 5; i = 0;
							while(f[i] && tab[(int) f[i]])
								i++;
							if (!f[i])
								return 0;
							let = f + i;

							if (!(j = make_cond(c_phone, let, tab)))
								return 0;

							f = let + j; i = 0;
							while(f[i] && tab[(int) f[i]])
								i++;
							if (!f[i] || f[i] == ';')
								return 0;
							let = f + i;

							j = 0;
							while (!tab[(int) let[j]] && let[j] != ';')
							{
								buf2[j] = let[j];
								j++;
							}
							buf2[j] = 0;
							//printf("buf2 = %s\n", buf2);
							if (!put_phone(buf2))
								return 0;

							f = let + j; i = 0;
							while(f[i] && tab[(int) f[i]])
								i++;
							if (!f[i])
								return 0;
							if (f[i] == ';')
							{
								c_ord = 3;
								flag = COR;
								return 1;
							}
							else
							{
								c_ord = 3;
								return find_order(f+1, tab);
							}
						}
						else
							return 0;
					}



				}
				else
					return 0;
			}


		}
	}
	else
		return 0;


}


int command::find_order(const char *let, int *tab)
{
	if ((let[0] == 'o') && (let[1] == 'r') && (let[2] == 'd') && (let[3] == 'e') && (let[4] == 'r') && (tab[(int) let[5]]) && (let[6] == 'b') && (let[7] == 'y') && (tab[(int) let[8]]))
	{
		let+=9;
		if ((let[0] == 'n') && (let[1] == 'a') && (let[2] == 'm') && (let[3] == 'e') && (let[4] == ';')) //strcmp(let,"name;"); - такие штуки вставить дальше еще два раза, но только поменять слова
		{
			//printf("\nPrivet\n");
			c_order = NAME;
			flag = COR;
			return 1;
		}
		if ((let[0] == 'p') && (let[1] == 'h') && (let[2] == 'o') && (let[3] == 'n') && (let[4] == 'e') && (let[5] == ';'))
		{
			c_order = PHONE;
			flag = COR;
			return 1;
		}
		if ((let[0] == 'g') && (let[1] == 'r') && (let[2] == 'o') && (let[3] == 'u') && (let[4] == 'p') && (let[5] == ';'))
		{
			c_order = GROUP;
			flag = COR;
			return 1;
		}
	}
	return 0;

}


void command::obnulis()
{
	flag = UNDEF;
	type = CMD_NONE;
	s_ord = 0;
	c_name = COND_NONE;
	c_phone = COND_NONE;
	c_group = COND_NONE;
	c_ord = 0;
	oper = OP_NONE;
	c_order = NONE_ORDER;
}
