#include "kernel.h"

kernel::kernel (int thread_quantity, data_bus *common_data)
{
  m_common_data = common_data;
  m_thread_quantity = thread_quantity;

  m_tids = new pthread_t [m_thread_quantity];
  m_kernel_data = new kernel_data [m_thread_quantity];

  for (int i = 0; i < m_thread_quantity; i++)
    m_kernel_data[i].set_arg (m_thread_quantity, i, common_data->m_nx, common_data->m_ny, common_data->eps, common_data);

  for (int i = 0; i < m_thread_quantity; i++)
    pthread_create (m_tids + i, 0, &thread_func, m_kernel_data + i);

}

kernel::~kernel ()
{
  delete [] m_tids;
  delete [] m_kernel_data;
}
