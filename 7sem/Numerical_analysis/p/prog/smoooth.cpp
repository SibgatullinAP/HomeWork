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
double* init_H(int N, int M, double* H)
{
	double h=10./M;
	for(int i=0;i<(N+1)*(M+1);i++)
    {
        H[i]=0.0;
    }
   
    for(int j=0;j<=M;j++)
    {
        H[0*(M+1)+j]=(cos(M_PI*j*h/10.)+1.5);
       
    }
    return H;
}

double* init_V(int N, int M, double* V)
{
	double h=10./M;
	for(int i=0;i<(N+1)*(M+1);i++)
    {
        V[i]=0.0;
    }
   
    for(int j=0;j<=M;j++)
    {
        V[0*(M+1)+j]=sin(M_PI*j*j*h*h/100.);
       
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
            cur=1./a[j-1+M+1];
            a[j-1]*=cur;
            b[j-1]*=cur;

            a[j+M+1]-=a[j+2*(M+1)]*a[j-1];
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
    double *H, *V,*a,*b;
    H=new double[(N+1)*(M+1)];
    V=new double[(N+1)*(M+1)];
    b=new double[M+1];
    a=new double[3*(M+1)];

    double max=-1.e108;
    double mu;
    double cur=1.;
    double h=10./M,t=1./N;
    sscanf(argv[4],"%lf",&mu);
    
    a = init_a(N, M, a);
    H = init_H(N, M, H);    
    V = init_V(N, M, V);
    
    
    solve(N, M, a, H, V, b, max, mu, cur, h, t);
    
    
    



    max=fabs(cos(2.*M_PI*0*t)*sin(M_PI*0*0*h*h/100.)-V[0*(M+1)+0]);

     for(int i=0;i<=N;i++)
     {
         for(int j=0;j<=M;j++)
         {
            if(max<fabs(cos(2.*M_PI*i*t)*sin(M_PI*j*j*h*h/100.)-V[i*(M+1)+j]))
            {
                max=fabs(cos(2.*M_PI*i*t)*sin(M_PI*j*j*h*h/100.)-V[i*(M+1)+j]);
            }
         }
     }
     
     
   printf("For V with  N=%d M=%d mu=%.3f C=%d C-norma:   %e \n",  N, M, mu, C, max);
     
     
     
     
     
     max=fabs(exp(0*t)*(cos(M_PI*0*h/10.)+1.5)-H[0*(M+1)+0]);
     
     for(int i=0;i<=N;i++)
     {
         for(int j=0;j<=M;j++)
         {
            if(max<fabs(exp(i*t)*(cos(M_PI*j*h/10.)+1.5)-H[i*(M+1)+j]))
            {
                max=fabs(exp(i*t)*(cos(M_PI*j*h/10.)+1.5)-H[i*(M+1)+j]);
            }
         }
     }
     
printf("For H with N=%d M=%d mu=%.3f C=%d C-norma:   %e \n", N, M, mu, C, max);
     
     
     FILE*fp1=fopen("matr_V.txt","w");
     for(int i=0;i<N+1;i++)
     {
         fprintf(fp1,"%d %d\n",i,M+1);
         for(int j=0;j<M+1;j++)
         {
             fprintf(fp1,"%d %f %f\n",j,j*h,V[i*(M+1)+j]);
         }
         fprintf(fp1,"\n\n\n");
     }
     FILE*fp=fopen("matr_H.txt","w");
     for(int i=0;i<N+1;i++)
     {
         fprintf(fp,"%d %d\n",i,M+1);
         for(int j=0;j<M+1;j++)
         {
             fprintf(fp,"%d %f %f\n",j,j*h,H[i*(M+1)+j]);
         }
         fprintf(fp,"\n\n\n");
     }






     double sum=0.; 
     double sum2=0.,nt1=0.,nt2=0.;
     sum2=sum2;
     nt1 = nt1;
     nt2 = nt2;
     for(int i=N;i<=N;i++)
     {
         for(int j=1;j<M;j++)
         {
           sum+=fabs(cos(2.*M_PI*i*t)*sin(M_PI*j*j*h*h/100.)-V[i*(M+1)+j])*fabs(cos(2.*M_PI*i*t)*sin(M_PI*j*j*h*h/100.)-V[i*(M+1)+j]);
         }

     }
     
     for(int i=N;i<=N;i++)
     {
         sum+=0.5*fabs(cos(2.*M_PI*i*t)*sin(M_PI*0*0*h*h/100.)-V[i*(M+1)+0])*fabs(cos(2.*M_PI*i*t)*sin(M_PI*0*0*h*h/100.)-V[i*(M+1)+0]);
         sum+=0.5*fabs(cos(2.*M_PI*i*t)*sin(M_PI*M*M*h*h/100.)-V[i*(M+1)+M])*fabs(cos(2.*M_PI*i*t)*sin(M_PI*M*M*h*h/100.)-V[i*(M+1)+M]);   
     }
     
    

         for(int j=0;j<M;j++)
         {
            nt1=cos(2.*M_PI*N*t)*sin(M_PI*j*j*h*h/100.)-V[N*(M+1)+j];
            nt2=cos(2.*M_PI*N*t)*sin(M_PI*(j+1)*(j+1)*h*h/100.)-V[N*(M+1)+j+1];
            nt1=(nt2-nt1)/h;
            nt1*=nt1;
            sum2+=nt1;
         }

     sum*=h;
     sum2*=h;
    
     printf("For V with N=%d M=%d mu=%.3f C=%d L2-norma:  %e\n", N, M, mu, C, sqrt(sum));
     
     printf("For V with N=%d M=%d mu=%.3f C=%d W-norma:   %e\n", N, M, mu, C, sqrt(sum+sum2));
     
     
     
     
     sum=0.;  
              for(int j=1;j<M;j++)
              {
                sum+=fabs(exp(N*t)*(cos(M_PI*j*h/10.)+1.5)-H[N*(M+1)+j])*fabs(exp(N*t)*(cos(M_PI*j*h/10.)+1.5)-H[N*(M+1)+j]);
              }

              sum+=0.5*fabs(exp(N*t)*(cos(M_PI*0*h/10.)+1.5)-H[N*(M+1)+0])*fabs(exp(N*t)*(cos(M_PI*0*h/10.)+1.5)-H[N*(M+1)+0]);
              sum+=0.5*fabs(exp(N*t)*(cos(M_PI*M*h/10.)+1.5)-H[N*(M+1)+M])*fabs(exp(N*t)*(cos(M_PI*M*h/10.)+1.5)-H[N*(M+1)+M]);
         sum2=0.;
         for(int j=0;j<M;j++)
         {
             nt1=exp(N*t)*(cos(M_PI*j*h/10.)+1.5)-H[N*(M+1)+j];
             nt2=exp(N*t)*(cos(M_PI*(j+1)*h/10.)+1.5)-H[N*(M+1)+j+1];
             nt1=(nt2-nt1)/h;
             nt1*=nt1;
             sum2+=nt1;
         }
          sum*=h;
          sum2*=h;

          printf("For H with N=%d M=%d mu=%.3f C=%d L2-norma:  %e\n", N, M, mu, C, sqrt(sum));
         
          printf("For H with N=%d M=%d mu=%.3f C=%d W-norma:   %e\n", N, M, mu, C, sqrt(sum+sum2));
         
   
    delete[]H;
    delete[]V;
    delete[]b;
    delete[]a;
    return 0;

}
double p(double x)
{
    return C*x;
}
double f0(int i,int j,double t,double h)
{

    return exp(i*t)*(cos(M_PI*j*h/10.)+1.5)+
            exp(i*t)*cos(2.*M_PI*i*t)*(-M_PI*sin(M_PI*h*j/10.)*sin(M_PI*h*h*j*j/100.)/10.+
    (M_PI*j*h/50.)*cos(M_PI*h*j*h*j/100.)*(cos(M_PI*h*j/10.)+1.5));
}
double f(int i,int j,double t,double h,double mu)
{
    return (-exp(i*t)*(cos(M_PI*h*j/10.)+1.5)*2.*M_PI*sin(2.*M_PI*i*t)*sin(M_PI*j*j*h*h/100.)+
    exp(i*t)*(cos(M_PI*j*h/10.)+1.5)*sin(M_PI*j*j*h*h/100.)*cos(2.*M_PI*i*t)*cos(2.*M_PI*i*t)*(M_PI*h*j/50.)*cos(M_PI*j*j*h*h/100.)-
    p(M_PI/10.)*exp(i*t)*sin(M_PI*h*j/10.)-
    mu*cos(2.*M_PI*i*t)*((M_PI/50.)*cos(M_PI*j*h*j*h/100.)-(M_PI*M_PI*j*j*h*h/2500)*sin(M_PI*j*h*j*h/100.)))/(exp(i*t)*(cos(M_PI*j*h/10.)+1.5));


}
