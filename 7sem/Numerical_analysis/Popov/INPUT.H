// Описание структуры Str_param_gas
typedef struct
{
// zadanie parametrov gaza i oblasti:
// T,X - razmeri oblasti [0;T]x[0;X]
// mu - nachalnii parametr viazkosti
// mu_dr - koefficient droblenia viazkosti
// mu_max - chislo variantov viazkosti

double T;
double X;
double mu;
int mu_dr;
int mu_max;
} Str_param_gas;

// Описание структуры Str_setka
typedef struct
{
// zadanie parametrov cetok
// N0,M0 - nachalnoe chislo razbienii [0,T] i [0,X]
// n_max, m_max - chislo cetok po t i x
// k_dr - koefficient droblenia cetok

int N0;
int M0;
int k_dr;
int n_max;
int m_max;
} Str_setka;

int input(Str_param_gas *str_param_gas, Str_setka *str_setka,char *filename);

