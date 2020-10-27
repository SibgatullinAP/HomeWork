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

	ListNode* max = current;

	current = current -> get_next();

	while(current)
	{
		if((*current) > (*max))
		{
			max = current;
			answer = 1;
		}
		else
		{
			if((*current) == (*max))
			{
				answer ++;
			}
		}
		
		current = current -> get_next();
	}
	return answer;
}
