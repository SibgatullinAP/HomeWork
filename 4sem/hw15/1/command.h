#ifndef COMMAND_H
#define COMMAND_H

#include "record.h"

class Command: public Record
{
    private:
		commandType command = CMD_NONE;
		int commandOrder = 0;
		operationType operation = OP_NONE;
		conditionType condName = COND_NONE;
		conditionType condPhone = COND_NONE;
		conditionType condGroup = COND_NONE;
		int selectOrder = 0;
		requestStatement statement = REQ_NONE;

    public:
		Command() = default;
		~Command() = default;


		const char* getType();
		const char* getCondition(conditionType& type);
		const char* getOperationString();
		const char* getArguments();

		int getCommandOrder()
		{
		    return commandOrder;
		}
		int getSelectOrder()
		{
		    return selectOrder;
		}

		conditionType getNameCondition();
		conditionType getPhoneCondition();
		conditionType getGroupCondition();

		operationType getOperation();

		commandType getCommand();
		int getOrder()
		{
			return commandOrder;
		}

		int parse(const char *str, int *space, char* buff2);
		int parseAddition(const char *str, int *space, char* buff2);
		int setCondition(conditionType &current, const char *let, int *spaces);

		bool print(int commandCounter, bool isDebugPrint, FILE* outFile = stdout);

};

#endif // COMMAND_H
