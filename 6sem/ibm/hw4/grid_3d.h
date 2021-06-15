#ifndef GRID_3D_H
#define GRID_3D_H

#include "domain.h"

class grid_3d
{
public:
  double m_max_val = 0;
  int m_nx = 0;
  int m_ny = 0;
  domain m_rectangle = {};
  std::function<double(double, double)> m_func = {};
  std::vector<point_3d> m_points = {};
  std::vector<triangle_3d> m_triangles = {};

public:
  grid_3d () = default;
  grid_3d (domain &rect, int nx, int ny, std::function<double(double, double)> func = [] (double, double) {return 0.;});
  ~grid_3d() = default;

  void fill_points ();
  void fill_triangles ();
  void update (int nx, int ny, std::function<double(double, double)> func);
  void find_max ();
  double get_max_val () const {return m_max_val;}


};

class drawable_grid : public grid_3d
{
public:
  drawable_grid (domain &rect, int nx, int ny, std::function<double(double, double)> func = [] (double, double) {return 0.;})
    : grid_3d (rect, nx, ny, func) {};
  virtual ~drawable_grid ();
  void draw_lines ();
  virtual void enable_style ();
  void disable_style ();

};

class function_draw_grid : public drawable_grid
{
public:
  function_draw_grid (domain &rect, int nx, int ny, std::function<double(double, double)> func = [] (double, double) {return 0.;})
    : drawable_grid (rect, nx, ny, func) {};
  void enable_style () override;
};

class approximation_draw_grid : public drawable_grid
{
public:
  approximation_draw_grid (domain &rect, int nx, int ny, std::function<double(double, double)> func = [] (double, double) {return 0.;})
    : drawable_grid (rect, nx, ny, func) {};
  void enable_style () override;
};

class residual_draw_grid : public drawable_grid
{
public:
  residual_draw_grid (domain &rect, int nx, int ny, std::function<double(double, double)> func = [] (double, double) {return 0.;})
    : drawable_grid (rect, nx, ny, func) {};
  void enable_style () override;
};

#endif // GRID_3D_H
