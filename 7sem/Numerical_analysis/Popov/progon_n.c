//progon.h
/*
C*********************************************
C           ???????? ??? ??????? N*N
C*****************************************************
C
C !A(1) B(1)                 000   ! ! X(1) ! ! F(1) !
C !C(1) A(2) B(2)            0 0   ! ! X(2) ! ! F(2) !
C !     C(2) A(3) B(3)       000   ! ! X(3) ! ! F(3) !
C !    000   ...................   !*! .... !*! .... !
C !    0 0    C(N-2) A(N-1) B(N-1) ! !X(N-1)! !F(N-1)!
C !    000              C(N-1) A(N)! ! X(N) ! ! F(N) !
C
C*****************************************************
C
C   X(J)=AL(J)*X(J) + BE(J)   J = N-1, ... 1.
C
C  AL(1)=-B(1)/A(1)      BE(1)=F(1)/A(1)
C
C  AL(I)=-B(I)/(A(I)+C(I-1)*AL(I-1))
C
C  BE(I)=(F(I)-C(I-1)*BE(I-1))/(A(I)+C(I-1)*AL(I-1))
C
C                    I=2,...,N-1
C
C  X(N)=(F(N)-C(N-1)*BE(N-1))/(A(N)+C(N-1)*AL(N-1))
C
C****************************************************
C           i.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int PROG (double *a, double *b, double *c, int n, double *f, double *x)
{
  double *al,*be,y,tmp;
  int i;

  al = (double*) malloc ((n-1) * sizeof(double));
    if (al == 0) {
        printf("Malloc error for al \n");
        return 2;
    }
  be = (double*) malloc ((n-1) * sizeof(double));
    if (be == 0) {
        printf("Malloc error for be \n");
        return 2;
    }
  tmp = 1./ a[0];
  al[0] = -b[0]*tmp;
  be[0] = f[0]*tmp;
  for (i = 1; i <= n-2; i++)
    {
      y = -1.0/(a[i] + c[i-1] * al[i-1]);
      al[i] =  b[i] * y;
      be[i] = (c[i-1] * be[i-1]-f[i])*y;
    }
  x[n-1] = (f[n-1] - c[n-2] * be[n-2]) / (a[n-1] + c[n-2] * al[n-2]);
  for (i = n-2; i >= 0; i--)
    {
      x[i] = al[i] * x[i+1] + be[i];
    }
  free (al);
  free (be);
  return 0;
}
