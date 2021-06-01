#include "window.h"

event_painter_type operator++(event_painter_type &x)
{
  x = (event_painter_type)((std::underlying_type<event_painter_type>::type(x) + 1)
                           % (int) event_painter_type::COUNT);
  return x;
}

const char *enum_to_string (event_painter_type event_type)
{
  switch (event_type)
    {
    case event_painter_type::NEWTON:
      return "Newton's polynoms";
    case event_painter_type::SPLINE_QUADRIC:
      return "Parabolic spline with first derivative";
    case event_painter_type::BOTH:
      return "Spline and Newton";
    case event_painter_type::NEWTON_RESIDUAL:
      return "Newton's residual";
    case event_painter_type::SPLINE_RESIDUAL:
      return "Spline's residual";
    case event_painter_type::BOTH_RESIDUAL:
      return "Residual of both methods";
    case event_painter_type::COUNT:
      return "Invalid method";
    }
  return "";
}

window::window (QWidget *parent)
  : QWidget (parent)
{
  m_a = 0;
  m_b = 0;
  m_n = 0;

  m_func = {};
  m_newton_approx = {};
  m_spline_approx = {};
  m_event_type = event_painter_type::SPLINE_QUADRIC;
}

QSize window::minimumSizeHint () const
{
  return QSize (300, 300);
}

QSize window::sizeHint () const
{
  return QSize (1000, 1000);
}

int window::parse_command_line (int argc, char *argv[])
{
  if (argc != 5)
    return -1;

  int formula_type = 0;

  if (   sscanf (argv[1], "%lf", &m_a) != 1
         || sscanf (argv[2], "%lf", &m_b) != 1
         || sscanf (argv[3], "%d", &m_n) != 1
         || m_n <= 0
         || sscanf (argv[4], "%d", &formula_type) != 1
         || (formula_type > 6 || formula_type < 0))
    return -2;

  m_func.set_func_type ((function_type) (formula_type));
  m_func.set_pertrub_params (m_a, m_b, m_n);

  m_newton_approx.set_func (&m_func);
  m_spline_approx.set_func (&m_func);
  return 0;
}

void window::set_warning (bool is_enabled)
{
  m_enable_warning = is_enabled;
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
const char *window::change_paint_event_handler ()
{
  event_painter_type tmp_type = m_event_type;
  ++tmp_type;

  if (m_n > NEWTON_BOUNDS_MAX)
    {
      if (tmp_type == event_painter_type::NEWTON)
        {
          m_event_type = event_painter_type::SPLINE_QUADRIC;
          return "Error! N is too much for Newton's interpolation.\n"
                 "Spline interpolation will be shown instead!";
        }

      if (tmp_type == event_painter_type::BOTH)
        {
          m_event_type = event_painter_type::SPLINE_QUADRIC;
          return "Error! N is too much for Newton's interpolation.\n"
                 "Spline interpolation will be shown instead!";
        }

      if (tmp_type == event_painter_type::NEWTON_RESIDUAL)
        {
          m_event_type = event_painter_type::SPLINE_RESIDUAL;
          return "Error! N is too much for Newton's interpolation.\n"
                 "Spline interpolation's residual be will be shown instead!";
        }

      if (tmp_type == event_painter_type::BOTH_RESIDUAL)
        {
          m_event_type = event_painter_type::SPLINE_RESIDUAL;
          return "Error! N is too much for Newton's interpolation.\n"
                 "Spline interpolation's residual be will be shown instead!";
        }

      m_event_type = tmp_type;
      return "";
    }

  m_event_type = tmp_type;
  return "";
}

const char *window::double_domain_handler ()
{
  double new_a = m_a;
  double new_b = m_b;
  double center = (new_a + new_b) / 2;

  new_b = (new_b - center) * 2 + center;
  new_a = (new_a - center) * 2 + center;

  if (new_b - new_a > 1e306)
    return "Error, [a;b] has too large length";

  double a_bounds = m_func.get_domain_bounds (m_func.get_func_type ()).first;
  double b_bounds = m_func.get_domain_bounds (m_func.get_func_type ()).second;

  if (new_a < a_bounds || new_b > b_bounds)
    return "Error! [a;b] is incorrect domain for function.\n"
           "Spline interpolation's residual be will be shown instead!";

  m_a = new_a;
  m_b = new_b;

  m_func.set_pertrub_params (m_a, m_b, std::nullopt);
  return "";
}

const char *window::halve_domain_handler ()
{
  double new_a = m_a;
  double new_b = m_b;
  double center = (new_a + new_b) / 2;

  new_b = (new_b - center) / 2 + center;
  new_a = (new_a - center) / 2 + center;

  if (new_b - new_a < 1e-5)
    return "Error, [a;b] has too small length";

  double a_bounds = m_func.get_domain_bounds (m_func.get_func_type ()).first;
  double b_bounds = m_func.get_domain_bounds (m_func.get_func_type ()).second;

  if (new_a < a_bounds || new_b > b_bounds)
    return "Error! [a;b] is incorrect domain for function.\n"
           "Spline interpolation's residual be will be shown instead!";

  m_a = new_a;
  m_b = new_b;

  m_func.set_pertrub_params (m_a, m_b, std::nullopt);
  return "";
}

const char *window::add_perturbation_handler ()
{
  m_func.increase_pertrub ();
  return "";
}

const char *window::subtract_perturbation_handler ()
{
  m_func.decrease_pertrub ();
  return "";
}

const char *window::change_func_handler ()
{
  function_type tmp_type = m_func.get_func_type ();
  ++tmp_type;

  double bound_a = m_func.get_domain_bounds (tmp_type).first;
  double bound_b = m_func.get_domain_bounds (tmp_type).second;

  if (m_b > bound_b || m_a < bound_a)
    return "Error! [a;b] is incorrect domain for function.\n"
           "Spline interpolation's residual be will be shown instead!";

  m_func.set_func_type (tmp_type);
  return "";
}

const char *window::double_n_handler ()
{
  int tmp_n = m_n * 2;

  if (m_event_type == event_painter_type::NEWTON
      || m_event_type == event_painter_type::BOTH
      || m_event_type == event_painter_type::NEWTON_RESIDUAL
      || m_event_type == event_painter_type::BOTH_RESIDUAL)
    {
      if (tmp_n > NEWTON_BOUNDS_MAX)
        return "Error! N is too much for Newton's interpolation.\n"
               "Previuos N values will be used instead!";
      else if (tmp_n < NEWTON_BOUNDS_MIN)
        return "Error! N is too small for Newton's interpolation.\n"
               "Previuos N values will be used instead!";

      m_n = tmp_n;
      m_func.set_pertrub_params (std::nullopt, std::nullopt, m_n);
      return "";
    }

  if (m_event_type == event_painter_type::SPLINE_QUADRIC
      || m_event_type == event_painter_type::BOTH
      || m_event_type == event_painter_type::SPLINE_RESIDUAL
      || m_event_type == event_painter_type::BOTH_RESIDUAL)
    {
      if (tmp_n < SPLINE_BOUNDS_MIN)
        return "Error! N is too small for Spline interpolation."
               "Previuos N values will be used instead!";

      m_n = tmp_n;
      m_func.set_pertrub_params (std::nullopt, std::nullopt, m_n);
      return "";
    }

  return "";
}

const char *window::halve_n_handler ()
{
  int tmp_n = m_n / 2;

  if (m_event_type == event_painter_type::NEWTON
      || m_event_type == event_painter_type::BOTH
      || m_event_type == event_painter_type::NEWTON_RESIDUAL
      || m_event_type == event_painter_type::BOTH_RESIDUAL)
    {
      if (tmp_n > NEWTON_BOUNDS_MAX)
        return "Error! N is too much for Newton's interpolation.\n"
               "Previuos N values will be used instead!";
      else if (tmp_n < NEWTON_BOUNDS_MIN)
        return "Error! N is too small for Newton's interpolation.\n"
               "Previuos N values will be used instead!";

      m_n = tmp_n;
      m_func.set_pertrub_params (std::nullopt, std::nullopt, m_n);
      return "";
    }

  if (m_event_type == event_painter_type::SPLINE_QUADRIC
      || m_event_type == event_painter_type::BOTH
      || m_event_type == event_painter_type::SPLINE_RESIDUAL
      || m_event_type == event_painter_type::BOTH_RESIDUAL)
    {
      if (tmp_n < SPLINE_BOUNDS_MIN)
        return "Error! N is too much for Spline interpolation."
               "Previuos N values will be used instead!";

      m_n = tmp_n;
      m_func.set_pertrub_params (std::nullopt, std::nullopt, m_n);
      return "";
    }

  return "";
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
void window::change_paint_event ()
{
  QString ret_err = change_paint_event_handler ();
  if (ret_err != "" && m_enable_warning)
    QMessageBox::warning (0, "Warning", ret_err);

  update ();
}

void window::double_n ()
{
  QString ret_err = double_n_handler ();
  if (ret_err != "" && m_enable_warning)
    QMessageBox::warning (0, "Warning", ret_err);

  update ();
}

void window::halve_n ()
{
  QString ret_err = halve_n_handler ();
  if (ret_err != "" && m_enable_warning)
    QMessageBox::warning (0, "Warning", ret_err);

  update ();
}

void window::double_domain ()
{
  QString ret_err = double_domain_handler ();
  if (ret_err != "" && m_enable_warning)
    QMessageBox::warning (0, "Warning", ret_err);

  update ();
}
void window::halve_domain ()
{
  QString ret_err = halve_domain_handler ();
  if (ret_err != "" && m_enable_warning)
    QMessageBox::warning (0, "Warning", ret_err);

  update ();
}

void window::add_perturbation ()
{
  QString ret_err = add_perturbation_handler ();
  if (ret_err != "" && m_enable_warning)
    QMessageBox::warning (0, "Warning", ret_err);

  update ();
}
void window::subtract_perturbation ()
{
  QString ret_err = subtract_perturbation_handler ();
  if (ret_err != "" && m_enable_warning)
    QMessageBox::warning (0, "Warning", ret_err);

  update ();
}

void window::change_func ()
{
  QString ret_err = change_func_handler ();
  if (ret_err != "" && m_enable_warning)
    QMessageBox::warning (0, "Warning", ret_err);

  update ();
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
void window::paint_func_graph (QPainter &painter, coordinate &coord, std::function<double(double)> func)
{
  int dot_x1 = 1;
  int dot_y1 = coord.get_v (func (coord.get_x (dot_x1)));

  int dot_x2 = 0;
  int dot_y2 = 0;

  for (int i = 1; i < width(); i++)
    {
      dot_x2 = dot_x1 + 1;
      dot_y2 = coord.get_v (func (coord.get_x (dot_x2)));

      painter.drawLine (QPointF(dot_x1, dot_y1), QPointF(dot_x2, dot_y2));

      dot_x1 = dot_x2;
      dot_y1 = dot_y2;
    }
}

void window::paintEvent (QPaintEvent * /* event */)
{  
  QPainter painter (this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.save ();

  QPen pen_ref_func (Qt::black, 0, Qt::SolidLine);
  QPen pen_newton (Qt::blue, 0, Qt::SolidLine);
  QPen pen_spline (Qt::green, 0, Qt::SolidLine);
  QPen pen_newton_residual (Qt::blue, 3, Qt::DotLine);
  QPen pen_spline_residual (Qt::green, 3, Qt::DotLine);
  QPen pen_axis (Qt::red, 0, Qt::SolidLine);

  painter.translate (0, height ());
  painter.scale (1, -1);

  std::function<double(double)> func = m_func.get_func ();
  std::function<double(double)> func_newton_approx;
  std::function<double(double)> func_spline_approx;
  std::pair<double, double> min_max;
  coordinate coord;

  switch (m_event_type)
    {
    case event_painter_type::NEWTON:
      m_newton_approx.update (m_a, m_b, m_n);
      func_newton_approx = m_newton_approx.get_func ();
      min_max = find_min_max (m_a, m_b, func, width ());
      coord.set_state (m_a, m_b, min_max.first, min_max.second, width (), height ());
      painter.setPen (pen_ref_func);
      paint_func_graph (painter, coord, m_func.get_func ());
      painter.setPen (pen_newton);
      paint_func_graph (painter, coord, func_newton_approx);
      break;

    case event_painter_type::SPLINE_QUADRIC:
      m_spline_approx.update (m_a, m_b, m_n);
      func_spline_approx = m_spline_approx.get_func ();
      min_max = find_min_max (m_a, m_b, func, width ());
      coord.set_state (m_a, m_b, min_max.first, min_max.second, width (), height ());
      painter.setPen (pen_ref_func);
      paint_func_graph (painter, coord, m_func.get_func ());
      painter.setPen (pen_spline);
      paint_func_graph (painter, coord, func_spline_approx);
      break;

    case event_painter_type::BOTH:
      m_newton_approx.update (m_a, m_b, m_n);
      m_spline_approx.update (m_a, m_b, m_n);
      func_newton_approx = m_newton_approx.get_func ();
      func_spline_approx = m_spline_approx.get_func ();
      min_max = find_min_max (m_a, m_b, func, width ());
      coord.set_state (m_a, m_b, min_max.first, min_max.second, width (), height ());
      painter.setPen (pen_ref_func);
      paint_func_graph (painter, coord, m_func.get_func ());
      painter.setPen (pen_newton);
      paint_func_graph (painter, coord, func_newton_approx);
      painter.setPen (pen_spline);
      paint_func_graph (painter, coord, func_spline_approx);
      break;

    case event_painter_type::NEWTON_RESIDUAL:
      m_newton_approx.update (m_a, m_b, m_n);
      func_newton_approx = m_newton_approx.get_func ();
      min_max = find_min_max (m_a, m_b, residual (func, func_newton_approx), width ());
      coord.set_state (m_a, m_b, min_max.first, min_max.second, width (), height ());
      painter.setPen (pen_newton_residual);
      paint_func_graph (painter, coord, residual (func, func_newton_approx));
      break;

    case event_painter_type::SPLINE_RESIDUAL:
      m_spline_approx.update (m_a, m_b, m_n);
      func_spline_approx = m_spline_approx.get_func ();
      min_max = find_min_max (m_a, m_b, residual (func, func_spline_approx), width ());
      coord.set_state (m_a, m_b, min_max.first, min_max.second, width (), height ());
      painter.setPen (pen_spline_residual);
      paint_func_graph (painter, coord, residual (func, func_spline_approx));
      break;

    case event_painter_type::BOTH_RESIDUAL:
      m_newton_approx.update (m_a, m_b, m_n);
      m_spline_approx.update (m_a, m_b, m_n);
      func_newton_approx = m_newton_approx.get_func ();
      func_spline_approx = m_spline_approx.get_func ();
      min_max = find_min_max (m_a, m_b, residual (func, func_newton_approx), width ());
      coord.set_state (m_a, m_b, min_max.first, min_max.second, width (), height ());
      painter.setPen (pen_newton_residual);
      paint_func_graph (painter, coord, residual (func, func_newton_approx));
      min_max = find_min_max (m_a, m_b, residual (func, func_spline_approx), width ());
      coord.set_state (m_a, m_b, min_max.first, min_max.second, width (), height ());
      painter.setPen (pen_spline_residual);
      paint_func_graph (painter, coord, residual (func, func_spline_approx));
      break;

    case event_painter_type::COUNT:
      abort ();
    }

  painter.setPen (pen_axis);
  painter.drawLine (0, coord.get_v (0), width (), coord.get_v (0)); // x axis
  painter.drawLine (coord.get_u (0), 0, coord.get_u (0), height ()); // y axis

  painter.restore ();
  painter.setPen ("blue");
  painter.drawText (30, 30, m_func.get_func_name ());
  painter.drawText (30, 50, enum_to_string (m_event_type));
  painter.drawText (30, 70, "N = " + QString::number (m_n));
  painter.drawText (30, 90, "[a;b] = [" + QString::number (m_a) + ";" + QString::number (m_b) + "]");
  painter.drawText (30, 110, "max{|Fmin|, |Fmax|} = "
                    + QString::number (fabs (min_max.first) > fabs (min_max.second) ? fabs (min_max.first) : fabs (min_max.second)
                                                                                      ,'e', 2));
  painter.drawText (30, 130, "Pertrubation = " + QString::number (m_func.get_pertrubation_value ()));

  printf ("\n-------------\n");
  printf ("%s\n", m_func.get_func_name ().toStdString().c_str());
  printf ("%s\n", enum_to_string (m_event_type));
  printf ("N = %d\n", m_n);
  printf ("[a;b] = [%lf;%lf]\n", m_a, m_b);
  printf ("max{|Fmin|, |Fmax|} = %lf\n", fabs (min_max.first) > fabs (min_max.second) ? fabs (min_max.first) : fabs (min_max.second));
  printf ("Pertrubation = %lf\n", m_func.get_pertrubation_value ());
  printf ("-------------\n");
}
