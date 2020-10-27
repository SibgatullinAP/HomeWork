#ifndef QUEUE_H
#define QUEUE_H

#include "queueNode.h"

class Queue
{
    private:
        QueueNode* Front = nullptr;
        QueueNode* Rear = nullptr;

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
	Queue() = default;
	~Queue();

	void deleteQueue();
	void print (FILE* out = stdout);
	int read(FILE *fp, int size_queue);

	bool isEmpty();
	void enQueue();
	void deQueue();
        int operator< (const Queue& x)
        {
	    return (*Front) < (*x.Front);
        }
        int operator> (const Queue& x)
        {
	    return (*Front) > (*x.Front);
	}
	void menu();
	void print_menu();
};

#endif // QUEUE_H
