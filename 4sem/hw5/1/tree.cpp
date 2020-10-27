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

TreeNode* Tree::add_left(TreeNode *tmp, TreeNode *root)
{
    return add(tmp, root -> LeftChild);
}

TreeNode* Tree::add_right(TreeNode *tmp, TreeNode *root)
{
    return add(tmp, root -> RightChild);
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


int Tree::func1(TreeNode* root, int k)
{
    int answer = 0;
    subfunc1(root, k, answer);
    return answer;
}

int Tree::subfunc1(TreeNode* root, int k, int &answer)
{
    int itterator = 1;

    if(root == nullptr)
    {
        return 0;
    }

    if(root -> LeftChild != nullptr)
    {
        itterator += subfunc1(root -> LeftChild, k, answer);
    }
    if(root -> RightChild != nullptr)
    {
        itterator += subfunc1(root -> RightChild, k, answer);
    }

    if(itterator <= k)
    {
        answer ++;
    }
    return itterator;
}



/*int Tree::func2(TreeNode* root, int k)
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
*/

int Tree::func2(TreeNode* root, int k)
{
    int answer = 0;
    subfunc2(root, k, answer);
    return answer;
}

int Tree::subfunc2(TreeNode* root, int k, int &answer)
{
    int itterator = 1;

    if(root == nullptr)
    {
        return 0;
    }
    if(root -> LeftChild != nullptr)
    {
        itterator += subfunc2(root -> LeftChild, k, answer);
    }
    if(root -> RightChild != nullptr)
    {
        itterator += subfunc2(root -> RightChild, k, answer);
    }

    if(itterator <= k)
    {
        answer += itterator;
    }
    return itterator;
}


int Tree::depth(TreeNode* root)
{
    if(root == nullptr)
    {
        return 0;
    }
    if(root -> LeftChild == nullptr && root -> RightChild == nullptr)
    {
        return 1;
    }
    return depth(root -> LeftChild) + depth(root -> RightChild);
}


int Tree::func3(TreeNode* root, int k)
{
    int answer = 0;
    subfunc3(root, k, answer);
    return answer;
}


 int Tree::subfunc3(TreeNode* root, int k, int & answer)
 {
     int itterator = 1;
     int left_value = 0, right_value = 0;

     if(root == nullptr)
     {
         return 0;
     }
     if(root -> LeftChild != nullptr)
     {
         left_value = subfunc3(root -> LeftChild, k, answer);
     }
     if(root -> RightChild != nullptr)
     {
         right_value = subfunc3(root -> RightChild, k, answer);
     }

     itterator += (left_value > right_value ? left_value : right_value);

     if(itterator <= k)
     {
         answer ++;
     }
     return itterator;
}

int Tree::func4(TreeNode* root)
{
    int answer = 0;
    return subfunc4(root, &answer);
}

int Tree::subfunc4(TreeNode* root, int * answer)
{
    if( root == nullptr)
    {
        return 0;
    }

    int valueLeft = subfunc4(root -> LeftChild, answer);
    int valueRight = subfunc4(root -> RightChild, answer);
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
            return func5(root -> LeftChild, level - 1) +
                   func5(root -> RightChild, level - 1);
        }
    }
    return 0;
}
