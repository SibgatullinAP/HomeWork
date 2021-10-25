// print.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_norm_c(double *norm_c, int n_max, int m_max)
{
int i,j;
printf ("*********************\n");
printf ("??????? ???? ?????? ? C\n");
printf ("*********************\n");
for (i=0; i<n_max; i++)
{
for (j=0; j<m_max; j++)
{
  printf(" %lf ",norm_c[i*m_max+j]);
}
  printf("\n");
}
}

void print_norm_l(double *norm_l, int n_max, int m_max)
{
int i,j;
printf ("*********************\n");
printf ("??????? ???? ?????? ? L2\n");
printf ("*********************\n");
for (i=0; i<n_max; i++)
{
for (j=0; j<m_max; j++)
{
  printf(" %lf ",norm_l[i*m_max+j]);
}
  printf("\n");
}
}

void print_norm_w(double *norm_w,  int n_max, int m_max)
{
int i,j;
printf ("*********************\n");
printf ("??????? ???? ?????? ? W21\n");
printf ("*********************\n");
for (i=0; i<n_max; i++)
{
for (j=0; j<m_max; j++)
{
  printf(" %lf ",norm_w[i*m_max+j]);
}
  printf("\n");
}
}

void print_t_nm(double *t_nm,  int n_max, int m_max)
{
int i,j;
printf ("*********************\n");
printf ("??????? ??????? ??????? ???????? \n");
printf ("*********************\n");
for (i=0; i<n_max; i++)
{
for (j=0; j<m_max; j++)
{
  printf(" %lf ",t_nm[i*m_max+j]);
}
  printf("\n");
}
}
