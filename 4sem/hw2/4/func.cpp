#include "func.h"
#include "list.h"
#include "listNode.h"
#include "student.h"

int func (ListNode* head)
{
	int answer = 0;
	ListNode *current, *previous, *next;

	if(head == nullptr)
	{
		return 0;
	}
	
	previous = head;
	next = head -> get_next();
	if(next == nullptr)
	{
		return 0;
	}
	current = next;

	current = current -> get_next();
	while(next)
	{
		if((*current) > (*previous) && (*current) > (*next))
		{
			answer ++;
		}

		previous = current;
		current = next;
		next = next -> get_next();
	}
	return answer;
}
