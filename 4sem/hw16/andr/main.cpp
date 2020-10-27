 #include <stdio.h>
#include <string.h>
#include "database.h"
#include <time.h>
#include <stdlib.h>
int main(int argc,char **argv)
{
       FILE *atxt;
       char buf[1234];
       char alphabet[256]={0};
       char *a;
       command x;
       database d;
       double t;
       int i,k,v,n1,n2;
       if(argc!=4  ||(n1 = atoi(argv[2])) == 0 ||(n2 = atoi(argv[3])) == 0 ) 
       {
		   printf("usage ./a.out    file    big_phone_hash    small_phone_hash_in_group_tree  \n");
           return 1;
       }
       if(n1<0 || n2<0){ printf("bad hashmodeule"); return 1;}
       a=argv[1];
       alphabet[(unsigned char)(' ')]=1;
       alphabet[(unsigned char)('(')]=1;
       alphabet[(unsigned char)(')')]=1;
       alphabet[(unsigned char)(',')]=1;
       alphabet[(unsigned char)(';')]=1;
       alphabet[(unsigned char)('\n')]=1;
       alphabet[(unsigned char)('\t')]=1;
       t=clock();
       d.initi(n1,n2);
       if(!(atxt=fopen(a,"r")))
       {
           printf("error cannot open file\n");
           return 1;
         }
       if(d.read(atxt)<0) {printf("something is bad\n"); return 1;}
       t=clock()-t;
       printf("reading time:: %f \n",t/CLOCKS_PER_SEC);
                    
       while(fgets(buf,1234,stdin))
       {
           k=1;
               for(i=0;buf[i];i++)
               if(buf[i]==';')
               {buf[i]=0; k=0; break;}
               
        if(k==0)
        {
        v=x.parser(buf,alphabet);
            if(v>0)
            {
                //x.print_parse();
                d.docommand(x);

            }
            else
            {
                if(v==-243)
                {t=clock()-t;
                    printf("kosmos time:: %f \n",t/CLOCKS_PER_SEC);
                    fclose(atxt);
                    return 3;
                }
            }
        }
       x.destroy();
       }
       t=clock()-t;
       printf("commands work time:: %f \n",t/CLOCKS_PER_SEC);
       fclose(atxt);
       return 0;
}

