#include "common.hpp"
#include "thread_func.hpp"
#include "task.hpp"

/* Идея:
 *         /  текущий файл   \
 * .... b0 | b1 b2 ... e0 e1 | e2 ...
 */

void *
thread_func (void * arg)
{
  Argument * data;
  const char * file;
  double * shm1;
  double * shm2;
  int * file_size;
  int * status;
  int * result;
  int p, g, i;
  double b0, b1, b2;
  double e0, e1, e2;
  int count, size;
  double sum;
  bool is_beg, is_end;

  data = (Argument *) arg;

  file = data -> file;
  shm1 = data -> shm1;
  shm2 = data -> shm2;
  file_size = data -> file_size;
  status = data -> status;
  result = data -> result;
  p = data -> p;
  g = data -> g;

  size = 0;
  b0 = b1 = b2 = e0 = e1 = e2 = sum = 0;

  status[g] = calc_count (file, &count, &size, &sum, &b1, &b2, &e0, &e1);

  // размер текущего файла
  file_size[g] = size;
  // первый элемент текущего файла
  shm1[g] = b1;
  // последний элемент текущего файла
  shm2[g] = e1;

  pthread_barrier_wait (data -> barrier);

  for (i = 0; i < p; i++)
    {
      if (status[i] != SUCESS)
        {
          return nullptr;
        }
    }

  /* Теперь известно сколько элементов в каждом из файлов
   * и крайние элементы соответствующих файлов. */

  /* Если в текущем файле не было элементов, то его нет смысла рассматривать. */
  if (size != 0)
    {

      is_beg = is_end = false;

      i = g - 1;

      while (i >= 0 && file_size[i] == 0)
        {
          i--;
        }

      if (i == -1)
        {
          is_beg = true;
        }
      else
        {
          b0 = shm2[i];
        }

      i = g + 1;

      while (i < p && file_size[i] == 0)
        {
          i++;
        }

      if (i == p)
        {
          is_end = true;
        }
      else
        {
          e2 = shm1[i];
        }

      /* Проверим условие на крайние элементы. */

      if (size == 1)
        {
          b2 = e2;
          e0 = b0;
        }

      /* На первый */
         /* Если первый и не единственный, то проверяем. */
      if ((is_beg && !is_end && b1 > b2)
          /* Если не последний и не единственный. */
          || (is_end && !is_beg && b1 > b2)
          /* Общий случай -- из середины последовательности. */
          || (!is_beg && !is_end && (b0 > b1 || b1 > b2))
          /* Наш файл единственный или единственный непустой. */
          || (is_beg && is_end && (b0 > b1 || b1 > b2)))
        {
          count += 1;
          sum += b1;
        }

      /* Если размер 1 то мы уже учли / не учли данный элемент. */
      if (size != 1)
        {

          /* На последний */
          /* Если последний и не единственный, то проверяем. */
          if ((is_end && !is_beg && e0 > e1)
              /* Если не первый и не единственный. */
              || (is_beg && !is_end && e0 > e1)
              /* Общий случай -- из середины последовательности. */
              || (!is_beg && !is_end && (e0 > e1 || e1 > e2))
              /* Наш файл единственный или единственный непустой. */
              || (is_beg && is_end && (e0 > e1 || e1 > e2)))
            {
              count += 1;
              sum += e1;
            }

        }

    }
  else
    {
      sum = 0;
      count = 0;
    }

  pthread_barrier_wait (data -> barrier);

  shm1[g] = sum;
  file_size[g] = count;

  pthread_barrier_wait (data -> barrier);

  /* Вычисляем среднее арифметическое. */
  sum = 0;
  count = 0;

  for (i = 0; i < p; i++)
    {
      if (file_size[i] != 0)
        {
          sum += shm1[i];
          count += file_size[i];
        }
    }

  if (count != 0)
    {
      sum /= count;
    }

  /* Теперь каждый поток имеет в своем распоряжении ср. арфиметическое. */
  result[g] = count_great (file, sum);

  pthread_barrier_wait (data -> barrier);

  return nullptr;

}
