#include "command.h"

bool Command::like(const char * string, const char * reference)
{
    int i = 0, j=0;
    for(i = 0;reference[i] && string[j];)
    {
	if(reference[i]=='%') return true;
	if(reference[i]=='\\')
	{
	    i++;
	    if(reference[i]=='\\' && string[j]=='\\')
	    {
		i++;
		j++;
		continue;
	    }
	    if(reference[i]=='_' && string[j]=='_')
	    {
		i++;
		j++;
		continue;
	    }
	    if(reference[i]=='%' && string[j]=='%')
	    {
		i++;
		j++;
		continue;
	    }
	    return false;
	}
	else
	{
	    if(reference[i] == string[j])
	    {
		i++;
		j++;
	    }
	    else
	    {
		return false;
	    }
	}
    }
    if(reference[i] || string[j])
    {
	return false;
    }
    return true;
}

bool Command::isOk(Record * tmp, int flagType)
{
    bool nameFlag = false;
    bool phoneFlag = false;
    bool groupFlag = false;

    switch(flagType)
    {
        case 1:
	    switch (getNameCondition())
	    {
	        case EQ:
		    if(strcmp(tmp->getName(), getName()) == 0)
		    {
			nameFlag = true;
		    }
		    break;

	        case NE:
		    if(strcmp(tmp->getName(), getName()) != 0)
		    {
			nameFlag = true;
		    }
		    break;

	        case LT:
		    if(strcmp(tmp->getName(), getName()) < 0)
		    {
			nameFlag = true;
		    }
		    break;

	        case GT:
		    if(strcmp(tmp->getName(), getName()) > 0)
		    {
			nameFlag = true;
		    }
		    break;

	        case LE:
		    if(strcmp(tmp->getName(), getName()) <= 0)
		    {
			nameFlag = true;
		    }
		    break;

	        case GE:
		    if(strcmp(tmp->getName(), getName()) >= 0)
		    {
			nameFlag = true;
		    }
		    break;

	        case LIKE:
		    if(like(tmp->getName(), getName()))
		    {
			nameFlag = true;
		    }
		    break;
	        case COND_NONE: break;
	    }
	    return nameFlag;

        case 2:
	    switch (getPhoneCondition())
	    {
	        case EQ:
		    if(tmp->getPhone() == getPhone())
		    {
			phoneFlag = true;
		    }
		    break;

	        case NE:
		    if(tmp->getPhone() != getPhone())
		    {
			phoneFlag = true;
		    }
		    break;

	        case LT:
		    if(tmp->getPhone() < getPhone())
		    {
			phoneFlag = true;
		    }
		    break;

	        case GT:
		    if(tmp->getPhone() > getPhone())
		    {
			phoneFlag = true;
		    }
		    break;

	        case LE:
		    if(tmp->getPhone() <= getPhone())
		    {
			phoneFlag = true;
		    }
		    break;

	        case GE:
		    if(tmp->getPhone() >= getPhone())
		    {
			phoneFlag = true;
		    }
		    break;

	        case LIKE: break;
	        case COND_NONE: break;
	    }
	    return phoneFlag;

        case 3:
	    switch (getGroupCondition())
	    {
	        case EQ:
		    if(tmp->getGroup() == getGroup())
		    {
			groupFlag = true;
		    }
		    break;

	        case NE:
		    if(tmp->getGroup() != getGroup())
		    {
			groupFlag = true;
		    }
		    break;

	        case LT:
		    if(tmp->getGroup() < getGroup())
		    {
			groupFlag = true;
		    }
		    break;

	        case GT:
		    if(tmp->getGroup() > getGroup())
		    {
			groupFlag = true;
		    }
		    break;

	        case LE:
		    if(tmp->getGroup() <= getGroup())
		    {
			groupFlag = true;
		    }
		    break;

	        case GE:
		    if(tmp->getGroup() >= getGroup())
		    {
			groupFlag = true;
		    }
		    break;

	        case LIKE: break;
	        case COND_NONE: break;
	    }
	    return groupFlag;

        case 0:
	    return true;
        }

    return false;
}

bool Command::check(Record * tmp)
{

    bool nameFlag = false;
    bool phoneFlag = false;
    bool groupFlag = false;

    switch (getNameCondition())
    {
        case EQ:
	    if(strcmp(tmp->getName(), getName()) == 0)
	    {
		nameFlag = true;
	    }
	    break;

        case NE:
	    if(strcmp(tmp->getName(), getName()) != 0)
	    {
		nameFlag = true;
	    }
	    break;

        case LT:
	    if(strcmp(tmp->getName(), getName()) < 0)
	    {
		nameFlag = true;
	    }
	    break;

        case GT:
	    if(strcmp(tmp->getName(), getName()) > 0)
	    {
		nameFlag = true;
	    }
	    break;

        case LE:
	    if(strcmp(tmp->getName(), getName()) <= 0)
	    {
		nameFlag = true;
	    }
	    break;

        case GE:
	    if(strcmp(tmp->getName(), getName()) >= 0)
	    {
		nameFlag = true;
	    }
	    break;

        case LIKE:
	    if(like(tmp->getName(), getName()))
	    {
		nameFlag = true;
	    }
	    break;
        case COND_NONE: break;
    }

    switch (getPhoneCondition())
    {
        case EQ:
	    if(tmp->getPhone() == getPhone())
	    {
		phoneFlag = true;
	    }
	    break;

        case NE:
	    if(tmp->getPhone() != getPhone())
	    {
		phoneFlag = true;
	    }
	    break;

        case LT:
	    if(tmp->getPhone() < getPhone())
	    {
		phoneFlag = true;
	    }
	    break;

        case GT:
	    if(tmp->getPhone() > getPhone())
	    {
		phoneFlag = true;
	    }
	    break;

        case LE:
	    if(tmp->getPhone() <= getPhone())
	    {
		phoneFlag = true;
	    }
	    break;

        case GE:
	    if(tmp->getPhone() >= getPhone())
	    {
		phoneFlag = true;
	    }
	    break;

        case LIKE: break;
        case COND_NONE: break;
    }

    switch (getGroupCondition())
    {
        case EQ:
	    if(tmp->getGroup() == getGroup())
	    {
		groupFlag = true;
	    }
	    break;

        case NE:
	    if(tmp->getGroup() != getGroup())
	    {
		groupFlag = true;
	    }
	    break;

        case LT:
	    if(tmp->getGroup() < getGroup())
	    {
		groupFlag = true;
	    }
	    break;

        case GT:
	    if(tmp->getGroup() > getGroup())
	    {
		groupFlag = true;
	    }
	    break;

        case LE:
	    if(tmp->getGroup() <= getGroup())
	    {
		groupFlag = true;
	    }
	    break;

        case GE:
	    if(tmp->getGroup() >= getGroup())
	    {
		groupFlag = true;
	    }
	    break;

        case LIKE: break;
        case COND_NONE: break;
    }

    bool result = false;

    switch (getOperation())
    {
        case OR:
	    if(getNameCondition() != COND_NONE && getPhoneCondition() != COND_NONE)
	    {
		result = nameFlag || phoneFlag;
	    }
	    if(getNameCondition() != COND_NONE && getGroupCondition() != COND_NONE)
	    {
		result = nameFlag || groupFlag;
	    }
	    if(getGroupCondition() != COND_NONE && getPhoneCondition() != COND_NONE)
	    {
		result = groupFlag || phoneFlag;
	    }
	    break;

        case AND:
	    if(getNameCondition() != COND_NONE && getPhoneCondition() != COND_NONE)
	    {
		result = nameFlag && phoneFlag;
	    }
	    if(getNameCondition() != COND_NONE && getGroupCondition() != COND_NONE)
	    {
		result = nameFlag && groupFlag;
	    }
	    if(getGroupCondition() != COND_NONE && getPhoneCondition() != COND_NONE)
	    {
		result = groupFlag && phoneFlag;
	    }
	    break;

        case OP_NONE:
	    if(getNameCondition() != COND_NONE)
	    {
		result = nameFlag;
	    }
	    if(getPhoneCondition() != COND_NONE)
	    {
		result = phoneFlag;
	    }
	    if(getGroupCondition() != COND_NONE)
	    {
		result = groupFlag;
	    }
	    break;
    }
    return result;
}



bool Command::print(int commandCounter, bool isDebugPrint, FILE* outFile)
{
    if (isDebugPrint)
    {
	if(commandCounter == 0)
	{
	    fprintf(outFile, "\t|     №    |     Name     |   Phone   | Group | Order |   Type   | Argumets | Condition_Name | Condition_Phone | Condition_Group | Operation |\n"
	                      "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	}
	fprintf(outFile, "\t|%10d|%14s|%11d|%7d|%7d|%10s|%10s|%16s|%17s|%17s|%11s|\n",
	        commandCounter, getName(), getPhone(), getGroup(), getOrder(), getType(), getArguments(),
	            getCondition(condName), getCondition(condPhone), getCondition(condGroup), getOperationString());
	return 1;
    }
    else
    {
	if ((command == SELECT) || (command == DELETE))
	{
	    fprintf(outFile, "%s %swhere ", getType(), getArguments());
	    if (commandOrder == 1)
	    {
		if (condName)
		{
		    fprintf(outFile, "name %s %s;\n", getCondition(condName), getName());
		}
		if (condPhone)
		{
		    fprintf(outFile, "phone %s %d;\n", getCondition(condPhone), getPhone());
		}
		if (condGroup)
		{
		    fprintf(outFile, "group %s %d;\n", getCondition(condGroup), getGroup());
		}
		return true;
	    }
	    else
	    {
		if (commandOrder == 2)
		{
		    if (condName)
		    {
			fprintf(outFile, "name %s %s %s ", getCondition(condName), getName(), getOperationString());
			if (condPhone)
			{
			    fprintf(outFile, "phone %s %d;\n", getCondition(condPhone), getPhone());
			}
			if (condGroup)
			{
			    fprintf(outFile, "group %s %d;\n", getCondition(condGroup), getGroup());
			}
			return true;
		    }
		    else
		    {
			fprintf(outFile, "phone %s %d %s group %s %d;\n", getCondition(condPhone), getPhone(), getOperationString(), getCondition(condGroup), getGroup());
			return true;
		    }
		}
		else
		{
		    if (condGroup)
		    {
			fprintf(outFile, "group %s %d %s ", getCondition(condGroup), getGroup(), getOperationString());
			if (condName)
			{
			    fprintf(outFile, "name %s %s;\n", getCondition(condName), getName());
			}
			if (condPhone)
			{
			    fprintf(outFile, "phone %s %d;\n", getCondition(condPhone), getPhone());
			}
			return true;
		    }
		    else
		    {
			fprintf(outFile, "phone %s %d %s name %s %s;", getCondition(condPhone), getPhone(), getOperationString(), getCondition(condName), getName());
			return true;
		    }
		}
	    }
	}
	if ((command == QUIT) || (command == STOP))
	{
	        fprintf(outFile, "%s;\n", getType());
		return true;
	}
	if (command == INSERT)
	{
	        fprintf(outFile, "%s (%s, %d, %d);\n", getType(), getName(), getPhone(), getGroup());
		return true;
	}
	fprintf(outFile, "\n");
	return false;
    }
}


const char* Command::getArguments()
{
    switch(selectOrder)
    {
        case 0:
	        return "";
        case 1<<4:
	        return "name";
        case 1<<2:
	        return "phone";
        case 1<<0:
	        return "group";
        case (1<<4) + (1<<3):
	        return "name, phone";
        case (1<<4) + (1<<1):
	        return "name, group";
        case (1<<2) + (1<<5):
	        return "phone, name";
        case (1<<2) + (1<<1):
	        return "phone, group";
        case (1<<0) + (1<<5):
	        return "group, name";
        case (1<<0) + (1<<3):
	        return "group, phone";
        case (1<<4) + (1<<3) + (1<<1) + (1<<0):
	        return "name, phone, group";
        case (1<<4) + (1<<3) + (1<<2) + (1<<1):
	        return "name, group, phone";
        case (1<<6) + (1<<2) + (1<<1) + (1<<0):
	        return "phone, name, group";
        case (1<<6) + (1<<5) + (1<<2) + (1<<1):
	        return "phone, group, name";
        case (1<<6) + (1<<4) + (1<<3) + (1<<0):
	        return "group, name, phone";
        case (1<<6) + (1<<5) + (1<<4) + (1<<0):
	        return "group, phone, name";
        case 90:
	        return "* ";
        default:
	        return "!!!";
    }
}

commandType Command::getCommand()
{
    return command;
}

const char* Command::getType()
{
    switch(command)
    {
        case CMD_NONE:
	        return "";
        case QUIT:
	        return "quit";
        case STOP:
	        return "stop";
        case SELECT:
	        return "select";
        case INSERT:
	        return "insert";
        case DELETE:
	        return "delete";
    }
    return "";
}

conditionType Command::getNameCondition()
{
    return condName;
}
conditionType Command::getPhoneCondition()
{
    return condPhone;
}
conditionType Command::getGroupCondition()
{
    return condGroup;
}

operationType Command::getOperation()
{
    return operation;
}

const char* Command::getCondition(conditionType& type)
{
    switch(type)
    {
        case COND_NONE:
	        return "";
        case EQ:
	        return "=";
        case NE:
	        return "<>";
        case LT:
	        return "<";
        case GT:
	        return ">";
        case LE:
	        return "<=";
        case GE:
	        return ">=";
        case LIKE:
	        return "like";
    }
    return "";
}

const char* Command::getOperationString()
{
    switch(operation)
    {
        case OP_NONE:
	        return "";
        case AND:
	        return "and";
        case OR:
	        return "or";
    }
    return "";
}


int Command::parse(const char *string, int *spaces, char *buff)
{
    int i = 0, j = 0;
    const char *let,  *f = string;
    statement = INCORRECT;

    while(spaces[(int) f[i]])
    {
	i++;
    }
    if (!f[i])
    {
	return 0;
    }
    let = f + i;

    if ((let[0] == 's') && (let[1] == 'e') && (let[2] == 'l') && (let[3] == 'e') && (let[4] == 'c') && (let[5] == 't') && (spaces[(int) let[6]]))
    {
	command = SELECT; f = let + 6; i = 0;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	let = f + i;
	                                                                                                                                                                                                                                        //сценарий аргументов selecet
	                                                                                                                                                                                                                                        //тут можно реализовать возможность иметь 1,2 аргументов вывода select
	                                                                                                                                                                                                                                        //также, как и в AND и OR
	if (let[0] == '*')
	{
	    selectOrder = 90; f = let + 1; i = 0;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i])
	    {
		return 0;
	    }
	    if (f[i] == ';')
	    {
		selectOrder = 100;
		statement = CORRECT;
		return 1;
	    }
	    let = f + i;
	    return parseAddition(let, spaces, buff);
	}
	else
	{
	    return 0;
	}
    }

    if ((let[0] == 's') && (let[1] == 't') && (let[2] == 'o') && (let[3] == 'p'))
    {
	command = STOP; f = let + 4; i = 0;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] == ';')
	{
	    statement = CORRECT;
	    return 1;
	}
	else
	{
	    return 0;
	}
    }
    if ((let[0] == 'd') && (let[1] == 'e') && (let[2] == 'l') && (let[3] == 'e') && (let[4] == 't') && (let[5] == 'e'))
    {
	command = DELETE; f = let + 6; i = 0;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] == ';')
	{
	    statement = CORRECT;
	    return 1;
	}
	let = f + i;
	return parseAddition(let, spaces, buff);
    }

    if ((let[0] == 'q') && (let[1] == 'u') && (let[2] == 'i') && (let[3] == 't'))
    {
	command = QUIT; f = let + 4; i = 0;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] == ';')
	{
	    statement = CORRECT;
	    return 1;
	}
    }

    if ((let[0] == 'i') && (let[1] == 'n') && (let[2] == 's') && (let[3] == 'e') && (let[4] == 'r') && (let[5] == 't') && (spaces[(int) let[6]]))
    {
	command = INSERT; f = let + 6; i = 0;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] != '(')
	{
	    return 0;
	}

	i++;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}


	for (let = f + i, j = 0; let[j] && (!spaces[(int) let[j]]) && (let[j] != ','); j++)
	{
	    buff[j] = let[j];
	}
	buff[j] = 0;

	if (!let[j])
	{
	    return 0;
	}
	if (let[j] == ',')
	{
	    j++;
	}
	setName(buff);

	f = let + j; i = 0;

	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] == ',')
	{
	    i++;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i])
	    {
		return 0;
	    }
	}

	for (let = f + i, j = 0; let[j] && (!spaces[(int) let[j]]) && (let[j] != ','); j++)
	{
	    buff[j] = let[j];
	}
	buff[j] = 0;

	if (!let[j])
	{
	    return 0;
	}
	if (let[j] == ',')
	{
	    j++;
	}
	if (!setPhone(buff))
	{
	    return 0;
	}
	f = let + j; i = 0;

	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] == ',')
	{
	    i++;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i])
	    {
		return 0;
	    }
	}
	for (let = f + i, j = 0; let[j] && (!spaces[(int) let[j]]) && (let[j] != ')'); j++)
	{
	    buff[j] = let[j];
	}
	buff[j] = 0;

	if (!let[j])
	{
	    return 0;
	}

	if (!setGroup(buff))
	{
	    return 0;
	}

	if (let[j] == ')')
	{
	    j++;
	    f = let + j; i = 0;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i])
	    {
		return 0;
	    }
	    if (f[i] ==';')
	    {
		statement = CORRECT;
		return 1;
	    }
	    else
	    {
		return 0;
	    }
	}

	f = let + j; i = 0;

	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] == ')')
	{
	    i++;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i])
	    {
		return 0;
	    }
	    if (f[i] ==';')
	    {
		statement = CORRECT;
		return 1;
	    }
	    else
	    {
		return 0;
	    }
	}
    }

    return 0;
}

int Command::parseAddition(const char *let, int *spaces, char *buff)
{
    int i = 0, j = 0;
    const char *f;
    if ((let[0] == 'w') && (let[1] == 'h') && (let[2] == 'e') && (let[3] == 'r') && (let[4] == 'e') && (spaces[(int) let[5]]))
    {
	f = let + 5; i = 0;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	let = f + i;
	                                                                                                                                                                                                                                //первый name
	if ((let[0] == 'n') && (let[1] == 'a') && (let[2] == 'm') && (let[3] == 'e') && (spaces[(int) let[4]]))
	{
	        f = let + 4; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		        i++;
		}
		if (!f[i])
		{
		        return 0;
		}
		let = f + i;

		if (!(j = setCondition(condName, let, spaces)))
		{
		        return 0;
		}

		f = let + j; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		        i++;
		}
		if (!f[i] || f[i] == ';')
		{
		        return 0;
		}
		let = f + i;

		j = 0;
		while (!spaces[(int) let[j]] && let[j] != ';')
		{
		        buff[j] = let[j];
			j++;
		}
		buff[j] = 0;
		//printf("buff = %s\n", buff);
		setName(buff);

		f = let + j; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		        i++;
		}
		if (!f[i])
		{
		        return 0;
		}
		if (f[i] == ';')
		{
		        commandOrder = 1;
			statement = CORRECT;
			return 1;
		}
		let = f + i;

		if ((let[0] == 'a') && (let[1] == 'n') && (let[2] == 'd') && (spaces[(int) let[3]]))
		{
		        operation = AND;
			j = 3;
		}
		else
		{
		        if ((let[0] == 'o') && (let[1] == 'r') && (spaces[(int) let[2]]))
			{
			        operation = OR;
				j = 2;
			}
			else
			{
			        return 0;
			}
		}
		f = let + j; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		        i++;
		}
		if (!f[i])
		{
		        return 0;
		}
		let = f + i;


		if ((let[0] == 'p') && (let[1] == 'h') && (let[2] == 'o') && (let[3] == 'n') && (let[4] == 'e') && (spaces[(int) let[5]]))
		{
		        f = let + 5; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			        i++;
			}
			if (!f[i])
			{
			        return 0;
			}
			let = f + i;

			if (!(j = setCondition(condPhone, let, spaces)))
			{
			        return 0;
			}

			f = let + j; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			        i++;
			}
			if (!f[i] || f[i] == ';')
			{
			        return 0;
			}
			let = f + i;

			j = 0;
			while (!spaces[(int) let[j]] && let[j] != ';')
			{
			        buff[j] = let[j];
				j++;
			}
			buff[j] = 0;
			//printf("buff = %s\n", buff);
			if (!setPhone(buff))
			{
			        return 0;
			}

			f = let + j; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			        i++;
			}
			if (!f[i])
			{
			        return 0;
			}
			if (f[i] == ';')
			{
			        commandOrder = 2;
				statement = CORRECT;
				return 1;
			}
			else
			{
			        return 0;
			}
		}
		else
		{
		        if ((let[0] == 'g') && (let[1] == 'r') && (let[2] == 'o') && (let[3] == 'u') && (let[4] == 'p') && (spaces[(int) let[5]]))
			{
			        f = let + 5; i = 0;
				while(f[i] && spaces[(int) f[i]])
				{
				        i++;
				}
				if (!f[i])
				{
				        return 0;
				}
				let = f + i;

				if (!(j = setCondition(condGroup, let, spaces)))
				{
				        return 0;
				}

				f = let + j; i = 0;
				while(f[i] && spaces[(int) f[i]])
				{
				        i++;
				}
				if (!f[i] || f[i] == ';')
				{
				        return 0;
				}
				let = f + i;

				j = 0;
				while (!spaces[(int) let[j]] && let[j] != ';')
				{
				        buff[j] = let[j];
					j++;
				}
				buff[j] = 0;
				        //printf("buff = %s\n", buff);
				if (!setGroup(buff))
				{
				        return 0;
				}

				f = let + j; i = 0;
				while(f[i] && spaces[(int) f[i]])
				{
				        i++;
				}
				if (!f[i])
				{
				        return 0;
				}
				if (f[i] == ';')
				{
				        commandOrder = 2;
					statement = CORRECT;
					return 1;
				}
				else
				{
				        return 0;
				}
			}
			else
			{
			        return 0;
			}
		}
	}
	else
	{																															//первый phone
	    if ((let[0] == 'p') && (let[1] == 'h') && (let[2] == 'o') && (let[3] == 'n') && (let[4] == 'e') && (spaces[(int) let[5]]))
	    {
		f = let + 5; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		    i++;
		}
		if (!f[i])
		{
		    return 0;
		}
		let = f + i;

		if (!(j = setCondition(condPhone, let, spaces)))
		{
		    return 0;
		}

		f = let + j; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		    i++;
		}
		if (!f[i] || f[i] == ';')
		{
		    return 0;
		}
		let = f + i;

		j = 0;
		while (!spaces[(int) let[j]] && let[j] != ';')
		{
		    buff[j] = let[j];
		    j++;
		}
		buff[j] = 0;
		if (!setPhone(buff))
		{
		    return 0;
		}

		f = let + j; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		    i++;
		}
		if (!f[i])
		{
		    return 0;
		}
		if (f[i] == ';')
		{
		    commandOrder = 1;
		    statement = CORRECT;
		    return 1;
		}
		let = f + i;

		if ((let[0] == 'a') && (let[1] == 'n') && (let[2] == 'd') && (spaces[(int) let[3]]))
		{
		    operation = AND;
		    j = 3;
		}
		else
		{
		    if ((let[0] == 'o') && (let[1] == 'r') && (spaces[(int) let[2]]))
		    {
			operation = OR;
			j = 2;
		    }
		    else
		    {
			return 0;
		    }
		}
		f = let + j; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		    i++;
		}
		if (!f[i])
		{
		    return 0;
		}
		let = f + i;

		                                                                                                                                                                                                                                                                //PN
		if ((let[0] == 'n') && (let[1] == 'a') && (let[2] == 'm') && (let[3] == 'e') && (spaces[(int) let[4]]))
		{
		    f = let + 4; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i])
		    {
			return 0;
		    }
		    let = f + i;

		    if (!(j = setCondition(condName, let, spaces)))
		    {
			return 0;
		    }

		    f = let + j; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i] || f[i] == ';')
		    {
			return 0;
		    }
		    let = f + i;

		    j = 0;
		    while (!spaces[(int) let[j]] && let[j] != ';')
		    {
			buff[j] = let[j];
			j++;
		    }
		    buff[j] = 0;
		    setName(buff);

		    f = let + j; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i])
		    {
			return 0;
		    }
		    if (f[i] == ';')
		    {
			commandOrder = 3;
			statement = CORRECT;
			return 1;
		    }
		    else
		    {
			return 0;
		    }
		}
		else
		{																																		    //PG
		    if ((let[0] == 'g') && (let[1] == 'r') && (let[2] == 'o') && (let[3] == 'u') && (let[4] == 'p') && (spaces[(int) let[5]]))
		    {
			f = let + 5; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			    i++;
			}
			if (!f[i])
			{
			    return 0;
			}
			let = f + i;

			if (!(j = setCondition(condGroup, let, spaces)))
			{
			    return 0;
			}

			f = let + j; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			    i++;
			}
			if (!f[i] || f[i] == ';')
			{
			    return 0;
			}
			let = f + i;

			j = 0;
			while (!spaces[(int) let[j]] && let[j] != ';')
			{
			    buff[j] = let[j];
			    j++;
			}
			buff[j] = 0;
			if (!setGroup(buff))
			{
			    return 0;
			}

			f = let + j; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			    i++;
			}
			if (!f[i])
			{
			    return 0;
			}
			if (f[i] == ';')
			{
			    commandOrder = 2;
			    statement = CORRECT;
			    return 1;
			}
			else
			{
			    return 0;
			}
		    }
		    else
		    {
			return 0;
		    }
		}
	    }
	    else
	    {
		                                                                                                                                                                                                                                                            //group первый
		if ((let[0] == 'g') && (let[1] == 'r') && (let[2] == 'o') && (let[3] == 'u') && (let[4] == 'p') && (spaces[(int) let[5]]))
		{
		    f = let + 5; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i])
		    {
			return 0;
		    }
		    let = f + i;

		    if (!(j = setCondition(condGroup, let, spaces)))
		    {
			return 0;
		    }

		    f = let + j; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i] || f[i] == ';')
		    {
			return 0;
		    }
		    let = f + i;

		    j = 0;
		    while (!spaces[(int) let[j]] && let[j] != ';')
		    {
			buff[j] = let[j];
			j++;
		    }
		    buff[j] = 0;
		    if (!setGroup(buff))
		    {
			return 0;
		    }

		    f = let + j; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i])
		    {
			return 0;
		    }
		    if (f[i] == ';')
		    {
			commandOrder = 1;
			statement = CORRECT;
			return 1;
		    }
		    let = f + i;

		    if ((let[0] == 'a') && (let[1] == 'n') && (let[2] == 'd') && (spaces[(int) let[3]]))
		    {
			operation = AND;
			j = 3;
		    }
		    else
		    {
			if ((let[0] == 'o') && (let[1] == 'r') && (spaces[(int) let[2]]))
			{
			    operation = OR;
			    j = 2;
			}
			else
			{
			    return 0;
			}
		    }
		    f = let + j; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i])
		    {
			return 0;
		    }
		    let = f + i;

		                                                                                                                                                                                                                                    //GN

		    if ((let[0] == 'n') && (let[1] == 'a') && (let[2] == 'm') && (let[3] == 'e') && (spaces[(int) let[4]]))
		    {
			f = let + 4; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			        i++;
			}
			if (!f[i])
			{
			    return 0;
			}
			let = f + i;

			if (!(j = setCondition(condName, let, spaces)))
			{
			    return 0;
			}


			f = let + j; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			    i++;
			}
			if (!f[i] || f[i] == ';')
			{
			    return 0;
			}
			let = f + i;

			j = 0;
			while (!spaces[(int) let[j]] && let[j] != ';')
			{
			    buff[j] = let[j];
			    j++;
			}
			buff[j] = 0;
			setName(buff);

			f = let + j; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			    i++;
			}
			if (!f[i])
			{
			    return 0;
			}
			if (f[i] == ';')
			{
			    commandOrder = 3;
			    statement = CORRECT;
			    return 1;
			}
			else
			{
			    return 0;
			}
		    }
		                                                                                                                                                                                                                                    //GP
		    else
		    {
			if ((let[0] == 'p') && (let[1] == 'h') && (let[2] == 'o') && (let[3] == 'n') && (let[4] == 'e') && (spaces[(int) let[5]]))
			{
			    f = let + 5; i = 0;
			    while(f[i] && spaces[(int) f[i]])
			    {
				i++;
			    }
			    if (!f[i])
			    {
				return 0;
			    }
			    let = f + i;

			    if (!(j = setCondition(condPhone, let, spaces)))
			    {
				return 0;
			    }

			    f = let + j; i = 0;
			    while(f[i] && spaces[(int) f[i]])
			    {
				i++;
			    }
			    if (!f[i] || f[i] == ';')
			    {
				return 0;
			    }
			    let = f + i;

			    j = 0;
			    while (!spaces[(int) let[j]] && let[j] != ';')
			    {
				buff[j] = let[j];
				j++;
			    }
			    buff[j] = 0;
			    if (!setPhone(buff))
			    {
				return 0;
			    }

			    f = let + j; i = 0;
			    while(f[i] && spaces[(int) f[i]])
			    {
				i++;
			    }
			    if (!f[i])
			    {
				return 0;
			    }
			    if (f[i] == ';')
			    {
				commandOrder = 3;
				statement = CORRECT;
				return 1;
			    }
			    else
			    {
				return 0;
			    }
			}
			else
			{
			    return 0;
			}
		    }
		}
		else
		{
		    return 0;
		}
	    }
	}
    }
    else
    {
	return 0;
    }
}

int Command::setCondition(conditionType &current, const char *let, int *spaces)
{
    if (let[0] == '<')
    {
	if (let[1] == '>')
	{
	    current = NE;
	    return 2;
	}
	else
	{
	    if (let[1] == '=')
	    {
		current = LE;
		return 2;
	    }
	    else
	    {
		if (spaces[(int) let[1]])
		{
		    current = LT;
		    return 1;
		}
		else
		{
		    return 0;
		}
	    }
	}
    }
    else
    {
	if (let[0] == '>')
	{
	    if (let[1] == '=')
	    {
		current = GE;
		return 2;
	    }
	    else
	    {
		if (spaces[(int) let[1]])
		{
		    current = GT;
		    return 1;
		}
		else
		{
		    return 0;
		}
	    }
	}
	else
	{
	    if (let[0] == '=')
	    {
		if (spaces[(int) let[1]])
		{
		    current = EQ;
		    return 1;
		}
		else
		{
		    return 0;
		}
	    }
	    else
	    {
		if ((let[0] == 'l') && (let[1] == 'i') && (let[2] == 'k') && (let[3] == 'e') && (spaces[(int) let[4]]))
		{
		    current = LIKE;
		    return 4;
		}
		else
		{
		    return 0;
		}
	    }
	}
    }
    return 1;
}
