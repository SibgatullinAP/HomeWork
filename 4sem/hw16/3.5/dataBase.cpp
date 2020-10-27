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
    NameSearch->print(NameSearch->getRoot());
    printf("\n");
    //GroupSearch->print(GroupSearch->getRoot());
    //printf("\n");
    PhoneSearch->print();
}

int DataBase::insertingRequest(char* name, int phone, int group)
{
    ListNode *tmp;
    tmp = new ListNode;
    if(!(tmp->setName(name) && tmp->setPhone(phone) && tmp->setGroup(group)))
    {
	delete tmp;
	return false;
    }

    if(NameSearch->insert(tmp))
    {
	PhoneSearch->insert(tmp);
	//GroupSearch->insert(tmp);
	Container->insert(tmp);
	return true;
    }

    delete tmp;
    return true;
}


int DataBase::deletingRequest(Command &current)
{
    ListNode * select = nullptr;
    if(current.getCommandOrder() == 0)
    {
	Container->~List();
	NameSearch->~RedBlackTreeName();
	PhoneSearch->~Hash();
	return 1;
    }
    else
    {

	switch (current.getOperation())
	{
	    case COND_NONE:
	        /*int flagData = 0; 0 - ничего 1- имя 2- телефон - 3 группа
		int flag = 1;
		if(current.getPhoneCondition() == EQ)
		{
		    select = Container->search(current);
		    select = PhoneSearch->search(current, flagData, flag);
		}
		else if(current.getNameCondition() == EQ)
		{
		    select = NameSearch->search(current, flagData, flag);
		}
		else
		{*/
	            select = Container->search(current);
		//}
	        break;

	    case OR:
	        /*if(current.getNameCondition() && current.getPhoneCondition() == EQ)
		{
		    select = NameSearch->search(current);
		    while(select)
		    {
			select->print();
			select = select->NextSelect;
		    }
		    select = PhoneSearch->search(current);
		}
		else
		{*/
	            select = Container->search(current);
		//}
	        break;

	    case AND:
	        /*int flagData = 0;
		int flag = 1;
		if(current.getPhoneCondition() == EQ)
		{
		    if(current.getNameCondition() == COND_NONE)
		    {
			flagData = 3;
			select = PhoneSearch(current,flagData, flag);
		    }
		    else
		    {
			flagData = 1;
			select = PhoneSearch(current,flagData, flag);
		    }
		}
		else if(current.getNameCondition() == EQ)
		{
		    if(current.getPhoneCondition() == COND_NONE)
		    {
			flagData = 3;
			select = PhoneSearch(current,flagData, flag);
		    }
		    else
		    {
			flagData = 2;
			select = PhoneSearch(current,flagData, flag);
		    }
		}
		else
		{*/
	            select = Container->search(current);
		//}
	        break;
	}

	ListNode *tmp = nullptr;
	ListNode *buff = nullptr;
	while(select)
	{
	    tmp = select->NextSelect;
	    buff = Container->moveFromList(select);
	    delete buff;

	    select = tmp;
	}
	return 1;

	/*ListNode *tmp = nullptr, *i = nullptr;
	i = Container->Head;
	while (i)
	{
	    if(command.check(i))
	    {
		//GroupSearch->deleteValue(i);
		NameSearch->deleteValue(i);
		PhoneSearch->deleteValue(i);

		tmp = i->Next;
		if(i == Container->Head)
		{
		    Container->Head = Container->Head->Next;
		    if(Container->Head != nullptr)
		    {
			Container->Head->Previous = nullptr;
		    }
		    delete i;
		}
		else
		{
		    i->Previous->Next = i->Next;
		    if(i->Next != nullptr)
		    {
			i->Next->Previous = i->Previous;
		    }
		    delete i;
		}
		i = tmp;
	    }
	    else
	    {
		i = i->Next;
	    }
	}
	return true;*/
    }
    return false;
}

int DataBase::selectingRequest(Command &current, FILE* outFile)
{
    ListNode * select = nullptr;
    if(current.getSelectOrder() == 100)
    {
	print(outFile);
	return 1;
    }
    else
    {
	switch (current.getOperation())
	{
	    case COND_NONE:
	        /*int flagData = 0; 0 - ничего 1- имя 2- телефон - 3 группа
		int flag = 1;
		if(current.getPhoneCondition() == EQ)
		{
		    select = Container->search(current);
		    select = PhoneSearch->search(current, flagData, flag);
		}
		else if(current.getNameCondition() == EQ)
		{
		    select = NameSearch->search(current, flagData, flag);
		}
		else
		{*/
	            select = Container->search(current);
		//}
	        break;

	    case OR:
	        /*if(current.getNameCondition() && current.getPhoneCondition() == EQ)
		{
		    select = NameSearch->search(current);
		    while(select)
		    {
			select->print();
			select = select->NextSelect;
		    }
		    select = PhoneSearch->search(current);
		}
		else
		{*/
	            select = Container->search(current);
		//}
	        break;

	    case AND:
	        /*int flagData = 0;
		int flag = 1;
		if(current.getPhoneCondition() == EQ)
		{
		    if(current.getNameCondition() == COND_NONE)
		    {
			flagData = 3;
			select = PhoneSearch(current,flagData, flag);
		    }
		    else
		    {
			flagData = 1;
			select = PhoneSearch(current,flagData, flag);
		    }
		}
		else if(current.getNameCondition() == EQ)
		{
		    if(current.getPhoneCondition() == COND_NONE)
		    {
			flagData = 3;
			select = PhoneSearch(current,flagData, flag);
		    }
		    else
		    {
			flagData = 2;
			select = PhoneSearch(current,flagData, flag);
		    }
		}
		else
		{*/
	            select = Container->search(current);
		//}
	        break;
	}

	while(select)
	{
	    select->print();
	    select = select->NextSelect;
	}
	return 1;

	/*ListNode *i = nullptr;
	for(i = Container->Head; i; i = i->Next)
	{
	    if(i->check(current))
	    {
		i->print(outFile);
	    }
	}
	return true;*/
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
	        case END_OF_WORKING: return;
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
        case QUIT: return END_OF_WORKING;
        case STOP: return END_OF_WORKING;
        case INSERT: return insertingRequest(current.getName(), current.getPhone(), current.getGroup());
        case DELETE: return deletingRequest(current);
        case SELECT: return selectingRequest(current, outputResult);
    }
    return 1;
}
