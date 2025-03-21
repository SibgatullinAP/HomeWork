#define ERROR_OPEN_FILE -1
#define ERROR_READ_FILE -2
#define MAX_PRINT 10

int errors(int ret, const char *name);

int read_matrix(double *a, int m, int n, const char *name);
void  init_matrix(double *a, int m, int n, double(*f)(double, double));
void print_matrix(double *a, int m, int n);
void print_tr_matrix(double *a, int m, int n);

double fa(double i, double j);
double fx0(double i, double j);

void solve(double *a, double *x0, double *x, int m, int n);
void Ax(double *a, double *x0, double *x, int n);
