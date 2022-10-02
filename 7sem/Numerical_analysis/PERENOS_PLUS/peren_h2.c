// peren_h2.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "input.h"
#include "func.h"
#include "normi.h"
#include "progon.h"

int Sxema_peren_h2(int N,int M1,Str_param_gas *str_param_gas,double *n_c,double *n_l,double *n_w)
{
// Dim kollichestvo neizvestnih na vremennom sloe
  int Dim;
// v- massiv neizvestnih, a,b,c,d - diagonali matrici i pravoi chasti
  double *a,*b,*c,*v,*d;
// h, tau - shagi setki
  double  h, tau;
  tau = str_param_gas->T/(double)N;
  h = str_param_gas->X/(double)M1;
  Dim = M1+1;
  v=(double*)malloc(Dim*sizeof(double));
    if (v == 0) {
        printf("Malloc error for v \n");
        return 2;
    }
  d=(double*)malloc(Dim*sizeof(double));
    if (d == 0) {
        printf("Malloc error for d \n");
        return 2;
    }
  a=(double*)malloc(Dim*sizeof(double));
    if (a == 0) {
        printf("Malloc error for a \n");
        return 2;
    }
  b=(double*)malloc(M1*sizeof(double));
    if (b == 0) {
        printf("Malloc error for b \n");
        return 2;
    }
  c=(double*)malloc(M1*sizeof(double));
    if (c == 0) {
        printf("Malloc error for c \n");
        return 2;
    }
// chasto ispolzuemai const
  double th4;
  th4=tau/h/4;
// m,n - tekushie shagi; m0 - centralnii uzel shablona
  int m,n,m0;
// xL,x0,xR,t_hat - koordinati uzlov shablona
  double  xL,x0,xR,t_hat;
// v0 - znachenie v centralnom uzle shablona
  double v0;
//initial conditions---------------------------------------
  for(m=0; m<Dim; m++)
     {
        v[m]=u(0,m*h);
     }
//------------------------------------------------------
     t_hat=tau;
  for(n=1; n<N+1; n++)
     {
//left boundary-----------------------------------------
        m0=0;
        x0=0.;
        xR=h;
        v0=v[m0];
        a[0]=0.5;
        b[0]=th4*aa(t_hat,xR);
        d[0] =0.5*tau*f(t_hat,x0)+(0.5-th4*aa(t_hat,xR))*v0;
        d[0]+=tau/h/2*(aa(t_hat-tau,x0)*v0-2*aa(t_hat-tau,xR)*v[m0+1]+aa(t_hat-tau,xR+h)*v[m0+2]);
        d[0]-=tau/h/4*(aa(t_hat-tau,xR)*v[m0+1]-2*aa(t_hat-tau,xR+h)*v[m0+2]+aa(t_hat-tau,xR+2*h)*v[m0+3]);
//cikl po vnutrennim uzlam------------------------------
        for(m=1; m<M1; m++)
           {
            m0=m;
            xL=x0;
            x0=xR;
            xR+=h;
            v0=v[m0];
            c[m-1]=-b[m-1];
            a[m]=1.;
            b[m]=th4*(aa(t_hat,x0)+aa(t_hat,xR));
            d[m] =tau*f(t_hat,x0)+(1-th4*(aa(t_hat,xR)-aa(t_hat,xL)))*v0;
           }
//right boundary-------------------------------------------------------
            m0=M1;
            xL=x0;
            x0=xR;
            v0=v[m0];
            c[M1-1]=-b[M1-1];
            a[M1]=0.5;
            d[M1] =0.5*tau*f(t_hat,x0)+(0.5+th4*aa(t_hat,xL))*v0;
d[M1]-=tau/h/2*(aa(t_hat-tau,x0)*v0-2*aa(t_hat-tau,xL)*v[m0-1]+aa(t_hat-tau,xL-h)*v[m0-2]);
d[M1]+=tau/h/4*(aa(t_hat-tau,xL)*v[m0-1]-2*aa(t_hat-tau,xL-h)*v[m0-2]+aa(t_hat-tau,xL-2*h)*v[m0-3]);
// Solving SLAU
    if(PROG(a,b,c,Dim,d,v) != 0) {
    return 3;
    }
        t_hat+=tau;
     }

// vichislenie oshibki
  for(m=0; m<Dim; m++)
     {
        v[m]-=u(str_param_gas->T,m*h);
     }

*n_c=norma_c(v,Dim);
*n_l=norma_l(v,Dim,h);
*n_w=norma_w(v,Dim,h);

  free(a);
  free(b);
  free(c);
  free(d);
  free(v);
  return 0;
}
