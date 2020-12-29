#include <iostream>

#include "tree.h"
#define TASK_QUANTITY 5

int main(int argc, char *argv[])
{
  if (argc != 4)
    {
      printf ("[ERROR] Please use %s r filename m\n", argv[0]);
      return -1;
    }

  int m;
  int r;
  if (sscanf (argv[1], "%d", &r) != 1 || sscanf (argv[3], "%d", &m) != 1)
    {
      printf ("[ERROR] r and m should be non-negative integer numbers!");
      return -1;
    }

  list2::set_m (m);
  list2::set_r (r);

  tree<student> *a = new tree<student>;

  char *filename = argv[2];
  int ret = a->read (filename);
  if (ret < 0)
    {
      switch (ret)
        {
        case ERROR_CANNOT_OPEN_FILE:
          printf("[ERROR] Can't open file %s\n", filename);
          break;
        case ERROR_CANNOT_READ_FILE:
          printf("[ERROR] Can't read file %s\n", filename);
          break;
        case ERROR_INVALID_FILE:
          printf("[ERROR] Invalid file %s\n", filename);
          break;
        case ERROR_INTERNAL_ERROR_STUDENT:
          printf("[ERROR] Internal error (not enough memmory for student)\n");
          break;
        case ERROR_INTERNAL_ERROR_TREE:
          printf("[ERROR] Internal error (not enough memmory for tree_node)\n");
          break;
        default:
          printf("[ERROR] Unknown error %d)\n", ret);
        }
      delete a;
      return -2;
    }

  a->print (r);

  int answer[TASK_QUANTITY] = {0};
  double time[TASK_QUANTITY];

  time[0] = clock();
  answer[0] = a->task_1 ();
  time[0] = (clock() - time[0]) / CLOCKS_PER_SEC;

  time[1] = clock();
  answer[1] = a->task_2 ();
  time[1] = (clock() - time[1]) / CLOCKS_PER_SEC;

  time[2] = clock();
  answer[2] = a->task_3 ();
  time[2] = (clock() - time[2]) / CLOCKS_PER_SEC;

  time[3] = clock();
  answer[3] = a->task_4 ();
  time[3] = (clock() - time[3]) / CLOCKS_PER_SEC;

  time[4] = clock();
  answer[4] = a->task_5 ();
  time[4] = (clock() - time[4]) / CLOCKS_PER_SEC;


  for (int i = 0; i < TASK_QUANTITY; i++)
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], i + 1, answer[i], time[i]);

  delete a;

  tree<list2> *b = new tree<list2>;
  ret = b->read (filename);
  if (ret < 0)
    {
      switch (ret)
        {
        case ERROR_CANNOT_OPEN_FILE:
          printf("[ERROR] Can't open file %s\n", filename);
          break;
        case ERROR_CANNOT_READ_FILE:
          printf("[ERROR] Can't read file %s\n", filename);
          break;
        case ERROR_INVALID_FILE:
          printf("[ERROR] Invalid file %s\n", filename);
          break;
        case ERROR_INTERNAL_ERROR_STUDENT:
          printf("[ERROR] Internal error (not enough memmory for student)\n");
          break;
        case ERROR_INTERNAL_ERROR_LIST2:
          printf("[ERROR] Internal error (not enough memmory for list2_node)\n");
          break;
        case ERROR_INTERNAL_ERROR_TREE:
          printf("[ERROR] Internal error (not enough memmory for tree_node)\n");
          break;
        default:
          printf("[ERROR] Unknown error %d)\n", ret);
        }
      delete b;
      return -2;
    }

  b->print (r);

  time[0] = clock();
  answer[0] = b->task_1 ();
  time[0] = (clock() - time[0]) / CLOCKS_PER_SEC;

  time[1] = clock();
  answer[1] = b->task_2 ();
  time[1] = (clock() - time[1]) / CLOCKS_PER_SEC;

  time[2] = clock();
  answer[2] = b->task_3 ();
  time[2] = (clock() - time[2]) / CLOCKS_PER_SEC;

  time[3] = clock();
  answer[3] = b->task_4 ();
  time[3] = (clock() - time[3]) / CLOCKS_PER_SEC;

  time[4] = clock();
  answer[4] = b->task_5 ();
  time[4] = (clock() - time[4]) / CLOCKS_PER_SEC;


  for (int i = 0; i < TASK_QUANTITY; i++)
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], i + 1, answer[i], time[i]);

  delete b;

  return 0;
}
