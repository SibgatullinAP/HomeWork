#include "func.h"
#include "list.h"
#include "listNode.h"
#include "student.h"

int func (ListNode* current)
{
	int answer = 0;
	if(current == nullptr)
	{
		return 0;
	}

	ListNode* previous = current;
	current = current -> get_next();

	while(current)
	{
		if((*previous) < (*current))
		{
			answer ++;
		}
		previous = current;
		current = current -> get_next();
	}
	return answer;
}
