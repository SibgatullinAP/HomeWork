#include "thread_func.h"

void * thread_func (void * ptr)
{
  kernel_data *data = (kernel_data *) ptr;
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

          int nx = data->m_nx;
          int ny = data->m_ny;
          data->m_eps = data->m_common_data->eps;

          if (data->m_k == 0)
            {
              pthread_mutex_lock (&(data->m_common_data->all));

              data->m_common_data->first = false;
              data->m_common_data->b = new double [(nx + 1) * (ny + 1)];
              data->m_common_data->answer = new double [(nx + 1) * (ny + 1)];
              data->m_common_data->r = new double [(nx + 1) * (ny + 1)];
              data->m_common_data->u = new double [(nx + 1) * (ny + 1)];
              data->m_common_data->v = new double [(nx + 1) * (ny + 1)];
              data->m_common_data->A = new double [(nx + 1) * (ny + 1) + 1 + data->get_len (nx, ny)];
              data->m_common_data->I = new int [(nx + 1) * (ny + 1) + 1 + data->get_len (nx, ny)];
              data->m_common_data->buff = new double [data->m_thread_quantity];
              data->allocate (data->m_common_data->A,
                              data->m_common_data->b,
                              data->m_common_data->I,
                              data->m_nx,
                              data->m_ny);

              pthread_mutex_unlock (&(data->m_common_data->all));
            }

          data->m_rectangle = data->m_common_data->m_rectangle;

          if (data->m_k == 0)
            {
              for (int u = 0; u < (nx + 1) * (ny + 1); u ++)
                {
                  data->m_common_data->answer[u] = 0.0;
                  data->m_common_data->b[u] = 0.0;
                  data->m_common_data->r[u] = 0.0;
                  data->m_common_data->u[u] = 0.0;
                  data->m_common_data->v[u] = 0.0;
                }
            }

          reduce_sum (data->m_thread_quantity, 0, 1);

          data->calculate_matrix (data->m_common_data->A,
                                  data->m_common_data->I,
                                  data->m_nx,
                                  data->m_ny,
                                  data->m_thread_quantity,
                                  data->m_k);
          data->calculate_rhs (data->m_common_data->b,
                               data->m_nx,
                               data->m_ny,
                               data->m_thread_quantity,
                               data->m_k);

          if (data->m_k == 0)
            data->normalization (data->m_common_data->A,
                                 data->m_common_data->b,
                                 data->m_nx,
                                 data->m_ny,
                                 data->m_thread_quantity,
                                 data->m_k);

          int ret = data->solver (data->m_common_data->A, data->m_common_data->I,
                                  (data->m_nx + 1) * (data->m_ny + 1), data->m_common_data->b,
                                  data->m_common_data->answer, data->m_common_data->r,
                                  data->m_common_data->u, data->m_common_data->v, data->m_eps,
                                  1000, data->m_thread_quantity,
                                  data->m_k, data->m_common_data->buff);
          if (ret < 0)
            printf ("[ERROR] Can't solve matrix\n");

          reduce_sum (data->m_thread_quantity, 0, 1);
          pthread_mutex_lock (&(data->m_common_data->all));
          data->m_common_data->m_task = gui_task::NO_CHANGED;
          data->m_common_data->m_status = status::DONE;
          data->m_common_data->m_iter = data->m_itter;
          pthread_mutex_unlock (&(data->m_common_data->all));
        }
    }
  return 0;
}
