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
    float X,T;
    int N0,M0,k_dr,m_max,n_max;
    if ((input = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Can't open %s\n", filename);
        return -1;
    }
            if (fgets(name,100,input) == 0) {
                printf("Wrong input 1 \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input) == 0) {
                printf("Wrong input 2 \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%f", &X) != 1) {
                printf("Wrong input 3 \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input 4 \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%f", &T) != 1) {
                printf("Wrong input 5 \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input 6 \n");
                fclose(input);
                return -1;
            }
    printf("x=%f T=%f\n",X,T);
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input 7 \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input 8 \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input 9 \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%d", &N0) != 1) {
                printf("Wrong input 10 \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input 11 \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%d", &M0) != 1) {
                printf("Wrong input 12 \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input 13 \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%d", &k_dr) != 1) {
                printf("Wrong input 14 \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input 15 \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%d", &n_max) != 1) {
                printf("Wrong input 16 \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input 17 \n");
                fclose(input);
                return -1;
            }
            if (fscanf(input, "%d", &m_max) != 1) {
                printf("Wrong input 18 \n");
                fclose(input);
                return -1;
            }
            if (fgets(name,100,input ) == 0) {
                printf("Wrong input 19 \n");
                fclose(input);
                return -1;
            }
    printf("M0=%d N0=%d k_dr=%d n_max=%d m_max=%d \n",M0,N0,k_dr,n_max,m_max);
    str_param_gas->X=(double) X;
    str_param_gas->T=(double) T;
      str_setka->N0=N0;
      str_setka->M0=M0;
      str_setka->k_dr=k_dr;
      str_setka->n_max=n_max;
      str_setka->m_max=m_max;
    fclose(input);
    return 0;
}
