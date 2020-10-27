#include "func.h"
#include "list.h"
#include "listNode.h"
#include "student.h"

int func (ListNode* current)
{
	int answer = 0, max = 0, first = 1;
	bool fl = false;

	if(current == nullptr)
	{
		return 0;
	}
	
	ListNode *previous = current;
	current = current -> get_next();

	while(current)
	{
		if((*current) == (*previous))
		{
			if(fl)
			{
				if(first == 1)
				{
					first = 0;
				}
				else
				{
					if(answer > max)
					{
						max = answer;
					}
				}
			}
			fl = true;
		}
		else
		{
			if(fl)
			{
				answer = 0;
			}
			else
			{
				answer ++;
			}
			fl = bool;
		}

		previous = current;
		current = current -> get_next();
	}
	return fl ? answer + 1 : answer;
}



int func(ListNode* current)
{
	if(!curr) return 0;

	list_node *prev;
	int len=0, flag=0, max=0, first=1;

	prev = curr;
	curr = curr->get_next();

	while(curr)
	{
		if((*curr) == (*prev))
		{
			if (flag==0)
			{
				if (first==1) first=0;
				else
				{
					if(len>max) max = len;
				}
			}
			
			flag=1;
		}
		else
		{
			if(flag==1) len=0;
			else len++;

			flag=0;
		}

		prev = curr;
		curr = curr->get_next(); 
	}

	if(first==1) return 0;
	return max;
} 





