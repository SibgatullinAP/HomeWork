#include <math.h>
double norma_c(double *v,int Dim)
{
  int m;
  double n_c,tmp;
  n_c=fabs(v[0]);
  for(m=1; m<Dim; m++)
     {
        tmp=fabs(v[m]);
        if(n_c < tmp) n_c=tmp;
     }
  return (double) (n_c);
}

double norma_l(double *v,int Dim, double h)
{
  int m;
  double n_l,tmp;
  n_l=v[0]*v[0];
  for(m=1; m<Dim; m++)
     {
      n_l+=v[m]*v[m];
     }
  return (double) (sqrt(h*n_l));
}

double norma_w(double *v,int Dim,double h)
{
  int m;
  double n_l,n_w,tmp;
  n_l=v[0]*v[0];
  n_w=0;
  for(m=1; m<Dim; m++)
     {
      n_l+=v[m]*v[m];
      n_w+=(v[m]-v[m-1])*(v[m]-v[m-1]);
     }
  return (double) (sqrt(h*n_l+n_w/h));
}
