#include "constants.h"

double get_time ()
{
  struct timeval time;
  gettimeofday (&time, nullptr);
  return (double) (time.tv_sec + time.tv_usec / 1e6);
}

double get_cpu_time ()
{
  struct rusage time;
  getrusage (RUSAGE_THREAD, &time);
  return (double) (time.ru_utime.tv_sec + time.ru_utime.tv_usec / 1e6);
}
