#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double f0(int i,int j,double t,double h);
double f(int i,int j,double t,double h,double mu);
double p(double x);
double* init_a(int N, int M, double* a);
double* init_H(int N, int M, double* H);
double* init_V(int N, int M, double* V);
void solve(int N, int M, double* a, double* H, double* V, double *b, double max, double mu, double cur, double h, double t);
int C;
double find(double* A, int N, int M);



double find(double* A, int N, int M)
{
    double max=0., min=0.;
    max = A[N*(M+1) + 0];
    min = A[N*(M+1) + 0];
    for(int i = 0; i<M+1; i++)
          {
            if(A[N*(M+1) + i] >= max)
                max = A[N*(M+1) + i];
            if(A[N*(M+1) + i] <= min)
                min = A[N*(M+1) + i];
          }
   // printf ("MAX  %e      MIN   %e \n", max, min);

   return fabs(min-max);
}



double* init_H(int N, int M, double* H)
{
	 double h=0.01;
        h= h;
     
	for(int i=0;i<(N+1)*(M+1);i++)
    {
        H[i]=0.0;
    }
   
    for(int j=0;j<=M;j++)
    {
       
        if (j*h < 4.5 || j*h > 5.5)
			H[0*(M+1)+j]= 1.;
		else
			H[0*(M+1)+j]= 2.;
       
    }
    return H;
}




double* init_V(int N, int M, double* V)
{
        double h=0.01;
        h= h;
	for(int i=0;i<(N+1)*(M+1);i++)
    {
        V[i]=0.0;
    }
   
    for(int j=0;j<=M;j++)
    {
         V[0*(M+1)+j]=0.;
    }
    return V;
}


double* init_a(int N, int M, double* a)
{
    N = N;
	for(int i=0;i<3*(M+1);i++)
    {
        a[i]=0.0;
    }
    return a;
}





 
void solve(int N, int M, double* a, double* H, double* V, double *b, double max, double mu, double cur, double h, double t)
{



    for(int i=0;i<N;i++)
{
///////////matrix plotnosti
//////////////pervyi ryad
    a[0+M+1]=1./t;  ////a00

    a[0]=V[i*(M+1)+1]/(2.0*h); ////a01

    b[0]=-H[i*(M+1)+0]*V[i*(M+1)+1]/(2.0*h)+
    (1/(2.0*h))*
    (H[i*(M+1)+2]*V[i*(M+1)+2]-
    2*H[i*(M+1)+1]*V[i*(M+1)+1]+
    H[i*(M+1)+0]*V[i*(M+1)+0]-
    0.5*(H[i*(M+1)+3]*V[i*(M+1)+3]-
    2*H[i*(M+1)+2]*V[i*(M+1)+2]+
    H[i*(M+1)+1]*V[i*(M+1)+1])+
    H[i*(M+1)+0]*(V[i*(M+1)+2]-
    2*V[i*(M+1)+1]+V[i*(M+1)+0]-
    0.5*(V[i*(M+1)+3]-2*V[i*(M+1)+2]+
    V[i*(M+1)+1])))+
    H[i*(M+1)+0]/t+
    f0(i,0,t,h);


    a[0+M+1]*=t*h;
    a[0]*=t*h;
    b[0]*=t*h;


/////////////vnutri   - 2 uravnenie
    for(int j=1;j<M;j++)
    {
        a[j+2*(M+1)]=-(1./(4.*h))*(V[i*(M+1)+j-1]+V[i*(M+1)+j]);

        a[j+M+1]=1./t;

        a[j]=         (1./(4.*h))*(V[i*(M+1)+j+1]+V[i*(M+1)+j]);

        b[j]=f0(i,j,t,h)-H[i*(M+1)+j]*(V[i*(M+1)+j+1]-V[i*(M+1)+j-1])/(4.*h)+H[i*(M+1)+j]/t;

        a[j+2*(M+1)]*=t*h;
        a[j+M+1]*=t*h;
        a[j]*=t*h;
        b[j]*=t*h;
    }


    /////////////poslednyi ryad

    a[M+2*(M+1)]=-0.5*V[i*(M+1)+M-1]/h;

    a[M+(M+1)]=1./t+0.5*V[i*(M+1)+M]/h;

    b[M]=H[i*(M+1)+M]/t-0.5*H[i*(M+1)+M]*(V[i*(M+1)+M]-V[i*(M+1)+M-1])/h-0.5*h*((H[i*(M+1)+M]*V[i*(M+1)+M]-
            2.*H[i*(M+1)+M-1]*V[i*(M+1)+M-1]+H[i*(M+1)+M-2]*V[i*(M+1)+M-2])/(h*h)-
   0.5*(H[i*(M+1)+M-1]*V[i*(M+1)+M-1]-2.*H[i*(M+1)+M-2]*V[i*(M+1)+M-2]+H[i*(M+1)+M-3]*V[i*(M+1)+M-3])/(h*h)+
            H[i*(M+1)+M]*((V[i*(M+1)+M]-2*V[i*(M+1)+M-1]+V[i*(M+1)+M-2])/(h*h)-
            0.5*(V[i*(M+1)+M-1]-2*V[i*(M+1)+M-2]+V[i*(M+1)+M-3])/(h*h)))+f0(i,M,t,h);

    a[M+2*(M+1)]*=t*h;
    a[M+(M+1)]*=t*h;
    b[M]*=t*h;
    /////////////////////////////////////////////////////////////////////////////////////










    for(int j=1;j<=M;j++)
    {
       // printf("j = %d\n", j);
        cur=1./a[j-1+M+1];
        a[j-1]*=cur;
        b[j-1]*=cur;
       // printf("%d      %d  \n",  j,  j+M+1);
        a[j+M+1]-=
                a[j+2*(M+1)]*
                a[j-1];
        b[j]-=a[j+2*(M+1)]*b[j-1];
    }

    b[M]/=a[M+M+1];

    for(int j=M-1;j>=0;j--)
    {
        b[j]-=b[j+1]*a[j];
    }


    for(int j=0;j<=M;j++)
    {
        H[(i+1)*(M+1)+j]=b[j];
    }

    for(int j=0;j<=M;j++)
    {
        b[j]=0.;
    }
    for(int j=0;j<(M+1)*3;j++)
    {
        a[j]=0.;
    }

    max=1./H[(i)*(M+1)+0];

    for(int j=1;j<=M;j++)
    {
     if(1./H[(i)*(M+1)+j]>max)
     {
         max=1./H[(i)*(M+1)+j];
     }
    }
    max=mu*max;





    ////////matr skorosti(kraya 0)

    for(int j=1;j<M;j++)
    {
        a[j+2*(M+1)]=-(V[i*(M+1)+j]+V[i*(M+1)+j-1])/(6*h)-max/(h*h);

        a[j+M+1]=1./t+2.*max/(h*h);

        a[j]=(V[i*(M+1)+j]+V[i*(M+1)+j+1])/(6*h)-max/(h*h);

        b[j]=V[i*(M+1)+j]/t-(p(H[(i+1)*(M+1)+j+1])-p(H[(i+1)*(M+1)+j-1]))/(2.*h*H[(i+1)*(M+1)+j])-
                (max-mu/H[(i+1)*(M+1)+j])*(V[i*(M+1)+j+1]-2*V[i*(M+1)+j]+V[i*(M+1)+j-1])/(h*h)+f(i,j,t,h,mu);

        a[j+2*(M+1)]*=t*h;
        a[j+M+1]*=t*h;
        a[j]*=t*h;
        b[j]*=t*h;
    }
////////////



    for(int j=2;j<M;j++)
    {
        cur=1./a[j-1+M+1];
        a[j-1]*=cur;
        b[j-1]*=cur;

        a[j+M+1]-=a[j+2*(M+1)]*a[j-1];
        b[j]-=a[j+2*(M+1)]*b[j-1];
    }
    b[M-1]/=a[M-1+M+1];
    for(int j=M-2;j>=1;j--)
    {
        b[j]-=b[j+1]*a[j];
    }
    for(int j=1;j<M;j++)
    {
        V[(i+1)*(M+1)+j]=b[j];
    }


}
}


 






int main(int argc, char*argv[])
{
    argc=argc;
    int N,M;
    C=atoi(argv[1]);
    N=atoi(argv[2]);
    M=atoi(argv[3]);
    double rV=1., rH=1.;

    double *H, *V, *a,*b;
    
     //double norm = 0.;
    double max=-1.e108;
    double mu;
    double cur=1.;
    double t = 0.01, h = 0.01;
    sscanf(argv[4],"%lf",&mu);
    
    

    double *H1, *V1,*a1,*b1, *res, *resV;
    H1=new double[(N+1)*(M*2+1)];
    V1=new double[(N+1)*(M*2+1)];
    b1=new double[M*2+1];
    a1=new double[3*(M*2+1)];

    res = new double[M+1];
    resV = new double[M+1];

    for(int i= 0; i<M+1; i++)
    {
        res[i]=0.;
        resV[i]=0.;
    }

   
    

    
    H=new double[(N+1)*(M+1)];
    V=new double[(N+1)*(M+1)];
    b=new double[M+1];
    a=new double[3*(M+1)];
    
    
    a = init_a(N, M, a);
    H = init_H(N, M, H);    
    V = init_V(N, M, V);

    
    solve(N, M, a, H, V, b, max, mu, cur, h, t);
    rV = find(V, N, M);
    rH = find(H, N, M);
    
  //  printf("H:  %e    V:  %e     N: %d\n", rH, rV, N);
    //N = N + 1;
    
    
       //printf("Vmax - Vmin = %e      Hmax - Hmin = %e   N = %d\n", rV, rH, N-1);


	for(int i = 0; i < M+1; i++)
	{
		printf("%e ", H[N*(M+1) +i]);
	}
	
	printf("\n");
	
	for(int i = 0; i < M+1; i++)
	{
		printf("%e ", V[N*(M+1) +i]);
	}





delete[]H;
    delete[]V;
    delete[]b;
    delete[]a;



//    for(int i = 0; i<M+1; i++)
//    {

//          printf ("H  %e     H1  %e\n",H[0*(M+1) +i], H1[0*(M+1) +i*2] );
//    }

//    printf("\n");
//    printf("\n");
//    printf("\n");


   // solve(N, M*2, a1, H1, V1, b1, max, mu, cur, h, t);
  
   //   for(int i = 0; i<M+1; i++)
   //   {
   //         res[i] =  H[N*(M+1) +i] - H1[N*(M+1) +i*2];
   //         res[i] *= res[i];
   //       // printf("%f\n", res[i]);
   //         norm = norm + res[i];
          //  printf ("H  %e     H1  %e\n",H[N*(M+1) +i], H1[N*(M+1) +i*2] );
    //  }
     






 /*     norm = 0.;

      for(int i = 0; i<M+1; i++)
      {
            resV[i] =  V[N*(M+1) +i] - V1[N*(M+1) +i*2];
            resV[i] *= resV[i];
           // printf("%f\n", resV[i]);
            norm = norm + resV[i];
      }
      printf("V: N = %d   M: %d / %d       %e\n", N, M, M*2, sqrt(fabs(norm)));
*/




   
  /*  delete[]H;
    delete[]V;
    delete[]b;
    delete[]a;*/
    delete[]H1;
    delete[]V1;
    delete[]b1;
    delete[]a1;
    delete[]res;
    delete[]resV;
    return 0;

}

double p(double x)
{
    return C*x;
}
double f0(int i,int j,double t,double h)
{
    i =i;
    j = j;
    t = t;
    h = h;

   /* return exp(i*t)*(cos(M_PI*j*h/10.)+1.5)+
            exp(i*t)*cos(2.*M_PI*i*t)*(-M_PI*sin(M_PI*h*j/10.)*sin(M_PI*h*h*j*j/100.)/10.+
    (M_PI*j*h/50.)*cos(M_PI*h*j*h*j/100.)*(cos(M_PI*h*j/10.)+1.5));*/
    return 0;
}
double f(int i,int j,double t,double h,double mu)
{
    mu = mu;
    i =i;
    j = j;
    t = t;
    h = h;

   /* return (-exp(i*t)*(cos(M_PI*h*j/10.)+1.5)*2.*M_PI*sin(2.*M_PI*i*t)*sin(M_PI*j*j*h*h/100.)+
    exp(i*t)*(cos(M_PI*j*h/10.)+1.5)*sin(M_PI*j*j*h*h/100.)*cos(2.*M_PI*i*t)*cos(2.*M_PI*i*t)*(M_PI*h*j/50.)*cos(M_PI*j*j*h*h/100.)-
    p(M_PI/10.)*exp(i*t)*sin(M_PI*h*j/10.)-
    mu*cos(2.*M_PI*i*t)*((M_PI/50.)*cos(M_PI*j*h*j*h/100.)-(M_PI*M_PI*j*j*h*h/2500)*sin(M_PI*j*h*j*h/100.)))/(exp(i*t)*(cos(M_PI*j*h/10.)+1.5));*/
        return 0;

}



