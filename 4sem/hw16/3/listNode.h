#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "command.h"

class List;
class DataBase;

class ListNode: public Record
{
	private:
                ListNode  *Next = nullptr;
		ListNode  *Previous = nullptr;
		ListNode *NextSelect = nullptr;

	public:
		friend class List;
		friend class DataBase;

		ListNode () = default;
		~ListNode() = default;

		ListNode  *getNext() const {return Next;}
		ListNode  *getPrev() const{return Previous;}
		void setNext(ListNode  *next){this -> Next = next;}
		void setPrev (ListNode  *prev){this -> Previous = prev;}

		int operator== (ListNode &x)
		{
		    if(((this->getGroup()) == (x.getGroup()))
		        && ((this->getPhone()) == (x.getPhone()))
		        && ((strcmp(this->getName(), x.getName())) == 0))
		    {
			return true;
		    }
		    return false;
		}

		bool check(Command &condition)
		{
		    bool nameFlag = false;
		    bool phoneFlag = false;
		    bool groupFlag = false;

		    switch (condition.getNameCondition())
		    {
		        case EQ:
			    if(strcmp(this->getName(), condition.getName()) == 0)
			    {
				nameFlag = true;
			    }
			    break;

		        case NE:
			    if(strcmp(this->getName(), condition.getName()) != 0)
			    {
				nameFlag = true;
			    }
			    break;

		        case LT:
			    if(strcmp(this->getName(), condition.getName()) < 0)
			    {
				nameFlag = true;
			    }
			    break;

		        case GT:
			    if(strcmp(this->getName(), condition.getName()) > 0)
			    {
				nameFlag = true;
			    }
			    break;

		        case LE:
			    if(strcmp(this->getName(), condition.getName()) <= 0)
			    {
				nameFlag = true;
			    }
			    break;

		        case GE:
			    if(strcmp(this->getName(), condition.getName()) >= 0)
			    {
				nameFlag = true;
			    }
			    break;

		        case LIKE:
			    if(like(this->getName(), condition.getName()))
			    {
				nameFlag = true;
			    }
			    break;
		        case COND_NONE: break;
		    }

		    switch (condition.getPhoneCondition())
		    {
		        case EQ:
			    if(this->getPhone() == condition.getPhone())
			    {
				phoneFlag = true;
			    }
			    break;

		        case NE:
			    if(this->getPhone() != condition.getPhone())
			    {
				phoneFlag = true;
			    }
			    break;

		        case LT:
			    if(this->getPhone() < condition.getPhone())
			    {
				phoneFlag = true;
			    }
			    break;

		        case GT:
			    if(this->getPhone() > condition.getPhone())
			    {
				phoneFlag = true;
			    }
			    break;

		        case LE:
			    if(this->getPhone() <= condition.getPhone())
			    {
				phoneFlag = true;
			    }
			    break;

		        case GE:
			    if(this->getPhone() >= condition.getPhone())
			    {
				phoneFlag = true;
			    }
			    break;

		        case LIKE: break;
		        case COND_NONE: break;
		    }

		    switch (condition.getGroupCondition())
		    {
		        case EQ:
			    if(this->getGroup() == condition.getGroup())
			    {
				groupFlag = true;
			    }
			    break;

		        case NE:
			    if(this->getGroup() != condition.getGroup())
			    {
				groupFlag = true;
			    }
			    break;

		        case LT:
			    if(this->getGroup() < condition.getGroup())
			    {
				groupFlag = true;
			    }
			    break;

		        case GT:
			    if(this->getGroup() > condition.getGroup())
			    {
				groupFlag = true;
			    }
			    break;

		        case LE:
			    if(this->getGroup() <= condition.getGroup())
			    {
				groupFlag = true;
			    }
			    break;

		        case GE:
			    if(this->getGroup() >= condition.getGroup())
			    {
				groupFlag = true;
			    }
			    break;

		        case LIKE: break;
		        case COND_NONE: break;
		    }

		    bool result = false;

		    switch (condition.getOperation())
		    {
		        case OR:
			    if(condition.getNameCondition() != COND_NONE && condition.getPhoneCondition() != COND_NONE)
			    {
				result = nameFlag || phoneFlag;
			    }
			    if(condition.getNameCondition() != COND_NONE && condition.getGroupCondition() != COND_NONE)
			    {
				result = nameFlag || groupFlag;
			    }
			    if(condition.getGroupCondition() != COND_NONE && condition.getPhoneCondition() != COND_NONE)
			    {
				result = groupFlag || phoneFlag;
			    }
			    break;

		        case AND:
			    if(condition.getNameCondition() != COND_NONE && condition.getPhoneCondition() != COND_NONE)
			    {
				result = nameFlag && phoneFlag;
			    }
			    if(condition.getNameCondition() != COND_NONE && condition.getGroupCondition() != COND_NONE)
			    {
				result = nameFlag && groupFlag;
			    }
			    if(condition.getGroupCondition() != COND_NONE && condition.getPhoneCondition() != COND_NONE)
			    {
				result = groupFlag && phoneFlag;
			    }
			    break;

		        case OP_NONE:
			    if(condition.getNameCondition() != COND_NONE)
			    {
				result = nameFlag;
			    }
			    if(condition.getPhoneCondition() != COND_NONE)
			    {
				result = phoneFlag;
			    }
			    if(condition.getGroupCondition() != COND_NONE)
			    {
				result = groupFlag;
			    }
			    break;
		    }
		    return result;
		}

		bool like(const char * string,const char * reference)
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
};

#endif
