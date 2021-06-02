#include "thread_func.h"

void * thread_func (void * ptr)
{
  solver_unit *data = (solver_unit *) ptr;
  while (true)
    {
      pthread_mutex_lock (&(data->m_common_data->calc));

      while (data->m_common_data->m_task == gui_task::NO_CHANGED)
        pthread_cond_wait (&(data->m_common_data->c_in), &(data->m_common_data->calc));

      pthread_mutex_unlock (&(data->m_common_data->calc));

      if (data->m_common_data->m_task == gui_task::CHANGED_NXNY || data->m_common_data->m_task == gui_task::CHANGED_FUNCTION )
        {
          pthread_mutex_lock (&(data->m_common_data->all));
          data->m_common_data->m_status = status::COMPUTING;
          pthread_mutex_unlock (&(data->m_common_data->all));

          data->m_nx = data->m_common_data->m_nx;
          data->m_ny = data->m_common_data->m_ny;
          data->m_func = data->m_common_data->m_func;
          data->m_eps = data->m_common_data->m_eps;
          data->m_rectangle = data->m_common_data->m_rectangle;

          if (data->m_thread_id == 0)
            {
              pthread_mutex_lock (&(data->m_common_data->all));
              data->allocate ();
              pthread_mutex_unlock (&(data->m_common_data->all));
            }


          reduce_sum (data->m_thread_number, 0, 1);

          data->calculate_matrix ();
          data->calculate_rhs ();

          if (data->m_thread_id == 0)
            data->normalization ();

          int ret = data->solver (SOLVER_MAX_ITTERTION);

          if (ret < 0)
            printf ("[ERROR] Can't solve matrix\n");

          reduce_sum (data->m_thread_number, 0, 1);

          pthread_mutex_lock (&(data->m_common_data->all));
          data->m_common_data->m_task = gui_task::NO_CHANGED;
          data->m_common_data->m_status = status::DONE;
          data->m_common_data->m_iter = data->m_itter;
          pthread_mutex_unlock (&(data->m_common_data->all));
        }
    }
  return 0;
}

void reduce_sum (int p, int * a, int n)
{
  static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
  static pthread_cond_t c_in = PTHREAD_COND_INITIALIZER;
  static pthread_cond_t c_out = PTHREAD_COND_INITIALIZER;
  static int t_in = 0;
  static int t_out = 0;
  static int *p_a = 0;
  int i = 0;
  if (p <= 1)
    return;

  pthread_mutex_lock (&m);
  if (p_a == nullptr)
    p_a = a;

  else
    for (i = 0; i < n; i ++)
      p_a [i] += a[i];


  t_in ++;
  if (t_in >= p)
    {
      t_out = 0;
      pthread_cond_broadcast (&c_in);
    }
  else
    while (t_in < p)
      pthread_cond_wait (&c_in, &m);


  if (p_a != a)
    for (i = 0; i < n; i ++)
      a [i] = p_a [i];

  t_out++;
  if (t_out >= p)
    {
      t_in = 0;
      p_a = 0;
      pthread_cond_broadcast (&c_out);
    }
  else
    while (t_out < p)
      pthread_cond_wait (&c_out, &m);

  pthread_mutex_unlock (&m);
}

