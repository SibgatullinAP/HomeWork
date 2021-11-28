#include "process.h"

int from_root[2];
int to_root[2];

int main (int argc, char *argv[])
{
  pid_t pid;

  int num;
  int ret, total;

  ret = total = 0;

  if (argc < 2)
    {
      printf ("[ERROR] Please, use: %s file_1 file_2 ... file_m\n", argv[0]);
      return 1;
    }

  int process_quantity = argc - 1;

  if (pipe (from_root) == -1 || pipe (to_root) == -1)
    {
      fprintf (stderr, "[ERROR] Cannot pipe!\n");
      return 2;
    }

  int i;
  for (i = 0; i < process_quantity; i++)
    {

      pid = fork ();
      if (pid == -1)
        {
          fprintf (stderr, "[ERROR] Cannot fork!\n");
          return 3 + i;
        }
      else if (pid == 0)
        {
          close (from_root[1]);
          close (to_root[0]);

          process_function (i, argv[i + 1]);

          close (from_root[0]);
          close (to_root[1]);

          return 0;
        }
    }

  close (from_root[0]);
  close (to_root[1]);

  for (i = 0; i < process_quantity; i++)
    {
      char byte = (char) i;
      if (write (from_root[1], &byte, 1) != 1)
        {
          fprintf (stderr, "[ERROR] Error writing in root process\n");
          return 100;
        }

      if (read (to_root[0], &ret, sizeof (int))
          != sizeof (int))
        {
          fprintf (stderr, "[ERROR] Error reading in root process\n");
          return 101;
        }

      if (ret < 0)
        {
          total = -1000;
          if (read (to_root[0], &num, sizeof (int))
              != sizeof (int))
            {
              fprintf (stderr, "[ERROR] Error reading in root process\n");
              return 101;
            }

          if (ret == CANNOT_OPEN_FILE)
            fprintf (stderr, "[ERROR] Can't open file %s\n", argv[num + 1]);
          else
            fprintf (stderr, "[ERROR] Can't read from file %s\n", argv[num + 1]);

        }
      else if (total >= 0)
        total += ret;

    }

  close (from_root[1]);
  close (to_root[0]);

  if (total >= 0)
    printf ("[OUTPUT] Answer %d\n", total);

  return 0;
}
