#include "process.h"

/* Канал вывода из главного процесса в порожденные.
   from_root[0] - для чтения (в порожденных процессах),
   from_root[1] - для записи (в главном процессе). */
extern int from_root[2];

/* Канал вывода из порожденных процессов в главный.
   to_root[0] - для чтения (в порожденных процессах),
   to_root[1] - для записи (в главном процессе). */
extern int to_root[2];


/* Функция, работающая в процессе с номером my_rank,
   при общем числе процессов p. */
void process_function (int my_rank, const char * path)
{
  /* Вычислить количество в каждом из процессов */
  int ret = task (path);

  /* Ждать сообщения от главного процесса */
  char byte;
  if (read (from_root[0], &byte, 1) != 1)
    {
      /* Ошибка чтения */
      fprintf (stderr, "[ERROR] Error reading in process %d, pid = %d\n", my_rank, getpid ());
      return;
    }

  /* Передать результат главному процессу */
  if (write (to_root[1], &ret, sizeof (int)) != sizeof (int))
    {
      /* Ошибка записи */
      fprintf (stderr, "[ERROR] Error writing in process %d, pid = %d\n", my_rank, getpid ());
      return;
    }

  /* Передать место, где случились trouble's */
  if (ret < 0)
    {
      if (write (to_root[1], &my_rank, sizeof (int)) != sizeof (int))
        {
          /* Ошибка записи */
          fprintf (stderr, "[ERROR] Error writing in process %d, pid = %d\n", my_rank, getpid ());
          return;
        }
    }
}
