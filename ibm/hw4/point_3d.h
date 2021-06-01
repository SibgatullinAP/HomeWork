#ifndef POINT_3D_H
#define POINT_3D_H

class point_3d
{
public:
  point_3d(double x, double y, double z) : m_x (x), m_y (y), m_z (z) {}
  point_3d() = default;
  ~point_3d() = default;

  double m_x = 0;
  double m_y = 0;
  double m_z = 0;

  point_3d& operator= (const point_3d &other) = default;
};

class triangle_3d
{
public:
  triangle_3d(point_3d *a, point_3d *b, point_3d *c) : m_a (a), m_b (b), m_c (c) {}
  triangle_3d() = default;
  ~triangle_3d() = default;

  point_3d *m_a = nullptr;
  point_3d *m_b = nullptr;
  point_3d *m_c = nullptr;

  triangle_3d& operator= (const triangle_3d &other) = default;
};

#endif // POINT_3D_H
