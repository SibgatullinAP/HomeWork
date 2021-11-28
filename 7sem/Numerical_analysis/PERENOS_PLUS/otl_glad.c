#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "input.h"
#include "peren_h2.h"
#include "print.h"
#include "tabtex.h"

int main(int argc, char **argv)
{
//----------------------------------------------------------
//Присвоение filename значения, заданного в командной строке
//----------------------------------------------------------
    int exit_code = 0;
    char *filename_dat;
    char *filename_tex;
    filename_tex=(char*)malloc(20*sizeof(char));
    char dat[] = ".dat";
    char tex[] = ".tex";
    if((argc < 2) || (argc > 2)) {
        exit_code = 1;
    printf("неверное число параметров");
    return exit_code;
    }
    filename_dat=argv[1];
    strcpy(filename_tex,filename_dat);
    strcat(filename_dat,dat);
    strcat(filename_tex,tex);
//----------------------------------------------------------
//   Присвоение значений элементам структур str_param_gas и
// str_setka, в которых хранятся параметры дифференциальной
//                   и разностной задач
//----------------------------------------------------------
   Str_param_gas str_param_gas;
   Str_setka str_setka;
    if(input(&str_param_gas,&str_setka,filename_dat) != 0) {
        exit_code = 1;
    return exit_code;
    }
//----------------------------------------------------------
//          вспомогательные переменные для задания
//            числа узлов по направлениям x и t
//            n,m - kolichestvo uzlov po t i x
//       nm - общее число расчетов на различных сетках
//----------------------------------------------------------
int n,m,nm;
//----------------------------------------------------------
//          массивы для хранения значений норм ошибки
//                   для различных сеток
//        norm_c,norm_l2,norm_w - massivi normi C, L2, W
//           t_nm - massiv znachenii vremeni raschetov
//----------------------------------------------------------
  nm=str_setka.n_max*str_setka.m_max;
  double *norm_c,*norm_l,*norm_w,*t_nm;
  norm_c=(double*)malloc(nm*sizeof(double));
    if (norm_c == 0) {
        printf("Malloc error for norm_c \n");
        return 2;
    }
  norm_l=(double*)malloc(nm*sizeof(double));
    if (norm_l == 0) {
        printf("Malloc error for norm_l \n");
        return 2;
    }
  norm_w=(double*)malloc(nm*sizeof(double));
    if (norm_w == 0) {
        printf("Malloc error for norm_w \n");
        return 2;
    }
  t_nm=(double*)malloc(nm*sizeof(double));
    if (t_nm == 0) {
        printf("Malloc error for t_nm \n");
        return 2;
    }
//----------------------------------------------------------
//     циклы, запускающие расчеты на всех вариантах сеток
//----------------------------------------------------------
  clock_t BegClock, EndClock;
int i,j,ij;
ij=0;
n=str_setka.N0;
for (i=0; i<str_setka.n_max; i++)
{
m=str_setka.M0;
for (j=0; j<str_setka.m_max; j++)
{
  BegClock = clock();
//----------------------------------------------------------
    if(Sxema_peren_h2(n,m,&str_param_gas,&norm_c[ij],&norm_l[ij],&norm_w[ij]) != 0) {
        printf("Ошибка в процессе выполнения Sxema \n");
        exit_code = 2;
    return exit_code;
    }
    ij++;
//----------------------------------------------------------
  EndClock = clock();
  t_nm[ij] = (double)(EndClock - BegClock)/CLOCKS_PER_SEC;
m*=str_setka.k_dr;
}
n*=str_setka.k_dr;
}
print_norm_c(norm_c,str_setka.n_max,str_setka.m_max);
print_norm_l(norm_l,str_setka.n_max,str_setka.m_max);
print_norm_w(norm_w,str_setka.n_max,str_setka.m_max);
print_t_nm(t_nm,str_setka.n_max,str_setka.m_max);

tabtex(&str_param_gas,&str_setka,norm_c,norm_l,norm_w,t_nm,filename_tex);

  free(norm_c);
  free(norm_l);
  free(norm_w);
  free(t_nm);

    return 0;
}

