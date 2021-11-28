#ifndef TASK_HPP
#define TASK_HPP

int
calc_count (const char * path, int * count, int * size, double * sum,
            double * beg1, double * beg2, double * end1, double * end2);

// считается что файлы открываются читаются и все ок
int
count_great (const char * path, double x);

#endif /* TASK_HPP */
