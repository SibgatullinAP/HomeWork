#ifndef DEFENITIONS_H
#define DEFENITIONS_H
#include "stdio.h"
#include "stdlib.h"
#include "memory"
#include "time.h"
#include "string.h"


#define LEN 1555
#define SPACES 256
#define BRAKES 3
#define MAX_DEEP 20
#define MAX_LEN 6
#define MAX_PRINT 10

#define CANNOT_OPEN_FILE_A -1
#define READING_ERR -2
#define ERR_MEMORY -3
#define FGETS_ERR -4
#define EXIT -666

#define EOFile 101
#define WORK_DONE 102
#define MAKE_ROOT 103
#define HASH_EQUALITY 104
#define EQUALITY 105

enum cor_type { UNDEF, COR, NONE_COR};
enum cmd_type { CMD_NONE, QUIT, STOP, SELECT, INSERT, DELETE};
enum cond_type{ COND_NONE, EQ, NE, LT, GT, LE, GE, LIKE};
enum op_type {OP_NONE, AND, OR};
enum palitra {BLACK, RED};
enum ratio {LESS = 1, EQUAL, MORE};
enum location {LISTNODE = 5, DATABASE};
enum order_by {NONE_ORDER, NAME, PHONE, GROUP};
//enum work {WORK_DONE = 66, MAKE_ROOT, EQUALITY};
//enum sel_arg {AR_NONE, N, P, G, NP, NG, PG, NPG};

int like_c (char *a, char *b);


int c_EQ (char *a, char *b);
int c_NE (char *a, char *b);
int c_LT (char *a, char *b);
int c_GT (char *a, char *b);
int c_LE (char *a, char *b);
int c_GE (char *a, char *b);
int c_LIKE (char *a, char *b);

int i_EQ (int a, int b);
int i_NE (int a, int b);
int i_LT (int a, int b);
int i_GT (int a, int b);
int i_LE (int a, int b);
int i_GE (int a, int b);




typedef int (*ccmp)(char *, char *);
typedef int (*icmp)(int, int);

ccmp return_ccomp(cond_type x);
icmp return_icomp(cond_type x);
ccmp return_rccomp(cond_type x);
icmp return_ricomp(cond_type x);



#endif // DEFENITIONS_H
