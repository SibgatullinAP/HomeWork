#ifndef REDBLACKTREE_NODE_H
#define REDBLACKTREE_NODE_H
#include "defenitions.h"
#include "list_node.h"

template <class F>
class RBTree;

template <class F>
class RBTree_node: public F
{
private:
	palitra color = RED;
	RBTree_node *left = nullptr;
	RBTree_node *right = nullptr;
	RBTree_node *parent = nullptr;
	RBTree_node *prev = nullptr;
	RBTree_node *next = nullptr;
	friend class RBTree <F>;
	friend class database;
public:
	RBTree_node() = default;
	~RBTree_node() = default;


	list_node *create_list(list_node *nhead = nullptr)
	{

		nhead = this->get_list(nhead);
		RBTree_node <F> *run = this->next;
		while (run)
		{
			nhead = run->get_list(nhead);
			run = run->next;
		}
		return nhead;
	}
};

#endif // REDBLACKTREE_NODE_H
