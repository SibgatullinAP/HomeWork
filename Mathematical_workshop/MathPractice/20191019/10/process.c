#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#include "task.h"

/* Канал вывода из главного процесса в порожденные.
   from_root[0] - для чтения (в порожденных процессах), 
   from_root[1] - для записи (в главном процессе). */
static int from_root[2];

/* Канал вывода из порожденных процессов в главный.
   to_root[0] - для чтения (в порожденных процессах),
   to_root[1] - для записи (в главном процессе). */
static int to_root[2];

void
process_function (int my_rank, const char * path);
/* Функция, работающая в процессе с номером my_rank,
   при общем числе процессов p. */
void
process_function (int my_rank, const char * path)
{
  char byte;
  int ret;

  /* Вычислить количество в каждом из процессов */
  ret = task (path);

  /* Ждать сообщения от главного процесса */
  if (read (from_root[0], &byte, 1) != 1)
    {
      /* Ошибка чтения */
      fprintf (stderr,
               "Error reading in process %d, pid = %d\n",
               my_rank, getpid ());
      return;
    }

  /* Передать результат главному процессу */
  if (write (to_root[1], &ret, sizeof (int))
      != sizeof (int))
    {
      /* Ошибка записи */
      fprintf (stderr,
               "Error writing in process %d, pid = %d\n",
               my_rank, getpid ());
      return;
    }

  /* Передать место, где случились trouble's */
  if (ret < 0)
    {

      if (write (to_root[1], &my_rank, sizeof (int))
          != sizeof (int))
        {
          /* Ошибка записи */
          fprintf (stderr,
                   "Error writing in process %d, pid = %d\n",
                   my_rank, getpid ());
          return;
        }

    }

}

int main (int argc, char * argv[])
{
  /* Идентификатор запускаемого процесса */
  pid_t pid;
  /* Общее количество процессов */
  int p;
  int i;
  char byte;
  int num;
  int ret, total;

  ret = total = 0;

  if (argc < 2)
    {
      printf ("Usage: %s a^1 a^2 ... a^m\n", argv[0]);
      return 1;
    }

  /* Получаем количество процессов */
  p = argc - 1;

  /* Создаем каналы */
  if (pipe (from_root) == -1 || pipe (to_root) == -1)
    {
      fprintf (stderr, "Cannot pipe!\n");
      return 2;
    }

  /* Запускаем процессы */
  for (i = 0; i < p; i++)
    {

      /* Клонировать себя */
      pid = fork ();
      if (pid == -1)
        {
          fprintf (stderr, "Cannot fork!\n");
          return 3 + i;
        }
      else if (pid == 0)
        {
          /* Процесс - потомок */
          /* Закрываем ненужные направления обмена */
          close (from_root[1]);
          close (to_root[0]);

          /* Проводим вычисления */
          process_function (i, argv[i + 1]);

          /* Закрываем каналы */
          close (from_root[0]);
          close (to_root[1]);

          /* Завершаем потомка */
          return 0;

        }

      /* Цикл продолжает процесс - родитель */
    }

  /* Закрываем ненужные направления обмена */
  close (from_root[0]);
  close (to_root[1]);

  /* Получаем результаты */
  for (i = 0; i < p ; i++)
    {
      /* Сигнализируем процессу */
      byte = (char) i;
      if (write (from_root[1], &byte, 1) != 1)
        {
          /* Ошибка записи */
          fprintf (stderr,
                   "Error writing in root process\n");
          return 100;
        }

      /* Считываем результат */
      if (read (to_root[0], &ret, sizeof (int))
          != sizeof (int))
        {
          /* Ошибка чтения */
          fprintf (stderr,
                   "Error reading in root process\n");
          return 101;
        }

      if (ret < 0)
        {

          total = -1000;

          /* Узнаем, в каком файле произошла ошибка. */
          if (read (to_root[0], &num, sizeof (int))
              != sizeof (int))
            {
              /* Ошибка чтения */
              fprintf (stderr,
                       "Error reading in root process\n");
              return 101;
            }

          if (ret == CANT_OPEN_FILE)
            {
              fprintf (stderr, "Can't open file %s\n", argv[num + 1]);
            }
          else
            {
              fprintf (stderr, "Can't read from file %s\n", argv[num + 1]);
            }

        }
      else if (total >= 0)
        {
          total += ret;
        }

    }

  /* Закрываем каналы */
  close (from_root[1]);
  close (to_root[0]);

  if (total >= 0)
    {
      printf ("Total %d\n", total);
    }

  return 0;
}
