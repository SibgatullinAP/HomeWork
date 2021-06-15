#ifndef WINDOW_H
#define WINDOW_H

#include "function.h"
#include "coordinate.h"
#include "common.h"
#include "methods.h"

#define NEWTON_BOUNDS_MAX 40
#define NEWTON_BOUNDS_MIN 2

#define SPLINE_BOUNDS_MAX 10000000000000
#define SPLINE_BOUNDS_MIN 3

enum class event_painter_type
{
  SPLINE_QUADRIC,
  SPLINE_RESIDUAL,
  BOTH,
  NEWTON,
  NEWTON_RESIDUAL,
  BOTH_RESIDUAL,

  COUNT
};

event_painter_type operator++(event_painter_type &x);
const char *enum_to_string (event_painter_type event_type);

class window : public QWidget
{
  Q_OBJECT

private:
  function m_func;
  event_painter_type m_event_type;

  newton m_newton_approx;
  spline m_spline_approx;

  double m_a;
  double m_b;
  int m_n;

  bool m_enable_warning = true;

public:
  window (QWidget *parent);

  QSize minimumSizeHint () const;
  QSize sizeHint () const;

  void set_warning (bool is_enabled);

  int parse_command_line (int argc, char *argv[]);
  const char *change_paint_event_handler ();
  const char *change_func_handler ();
  const char *double_n_handler ();
  const char *halve_n_handler ();
  const char *double_domain_handler ();
  const char *halve_domain_handler ();
  const char *add_perturbation_handler ();
  const char *subtract_perturbation_handler ();

public slots:
  void change_func ();
  void change_paint_event ();

  void double_n ();
  void halve_n ();

  void double_domain ();
  void halve_domain ();

  void add_perturbation ();
  void subtract_perturbation ();

protected:
  void paintEvent (QPaintEvent *event);
  void paint_func_graph (QPainter &painter, coordinate &coord, std::function<double(double)> func);

};

#endif
