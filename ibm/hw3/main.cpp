#include "window.h"

int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);

  QApplication app (argc, argv);

  QMainWindow *window_main = new QMainWindow;
  QMenuBar *tool_bar = new QMenuBar (window_main);
  window *graph_area = new window (window_main);
  QAction *action;

  if (graph_area->parse_command_line (argc, argv))
    {
      printf ("%d\n", graph_area->parse_command_line (argc, argv));
      QMessageBox::warning (0, "Wrong input arguments!",
                            "Wrong input arguments!");
      return -1;
    }

#ifdef MISC_WARNING_DISABLE
    graph_area->set_warning (false);
#endif

  action = tool_bar->addAction ("&Change function", graph_area, SLOT (change_func ()));
  action->setShortcut (QString ("0"));

  action = tool_bar->addAction ("&Change method", graph_area, SLOT (change_paint_event ()));
  action->setShortcut (QString ("1"));

  action = tool_bar->addAction ("&Double domain", graph_area, SLOT (double_domain ()));
  action->setShortcut (QString ("2"));

  action = tool_bar->addAction ("&Halve domain", graph_area, SLOT (halve_domain ()));
  action->setShortcut (QString ("3"));

  action = tool_bar->addAction ("&Double N", graph_area, SLOT (double_n ()));
  action->setShortcut (QString ("4"));

  action = tool_bar->addAction ("&Halve N", graph_area, SLOT (halve_n ()));
  action->setShortcut (QString ("5"));

  action = tool_bar->addAction ("&Add pertrubtaion", graph_area, SLOT (add_perturbation ()));
  action->setShortcut (QString ("6"));

  action = tool_bar->addAction ("&Substract pertrubtaion", graph_area, SLOT (subtract_perturbation ()));
  action->setShortcut (QString ("7"));

  action = tool_bar->addAction ("Exit", window_main, SLOT (close ()));
  action->setShortcut (QString ("Ctrl+X"));

  tool_bar->setMaximumHeight (30);

  window_main->setMenuBar (tool_bar);
  window_main->setCentralWidget (graph_area);
  window_main->setWindowTitle ("Graph");

  window_main->show ();
  app.exec ();
  delete window_main;
  return 0;
}
