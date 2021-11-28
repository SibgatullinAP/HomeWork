// lin_burg.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "input.h"
#include "func.h"
#include "normi.h"
#include "progon.h"

int Sxema_lin_burg(double mu,int N,int M1,Str_param_gas *str_param_gas,double *n_c,double *n_l,double *n_w)
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
  double t_3h,tmu_h2;
  t_3h=tau/(h*3);
  tmu_h2=mu*tau/(h*h);
// m,n - tekushie shagi; m0 - centralnii uzel shablona
// mL - levii uzel shablona, mR - pravii uzel shablona
  int m,n,m0,mL,mR;
// xL,x0,xR,t_hat - koordinati uzlov shablona
  double  xL,x0,xR,t_hat;
// v0,vL,vR - znachenie v v uzlah shablona
  double v0,vL,vR;
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
        mR=1;
        x0=0.;
        xR=h;
        v0=v[m0];
        vR=v[mR];
        a[0]=1.;
        b[0]=0.;
        d[0] =u(t_hat,x0);
//cikl po vnutrennim uzlam------------------------------
        for(m=1; m<M1; m++)
           {
            mL=m0;
            m0=mR;
            mR++;
            xL=x0;
            x0=xR;
            xR+=h;
            vL=v0;
            v0=vR;
            vR=v[mR];
            c[m-1]=-t_3h*(vL+v0)-tmu_h2;
            a[m]=1.+2.*tmu_h2;
            b[m]=t_3h*(v0+vR)-tmu_h2;
            d[m] =tau*f(t_hat,x0,mu)+v0;
           }
//right boundary-------------------------------------------------------
            x0=xR;
            c[M1-1]=0.;
            a[M1]=1.;
            d[M1] =u(t_hat,x0);
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
