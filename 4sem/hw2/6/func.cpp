#include "func.h"
#include "list.h"
#include "listNode.h"
#include "student.h"

int func (ListNode* current)
{
	int answer = 1;

	if(current == nullptr)
	{
		return 0;
	}
	
	ListNode *previous = current;
	current = current -> get_next();

	int lengthOfIncreasing = 0;

	while(current)
	{
		if((*current) > (*previous))
		{
			lengthOfIncreasing ++;
		}
		else
		{
			if (lengthOfIncreasing > answer)
			{
				answer = lengthOfIncreasing;
			}
			if (lengthOfIncreasing != 0)
			{
				lengthOfIncreasing = 1;
			}
		}

		previous = current;
		current = current -> get_next();
	}
	return answer > lengthOfIncreasing ? answer : lengthOfIncreasing;
}
