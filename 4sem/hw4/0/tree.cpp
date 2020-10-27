#include "tree.h"
#include "treeNode.h"
#include "addons.h"

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
		for (int i = 0; i < level; ++i)
		{
                        printf("%c",' ');
		}
                print(Root -> LeftChild, ++level, max_print);
	}
        if(max_print < MAX_PRINT && Root -> RightChild)
	{
		for (int i = 0; i < level; ++i)
		{
                        printf("%c", ' ');
		}
                print(Root -> RightChild, ++level, max_print);
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

int Tree::func5(TreeNode* root)
{
    int answer = 0;
    if((root -> LeftChild == nullptr && root -> RightChild != nullptr)
       || (root -> LeftChild != nullptr && root -> RightChild == nullptr))
    {
        answer++;
    }
    if(root -> LeftChild != nullptr)
    {
        answer += func5(root -> LeftChild);
    }
    if(root -> RightChild != nullptr)
    {
        answer += func5(root -> RightChild);
    }
    return answer;
}













