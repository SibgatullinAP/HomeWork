#ifndef QUEUE_H
#define QUEUE_H

#include "queueNode.h"

template <class T>
class Queue
{
    private:
	QueueNode <T> *Front = nullptr;
	QueueNode <T> *Rear = nullptr;

        enum MENU_PROPERTIES
        {
            MENU = 'm',
            EXIT = 'e',
	    PRINT_QUEUE = 'p',
	    PRINT_FRONT = 'f',
            WORK_WITH_STUDENT = 'w',
            DEQUEUE = 'd',
            ENQUEUE = 'a',
            DELETE_QUEUE = 'x'
        };

    public:
	//
	Queue() = default;
	~Queue()
	{
	    deleteQueue();
	    Front = Rear = nullptr;
	}

	//
	void deleteQueue()
	{
	    if(Front == nullptr)
	    {
		delete Front;
		delete Rear;
		return;
	    }

	    QueueNode <T> *tmp = nullptr;
	    while (Front)
	    {
		tmp = Front;
		Front = Front->Next;
		delete tmp;
	    }
	    delete Front;
	    Front = nullptr;
	    Rear = nullptr;
	}

	void print(FILE* out = stdout)
	{
	    QueueNode <T> *tmp = Front;
	    if(isEmpty())
	    {
		return;
	    }
	    for(int i = 0; tmp && i < MAX_PRINT_QUEUE; i++)
	    {
		tmp->print(out);
		tmp = tmp->Next;
	    }
	    if(tmp != nullptr)
	    {
		fprintf(out," \x1b[1;33m ... \x1b[0m ");
	    }
	    fprintf(out,"\n");
	}

	int read(FILE *fp, int size_queue)
	{
	    deleteQueue();

	    QueueNode <T> *tmp;
	    tmp = new QueueNode<T> ;
	    if (tmp == nullptr)
	    {
		return ERROR_CANNOT_ALLOCATE_MEMMORY;
	    }

	    int ret = tmp->read(fp);
	    if (ret < 0)
	    {
		return delete tmp, ret;
	    }

	    Front = Rear = tmp;
	    int i = 1;
	    for (;;)
	    {
		i++;
		if(i > size_queue)
		{
		    return 0;
		}

		tmp = new QueueNode <T>;
		if (tmp == nullptr)
		{
		    return ERROR_CANNOT_ALLOCATE_MEMMORY;
		}

		ret = tmp->read(fp);
		if (ret < 0)
		{
		    return delete tmp, ret;
		}

		Rear->Next = tmp;
		Rear = tmp;
		Rear->Next = nullptr;
		tmp = nullptr;
	    }
	    return 0;
	}

	//
	bool isEmpty()
	{
	    if(Front != nullptr)
	    {
		return false;
	    }
	    printf("Queue is empty!\n");
	    return true;
	}

	void enQueue()
	{
	    if(!isEmpty())
	    {
		QueueNode <T> *tmp = new QueueNode <T>;
		tmp->change_student();
		Rear->Next = tmp;
		tmp->Next = nullptr;
		Rear = tmp;
	    }
	    else
	    {
		QueueNode <T> *tmp = new QueueNode <T>;
		tmp->change_student();
		tmp->Next = nullptr;
		Front = Rear = tmp;
	    }
	}

	void deQueue()
	{
	   if (!isEmpty())
	   {
	       if(Rear == Front)
	       {
		   delete Rear;
		   Rear = Front = nullptr;
	       }
	       else
	       {
		   QueueNode <T> *tmp = Front;
		   Front = tmp->Next;
		   delete tmp;
	       }
	   }
	}

	//
        int operator< (const Queue& x)
        {
	    return (*Front) < (*x.Front);
        }

        int operator> (const Queue& x)
        {
	    return (*Front) > (*x.Front);
	}

	//
	void menu()
	{
	    clear();
	    print_menu();

	    MENU_PROPERTIES key;
	    char buff[LEN];
	    for(;;)
	    {
		printf("Enter your choise: ");
		if(!fgets(buff, LEN, stdin)) return;

		key = MENU_PROPERTIES(buff[0]);
		switch(key)
		{
		    case MENU:
			clear();
			print_menu();
			break;

		    case EXIT:
			return;

		    case PRINT_QUEUE:
			clear();
			print();
			printf("\n");
			break;

		    case PRINT_FRONT:
			clear();
			if(!isEmpty())
			{
			    Front->print();
			}
			printf("\n");
			break;

		    case WORK_WITH_STUDENT:
			clear();
			if(!isEmpty()) Front->menu();
			break;

		    case DEQUEUE:
			clear();
			deQueue();
			break;

		    case ENQUEUE:
			clear();
			enQueue();
			break;

		    case DELETE_QUEUE:
			clear();
			deleteQueue();
			return;

		    default:
			clear();
			printf("\nFor coming back to menu press - \x1b[1;33mm\x1b[0m!\n");
			break;
		}
	    }
	}

	void print_menu()
	{
	    printf(" -------------------------\n");
	    printf("|     ~Menu for Queue~    |\n");
	    printf("|      \x1b[1;33mm\x1b[0m - Show Menu      |\n");
	    printf("|      \x1b[1;33me\x1b[0m - Exit Menu      |\n");
	    printf("|     \x1b[1;33mp\x1b[0m - Print Queue     |\n");
	    printf("|     \x1b[1;33mf\x1b[0m - Print Front     |\n");
	    printf("|       \x1b[1;33md\x1b[0m - Dequeue       |\n");
	    printf("|       \x1b[1;33ma\x1b[0m - Add Rear      |\n");
	    printf("|  \x1b[1;33mw\x1b[0m - Work with Student  |\n");
	    printf("|    \x1b[1;33mx\x1b[0m - Delete Queue     |\n");
	    printf(" -------------------------\n");
	}
};

#endif // QUEUE_H
