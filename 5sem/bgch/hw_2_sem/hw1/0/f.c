#include <stdio.h>
#include <string.h>
#include "f.h"
#define LEN 1234

int f(const char *a, const char *b, const char *s, int(*ptr)(const char *, const char *)){
	FILE *in, *out;
	char buf[LEN];
	int count=0, i;
	if(!( in=fopen(a, "r"))) return ERROR_OPEN_A;
	if(!(out=fopen(b, "w"))) return ERROR_OPEN_B;

	while(fgets(buf, LEN, in)){
		for(i=0; buf[i]; i++) 
			if(buf[i]=='\n') { buf[i]=0; break; }
		if((*ptr)(buf, s)){
			fprintf(out, "%s\n", buf);
			if(ferror(out)){
				fclose(in);
				fclose(out);
				return ERROR_WRITE_B;
			}
			count++;
		}
	}
	if(ferror(in)){
		fclose(in);
		fclose(out);
		return ERROR_READ_A;
	}
	fclose(in);
	fclose(out);
	return count;
}

