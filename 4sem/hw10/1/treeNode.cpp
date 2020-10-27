#include "treeNode.h"

TreeNode::TreeNode(int size)
{
	if(size == 0)
	{
		Values = nullptr;
		Children = nullptr;
	}
	else
	{
		Values = new Student* [size];
		Children = new TreeNode* [size + 1];
		for (int i = 0; i < size; ++i)
		{
			Values[i] = nullptr;
		}
		for (int i = 0; i < size + 1; ++i)
		{
			Children[i] = nullptr;
		}
	}
	Size = 0;
}

void TreeNode::deleteNode()
{
	for (int i = 0; i < Size; ++i)
	{
		delete Values[i];
	}
	if (Size != 0)
	{
		delete [] Values;
		delete [] Children;
	}

	Size = 0;
}

void TreeNode::clear(int n)
{
	for (int i = 0; i < n; ++i)
	{
		Values[i] = nullptr;
		Children[i + 1] = nullptr;
	}
	Size = n;
}

void TreeNode::fullClear()
{
	int i = 0;
	for (i = 0; i < Size; ++i)
	{
		Values[i] = nullptr;
		Children[i] = nullptr;
	}
	Children[i] = nullptr;
	Size = 0;
}

int TreeNode::findInsert(Student *src)
{
	int left = 0, right = Size, center = 0;
	while(left != right)
	{
		center = (left + right) / 2.0;
		if ((*src) > (*Values[center]))
		{
			left = center + 1;
		}
		else
		{
			right = center;
		}
	}

	return left;
}

void TreeNode::print(int order, FILE *out)
{
	if(Values == nullptr)
	{
		return;
	}
	int printLimit = (2 * order < MAX_LEN_PRINT ? 2 * order : MAX_LEN_PRINT);
	for (int i = 0; i < printLimit; ++i)
	{
		if (Values != nullptr && Values[i] != nullptr)
		{
			Values[i]->print(out);
		}
		else
		{
			fprintf(out, "(\x1b[1;34mnull: 0\x1b[0m)");
		}
		fprintf(out, " <-> ");
	}
	if (Children != nullptr && Children[0] == nullptr)
	{
		fprintf(out, "END");
	}
	fprintf(out, "\n");
}
