#ifndef GRAPHICWIDGETOPENGL_H
#define GRAPHICWIDGETOPENGL_H

#include "common.h"
#include "grid_3d.h"

class graphicWidgetOpenGl: public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

public:
  graphicWidgetOpenGl (QWidget *parent);
  ~graphicWidgetOpenGl ();

  double get_x_angle () const {return m_x_angle;}
  double get_y_angle () const {return m_y_angle;}
  double get_z_angle () const {return m_z_angle;}

  void set_x_angle (double angle);
  void set_y_angle (double angle);
  void set_z_angle (double angle);

  void double_area () { m_scale *= SCALE_AREA_COEF; update ();}
  void halve_area () {m_scale /= SCALE_AREA_COEF; update ();}

  void set_domain_grid (drawable_grid *domain_grid) { m_domain_grid = domain_grid;}
  void set_actual_grid (drawable_grid *new_grid) { m_actual_grid = new_grid;}

protected:
  virtual void initializeGL() override;
  virtual void paintGL() override;

  virtual void mousePressEvent (QMouseEvent *event) override;
  virtual void mouseMoveEvent (QMouseEvent *event) override;
  virtual void wheelEvent (QWheelEvent *event) override;

private:
  QPoint m_mouse_position;
  drawable_grid *m_actual_grid = nullptr;
  drawable_grid *m_domain_grid = nullptr;

  double m_x_angle = 0;
  double m_y_angle = 0;
  double m_z_angle = 0;
  double m_scale = 1;

  void reset_coordinate_system ();

  void create_ortho_proj ();
  void create_ortho_proj (double near, double far);
  void draw_axis ();
};

#endif // GRAPHICWIDGETOPENGL_H
