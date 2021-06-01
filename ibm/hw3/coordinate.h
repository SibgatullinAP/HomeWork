#ifndef COORDINATE_H
#define COORDINATE_H
#include "common.h"

class coordinate
{
private:
  double m_x_min = 0;
  double m_x_max = 0;
  double m_y_min = 0;
  double m_y_max = 0;

  int m_width = 0;
  int m_height = 0;

public:
  coordinate () = default;
  coordinate(double x_min, double x_max, double y_min, double y_max, int width, int heigth)
  {
    set_state (x_min, x_max, y_min, y_max, width, heigth);
  }

  void set_state (double x_min, double x_max, double y_min, double y_max, int width, int heigth)
  {
    m_x_min = x_min;
    m_x_max = x_max;
    m_y_min = y_min;
    m_y_max = y_max;

    m_width = width;
    m_height = heigth;

    if ((y_max - y_min) < MINIMAL_SCALE_EPS)
      {
        m_y_max += MINIMAL_SCALE;
        m_y_min -= MINIMAL_SCALE;
      }

    if ((x_max - x_min) < MINIMAL_SCALE_EPS)
      {
        m_x_max += MINIMAL_SCALE;
        m_x_min -= MINIMAL_SCALE;
      }
  }

  int get_u (double x) {return 1 + (m_width - 1) * ((x - m_x_min) / (m_x_max - m_x_min));}
  int get_v (double y) {return 1 + (m_height - 1) * ((y - m_y_min) / (m_y_max - m_y_min));}

  double get_x (int u) {return m_x_min + (u - 1) * (m_x_max - m_x_min) / (m_width - 1);}
  double get_y (int v) {return m_y_min + (v - 1) * (m_y_max - m_y_min) / (m_height - 1);}
};

#endif // COORDINATE_H
