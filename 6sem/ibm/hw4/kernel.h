#ifndef KERNEL_H
#define KERNEL_H

#include "common.h"
#include "thread_func.h"


class kernel
{
  pthread_t *m_tids = nullptr;
  int m_thread_quantity = 0;
  data_bus *m_common_data = nullptr;
  solver_unit *m_kernel_data = nullptr;

public:
  kernel (int thread_quantity, data_bus *common_data);
  ~kernel ();
};

#endif // KERNEL_H
