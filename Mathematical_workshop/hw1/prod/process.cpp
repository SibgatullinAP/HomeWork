#include "process.h"

extern int from_root[2];
extern int to_root[2];

void process_function (int my_rank, const char * path)
{
  int ret = task (path);
  char byte;
  if (read (from_root[0], &byte, 1) != 1)
    {
      fprintf (stderr, "[ERROR] Error reading in process %d, pid = %d\n", my_rank, getpid ());
      return;
    }

  if (write (to_root[1], &ret, sizeof (int)) != sizeof (int))
    {
      fprintf (stderr, "[ERROR] Error writing in process %d, pid = %d\n", my_rank, getpid ());
      return;
    }

  if (ret < 0)
    {
      if (write (to_root[1], &my_rank, sizeof (int)) != sizeof (int))
        {
          fprintf (stderr, "[ERROR] Error writing in process %d, pid = %d\n", my_rank, getpid ());
          return;
        }
    }
}
