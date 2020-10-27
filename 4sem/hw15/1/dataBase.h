#ifndef DATABASE_H
#define DATABASE_H

#include "list.h"

template <typename T>
void run(List<T> &dataBase, FILE* inputRequest = stdin, FILE *outputResult = stdout)
{
    char buff1[BUFF_LEN], buff2[BUFF_LEN];
    char espace[ESCAPE_LEN] = {'\n', '\t',' '};
    int space[SPACE_LEN] = {0};
    for (int i = 0; i < ESCAPE_LEN; ++i)
    {
	    space[int(espace[i])] = 1;
    }

    int ret = 0;
    while (fgets(buff1, BUFF_LEN, inputRequest))
    {
	Command current;
	if(current.parse(buff1, space, buff2) == 0)
	{
	    fprintf(outputResult, "Warning! Incorrect request!\n");
	}
	if((ret = requestExecute(dataBase, current, outputResult)) < 0)
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

template <typename T>
int requestExecute(List<T> &dataBase, Command &current, FILE* outputResult )
{
    switch (current.getCommand())
    {
        case CMD_NONE: return EMPTY_REQUEST;
        case QUIT: return END_OF_WORKING;
        case STOP: return END_OF_WORKING;
        case INSERT: return dataBase.insertingRequest(current.getName(), current.getPhone(), current.getGroup());
        case DELETE:
        {
	    if(current.getCommandOrder() == 0)
	    {
		dataBase.deleteList();
		return 1;
	    }
	    else
	    {
		return dataBase.deletingRequest(current);
	    }
        }
        case SELECT:
        {
	    if(current.getSelectOrder() == 63)
	    {
		dataBase.print();
		return 1;
	    }
	    else
	    {
		return dataBase.selectingRequest(current);
	    }
        }
    }
    fprintf(outputResult, ":)\n");
    return 1;
}

#endif // DATABASE_H
