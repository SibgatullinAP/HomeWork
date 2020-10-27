#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "command.h"

template <class T>
class List;

template <class T>
class ListNode: public T
{
	private:
                ListNode <T> *Next = nullptr;
		ListNode <T> *Previous = nullptr;
	public:
		friend class List <T>;

		ListNode () = default;
		~ListNode() = default;

		ListNode <T> *getNext() const {return Next;}
		ListNode <T> *getPrev() const{return Previous;}
		void setNext(ListNode <T> *next){this -> Next = next;}
		void setPrev (ListNode <T> *prev){this -> Previous = prev;}

		int operator== (ListNode<T> &x)
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

		        case LIKE: break;
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

};

#endif
