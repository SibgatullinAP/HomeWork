#include "constants.h"
#include "thread.h"

int main (int argc, const char *argv[])
{
  int thread_quantity = argc - 1;

  if (argc < 2)
    {
      printf ("[ERROR] Usage %s file_name_1 file_name_2 ... file_name_p\n", argv[0]);
      return -1;
    }

  Data_Bus *data;
  data = new Data_Bus [thread_quantity];
  if (data == nullptr)
    {
      printf ("[ERROR] Not enough memmory for Data_Bus\n");
      return -2;
    }

  double *avg = new double [thread_quantity];
  if (avg == nullptr)
    {
      delete [] data;
      printf ("[ERROR] Not enough memmory for Average_array\n");
      return -2;
    }

  int *status = new int [thread_quantity];
  if (status == nullptr)
    {
      delete [] data;
      delete [] avg;
      printf ("[ERROR] Not enough memmory for Status_array\n");
      return -2;
    }

  int *result = new int [thread_quantity];
  if (result == nullptr)
    {
      delete [] data;
      delete [] avg;
      delete [] status;
      printf ("[ERROR] Not enough memmory for Result_array\n");
      return -2;
    }

  pthread_barrier_t barrier;
  int ret = pthread_barrier_init (&barrier, nullptr, thread_quantity);
  if (ret != 0)
    {
      printf ("[ERROR] Can't initialize barier\n");
      delete [] data;
      delete [] avg;
      delete [] status;
      delete [] result;
      return -3;
    }

  int i = 0;
  for (i = 0; i < thread_quantity; i++)
    {
      data[i].avg = avg;

      data[i].status = status;
      data[i].file_names = argv + 1;
      data[i].result = result;

      data[i].thread_quantity = thread_quantity;
      data[i].curr_thread = i;
      data[i].barrier = &barrier;

      avg[i] = 0;
      status[i] = 0;
      result[i] = 0;
    }

  pthread_t thread;
  for (i = 1; i < thread_quantity; i++)
    {
      ret = pthread_create (&thread, nullptr, thread_func, data + i);
      if (ret != 0)
        {
          printf ("[ERROR] Can't initialize barier\n");
          delete [] data;
          delete [] avg;
          delete [] status;
          delete [] result;
          return -4;
        }
    }

  thread_func (data + 0);
  pthread_barrier_destroy (&barrier);
  bool aborted = false;

  for (i = 0; i < thread_quantity; i++)
    {
      if (status[i] < 0)
        {
          aborted = true;
          if (status[i] == CANNOT_OPEN_FILE)
              printf ("[ERROR] Can't open %s\n", argv[i + 1]);

          else if (status[i] == CANNOT_READ_FILE)
              printf ("[ERROR] Can not read %s\n", argv[i + 1]);
        }
    }

  int answer = 0;
  if (!aborted)
    {
      answer = 0;
      for (i = 0; i < thread_quantity; i++)
          answer += result[i];

      printf ("[OUTPUT] Answer: %d\n", answer);
    }

    pthread_detach(thread);
  pthread_join(thread, 0);

  delete [] data;
  delete [] avg;
  delete [] status;
  delete [] result;

  return 0;
}
