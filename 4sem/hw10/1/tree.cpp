#include "tree.h"
#include <time.h>

Tree::Tree(int order)
{
    Root = nullptr;
    Order = order;
}

void Tree::deleteTree(TreeNode *tmp)
{
    if(tmp == nullptr)
    {
        return;
    }
    for (int i = 0; i < tmp->Size + 1; ++i)
    {
        deleteTree(tmp->Children[i]);
    }
    tmp->deleteNode();
    //delete tmp;
}

int Tree::read(FILE *fp)
{
    Student buff;
    int i = 0, ret = 0;
    if((ret = buff.read(fp) < 0))
    {
        delete &buff;
        return ret;
    }

    TreeNode ret1, ret2;
    TreeNode *retP1 = &ret1, * retP2 = &ret2;
    Student *res = insert(&((new Student)->move(buff)), 0, &retP1, &retP2);
    if(res != nullptr)
    {
        insertTreeNode(res, 0, &retP1, &retP2);
    }
    i++;

    for(;;)
    {
        if((ret = buff.read(fp)))
        {
            return ret;
        }
        Student *res = insert(&((new Student)->move(buff)), 0, &retP1, &retP2);
        if(res != nullptr)
        {
            insertTreeNode(res, 0, &retP1, &retP2);
        }

        i++;
    }
}

void Tree::print(TreeNode *Root, int level, int counter , FILE* out)
{
    if(Root == nullptr)
    {
        return;
    }
    if (level >  MAX_PRINT)
    {
        return;
    }
    for (int i = 0; i < level; ++i)
    {
        printf("| ");
    }
    if (counter >= 0)
    {
        printf("%d: ", counter);
    }
    Root->print(Order, out);
    int printLimit = (2 * Order + 1 < MAX_HEIGHT_PRINT ? 2 * Order + 1 : MAX_HEIGHT_PRINT);
    for (int i = 0; i < printLimit; ++i)
    {
        print(Root->Children[i], level + 1, i);
    }
}

TreeNode* Tree::getRoot()
{
    return Root;
}

int Tree::getOrder()
{
    return Order;
}


Student * Tree::insertTreeNode(Student * value, TreeNode* current, TreeNode ** p_left, TreeNode ** p_right)
{
    if(current == nullptr)
    {
        current = Root;
        if(current == Root)
        {
            Root = new TreeNode(2 * Order);
            Root->Values[0] = value;
            Root->Children[0] = *p_left;
            Root->Children[1] = *p_right;
            Root->Size++;
            return 0;
        }
    }
    int tmp = current->findInsert(value);
    if(current->Size < 2 * Order)
    {
        for(int i = current->Size - 1; i >= tmp; i--)
        {
            current->Values[i + 1] = current->Values[i];
            current->Children[i + 2] = current->Children[i + 1];
        }
        current->Values[tmp] = value; current->Size++;
        current->Children[tmp] = *p_left;
        current->Children[tmp + 1] = *p_right;
        return 0;
    }
    else
    {
        TreeNode * right = new TreeNode(2 * Order);
        Student * median = 0;
        if(tmp < Order)
        {
            median = current->Values[Order - 1];
        }
        else if(tmp == Order)
        {
            median = value;
        }
        else
        {
            median = current->Values[Order];
        }
        if(tmp <= Order)
        {
            int i = 0;
            for(i = 0; i < Order; i++)
            {
                right->Values[i] = current->Values[i + Order];
                right->Children[i] = current->Children[i + Order];
                current->Values[i + Order] = 0;
                current->Children[i + Order] = 0;
            }
            right->Children[i] = current->Children[i + Order];
            current->Children[i + Order] = 0;
        }
        else
        {
            int i = 0;
            for(i = 0; i < tmp - Order - 1; i++)
            {
                right->Values[i] = current->Values[i + Order + 1];
                right->Children[i] = current->Children[i + Order + 1];
                current->Values[i + Order + 1] = 0;
                current->Children[i + Order + 1] = 0;
            }
            right->Values[i] = value;
            right->Children[i] = *p_left;
            current->Children[i + Order + 1] = *p_right;
            i++;
            for(; i < Order; i++) 
            {
                right->Values[i] = current->Values[i + Order];
                right->Children[i] = current->Children[i + Order];
                current->Values[i + Order] = 0;
                current->Children[i + Order] = 0;
            }
            right->Children[i] = current->Children[i + Order];
            current->Children[i + Order] = 0;
        }

        if(tmp < Order)
        {
            for(int i = Order - 1; i >= tmp; i--)
            {
                current->Values[i + 1] = current->Values[i];
                current->Children[i + 2] = current->Children[i + 1];
            }
            current->Values[tmp] = value; current->Size++;
            current->Children[tmp] = *p_left;
            current->Children[tmp + 1] = *p_right;
        }

        if(tmp == Order)
        {
            right->Children[0] = *p_right;
            current->Children[Order] = *p_left;
        }
        for(int i = Order; i < 2 * Order; i++)
        {
            current->Values[i] = 0;
            right->Values[i] = 0;
        }
        right->Size = Order;
        current->Size = right->Size = Order;
        *p_right = right;
        *p_left = current;
        return median;
    }
}


Student* Tree::insert(Student *value, TreeNode *current, TreeNode **p_left, TreeNode **p_right)
{
    if(Root == nullptr)
    {
        Root = new TreeNode(2 * Order);
    }
    if(current == nullptr)
    {
        current = Root;
    }

    int tmp = current->findInsert(value);
    if(current->Children[0])
    {
        Student *res = insert(value, current->Children[tmp], p_left, p_right);
        if(!(res == 0))
        {
            res = insertTreeNode(res, current, p_left, p_right);
        }
        return res;
    }
    else
    {
        if(current->Size < 2 * Order)
        {
          for(int i = current->Size - 1; i >= tmp; i--)
          {
              current->Values[i + 1] = current->Values[i];
          }
          current->Values[tmp] = value; 
          current->Size++;
          return 0;
        }
        else
        {
            TreeNode * right = new TreeNode(2 * Order);
            Student * median = 0;
            if(tmp < Order)
            {
                median = current->Values[Order - 1];
            }
            else if(tmp == Order)
            {
                median = value;
            }
            else
            {
                median = current->Values[Order];
            }
            if(tmp <= Order)
            {
                for(int i = 0; i < Order; i++)
                {
                    right->Values[i] = current->Values[i + Order];
                    current->Values[i + Order] = 0;
                }
            }
            else
            {
                int i = 0;
                for(i = 0; i < tmp - Order - 1; i++)
                {
                    right->Values[i] = current->Values[i + Order + 1];
                    current->Values[i + Order + 1] = 0;
                }
                right->Values[i] = value; i++;
                for(; i < Order; i++)
                {
                    right->Values[i] = current->Values[i + Order];
                    current->Values[i + Order] = 0;
                }
            }

            if(tmp < Order)
            {
                for(int i = Order - 1; i >= tmp; i--)
                {
                    current->Values[i + 1] = current->Values[i];
                }
                current->Values[tmp] = value; current->Size++;
            }
            for(int i = Order; i < 2 * Order; i++)
            {
                current->Values[i] = nullptr;
                right->Values[i] = nullptr;
            }
            right->Size = Order;
            current->Size = Order;
            *p_right = right;
            *p_left = current;
            return median;
        }
    }
}

void Tree::testAll(int k)
    {
        double t = clock(); int res = func1(k); t = (clock() - t) / CLOCKS_PER_SEC;
        printf("Result1: %d Time: %1.2f\n\n", res, t);

        t = clock(); res = func2(k); t = (clock() - t) / CLOCKS_PER_SEC;
        printf("Result2: %d Time: %1.2f\n\n", res, t);

        t = clock(); res = func3(k); t = (clock() - t) / CLOCKS_PER_SEC;
        printf("Result3: %d Time: %1.2f\n\n", res, t);

        t = clock(); res = func4(k); t = (clock() - t) / CLOCKS_PER_SEC;
        printf("Result4: %d Time: %1.2f\n\n", res, t);

        t = clock(); res = func5(k); t = (clock() - t) / CLOCKS_PER_SEC;
        printf("Result5: %d Time: %1.2f\n\n", res, t);

        t = clock(); res = func6(k); t = (clock() - t) / CLOCKS_PER_SEC;
        printf("Result6: %d Time: %1.2f\n\n", res, t);
    }

    int Tree::func1(int k)
    {
        int counter = 0;
        solve1(Root, k, counter);
        return counter;
    }
    void Tree::solve1(TreeNode * Root, int k, int & counter)
    {
        if(Root == nullptr)
        {
            return;
        }
        for(int i = 0; i < Root->Size + 1; i++)
        {
            solve1(Root->Children[i], k, counter);
        }
        if(Root->Size + 1 == k && Root->Children && Root->Children[0])
        {
            counter += Root->Size;
        }
    }

    int Tree::func2(int k)
    {
        int counter = 0, count_students = 0;
        solve2(Root, k, counter,count_students);
        return counter;
    }
    int Tree::solve2(TreeNode * Root, int k, int & counter, int & count_students)
    {
        if(Root == nullptr)
        {
            return 0;
        }
        int n_nodes = 1;
        int n_students = Root->Size;
        count_students = n_students;
        if(Root->Children[0])
        {
            for(int i = 0; i < Root->Size +1 ; i++)
            {
                n_nodes += solve2(Root->Children[i], k, counter, count_students);
                n_students += count_students;
            }
        }
        count_students = n_students;
        if (n_nodes <= k) counter += n_students;
        return n_nodes;
    }

    int Tree::func3(int k)
    {
        int counter = 0, sum = 0, res = 0;
        solve3(Root, k, counter, sum, res);
        return res;
    }
    int Tree::solve3(TreeNode * Root, int k, int &counter, int &count_students, int &res)
    {
        if(Root == nullptr) 
        {
            return 0;
        }
        int max = 0, tmp = 0;
        int n_students = Root->Size;
        count_students = n_students;
        if(Root->Children[0])
        {
            for(int i = 0; i < Root->Size + 1; i++)
            {
                tmp = solve3(Root->Children[i], k, counter, count_students, res);
                n_students += count_students;
                max = tmp > max ? tmp : max;
            }
        }
        count_students = n_students;
        int height = max + 1;
        if(height <= k) 
        {
            res += n_students;
        }
        return height;
    }



    int Tree::func4(int k)
    {
        int counter = 0, sum = 0, res = 0;
        solve4(Root, k, counter, getHeight(Root), sum, res);
        return res;
    }

    int Tree::getHeight(TreeNode * Root)
    {
        if(Root == nullptr) 
        {
            return 0;
        }
        int max = 0, tmp = 0;
        if(Root->Children[0])
        {
            for(int i = 0; i < Root->Size + 1; i++)
            {
                tmp = getHeight(Root->Children[i]);
                max = tmp > max ? tmp : max;
            }
        }
        int height = max + 1;
        return height;
    }

    int Tree::solve4(TreeNode * Root, int k, int &counter, int h, int &count_students, int &res)
    {
        if(Root == nullptr)
        {
            return 0;
        }

        int maxWidth = 0;
        int n_students = Root->Size;
        count_students = n_students;
        if(Root->Children[0])
        {
            for(int i = 0; i < Root->Size + 1; i++)
            {
                solve4(Root->Children[i], k, counter, h - 1, count_students, res);
                n_students += count_students;
            }
        }

        count_students = n_students;
        if(maxWidth > k)
        {
            return k + 1;
        }
        int Width;
        int i;
        for(i = 1; i <= h; i++)
        {
            Width = getNodeWidth(Root, i);
            if(Width > maxWidth)
            {
                maxWidth = Width;
                if(maxWidth > k)
                {
                    break;
                }
            }
        }
        if(maxWidth <= k)
        {
            counter++; res += n_students;
        }
        return maxWidth;
    }

    int func5solve(TreeNode* Root, int level)
    {
      if(!Root) {return 0;}
      if(level == 1)
      {return Root->Size;}
      else if (level > 1)
      {
        int tmp = 0;
        if(Root->Children[0])
        {
          for(int i = 0; i < Root->Size + 1; i++)
          {tmp += func5solve(Root->Children[i], level - 1);}
        }
        return tmp;
      }
      return 0;
    }

    void func6solve(TreeNode * Root, int k, int curlevel, int &counter, int &count_students)
    {
      if(!Root) {return;}
      if(curlevel > k) {return;}
      count_students += Root->Size;
      if(curlevel==k && !Root->Children[0]){
        counter+=count_students;
      }
      if(Root->Children[0])
      {
        for(int i = 0; i < Root->Size + 1; i++)
        {func6solve(Root->Children[i], k, curlevel + 1, counter, count_students);}
      }
      count_students -= Root->Size;
    }

    int getNodeWidth(TreeNode* Root, int level)
    {
      if(!Root) {return 0;}
      if(level == 1) {return 1;}
      else if (level > 1)
      {
        int tmp = 0;
        if(Root->Children[0])
        {
          for(int i = 0; i < Root->Size + 1; i++)
          {tmp += getNodeWidth(Root->Children[i], level - 1);}
        }
        return tmp;
      }
      return 0;
    }

    int func4(int k)
    {
      int counter = 0, sum = 0, res = 0;
      func4solve(Root, k, counter, getHeight(Root), sum, res);
      return res;
    }

    int func5(int k)
    {return func5solve(Root, k);}

    int func6(int k)
    {
      int counter = 0, count_students = 0;
      func6solve(Root, k, 1, counter, count_students);
      return counter;
    }

    int getHeight(TreeNode * Root)
    {
      if(!Root) {return 0;}
      int max = 0, tmp = 0;
      if(Root->Children[0])
      {
        for(int i = 0; i < Root->Size + 1; i++)
        {
          tmp = getHeight(Root->Children[i]);
          max = tmp > max ? tmp : max;
        }
      }
      int height = max + 1;
      return height;
    }
};