#include "domain.h"

bool domain::parse_file (char *file_name)
{
  FILE *file = fopen (file_name, "r");
  if (file == nullptr)
      return false;

  double x_1, y_1;
  double x_2, y_2;

  char buff_line[BUFF_SIZE];
  int read_counter = 0;
  while (fgets (buff_line, BUFF_SIZE, file))
    {
      if (*buff_line == '#')
        continue;

      if (read_counter == 0)
        {
          if (sscanf (buff_line, "%lf %lf", &x_1, &y_1) == 2)
             read_counter = 1;
        }
      else
        {
          if (sscanf (buff_line, "%lf %lf", &x_2, &y_2) == 2)
            {
             read_counter = 2;
             break;
            }
        }
    }

  fclose (file);
  if (read_counter != 2)
    return false;

  set_corners ({x_1, y_1, 0}, {x_2, y_2, 0});
  return true;
}

void domain::set_corners (const point_3d &a, const point_3d &d)
{
  m_a = a;
  m_d = d;

  m_b = {m_d.m_x, m_a.m_y , 0};
  m_c = {m_a.m_x, m_d.m_y , 0};
}
