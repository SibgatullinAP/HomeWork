#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
// input.h

int input(Str_param_gas *str_param_gas,Str_setka *str_setka,char *filename)
{
    FILE* input;
//    char filename[]="perenos.dat";
    char name[100];
    float X,T,mu;
    int mu_dr,mu_max,N0,M0,k_dr,m_max,n_max;
    if ((input = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Can't open %s\n", filename);
        return -1;
    }
            if (fgets(name,100,input) == 0) {
                printf("Wrong input: the first line \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input) == 0) {
                printf("Wrong input: the second line \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%f", &X) != 1) {
                printf("Wrong input X  \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input: text in line X \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%f", &T) != 1) {
                printf("Wrong input T \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input: text in line T \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%f", &mu) != 1) {
                printf("Wrong input mu \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input: text in line mu \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%d", &mu_dr) != 1) {
                printf("Wrong input mu_dr \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input: text in line mu_dr \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%d", &mu_max) != 1) {
                printf("Wrong input mu_max \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input: text in line mu_max \n");
                fclose(input);
                return -1;
            }
    printf("x=%f T=%f\n mu=\%f mu_dr=%d mu_max=%d \n",X,T,mu,mu_dr,mu_max);
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input: the first line after input gas parametrs \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input: the second line after input gas parametrs \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input: the third line after input gas parametrs \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%d", &N0) != 1) {
                printf("Wrong input: N0 \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input: text in line N0 \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%d", &M0) != 1) {
                printf("Wrong input M0 \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input: text in line M0 \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%d", &k_dr) != 1) {
                printf("Wrong input k_dr \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input: text in line k_dr \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%d", &n_max) != 1) {
                printf("Wrong input n_max \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input: text in line n_max \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%d", &m_max) != 1) {
                printf("Wrong input m_max \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input: text in line m_max \n");
                fclose(input);
                return -1;
            }
    printf("M0=%d N0=%d k_dr=%d n_max=%d m_max=%d \n",M0,N0,k_dr,n_max,m_max);
    str_param_gas->X=(double) X;
    str_param_gas->T=(double) T;
    str_param_gas->mu=(double) mu;
    str_param_gas->mu_dr= mu_dr;
    str_param_gas->mu_max= mu_max;
      str_setka->N0=N0;
      str_setka->M0=M0;
      str_setka->k_dr=k_dr;
      str_setka->n_max=n_max;
      str_setka->m_max=m_max;
    fclose(input);
    return 0;
}
