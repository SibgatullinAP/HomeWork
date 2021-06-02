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
  domain m_rectangle = {};
  std::function<double(double, double)> m_func = {};
  double m_eps = 0;

  // for GUI and Kernel
  double *answer = nullptr;

  //for Kernel
  double *m_b = nullptr;
  double *m_u = nullptr;
  double *m_v = nullptr;
  double *m_r = nullptr;
  double *m_A = nullptr;
  int *m_I = nullptr;
  double *m_buff = nullptr;

  pthread_mutex_t all = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_t calc = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t c_in = PTHREAD_COND_INITIALIZER;
};

#endif // DATA_BUS_H
