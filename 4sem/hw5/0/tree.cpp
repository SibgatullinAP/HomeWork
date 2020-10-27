#include "tree.h"
#include "treeNode.h"
#include "addons.h"

#include <math.h>

void Tree::delete_tree(TreeNode *tmp)
{
	if(tmp != nullptr)
	{
		delete_tree(tmp -> LeftChild);
		delete_tree(tmp -> RightChild);
	}
        if(tmp == Root)
        {
            Root = nullptr;
        }
	delete tmp;
}

int Tree::read (FILE *fp)
{
    delete_tree(Root);
    TreeNode *tmp = nullptr;
    tmp = new TreeNode ();
    if (tmp == nullptr)
    {
        return ERROR_CANNOT_ALLOCATE_MEMMORY;
    }
    int ret = tmp -> read (fp);
    if (ret < 0)
    {
        return delete tmp, ret;
    }
    if(ret > 0)
    {
        return delete tmp, NOT_ERROR_END_OF_INPUT;
    } 
	Root = Current = tmp;

	for (;;)
	{
        tmp = new TreeNode ();
        if (tmp == nullptr)
        {
           	return ERROR_CANNOT_ALLOCATE_MEMMORY;
        }
        ret = tmp -> read (fp);
        if (ret < 0)
        {
            return delete tmp, ret;
        }
        if(ret > 0)
        {
            return delete tmp, NOT_ERROR_END_OF_INPUT;
        }
        if(add(tmp, Root) == nullptr)
        {
        	return delete tmp, ret;
        }
        tmp = nullptr;
	}
	return 0;
}

void Tree::print(TreeNode *Root, int level, int max_print)
{
	max_print ++;
	Root -> print();

        level ++;
        if(max_print < MAX_PRINT && Root -> LeftChild)
	{
                for (int i = 0; i < level; i ++)
		{
                        printf("-");
		}
                print(Root -> LeftChild,  level, max_print);
	}
        if(max_print < MAX_PRINT && Root -> RightChild)
	{
                for (int i = 0; i < level; i ++)
		{
                        printf("-");
		}
                print(Root -> RightChild, level, max_print);
	}
}

TreeNode* Tree::add(TreeNode *tmp, TreeNode *Root)
{
	if( Root == nullptr)
	{	
		Root = tmp;
		return Root;
	}
	else
	{
		if((*tmp) < (*Root))
		{
			tmp = add(tmp,Root -> LeftChild);
			if(tmp != nullptr)
			{
				Root -> LeftChild = tmp;

			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			tmp = add(tmp,Root -> RightChild);
			if(tmp != nullptr)
			{
				Root -> RightChild = tmp;
			}
			else
			{
				return nullptr;
			}
		}
	}
	return Root;
}

TreeNode* Tree::get_root() const
{
	return Root;
}


TreeNode* Tree::go_root(TreeNode* root)
{
    return root = Root;
}

TreeNode* Tree::go_left(TreeNode* curr)
{
    return curr = curr -> LeftChild;
}

TreeNode* Tree::go_right(TreeNode* curr)
{
    return curr = curr -> RightChild;
}
TreeNode* Tree::del_sub_left()
{
	delete_tree(Current -> LeftChild);
	return Root;
}

TreeNode* Tree::del_sub_right()
{
	delete_tree(Current -> RightChild);
	return Root;
}



int Tree::func1(TreeNode* root)
{
    if(root == nullptr)
    {
        return 0;
    }
    if(root -> LeftChild == nullptr && root -> RightChild == nullptr)
    {
        return 1;
    }
    return func1(root -> LeftChild) + func1(root -> RightChild);
}

int Tree::func2(TreeNode* root)
{
    int lvalue = 0, rvalue = 0;

    if(root == nullptr)
    {
        return 0;
    }
    else
    {
        lvalue = func2(root -> LeftChild);
        rvalue = func2(root -> RightChild);
    }
    return lvalue > rvalue ? lvalue +1 : rvalue + 1;
}

int Tree::func3(TreeNode* root)
{
    int max = 0;
    int width = 0;
    int depth = func2(root);

    for (int i = 0; i < depth; i++)
    {
        width = subfunc3(Root, i);
        if(width > max)
        {
            max = width;
        }
    }
    return max;
}

 int Tree::subfunc3(TreeNode* root, int level)
 {
    if(root == nullptr)
    {
        return 0;
    }
    if(level == 1)
    {
        return 1;
    }
    else
    {
        if(level > 1)
        {
            return subfunc3(root -> LeftChild, level - 1) +
                   subfunc3(root -> RightChild, level - 1);
        }
    }
    return 0;
 }


int Tree::func4(TreeNode* root, int * answer)
{
    if( root == nullptr)
    {
        return 0;
    }

    int valueLeft = func4(root -> LeftChild, answer);
    int valueRight = func4(root -> RightChild, answer);
    if(abs(valueLeft - valueRight) > *answer)
    {
        *answer = abs(valueLeft - valueRight);
    } 
    if (root == Root)
    {
        valueRight = *answer;
        return valueRight;
    }
    return valueRight > valueLeft ? valueRight + 1 : valueLeft + 1;
}

int Tree::func5(TreeNode* root, int level)
{
    if(root == nullptr)
    {
        return 0;
    }
    if(level == 1)
    {
        return 1;
    }
    else
    {
        if(level > 1)
        {
            return subfunc3(root -> LeftChild, level - 1) +
                   subfunc3(root -> RightChild, level - 1);
        }
    }
    return 0;
}
