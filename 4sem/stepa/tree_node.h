#ifndef TREE_NODE_H
#define TREE_NODE_H

class list_node;
class tree_node;
class tree;

enum color_t{
	RED, BLACK
};

class tree_node {
	private:
		list_node *data = nullptr;
	    tree_node *left = nullptr;
		tree_node *right = nullptr;
		tree_node *next = nullptr;
		color_t color = RED;

	public:
		tree_node() = default;
		~tree_node() = default;

		list_node * getData() const { return data; }
		tree_node * getLeft() const { return left; }
		tree_node * Right() const { return right; }
		tree_node * getNext() const { return next; }

	friend class tree;
};

#endif // TREE_NODE_H
