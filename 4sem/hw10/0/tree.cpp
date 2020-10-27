#include "tree.h"


int Btree::read(const char * filename)
{
  FILE * fp;
  student buf; int i = 0;
  if(!(fp = fopen(filename, "r"))) return -1;
  if(!(buf.read(fp)))
  {fclose(fp); printf("cant read\n"); return -2;}

  Node_Btree ret1 = 0, ret2;
  Node_Btree * retP1 = &ret1, * retP2 = &ret2;
  student * res = insert(&((new student) -> move(buf)), 0, &retP1, &retP2);
  if(res) {insertnode(res, 0, &retP1, &retP2);}
  i++;
  while(1) 
  {
    if(!buf.read(fp)) {fclose(fp); return i;}
    student * res = insert(&((new student) -> move(buf)), 0, &retP1, &retP2);
    if(res) {insertnode(res, 0, &retP1, &retP2);}
    i++;
  }
}

student * Btree::insert(student * value, Node_Btree * cur, Node_Btree ** p_left, Node_Btree ** p_right)
{
  if(!root) {root = new Node_Btree(2 * order);}
  if(!cur) {cur = root;}
  int tmp = cur -> find_ins(value);
  if(cur->pchildren[0])
  {
    student * res = insert(value, cur -> pchildren[tmp], p_left, p_right);
    if(!(res == 0))
    {res = insertnode(res, cur, p_left, p_right);}
    return res;
  }
  else
  {
    if(cur -> cur_size < 2 * order)
    {
      for(int i = cur -> cur_size - 1; i >= tmp; i--)
      {cur -> pvalues[i + 1] = cur -> pvalues[i];}
      cur -> pvalues[tmp] = value; cur -> cur_size++;
      return 0;
    }
    else
    {
      Node_Btree * right = new Node_Btree(2 * order);
      student * median = 0;
      if(tmp<order)
      {median = cur -> pvalues[order - 1];}
      else if(tmp == order)
      {median = value;}
      else
      {median = cur -> pvalues[order];}

      if(tmp <= order)
      {
          for(int i = 0; i < order; i++)
          {
              right -> pvalues[i] = cur -> pvalues[i + order];
              cur -> pvalues[i + order] = 0;
          }
      }
      else
      {
          int i = 0;
          for(i = 0; i < tmp - order - 1; i++)
          {
              right -> pvalues[i] = cur -> pvalues[i + order + 1];
              cur -> pvalues[i + order + 1] = 0;
          }
          right -> pvalues[i] = value; i++;
          for(; i < order; i++)
          {
              right -> pvalues[i] = cur -> pvalues[i + order];
              cur -> pvalues[i + order] = 0;
          }
      }

      if(tmp < order)
      {
          for(int i = order - 1; i >= tmp; i--)
          {cur -> pvalues[i + 1] = cur -> pvalues[i];}
          cur -> pvalues[tmp] = value; cur -> cur_size++;
      }
      for(int i = order; i < 2 * order; i++)
      {
          cur -> pvalues[i] = 0;
          right -> pvalues[i] = 0;
      }
      right -> cur_size = order;
      cur -> cur_size = order;
      *p_right = right;
      *p_left = cur;
      return median;
    }
  }
}

student * Btree::insertnode(student * value, Node_Btree* cur, Node_Btree ** p_left, Node_Btree ** p_right)
{
    if(!cur)
    {
        cur = root;
        if(cur == root)
        {
            root = new Node_Btree(2 * order);
            root -> pvalues[0] = value;
            root -> pchildren[0] = *p_left;
            root -> pchildren[1] = *p_right;
            root -> cur_size++;
            return 0;
        }
    }
    int tmp = cur -> find_ins(value);
    if(cur -> cur_size < 2 * order)
    {
        for(int i = cur -> cur_size - 1; i >= tmp; i--)
        {
            cur -> pvalues[i + 1] = cur -> pvalues[i];
            cur -> pchildren[i + 2] = cur -> pchildren[i + 1];
        }
        cur -> pvalues[tmp] = value; cur -> cur_size++;
        cur -> pchildren[tmp] = *p_left;
        cur -> pchildren[tmp + 1] = *p_right;
        return 0;
    }
    else
    {
        Node_Btree * right = new Node_Btree(2 * order);
        student * median = 0;
        if(tmp < order)
        {median = cur -> pvalues[order - 1];}
        else if(tmp == order)
        {median = value;}
        else
        {median = cur -> pvalues[order];}
        if(tmp <= order)
        {
            int i = 0;
            for(i = 0; i < order; i++)
            {
                right -> pvalues[i] = cur -> pvalues[i + order];
                right -> pchildren[i] = cur -> pchildren[i + order];
                cur -> pvalues[i + order] = 0;
                cur -> pchildren[i + order] = 0;
            }
            right -> pchildren[i] = cur -> pchildren[i + order];
            cur -> pchildren[i + order] = 0;
        }
        else
        {
            int i = 0;
            for(i = 0; i < tmp - order - 1; i++)
            {
                right -> pvalues[i] = cur -> pvalues[i + order + 1];
                right -> pchildren[i] = cur -> pchildren[i + order + 1];
                cur -> pvalues[i + order + 1] = 0;
                cur -> pchildren[i + order + 1] = 0;
            }
            right -> pvalues[i] = value;
            right -> pchildren[i] = *p_left;
            cur -> pchildren[i + order + 1] = *p_right;
            i++;
            for(; i < order; i++) 
            {
                right -> pvalues[i] = cur -> pvalues[i + order];
                right -> pchildren[i] = cur -> pchildren[i + order];
                cur -> pvalues[i + order] = 0;
                cur -> pchildren[i + order] = 0;
            }
            right -> pchildren[i] = cur -> pchildren[i + order];
            cur -> pchildren[i + order] = 0;
        }

        if(tmp < order)
        {
            for(int i = order - 1; i >= tmp; i--)
            {
                cur -> pvalues[i + 1] = cur -> pvalues[i];
                cur -> pchildren[i + 2] = cur -> pchildren[i + 1];
            }
            cur -> pvalues[tmp] = value; cur -> cur_size++;
            cur -> pchildren[tmp] = *p_left;
            cur -> pchildren[tmp + 1] = *p_right;
        }

        if(tmp == order)
        {
            right -> pchildren[0] = *p_right;
            cur -> pchildren[order] = *p_left;
        }
        for(int i = order; i < 2 * order; i++)
        {
            cur -> pvalues[i] = 0;
            right -> pvalues[i] = 0;
        }
        right -> cur_size = order;
        cur -> cur_size = right -> cur_size = order;
        *p_right = right;
        *p_left = cur;
        return median;
  }
}

void Btree::print(Node_Btree * root, int level, int index)
{
  if(!root) {return;}
  if(level > MAX_PRINT) {return;}
  for(int i = 0; i < level; i++) {printf("| ");}
  if(index >= 0) {printf("%i: ", index);}
  root -> print(order);
  for(int i = 0; i < (2 * order + 1 < MAX_HEIGHT_PRINT ? 2 * order + 1 : MAX_HEIGHT_PRINT); i++)
  {print(root -> pchildren[i], level + 1, i);}
}



void Tree::testAll(int k)
    {
      double t = clock(); int res = task1(k); t = (clock() - t) / CLOCKS_PER_SEC;
      printf("Result1: %d Time: %1.2f\n\n", res, t);

      t = clock(); res = task2(k); t = (clock() - t) / CLOCKS_PER_SEC;
      printf("Result2: %d Time: %1.2f\n\n", res, t);

      t = clock(); res = task3(k); t = (clock() - t) / CLOCKS_PER_SEC;
      printf("Result3: %d Time: %1.2f\n\n", res, t);

      t = clock(); res = task4(k); t = (clock() - t) / CLOCKS_PER_SEC;
      printf("Result4: %d Time: %1.2f\n\n", res, t);

      t = clock(); res = task5(k); t = (clock() - t) / CLOCKS_PER_SEC;
      printf("Result5: %d Time: %1.2f\n\n", res, t);

      t = clock(); res = task6(k); t = (clock() - t) / CLOCKS_PER_SEC;
      printf("Result6: %d Time: %1.2f\n\n", res, t);
    }

    void task1solve(Node_Btree * root, int k, int & counter)
    {
      if(!root) {return;}
      for(int i = 0; i < root -> cur_size + 1; i++)
      {task1solve(root -> pchildren[i], k, counter);}
      if(root -> cur_size + 1 == k && root -> pchildren && root -> pchildren[0])
      {counter += root -> cur_size;}
    }

    int task2solve(Node_Btree * root, int k, int & counter, int & count_students)
    {
      if(!root) {return 0;}
      int n_nodes = 1;
      int n_students = root -> cur_size;
      count_students = n_students;
      if(root -> pchildren[0])
      {
        for(int i = 0; i < root -> cur_size +1 ; i++)
        {
          n_nodes += task2solve(root -> pchildren[i], k, counter, count_students);
          n_students += count_students;
        }
      }
      count_students = n_students;
      if (n_nodes <= k) counter += n_students;
      return n_nodes;
    }

    int task3solve(Node_Btree * root, int k, int &counter, int &count_students, int &res)
    {
      if(!root) {return 0;}
      int max = 0, tmp = 0;
      int n_students = root -> cur_size;
      count_students = n_students;
      if(root -> pchildren[0])
      {
        for(int i = 0; i < root -> cur_size + 1; i++)
        {
          tmp = task3solve(root -> pchildren[i], k, counter, count_students, res);
          n_students += count_students;
          max = tmp > max ? tmp : max;
        }
      }
      count_students = n_students;
      int height = max + 1;
      if(height <= k) 
      {res += n_students;}
      return height;
    }

    int  task4solve(Node_Btree * root, int k, int &counter, int h, int &count_students, int &res)
    {
      if(!root) return 0;
      int maxWidth = 0;
      int n_students = root -> cur_size;
      count_students = n_students;
      if(root -> pchildren[0])
      {
        for(int i = 0; i < root -> cur_size + 1; i++)
        {
          task4solve(root -> pchildren[i], k, counter, h - 1, count_students, res);
          n_students += count_students;
        }
      }
      count_students = n_students;
      if(maxWidth > k)
      {return k + 1;}
      int Width;
      int i;
      for(i = 1; i <= h; i++)
      {
        Width = getNodeWidth(root, i);
        if(Width > maxWidth)
        {maxWidth = Width; if(maxWidth > k) break;}
      }
      if(maxWidth <= k) {counter++; res += n_students;}
      return maxWidth;
    }

    int task5solve(Node_Btree* root, int level)
    {
      if(!root) {return 0;}
      if(level == 1)
      {return root -> cur_size;}
      else if (level > 1)
      {
        int tmp = 0;
        if(root -> pchildren[0])
        {
          for(int i = 0; i < root -> cur_size + 1; i++)
          {tmp += task5solve(root -> pchildren[i], level - 1);}
        }
        return tmp;
      }
      return 0;
    }

    void task6solve(Node_Btree * root, int k, int curlevel, int &counter, int &count_students)
    {
      if(!root) {return;}
      if(curlevel > k) {return;}
      count_students += root->cur_size;
      if(curlevel==k && !root->pchildren[0]){
        counter+=count_students;
      }
      if(root -> pchildren[0])
      {
        for(int i = 0; i < root -> cur_size + 1; i++)
        {task6solve(root -> pchildren[i], k, curlevel + 1, counter, count_students);}
      }
      count_students -= root -> cur_size;
    }

    int getNodeWidth(Node_Btree* root, int level)
    {
      if(!root) {return 0;}
      if(level == 1) {return 1;}
      else if (level > 1)
      {
        int tmp = 0;
        if(root -> pchildren[0])
        {
          for(int i = 0; i < root -> cur_size + 1; i++)
          {tmp += getNodeWidth(root -> pchildren[i], level - 1);}
        }
        return tmp;
      }
      return 0;
    }

    int task1(int k)
    {
      int counter = 0;
      task1solve(root, k, counter);
      return counter;
    }

    int task2(int k)
    {
      int counter = 0, count_students = 0;
      task2solve(root, k, counter,count_students);
      return counter;
    }

    int task3(int k)
    {
      int counter = 0, sum = 0, res = 0;
      task3solve(root, k, counter, sum, res);
      return res;
    }

    int task4(int k)
    {
      int counter = 0, sum = 0, res = 0;
      task4solve(root, k, counter, getHeight(root), sum, res);
      return res;
    }

    int task5(int k)
    {return task5solve(root, k);}

    int task6(int k)
    {
      int counter = 0, count_students = 0;
      task6solve(root, k, 1, counter, count_students);
      return counter;
    }

    int getHeight(Node_Btree * root)
    {
      if(!root) {return 0;}
      int max = 0, tmp = 0;
      if(root -> pchildren[0])
      {
        for(int i = 0; i < root -> cur_size + 1; i++)
        {
          tmp = getHeight(root -> pchildren[i]);
          max = tmp > max ? tmp : max;
        }
      }
      int height = max + 1;
      return height;
    }
};