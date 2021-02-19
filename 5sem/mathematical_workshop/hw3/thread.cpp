#include "constants.h"
#include "thread.h"
#include "task.h"

void *thread_func (void *arg)
{
  Data_Bus *data;
  data = (Data_Bus *) arg;

  const char **file_names = data->file_names;
  double *min_ = data->min;
  int *status = data->status;
  int *result = data->result;
  int thread_quantity = data->thread_quantity;
  int curr_thread = data->curr_thread;

  status[curr_thread] = min_finder (file_names[curr_thread], min_ + curr_thread);
  pthread_barrier_wait (data -> barrier);

  int i = 0;
  for (i = 0; i < thread_quantity; i++)
    {
      if (status[i] < 0)
        return nullptr;
    }

  double min_answer = 0;
  for (i = 0; i < thread_quantity; i++)
    {
      if (status[i] > 0)
        {
          min_answer = min_[i];
          break;
        }
    }

  for (i = 0; i < thread_quantity; i++)
    {
      if (status[i] > 0 && min_[i] < min_answer)
        min_answer = min_[i];
    }

  result[curr_thread] = counter (file_names[curr_thread], min_answer);

  pthread_barrier_wait (data -> barrier);
  return nullptr;
}
