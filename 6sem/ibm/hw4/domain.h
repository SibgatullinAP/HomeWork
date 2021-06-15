#ifndef DOMAIN_H
#define DOMAIN_H

#include "common.h"

// a -- b
// |    |
// c -- d

class domain
{
  point_3d m_a = {};
  point_3d m_b = {};
  point_3d m_c = {};
  point_3d m_d = {};
public:
  domain() = default;
  ~domain() = default;

  void set_corners (const point_3d &a, const point_3d &d);
  point_3d get_a () const {return  m_a;}
  point_3d get_b () const {return  m_b;}
  point_3d get_c () const {return  m_c;}
  point_3d get_d () const {return  m_d;}

  domain& operator= (const domain &other) = default;
  bool parse_file (char *file_name);
};

#endif // DOMAIN_H
