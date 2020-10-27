#ifndef QUEUENODE_H
#define QUEUENODE_H

#include "student.h"

template<class T>
class Queue;

template <class T>
class QueueNode: public T
{
    private:
	QueueNode* Next = nullptr;

    public:
        QueueNode() = default;
	~QueueNode() = default;
	friend class Queue<T>;
};

#endif // QUEUENODE_H
