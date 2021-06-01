#ifndef DATA_BUS_H
#define DATA_BUS_H

#include "common.h"
#include "domain.h"

enum class gui_task
{
  NO_CHANGED,
  CHANGED_FUNCTION,
  CHANGED_NXNY,

  COUNT
};

enum class status
{
  FREE,
  COMPUTING,
  DONE,

  COUNT
};
const char *enum_to_string (status state);

class data_bus
{
public:
  data_bus () = default;
  ~data_bus () = default;

public :
  status m_status = status::FREE;
  gui_task m_task = gui_task::NO_CHANGED;
  int m_nx = 0;
  int m_ny = 0;
  int m_iter = 0;
  bool first = true;
  domain m_rectangle = {};
  std::function<double(double, double)> m_func = {};
  double eps = 0;

  // for GUI and Kernel
  double *answer = nullptr;

  //for Kernel
  double *b = nullptr;
  double *u = nullptr;
  double *v = nullptr;
  double *r = nullptr;
  double *A = nullptr;
  double *buff = nullptr;
  int *I = nullptr;
  pthread_mutex_t all = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_t calc = PTHREAD_MUTEX_INITIALIZER; // ONLY FOR KERNEL !!!
  pthread_cond_t c_in = PTHREAD_COND_INITIALIZER; // ONLY FOR KERNEL !!!
};

#endif // DATA_BUS_H
