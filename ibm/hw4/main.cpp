#include "common.h"
#include "window.h"

int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);

  std::optional<cmd_line_arguments> arguments = parse_command_line (argc, argv);
  if (!arguments)
    {
      printf ("Incorrect input values!\n"
              "Please use: %s FileName NX NY FuncType Eps ThreadNumber\n", argv[0]);
      return -1;
    }

  domain rectangle;
  if (!rectangle.parse_file (arguments->file_name))
    {
      printf ("Incorrect file with domain!\n");
      return -1;
    }


  QApplication app (argc, argv);
  Window main_window (nullptr, arguments.value (), rectangle);

  QTimer *timer = new QTimer (&main_window);
  timer->setInterval (100);
  main_window.connect (timer, SIGNAL(timeout ()), &main_window, SLOT (timer ()));
  timer->start ();

  main_window.show ();
  return app.exec ();
}
