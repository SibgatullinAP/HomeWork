#include "window.h"

const char *enum_to_string (paint_mode mode)
{
  switch (mode)
    {
    case paint_mode::FUNCTION:
      return "Function";
    case paint_mode::APPROXIMATION:
      return "Approximation";
    case paint_mode::RESIDUAL:
      return "Residual";
    case paint_mode::COUNT:
      return "Invalid mode";
    }
  return "";
}
paint_mode operator++(paint_mode &x)
{
  x = (paint_mode)((std::underlying_type<paint_mode>::type(x) + 1)
                   % (int) paint_mode::COUNT);
  return x;
}

Window::Window (QWidget *parent, cmd_line_arguments cmd_arguments, domain rectangle) : QWidget(parent)
{
  setup_ui ();
  make_connections ();

  m_rectangle = rectangle;
  m_mode = paint_mode::FUNCTION;
  m_status = status::FREE;
  m_task = gui_task::NO_CHANGED;

  m_nx_new = m_nx = cmd_arguments.nx;
  m_ny_new = m_ny = cmd_arguments.ny;
  m_eps = cmd_arguments.eps;
  m_thread_quantity = cmd_arguments.thread_quantity;

  m_func.set_domain (m_rectangle);
  m_func.set_func_type ((function_type) cmd_arguments.func_type);
  m_approx_func.update (m_rectangle, m_nx, m_ny, m_approx_answer);

  m_common_data = new data_bus;
  m_solver = new kernel (m_thread_quantity, m_common_data);

  domain_drawer = std::make_unique<function_draw_grid> (function_draw_grid (m_rectangle, VISUALIZATION_DOMAIN_NXNY, VISUALIZATION_DOMAIN_NXNY));
  function_drawer = std::make_unique<function_draw_grid> (function_draw_grid (m_rectangle, VISUALIZATION_NX, VISUALIZATION_NY, m_func.get_func ()));
  appproximation_drawer = std::make_unique<approximation_draw_grid> (approximation_draw_grid (m_rectangle, VISUALIZATION_NX, VISUALIZATION_NY));
  residual_drawer = std::make_unique<residual_draw_grid> (residual_draw_grid (m_rectangle, VISUALIZATION_NX, VISUALIZATION_NY));

  m_max_val_func = find_max (m_func.get_func ());

  graphic_widget->set_domain_grid (domain_drawer.get ());
  graphic_widget->set_actual_grid (function_drawer.get ());

  update_info ();
}

Window::~Window ()
{
  delete m_solver;
  delete m_common_data;
  delete [] m_approx_answer;
}

void Window::setup_ui ()
{
  resize(1000, 800);
  setMinimumSize(QSize(1000, 800));

  grid_layout_widget = new QWidget(this);
  graphic_widget = new graphicWidgetOpenGl (grid_layout_widget);
  info_widget = new QWidget(grid_layout_widget);

  grid_layout_widget->setGeometry(QRect(0, 0, width (), height ()));
  common_grid_layout = new QGridLayout(grid_layout_widget);

  //Buttons
  changeModeButton = new QPushButton("Change Mode", grid_layout_widget);
  changeFunctionButton = new QPushButton("Change Function", grid_layout_widget);
  doubleDomainButton = new QPushButton("Double Domain", grid_layout_widget);
  halveDomainButton = new QPushButton("Halve Domain", grid_layout_widget);
  doubleNXNYButton = new QPushButton("Double NX/NY", grid_layout_widget);
  halveNXNYButton = new QPushButton("Halve NX/NY", grid_layout_widget);
  addDisturbButton = new QPushButton("Add Disturbance", grid_layout_widget);
  subDisturbButton = new QPushButton("      Substract Disturbance      ", grid_layout_widget);
  rotateClockwiseButton = new QPushButton("Rotate Сlockwise", grid_layout_widget);
  rotateCoClockwiseButton = new QPushButton("Rotate Counter-clockwise", grid_layout_widget);
  exitButton = new QPushButton("Exit", grid_layout_widget);
  exitButton->setStyleSheet(QStringLiteral("QWidget {background-color:red;}"));

  //Labels
  modeLabel = new QLabel ("Mode: ", info_widget);
  functionLabel = new QLabel ("Function: ", info_widget);
  maxValLabel = new QLabel ("Maximum Value: ", info_widget);
  NXLable = new QLabel ("NX: ", info_widget);
  NYLable = new QLabel ("NY: ", info_widget);
  pertrubationLabel = new QLabel ("Pertrubation: ", info_widget);
  statusLabel = new QLabel ("Status: ", info_widget);
  threadNumberLabel = new QLabel ("Thread Number: ", info_widget);
  itterationsLabel = new QLabel ("Itterations: ", info_widget);
  epsLabel = new QLabel ("EPS: ", info_widget);
  areaLabel = new QLabel ("[a;b]x[c;d]: ", info_widget);

  //layouts
  buttons_vertical_layout = new QVBoxLayout();
  buttons_vertical_layout->addWidget(changeModeButton);
  buttons_vertical_layout->addWidget(changeFunctionButton);
  buttons_vertical_layout->addWidget(doubleDomainButton);
  buttons_vertical_layout->addWidget(halveDomainButton);
  buttons_vertical_layout->addWidget(doubleNXNYButton);
  buttons_vertical_layout->addWidget(halveNXNYButton);
  buttons_vertical_layout->addWidget(addDisturbButton);
  buttons_vertical_layout->addWidget(subDisturbButton);
  buttons_vertical_layout->addWidget(rotateClockwiseButton);
  buttons_vertical_layout->addWidget(rotateCoClockwiseButton);
  buttons_vertical_layout->addWidget(exitButton);
  buttons_vertical_layout->addWidget (info_widget);

  common_grid_layout->addLayout(buttons_vertical_layout, 0, 0, 1, 1);
  common_grid_layout->addWidget(graphic_widget, 0, 1, 1, 1);
  common_grid_layout->setColumnStretch (1, 2);
  common_grid_layout->setColumnStretch (0, 0);

  labels_vertical_layout = new QVBoxLayout (info_widget);
  labels_vertical_layout->setAlignment (Qt::AlignTop);
  labels_vertical_layout->addWidget (statusLabel);
  labels_vertical_layout->addWidget (modeLabel);
  labels_vertical_layout->addWidget (functionLabel);
  labels_vertical_layout->addWidget (NXLable);
  labels_vertical_layout->addWidget (NYLable);
  labels_vertical_layout->addWidget (maxValLabel);
  labels_vertical_layout->addWidget (pertrubationLabel);
  labels_vertical_layout->addWidget (threadNumberLabel);
  labels_vertical_layout->addWidget (itterationsLabel);
  labels_vertical_layout->addWidget (epsLabel);
  labels_vertical_layout->addWidget (areaLabel);
  info_widget->setLayout (labels_vertical_layout);
}

void Window::make_connections ()
{
  connect (changeFunctionButton, SIGNAL (released ()), this, SLOT(change_func_handler ()));
  changeFunctionButton->setShortcut (QString("0"));

  connect (changeModeButton, SIGNAL (released ()), this, SLOT(change_mode_handler ()));
  changeModeButton->setShortcut (QString("1"));

  connect (doubleDomainButton, SIGNAL (released ()), this, SLOT(double_area_handler ()));
  doubleDomainButton->setShortcut (QString("2"));
  connect (halveDomainButton, SIGNAL (released ()), this, SLOT(halve_area_handler ()));
  halveDomainButton->setShortcut (QString("3"));

  connect (doubleNXNYButton, SIGNAL (released ()), this, SLOT(double_nxny_handler ()));
  doubleNXNYButton->setShortcut (QString("4"));
  connect (halveNXNYButton, SIGNAL (released ()), this, SLOT(halve_nxny_handler ()));
  halveNXNYButton->setShortcut (QString("5"));

  connect (addDisturbButton, SIGNAL (released ()), this, SLOT(add_pertrub_handler ()));
  addDisturbButton->setShortcut (QString("6"));
  connect (subDisturbButton, SIGNAL (released ()), this, SLOT(sub_pertrub_handler ()));
  subDisturbButton->setShortcut (QString("7"));

  connect (rotateClockwiseButton, SIGNAL (released ()), this, SLOT(rotate_clockwise_handler ()));
  rotateClockwiseButton->setShortcut (QString("8"));
  connect (rotateCoClockwiseButton, SIGNAL (released ()), this, SLOT(rotate_counter_clockwise_handler ()));
  rotateCoClockwiseButton->setShortcut (QString("9"));

  connect (exitButton, SIGNAL (released ()), this, SLOT(close ()));
  exitButton->setShortcut (QString("Ctrl+X"));
}

void Window::timer ()
{
  pthread_mutex_lock (&(m_common_data->all));
  m_status = m_common_data->m_status;
  pthread_mutex_unlock (&(m_common_data->all));

  if (m_status == status::DONE)
    {
      pthread_mutex_lock (&(m_common_data->all));
      update_info ();
      from_bus ();
      m_status = m_common_data->m_status = status::FREE;
      pthread_mutex_unlock (&(m_common_data->all));

      appproximation_drawer->update (VISUALIZATION_NX, VISUALIZATION_NY, m_approx_func.get_func ());
      residual_drawer->update (VISUALIZATION_NX, VISUALIZATION_NY, residual (m_approx_func.get_func (), m_func.get_func ()));
      graphic_widget->update ();
      computational_buttons_state (true);

      m_max_val_appprox = appproximation_drawer->get_max_val ();
      m_max_val_residual = residual_drawer->get_max_val ();

      update_info ();
      update ();
    }
  if (m_status == status::COMPUTING)
    {
      computational_buttons_state (false);
      statusLabel->setText (QString ("Status: ") + QString (enum_to_string (m_status)));
    }

}

void Window::to_bus ()
{
  m_common_data->m_nx = m_nx_new;
  m_common_data->m_ny = m_ny_new;
  m_common_data->m_eps = m_eps;
  m_common_data->m_func = m_func.get_func ();
  m_common_data->m_rectangle = m_rectangle;
  m_common_data->m_task = m_task;
}

void Window::from_bus ()
{
  m_itterations = m_common_data->m_iter;
  m_nx = m_nx_new;
  m_ny = m_ny_new;

  delete [] m_approx_answer;
  m_approx_answer = m_common_data->answer;
  m_common_data->answer = nullptr;

  delete [] m_common_data->m_A;
  delete [] m_common_data->m_I;
  delete [] m_common_data->m_buff;
  delete [] m_common_data->m_b;
  delete [] m_common_data->m_r;
  delete [] m_common_data->m_u;
  delete [] m_common_data->m_v;

  m_approx_func.update (m_rectangle, m_nx, m_ny, m_approx_answer);
}

double Window::find_max (std::function<double(double, double)> func)
{
  point_3d a = m_rectangle.get_a ();
  point_3d b = m_rectangle.get_b ();
  point_3d c = m_rectangle.get_c ();

  double hx = (b.m_x - a.m_x) / m_nx;
  double hy = (a.m_y - c.m_y) / m_ny;

  double tmp_max = 0;
  for (int i = 0; i < m_nx + 1; i++)
    for (int j = 0; j < m_ny + 1; j++)
      {
        double func_x_y = fabs (func (a.m_x + j * hx, c.m_y + i * hy));
        tmp_max = func_x_y > tmp_max ? func_x_y : tmp_max;
      }


  return tmp_max;
}

void Window::update_info ()
{
  switch (m_mode)
    {
    case paint_mode::FUNCTION:
      graphic_widget->set_actual_grid (function_drawer.get ());
      m_max_val = m_max_val_func;
      break;
    case paint_mode::APPROXIMATION:
      graphic_widget->set_actual_grid (appproximation_drawer.get ());
      m_max_val = m_max_val_appprox;
      break;
    case paint_mode::RESIDUAL:
      graphic_widget->set_actual_grid (residual_drawer.get ());
      m_max_val = m_max_val_residual;
      break;
    case paint_mode::COUNT:
      graphic_widget->set_actual_grid (domain_drawer.get ());
      m_max_val = 0;
      break;
    }

  m_pertrub = m_func.get_pertrub ();

  update_labels ();

  printf ("\n------------------------------\n");
  printf ("Status: %s\n", enum_to_string (m_status));
  printf ("Mode: %s\n", enum_to_string (m_mode));
  printf ("Function: %s\n", m_func.get_func_name ().toStdString().c_str());
  printf ("Maximum value: %1.2e\n", m_max_val);
  printf ("NX: %d\n", m_nx);
  printf ("NY: %d\n", m_ny);
  printf ("Pertrubation: %1.2e\n", m_pertrub);
  printf ("Thread number: %d\n", m_thread_quantity);
  printf ("Itterations: %d\n", m_itterations);
  printf ("EPS: %1.2e\n", m_eps);
  printf ("[a;b]x[c;d] : [%1.1lf;%1.1lf]x[%1.1lf;%1.1lf]\n", m_rectangle.get_a ().m_x, m_rectangle.get_b ().m_x,
          m_rectangle.get_a ().m_y, m_rectangle.get_c ().m_y);
  printf ("------------------------------\n\n");
}

void Window::update_labels()
{
  modeLabel->setText (QString ("Mode: ") + QString(enum_to_string (m_mode)));
  functionLabel->setText (QString ("Function: ") + QString(m_func.get_func_name ()));
  maxValLabel->setText (QString ("Maximum Value: ") + QString::number (m_max_val, 'e', 2));
  NXLable->setText (QString ("NX: ") + QString::number (m_nx));
  NYLable->setText (QString ("NY: ") + QString::number (m_ny));
  pertrubationLabel->setText (QString ("Pertrubation: ") + QString::number (m_pertrub, 'e', 2));
  statusLabel->setText (QString ("Status: ") + QString (enum_to_string (m_status)));
  threadNumberLabel->setText (QString ("Thread Number: ") + QString::number (m_thread_quantity));
  itterationsLabel->setText (QString ("Itterations: ") + QString::number (m_itterations));
  epsLabel->setText (QString ("EPS: ") + QString::number (m_eps,'e', 2));
  areaLabel->setText (QString ("[a;b]x[c;d] : ") + QString("[") + QString::number (m_rectangle.get_a ().m_x)
                      + QString(";") + QString::number (m_rectangle.get_b ().m_x) + QString("]x[")
                      + QString::number (m_rectangle.get_a ().m_y) + QString(";")
                      + QString::number (m_rectangle.get_c ().m_y) + QString("]"));
}

void Window::rotate_clockwise_handler ()
{
  graphic_widget->set_z_angle (graphic_widget->get_z_angle () + 15);
  update ();
}

void Window::rotate_counter_clockwise_handler ()
{
  graphic_widget->set_z_angle (graphic_widget->get_z_angle () - 15);
  update ();
}

void Window::double_area_handler ()
{
  graphic_widget->double_area ();
  update ();
}

void Window::halve_area_handler ()
{
  graphic_widget->halve_area ();
  update ();
}

void Window::change_mode_handler ()
{
  if (m_first_execution)
    {
      pthread_mutex_lock (&(m_common_data->all));
      m_task = gui_task::CHANGED_NXNY;
      to_bus ();
      pthread_cond_broadcast (&(m_common_data->c_in));
      pthread_mutex_unlock (&(m_common_data->all));

      m_first_execution = false;
    }

  ++m_mode;
  switch (m_mode)
    {
    case paint_mode::FUNCTION:
      graphic_widget->set_actual_grid (function_drawer.get ());
      m_max_val = m_max_val_func;
      break;
    case paint_mode::APPROXIMATION:
      graphic_widget->set_actual_grid (appproximation_drawer.get ());
      m_max_val = m_max_val_appprox;
      break;
    case paint_mode::RESIDUAL:
      graphic_widget->set_actual_grid (residual_drawer.get ());
      m_max_val = m_max_val_residual;
      break;
    case paint_mode::COUNT:
      graphic_widget->set_actual_grid (domain_drawer.get ());
      m_max_val = 0;
      break;
    }
  graphic_widget->update ();
  update_info ();
  update ();
}

void Window::change_func_handler ()
{
  function_type curr_type = m_func.get_func_type ();
  ++curr_type;
  m_func.set_func_type (curr_type);
  m_task = gui_task::CHANGED_FUNCTION;

  if (m_first_execution)
    {
      pthread_mutex_lock (&(m_common_data->all));
      m_task = gui_task::CHANGED_NXNY;
      to_bus ();
      pthread_cond_broadcast (&(m_common_data->c_in));
      pthread_mutex_unlock (&(m_common_data->all));

      m_first_execution = false;
    }

  pthread_mutex_lock (&(m_common_data->all));
  to_bus ();
  pthread_cond_broadcast (&(m_common_data->c_in));
  pthread_mutex_unlock (&(m_common_data->all));

  function_drawer.get ()->update(VISUALIZATION_NX, VISUALIZATION_NY, m_func.get_func ());
  m_max_val_func = function_drawer->get_max_val ();
  graphic_widget->update ();

  update ();
}

void Window::double_nxny_handler ()
{
  m_nx_new *= 2;
  m_ny_new *= 2;

  m_task = gui_task::CHANGED_NXNY;

  pthread_mutex_lock (&(m_common_data->all));
  to_bus ();
  pthread_cond_broadcast (&(m_common_data->c_in));
  pthread_mutex_unlock (&(m_common_data->all));

  update ();
}

void Window::halve_nxny_handler ()
{
  if (m_nx_new / 2 == 0 || m_ny_new / 2 == 0)
    return;
  else
    {
      m_nx_new /= 2;
      m_ny_new /= 2;

      m_task = gui_task::CHANGED_NXNY;

      pthread_mutex_lock (&(m_common_data->all));
      to_bus ();
      pthread_cond_broadcast (&(m_common_data->c_in));
      pthread_mutex_unlock (&(m_common_data->all));
    }

  update ();
}

void Window::add_pertrub_handler ()
{
  m_func.increase_pertrub ();
  m_task = gui_task::CHANGED_FUNCTION;

  pthread_mutex_lock (&(m_common_data->all));
  to_bus ();
  pthread_cond_broadcast (&(m_common_data->c_in));
  pthread_mutex_unlock (&(m_common_data->all));

  function_drawer.get ()->update(VISUALIZATION_NX, VISUALIZATION_NY, m_func.get_func ());
  m_max_val_func = function_drawer->get_max_val ();

}

void Window::sub_pertrub_handler ()
{
  m_func.decrease_pertrub ();
  m_task = gui_task::CHANGED_FUNCTION;

  pthread_mutex_lock (&(m_common_data->all));
  to_bus ();
  pthread_cond_broadcast (&(m_common_data->c_in));
  pthread_mutex_unlock (&(m_common_data->all));

  function_drawer.get ()->update(VISUALIZATION_NX, VISUALIZATION_NY, m_func.get_func ());
  m_max_val_func = function_drawer->get_max_val ();
}


void Window::computational_buttons_state (bool enabled)
{
  addDisturbButton->setDisabled (!enabled);
  subDisturbButton->setDisabled (!enabled);

  doubleNXNYButton->setDisabled (!enabled);
  halveNXNYButton->setDisabled (!enabled);

  changeFunctionButton->setDisabled (!enabled);
}

void Window::resizeEvent(QResizeEvent *event)
{
  QWidget::resizeEvent(event);
  int oldWidth = event->oldSize().width();
  if (oldWidth >= 0)
    grid_layout_widget->resize(grid_layout_widget->width() + event->size().width() - oldWidth,
                               grid_layout_widget->height() + event->size().height() - event->oldSize().height());
}

std::optional <cmd_line_arguments> parse_command_line (int argc, char *argv[])
{
  if (argc != 7)
    return std::nullopt;

  cmd_line_arguments result;

  if (   sscanf (argv[1], "%s", result.file_name) != 1
         || sscanf (argv[2], "%d", &result.nx) != 1
         || sscanf (argv[3], "%d", &result.ny) != 1
         || result.nx <= 0 || result.ny <= 0
         || sscanf (argv[4], "%d", &result.func_type) != 1
         || (result.func_type > 7 || result.func_type < 0)
         || sscanf (argv[5], "%lf", &result.eps) != 1
         || sscanf (argv[6], "%d", &result.thread_quantity) != 1
         || result.thread_quantity < 1)
    return std::nullopt;

  return result;
}
