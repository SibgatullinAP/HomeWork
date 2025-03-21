//#include "par_gas.h"
//#include "setka.h"
#include "input.h"
#include "tabtex.h"
#include <stdio.h>

void tabtex(Str_param_gas *str_param_gas,Str_setka *str_setka,double *norm_c,double *norm_l,double *norm_w,double *t_nm,char *filename)
{
  int n,m,M0,N0,n_max,m_max,k_dr;
  M0=str_setka->M0;
  N0=str_setka->N0;
  n_max=str_setka->n_max;
  m_max=str_setka->m_max;
  k_dr=str_setka->k_dr;
  double h,tau;
//  FILE *fi1 = fopen("perenos.tex","a");
  FILE *fi1 = fopen(filename,"a");
  fprintf(fi1,"\\documentstyle{article}\n");
  fprintf(fi1,"\\begin{document}\n");
  fprintf(fi1,"\\begin{center}\n");
  fprintf(fi1,"table norms of the error in C,L2,W21 and times\n");
  fprintf(fi1,"\\\\[2.0ex]  \n");
  fprintf(fi1,"  \n");

  fprintf(fi1,"\\begin{tabular}{|p{0.6in}|");
  for (m=0;m<m_max;m++) fprintf(fi1,"p{0.7in}|");
  fprintf(fi1,"} \\hline\n");
  fprintf(fi1,"$\\tau\\setminus h$ ");
  h=str_param_gas->X/M0;for (m=0;m<m_max;m++) {fprintf(fi1,"& $%.4lf$",h);h/=k_dr;}
  fprintf(fi1,"\\\\ \\hline\n");
  tau=str_param_gas->T/N0;
  for(n = 0; n < n_max; n++)
    {
      fprintf(fi1,"\n");
      fprintf(fi1,"$%.4lf$ & ",tau);
      for(m = 0; m < m_max; m++)
        {
          fprintf(fi1, "$%.3le$ $%.3le$ $%.3le$ $%.3le$ ",norm_c[n*m_max+m],norm_l[n*m_max+m],norm_w[n*m_max+m],t_nm[n*m_max+m]);
          if(m < m_max-1)
             fprintf(fi1,"&");
        }
      fprintf(fi1," \\\\ \\hline");
      tau/=k_dr;
     }
  fprintf(fi1,"\n\\end{tabular}\\\\[20pt]\n");

  fprintf(fi1,"\\end{center}\n");
  fprintf(fi1,"\\end{document}\n");
  fclose(fi1);

}

