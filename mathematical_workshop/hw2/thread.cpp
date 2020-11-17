#include "constants.h"
#include "thread.h"
#include "task.h"

void *thread_func (void *arg)
{
  Data_Bus *data;
  data = (Data_Bus *) arg;

  const char **file_names = data->file_names;
  double *avg_ = data->avg;
  int *status = data->status;
  int *result = data->result;
  int thread_quantity = data->thread_quantity;
  int curr_thread = data->curr_thread;

  status[curr_thread] = avg (file_names[curr_thread], avg_ + curr_thread);
  pthread_barrier_wait (data -> barrier);

  int i = 0;
  for (i = 0; i < thread_quantity; i++)
    {
      if (status[i] != 0)
        return nullptr;
    }

  double avg_positive = 0;
  for (i = 0; i < thread_quantity; i++)
    avg_positive += avg_[i];

  result[curr_thread] = counter (file_names[curr_thread], avg_positive / (double) thread_quantity);

  pthread_barrier_wait (data -> barrier);
  return nullptr;
}
