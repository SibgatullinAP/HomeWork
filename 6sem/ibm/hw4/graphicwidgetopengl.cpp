#include "graphicwidgetopengl.h"

graphicWidgetOpenGl::graphicWidgetOpenGl(QWidget *parent) : QOpenGLWidget (parent)
{

}

graphicWidgetOpenGl::~graphicWidgetOpenGl () {}

void graphicWidgetOpenGl::initializeGL ()
{
  initializeOpenGLFunctions ();
  glClearColor (1, 1, 1, 1);
  glEnable (GL_DEPTH_TEST);
  create_ortho_proj ();
  reset_coordinate_system ();
}

void graphicWidgetOpenGl::paintGL()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode (GL_MODELVIEW_MATRIX);
  glLoadIdentity ();

  glRotated (m_x_angle, 1.0, 0.0, 0.0);
  glRotated (m_y_angle, 0.0, 1.0, 0.0);
  glRotated (-90, 1.0, 0.0, 0.0);
  glRotated (m_z_angle, 0.0, 0.0, 1.0);

  glScaled (m_scale, m_scale, m_scale);

  m_actual_grid->enable_style ();
  m_actual_grid->draw_lines ();
  m_actual_grid->disable_style ();

  m_domain_grid->draw_lines ();

  draw_axis ();
}

void graphicWidgetOpenGl::reset_coordinate_system ()
{
  glMatrixMode (GL_MODELVIEW_MATRIX);
  glLoadIdentity ();

  m_x_angle = 30;
  m_y_angle = 45;
  m_z_angle = -180;
  m_scale = 0.5;

  glRotated (m_x_angle, 1.0, 0.0, 0.0);
  glRotated (m_y_angle, 1.0, 1.0, 0.0);
  glRotated (-90, 1.0, 0.0, 0.0);
  glRotated (m_z_angle, 0.0, 0.0, 1.0);
}

void graphicWidgetOpenGl::create_ortho_proj ()
{
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  glOrtho (-1, 1, -1, 1, -10, 10);
  glMatrixMode (GL_MODELVIEW);
}

void graphicWidgetOpenGl::create_ortho_proj (double near, double far)
{
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  glOrtho (-2, 2, -2, 2, near, far);
  glMatrixMode (GL_MODELVIEW);
}

void graphicWidgetOpenGl::draw_axis ()
{
  // x axis
  glColorMaterial (GL_FRONT_AND_BACK, GL_SPOT_DIRECTION);
  glEnable (GL_COLOR_MATERIAL);

  glColor4ub (100, 0, 0, 1);
  glBegin (GL_LINES);
  glVertex3d (100, 0, 0);
  glVertex3d (-100, 0, 0);
  glEnd ();

  //y axis
  glColor3b (0, 0, 100);
  glBegin (GL_LINES);
  glVertex3d (0, 100, 0);
  glVertex3d (0, -100, 0);
  glEnd ();

  //z axis
  glColor3b (0, 100, 0);
  glBegin (GL_LINES);
  glVertex3d (0, 0, 100);
  glVertex3d (0, 0, -100);
  glEnd ();

  glColor3b (0, 0, 0);
}

void graphicWidgetOpenGl::mousePressEvent (QMouseEvent *event)
{
  if (event->buttons () == Qt::LeftButton)
    {
      m_mouse_position = event->pos ();
      return;
    }

  if (event->button () == Qt::MiddleButton)
    {
      reset_coordinate_system ();
      update ();
    }
}

void graphicWidgetOpenGl::mouseMoveEvent (QMouseEvent *event)
{
  QPoint diff = event->pos () - m_mouse_position;
  if (event->buttons () == Qt::LeftButton)
    {
      set_x_angle (m_x_angle + diff.y () / 2.);
      set_y_angle (m_y_angle + diff.x () / 2.);
    }
  m_mouse_position = event->pos ();
}

void graphicWidgetOpenGl::wheelEvent (QWheelEvent *event)
{
  if (event->delta () > 0)
    double_area ();
  else if (event->delta () < 0)
    halve_area ();
}

void graphicWidgetOpenGl::set_x_angle (double angle)
{
  if (fabs (angle - m_x_angle) > 1e-2)
    {
      m_x_angle = angle;
      update ();
    }
}

void graphicWidgetOpenGl::set_y_angle (double angle)
{
  if (fabs (angle - m_y_angle) > 1e-2)
    {
      m_y_angle = angle;
      update ();
    }
}

void graphicWidgetOpenGl::set_z_angle (double angle)
{
  if (fabs (angle - m_y_angle) > 1e-2)
    {
      m_z_angle = angle;
      update ();
    }
}
