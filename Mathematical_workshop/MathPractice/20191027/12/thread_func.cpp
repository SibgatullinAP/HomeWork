#include "common.hpp"
#include "thread_func.hpp"
#include "task.hpp"

void *
thread_func (void * arg)
{
  Argument * data;
  const char ** files;
  double * shared_min;
  double * shared_max;
  int * status;
  int * result;
  int p, g, i;
  double min, max;

  data = (Argument *) arg;

  files = data -> files;
  shared_min = data -> shared_min;
  shared_max = data -> shared_max;
  status = data -> status;
  result = data -> result;
  p = data -> p;
  g = data -> g;

  status[g] = average_of_min_max (files[g], shared_min + g, shared_max + g);

  pthread_barrier_wait (data -> barrier);

  for (i = 0; i < p; i++)
    {
      if (status[i] != SUCESS)
        {
//          pthread_barrier_wait (data -> barrier);
          return nullptr;
        }
    }

  min = shared_min[0];
  max = shared_max[0];

  for (i = 1; i < p; i++)
    {
      min = std::min (min, shared_min[i]);
      max = std::max (max, shared_max[i]);
    }

  result[g] = count_great (files[g], (min + max) * 0.5);

  pthread_barrier_wait (data -> barrier);
  return nullptr;

}
