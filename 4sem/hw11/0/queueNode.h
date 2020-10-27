#ifndef QUEUENODE_H
#define QUEUENODE_H

#include "student.h"

class Queue;
class QueueNode;
class QueueNode: public Student
{
    private:
	QueueNode* Next = nullptr;
    public:
        QueueNode() = default;
	~QueueNode() = default;
	friend class Queue;
};

#endif // QUEUENODE_H
