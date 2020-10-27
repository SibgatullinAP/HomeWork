#include "dataBase.h"

int DataBase::read(FILE *inFile)
{
    char buff[BUFF_LEN];
    char name[BUFF_LEN];
    int phone = 0, group = 0;
    while (fgets(buff, BUFF_LEN, inFile))
    {
	if(sscanf(buff,"%s %d %d", name, &phone, &group) != 3)
	{
	    return ERROR_CANNOT_READ_INPUT_FILE;
	}
	if(!insertingRequest(name, phone, group))
	{
	    return ERROR_CANNOT_ALLOCATE_MEMMORY_TO_READ_NAME;
	}
    }
    return 0;
}

void DataBase::print(FILE * outFile)
{
    Container->print(outFile);
    printf("\n");
}

int DataBase::insertingRequest(char* name, int phone, int group)
{
    ListNode *tmp;
    tmp = new ListNode;
    if(!(tmp->setName(name) && tmp->setPhone(phone) && tmp->setGroup(group)))
    {
	delete tmp;
	return 0;
    }

    if(NameSearch->insert(tmp))
    {
	PhoneSearch->insert(tmp);
	Container->insert(tmp);
	return 1;
    }

    delete tmp;
    return 1;
}


int DataBase::deletingRequest(Command &current)
{
    int flagData = 0;
    int flag = 1;
    ListNode * select = nullptr;
    if(current.getCommandOrder() == 0)
    {
	NameSearch->deleteRedBlackTreeName(NameSearch->getRoot());
	PhoneSearch->deleteHash();
	Container->~List();
	return 1;
    }
    else
    {

	switch (current.getOperation())
	{
	    case OP_NONE:
	    {
	        flagData = 0;
		flag = 1;
		if(current.getPhoneCondition() == EQ)
		{
		    select = PhoneSearch->search(current, flagData, flag, select);
		}
		else if(current.getNameCondition() == EQ)
		{
		    select = NameSearch->search(current, flagData, flag, select);
		}
		else
		{
		    select = Container->search(current);
		}
		break;
	    }

	    case OR:
	    {
	        flagData = 0;
		flag = 0;
		if(current.getNameCondition() && current.getPhoneCondition() == EQ)
		{
		    select = NameSearch->search(current, flagData, flag, select);
		    while(select)
		    {
			select->print();
			select = select->NextSelect;
		    }
		    select = PhoneSearch->search(current, flagData, flag, select);
		}
		else
		{
	            select = Container->search(current);
		}
	        break;
	    }
	    case AND:
	    {/*
	        flagData = 0;
		flag = 1;
		if(current.getPhoneCondition() == EQ)
		{
		    if(current.getNameCondition() == COND_NONE)
		    {
			flagData = 3;
			select = PhoneSearch->search(current,flagData, flag, select);
		    }
		    else
		    {
			flagData = 1;
			select = PhoneSearch->search(current,flagData, flag, select);
		    }
		}
		else if(current.getNameCondition() == EQ)
		{
		    if(current.getPhoneCondition() == COND_NONE)
		    {
			flagData = 3;
			select = PhoneSearch->search(current,flagData, flag, select);
		    }
		    else
		    {
			flagData = 2;
			select = PhoneSearch->search(current,flagData, flag, select);
		    }
		}
		else
		{*/
	            select = Container->search(current);
		//}
	        break;
	    }

	}

	ListNode *tmp = nullptr;
	ListNode *buff = nullptr;
	while(select)
	{
	    tmp = select->NextSelect;

	    NameSearch->deleteValue(select);
	    PhoneSearch->deleteValue(select);
	    buff = Container->moveFromList(select);
	    delete buff;

	    select = tmp;
	}
	return 1;
    }
    return 0;
}

int DataBase::selectingRequest(Command &current, FILE* outFile)
{
    ListNode * select = nullptr;
    int flagData = 0;
    int flag = 1;
    if(current.getSelectOrder() == 100)
    {
	print(outFile);
	return 1;
    }
    else
    {
	switch (current.getOperation())
	{
	    case OP_NONE:
	    {
	        flagData = 0;
		flag = 1;
		if(current.getPhoneCondition() == EQ)
		{
		    select = PhoneSearch->search(current, flagData, flag, select);
		}
		else if(current.getNameCondition() == EQ)
		{
		    select = NameSearch->search(current, flagData, flag, select);
		}
		else
		{
	            select = Container->search(current);
		}
		break;
	    }
	    case OR:
	    {
	        if(current.getNameCondition() && current.getPhoneCondition() == EQ)
		{
		    select = NameSearch->search(current, flagData, flag, select);
		    while(select)
		    {
			select->print();
			select = select->NextSelect;
		    }
		    select = PhoneSearch->search(current, flagData, flag, select);		}
		else
		{
	            select = Container->search(current);
		}
	        break;
	    }
	    case AND:
	    {
		flagData = 0;
		flag = 1;
		if(current.getPhoneCondition() == EQ)
		{
		    if(current.getNameCondition() == COND_NONE)
		    {
			flagData = 3;
			select = PhoneSearch->search(current,flagData, flag, select);
		    }
		    else
		    {
			flagData = 1;
			select = PhoneSearch->search(current,flagData, flag, select);
		    }
		}
		else if(current.getNameCondition() == EQ)
		{
		    if(current.getPhoneCondition() == COND_NONE)
		    {
			flagData = 3;
			select = PhoneSearch->search(current,flagData, flag, select);
		    }
		    else
		    {
			flagData = 2;
			select = PhoneSearch->search(current,flagData, flag, select);
		    }
		}
		else
		{
	            select = Container->search(current);
		}
	        break;
	    }
	}

	while(select)
	{
	    select->print();
	    select = select->NextSelect;
	}
	return true;
    }
    return false;
}

int DataBase::selectingRequest(Command &current, int fd)
{
    ListNode * select = nullptr;
    int flagData = 0;
    int flag = 1;
    if(current.getSelectOrder() == 100)
    {
	select = Container->Head;
	while(select)
	{
	    select->print(fd);
	    select = select->Next;
	}
    }
    else
    {
	switch (current.getOperation())
	{
	    case OP_NONE:
	    {
		flagData = 0;
		flag = 1;
		if(current.getPhoneCondition() == EQ)
		{
		    select = PhoneSearch->search(current, flagData, flag, select);
		}
		else if(current.getNameCondition() == EQ)
		{
		    select = NameSearch->search(current, flagData, flag, select);
		}
		else
		{
		    select = Container->search(current);
		}
		break;
	    }
	    case OR:
	    {
		if(current.getNameCondition() && current.getPhoneCondition() == EQ)
		{
		    select = NameSearch->search(current, flagData, flag, select);
		    while(select)
		    {
			select->print();
			select = select->NextSelect;
		    }
		    select = PhoneSearch->search(current, flagData, flag, select);
		}
		else
		{
		    select = Container->search(current);
		}
		break;
	    }
	    case AND:
	    {
		/*flagData = 0;
		flag = 1;
		if(current.getPhoneCondition() == EQ)
		{
		    if(current.getNameCondition() == COND_NONE)
		    {
			flagData = 3;
			select = PhoneSearch->search(current,flagData, flag, select);
		    }
		    else
		    {
			flagData = 1;
			select = PhoneSearch->search(current,flagData, flag, select);
		    }
		}
		else if(current.getNameCondition() == EQ)
		{
		    if(current.getPhoneCondition() == COND_NONE)
		    {
			flagData = 3;
			select = PhoneSearch->search(current,flagData, flag, select);
		    }
		    else
		    {
			flagData = 2;
			select = PhoneSearch->search(current,flagData, flag, select);
		    }
		}
		else
		{*/
		    select = Container->search(current);
		//}
		break;
	    }
	}

	while(select)
	{
	    select->print(fd);
	    select = select->NextSelect;
	}
	return 1;
    }
    return 0;
}

void DataBase::run(FILE* inputRequest, FILE *outputResult)
{
    char buff1[BUFF_LEN], buff2[BUFF_LEN];
    char espace[ESCAPE_LEN] = {'\n', '\t',' '};
    int space[SPACE_LEN] = {0};
    for (int i = 0; i < ESCAPE_LEN; ++i)
    {
	    space[int(espace[i])] = 1;
    }

    int ret = 0;
    Command current;
    while (fgets(buff1, BUFF_LEN, inputRequest))
    {
	current.clear();
	if(current.parse(buff1, space, buff2) == 0)
	{
	    fprintf(outputResult, "Warning! Incorrect request!\n");
	}
	//current.print(0, true);
	if((ret = requestExecute(current, outputResult)) < 0)
	{
	    switch (ret)
	    {
		case EMPTY_REQUEST: break;
		case END_OF_WORKING_QUIT: return;
		case END_OF_WORKING_STOP: return;
	        default: break;
	    }
	}
    }
}

int DataBase::requestExecute(Command & current, FILE* outputResult )
{
    switch (current.getCommand())
    {
	case CMD_NONE: return EMPTY_REQUEST;
	case QUIT: return END_OF_WORKING_QUIT;
	case STOP: return END_OF_WORKING_STOP;
        case INSERT: return insertingRequest(current.getName(), current.getPhone(), current.getGroup());
        case DELETE: return deletingRequest(current);
        case SELECT: return selectingRequest(current, outputResult);
    }
    return 1;
}


int DataBase::requestExecute(Command & current, int fd)
{
    switch (current.getCommand())
    {
	case CMD_NONE: return EMPTY_REQUEST;
	case QUIT: return END_OF_WORKING_QUIT;
	case STOP: return END_OF_WORKING_STOP;
	case INSERT: return insertingRequest(current.getName(), current.getPhone(), current.getGroup());
	case DELETE: return deletingRequest(current);
	case SELECT: return selectingRequest(current, fd);
    }
    return 1;
}
