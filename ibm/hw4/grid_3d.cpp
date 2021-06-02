#include "grid_3d.h"

grid_3d::grid_3d (domain &rect, int nx, int ny, std::function<double(double, double)> func)
{
  m_nx = nx;
  m_ny = ny;
  m_points.resize ((m_nx + 1) * (m_ny + 1));
  m_triangles.resize (2 * m_nx * m_ny);
  m_rectangle = rect;
  m_func = func;

  update (m_nx, m_ny, m_func);
}

void grid_3d::fill_points ()
{
  point_3d a = m_rectangle.get_a ();
  point_3d b = m_rectangle.get_b ();
  point_3d c = m_rectangle.get_c ();

  double hx = (b.m_x - a.m_x) / m_nx;
  double hy = (a.m_y - c.m_y) / m_ny;

  for (int i = 0; i < m_ny + 1; i++)
    for (int j = 0; j < m_nx + 1; j++)
      m_points[i * (m_ny + 1) + j] = {a.m_x + j * hx, c.m_y + i * hy, m_func (a.m_x + j * hx, c.m_y + i * hy)};

}

void grid_3d::fill_triangles ()
{
  point_3d *points_ptr = m_points.data ();
  for (int i = 0; i < 2 * m_ny; i += 2)
    for (int j = 0; j < m_nx; j++)
      {
        m_triangles [m_ny * (i + 0) + j] = {points_ptr + j + i / 2 * (m_ny + 1),
                                           points_ptr + j + 1 + i / 2 * (m_ny + 1),
                                           points_ptr + j + (i / 2 + 1) * (m_ny + 1)};

        m_triangles [m_ny * (i + 1) + j] = {points_ptr + j + 1 + i / 2 * (m_ny + 1),
                                           points_ptr + j + (i / 2 + 1) * (m_ny + 1),
                                           points_ptr + j + 1 + (i / 2 + 1) * (m_ny + 1)};
      }

}

void grid_3d::update (int nx, int ny, std::function<double(double, double)> func)
{
  if (m_nx != nx || m_ny != ny)
    {
      m_nx = nx;
      m_ny = ny;
      m_points.resize ((m_nx + 1) * (m_ny + 1));
      m_triangles.resize (2 * m_nx * m_ny);
    }

  m_func = func;
  fill_points ();
  fill_triangles ();
  find_max ();
}

void grid_3d::find_max ()
{
  point_3d a = m_rectangle.get_a ();
  point_3d b = m_rectangle.get_b ();
  point_3d c = m_rectangle.get_c ();

  double hx = (b.m_x - a.m_x) / m_nx;
  double hy = (a.m_y - c.m_y) / m_ny;

  double tmp_max = 0;
  for (int i = 0; i < m_ny + 1; i++)
    for (int j = 0; j < m_nx + 1; j++)
      tmp_max = fabs (m_func (a.m_x + j * hx, c.m_y + i * hy)) > tmp_max
                ?  fabs (m_func (a.m_x + j * hx, c.m_y + i * hy)) : tmp_max;

  m_max_val = tmp_max;
}


void drawable_grid::draw_lines ()
{
  fill_triangles ();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin (GL_TRIANGLES);

  for (int i = 0; i < 2 * m_ny; i += 2)
    for (int j = 0; j < m_nx; j++)
      {
        triangle_3d curr_triangle_1 = m_triangles[m_ny * (i + 0) + j];
        triangle_3d curr_triangle_2 = m_triangles[m_ny * (i + 1) + j];

        glVertex3d (curr_triangle_1.m_a->m_x, curr_triangle_1.m_a->m_y, curr_triangle_1.m_a->m_z);
        glVertex3d (curr_triangle_1.m_b->m_x, curr_triangle_1.m_b->m_y, curr_triangle_1.m_b->m_z);
        glVertex3d (curr_triangle_1.m_c->m_x, curr_triangle_1.m_c->m_y, curr_triangle_1.m_c->m_z);

        glVertex3d (curr_triangle_2.m_a->m_x, curr_triangle_2.m_a->m_y, curr_triangle_2.m_a->m_z);
        glVertex3d (curr_triangle_2.m_b->m_x, curr_triangle_2.m_b->m_y, curr_triangle_2.m_b->m_z);
        glVertex3d (curr_triangle_2.m_c->m_x, curr_triangle_2.m_c->m_y, curr_triangle_2.m_c->m_z);

      }
  glEnd ();
}

drawable_grid::~drawable_grid ()
{

};
void drawable_grid::enable_style ()
{
  (void) 0;
}

void drawable_grid::disable_style ()
{
 glColor4ub (0, 0, 0, 1);
 glDisable (GL_COLOR_MATERIAL);
}

void function_draw_grid::enable_style ()
{
  glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable (GL_COLOR_MATERIAL);

  glColor4ub (15, 150, 15, 1);
}

void approximation_draw_grid::enable_style ()
{
  glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable (GL_COLOR_MATERIAL);

  glColor4ub (15, 15, 150, 1);
}

void residual_draw_grid::enable_style ()
{
  glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable (GL_COLOR_MATERIAL);

  glColor4ub (150, 15, 15, 1);
}

