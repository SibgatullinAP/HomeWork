#ifndef WINDOW_H
#define WINDOW_H

#include "common.h"
#include "function.h"
#include "grid_3d.h"
#include "kernel.h"
#include "data_bus.h"
#include "graphicwidgetopengl.h"

enum class paint_mode
{
  FUNCTION,
  APPROXIMATION,
  RESIDUAL,

  COUNT
};
const char *enum_to_string (paint_mode mode);
paint_mode operator++(paint_mode &x);

struct cmd_line_arguments
{
  int nx = 0;
  int ny = 0;
  int func_type = 0;
  int thread_quantity = 0;
  char file_name[1024];
  double eps = 0;
};

std::optional <cmd_line_arguments> parse_command_line (int argc, char *argv[]);

class Window : public QWidget
{
  Q_OBJECT

private:
  int m_nx = 0;
  int m_ny = 0;
  int m_nx_new = 0;
  int m_ny_new = 0;
  int m_thread_quantity = 0;
  int m_itterations = 0;
  double m_eps = 0;

  double m_max_val_func = 0;
  double m_max_val_appprox = 0;
  double m_max_val_residual = 0;
  double m_max_val = 0;
  double m_pertrub = 0;

  bool m_first_execution = true;

  std::vector<double> m_approx_answer = {};
  data_bus *m_common_data = nullptr;
  kernel *m_solver = nullptr;

  paint_mode m_mode;
  status m_status;
  gui_task m_task;

  function m_func = {};
  approx_function m_approx_func = {};
  domain m_rectangle = {};

  std::unique_ptr<function_draw_grid> domain_drawer;
  std::unique_ptr<function_draw_grid> function_drawer;
  std::unique_ptr<approximation_draw_grid> appproximation_drawer;
  std::unique_ptr<residual_draw_grid> residual_drawer;

private:   //UI
  QWidget *grid_layout_widget;
  QWidget *info_widget;
  graphicWidgetOpenGl *graphic_widget;

  QPushButton *changeModeButton, *changeFunctionButton, *doubleDomainButton, *halveDomainButton, *doubleNXNYButton,
  *halveNXNYButton, *addDisturbButton, *subDisturbButton, *rotateClockwiseButton, *rotateCoClockwiseButton,
  *exitButton;

  QLabel *modeLabel, *functionLabel, *maxValLabel, *NXLable, *NYLable, *pertrubationLabel, *statusLabel,
  *threadNumberLabel, *itterationsLabel, *epsLabel, *areaLabel;

  QVBoxLayout *buttons_vertical_layout;
  QVBoxLayout *labels_vertical_layout;
  QGridLayout *common_grid_layout;

  void setup_ui ();
  void make_connections ();

public:
  explicit Window(QWidget *parent = nullptr, cmd_line_arguments cmd_arguments = {}, domain rectangle = {});
  ~Window ();
  void update_labels ();
  void update_info ();
  void computational_buttons_state (bool enabled);
  double find_max (std::function<double(double, double)> func);

  void to_bus ();
  void from_bus ();

public slots:
  void timer ();
  void rotate_clockwise_handler ();
  void rotate_counter_clockwise_handler ();
  void double_area_handler ();
  void halve_area_handler ();
  void change_mode_handler ();
  void change_func_handler ();
  void double_nxny_handler ();
  void halve_nxny_handler ();
  void add_pertrub_handler ();
  void sub_pertrub_handler ();

protected:
  void resizeEvent(QResizeEvent *event) override;

};

#endif // WINDOW_H
