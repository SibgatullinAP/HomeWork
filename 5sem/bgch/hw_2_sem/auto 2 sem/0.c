#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int read_matrix(FILE *fp, double *a, int m, int n);
void print_matrix(FILE *fp, double *a, int m, int n);

double norma1_string(double *a, int m, int n, int i);
double norma1_column(double *a, int m, int n, int j);
double norma2_string(double *a, int m, int n, int i);
double norma2_column(double *a, int m, int n, int j);
double norma3_string(double *a, int m, int n, int i);
double norma3_column(double *a, int m, int n, int j);

void change_strings(double *a, int m, int n, int s1, int s2);
void change_columns(double *a, int m, int n, int c1, int c2);

int cmp_up(double d1, double d2);
int cmp_down(double d1, double d2);

void bubble_sort(double *a, int m, int n, double (*norma)(double *a, int m, int n ,int k), void (*change)(double *a, int m, int n, int k1, int k2), int (*cmp)(double d1, double d2));

void mult_Aastr(double *a, int m, int n, double *c, int str);

int main(){
	int m, n;
	double *a, *c;
	FILE *in, *out;
	if(!( in=fopen( "input.txt","r"))) return -1;
	if(!(out=fopen("output.txt","w"))) return fclose(in), -1;

	if(fscanf(in,"%d%d",&m,&n)!=2) 			 {	fclose(in); fclose(out); return -1;	}
	if(m<1 || n<1) 								 {	fclose(in); fclose(out); return -1;	}
	if(!(a=(double*)malloc(n*m*sizeof(double)))) {	fclose(in); fclose(out); return -1;	}
	if(!(c=(double*)malloc(m*sizeof(double))))   {	fclose(in); fclose(out); free(a); return -1;	}
	if(!!read_matrix(in, a, m, n)) {	fclose(in); fclose(out); free(a); free(c); return -1;	}


    
    
    
    
    
    

	fprintf(out, "%d %d\n", m, n);
    print_matrix(out, a, m, n);
    fprintf(out, "\n");
    print_matrix(out, c, 1, m);

    fclose(in); fclose(out);
    free(a); free(c);
    return 0;
}



int read_matrix(FILE *fp, double *a, int m, int n){
	int i;
	for(i=0;i<m*n;i++) if(fscanf(fp,"%lf",a+i)!=1) return -1;
	return 0;	
}
void print_matrix(FILE *fp, double *a, int m, int n){
	int i, j;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++)
			fprintf(fp, "%lf ", a[i*n+j]);
		fprintf(fp, "\n");
	}
}



void mult_Aastr(double *a, int m, int n, double *c, int str){
    int i, j;
    double s, *pai, *pstr=a+str*n;
    for(i=0;i<m;i++){
        pai=a+i*n; s=0.;
        for(j=0;j<n;j++) s+=pai[j]*pstr[j];
        c[i]=s;
    }
}



void bubble_sort(double *a, int m, int n, double (*norma)(double *a, int m, int n ,int k), void (*change)(double *a, int m, int n, int k1, int k2), int (*cmp)(double d1, double d2)){
    int i, j;
    for (i=0;i<n;i++)
        for (j=0;j<n-i-1;j++)
            if( cmp( norma(a,m,n,j), norma(a,m,n,j+1) ) ) change(a,m,n,j,j+1);
}



int cmp_up(double d1, double d2)   { if (d1>d2) return 1; else return 0;}
int cmp_down(double d1, double d2) { if (d1<d2) return 1; else return 0;}

void change_strings(double *a, int m, int n, int s1, int s2){
    int j;
    double temp, *p1=a+s1*n, *p2=a+s2*n;
    (void) m;
    for(j=0;j<n;j++){  temp=p1[j]; p1[j]=p2[j]; p2[j]=temp;    }
}
void change_columns(double *a, int m, int n, int c1, int c2){
    int i;
    double temp, *p1=a+c1, *p2=a+c2;
    for(i=0;i<m*n;i+=n){  temp=p1[i]; p1[i]=p2[i]; p2[i]=temp;    }
}



double norma1_string(double *a, int m, int n, int i){
	int j;
	double s=0., *p=a+i*n;
	for(j=0;j<n;j++) s+=fabs(p[j]);
	return s;
}
double norma1_column(double *a, int m, int n, int j){
	int i;
	double s=0., *p=a+j;
	for(i=0;i<m*n;i+=n) s+=fabs(p[i]);
	return s;
}
double norma2_string(double *a, int m, int n, int i){
    int j;
    double s=0., *p=a+i*n;
    for(j=0;j<n;j++) s+=p[j]*p[j];
    return s;
}
double norma2_column(double *a, int m, int n, int j){
    int i;
    double s=0., *p=a+j;
    for(i=0;i<m*n;i+=n) s+=p[i]*p[i];
    return s;
}
double norma3_string(double *a, int m, int n, int i){
    int j;
    double *p=a+i*n, max=p[0];
    for(j=1;j<n;j++) if(p[j]>max) max=p[j];
    return max;
}
double norma3_column(double *a, int m, int n, int j){
    int i;
    double *p=a+j, max=p[0];
    for(i=1;i<m*n;i+=n) if(p[i]>max) max=p[i];
    return max;
}




