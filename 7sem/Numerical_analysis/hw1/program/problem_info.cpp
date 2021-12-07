#include "problem_info.h"

const math_vec &CDS_solver::get_answer_H() {
  if (!m_calculated) {
    m_calculated = true;
    if (!solve())
      m_answer_H = {};
  }

  return m_answer_H;
}

const math_vec &CDS_solver::get_answer_V() {
  if (!m_calculated) {
    m_calculated = true;
    if (!solve())
      m_answer_V = {};
  }

  return m_answer_V;
}

const math_vec CDS_solver::get_ethalon_H() const
{
  math_vec H (m_grid.m_nx + 1);
  for (unsigned int i = 0; i < H.size(); i++)
    H[i] = r(m_grid.m_T_max, i * m_grid.dx());

  return H;
}


const math_vec CDS_solver::get_ethalon_V() const
{
  math_vec V(m_grid.m_nx + 1);
  for (unsigned int i = 0; i < V.size(); i++)
    V[i] = u(m_grid.m_T_max, i * m_grid.dx());

  return V;
}

bool CDS_solver::solve() {

  double time = clock();

  double tau = m_grid.dt();
  double h = m_grid.dx();

  int nx = m_grid.m_nx;

  int dim = nx + 1;
  int timesteps = m_grid.m_nt;

  math_vec H_L (dim - 1);
  math_vec H_D (dim);
  math_vec H_R (dim - 1);
  math_vec H_rhs (dim);
  math_vec H_prev (dim);

  math_vec V_L (dim - 1);
  math_vec V_D (dim);
  math_vec V_R (dim - 1);
  math_vec V_rhs (dim);
  math_vec V_prev (dim);

  //Initial conditions for H (density)
  //Initial conditions for V (Speed)
  for (int i = 0; i < dim; i++)
    {
      H_prev[i] = r(m_grid.m_T_min, i * h);
      V_prev[i] = u(m_grid.m_T_min, i * h);
    }

  V_prev[0] = V_prev[dim - 1] = 0;

  auto f = [this] (double t, double x)
  {
     return (r(t, x) * du_dt(t, x) + r(t, x) * u(t, x) * du_dx(t, x) + dp_dr(r(t, x)) * dr_dx(t, x) - m_pde_info.m_mu * d2u_dxdx(t, x)) / r(t, x);
      //return du_dt(t, x) + (1./3.) * (u(t, x) * du_dx(t, x) + du2_dx(t, x)) + (1./r(t, x)) * (dp_dr(r(t, x)) * dr_dx(t, x)) - (m_pde_info.m_mu / r(t, x)) * d2u_dxdx(t, x);
  };

  auto f_0 = [this] (double t, double x)
  {
      return dr_dt(t, x) + dru_dx(t, x);
      //return dr_dt(t, x) + 0.5 * (u(t, x) * dr_dt(t, x) + dru_dx(t,x) + r(t, x) * du_dx(t, x));
  };

  auto dummy = [] () {};

  auto dump_matrix = [] (const math_vec &L, const math_vec &D, const math_vec &R, const math_vec &rhs)
  {
      printf("\n\n");
      unsigned int dim  = D.size();

      for (unsigned int i = 0; i < dim; i++)
        {
          for (unsigned int j = 0; j < dim; j++)
            {
               if (i == j)
                 printf ("%10.3e ", D[i]);
               else if (i == j - 1)
                 printf ("%10.3e ", R[i]);
               else if (i == j + 1)
                 printf ("%10.3e ", L[i - 1]);
               else
                 printf ("%10.3e ", 0.);
            }
          printf (" | %10.3e\n", rhs[i]);
        }

      printf("\n\n");
  };

  auto preconditioner = [this] (math_vec &vec)
  {
    for (auto &i : vec)
      i *= (m_grid.dt() * m_grid.dx());
  };

  for (int timestep = 0; timestep < timesteps; timestep ++)
    {
      //fill H begin
      H_D[0] = (1. / tau);
      H_R[0] = V_prev[1] / (2. * h);
      H_rhs[0] = H_prev[0] / tau - (H_prev[0] * (V_prev[1] - V_prev[0])) / (2. * h)
                + (1. / (2. * h)) * ((H_prev[2] * V_prev[2] - 2 * H_prev[1] * V_prev[1] + H_prev[0] * V_prev[0])
                            - 0.5 * ((H_prev[3] * V_prev[3] - 2 * H_prev[2] * V_prev[2] + H_prev[1] * V_prev[1]))
                            + H_prev[0] * ((V_prev[2] - 2 * V_prev[1] + V_prev[0])
                                        - 0.5 * ((V_prev[3] - 2 * V_prev[2] + V_prev[1])))) + f_0 ((timestep) * m_grid.dt(), 0);

      for (int m = 1; m < dim - 1; m++)
        {
          //fill internal part H
          H_L[m - 1] = -(V_prev[m] + V_prev[m - 1]) / (4. * h);
          H_D[m] = 1. / tau;
          H_R[m] = (V_prev[m] + V_prev[m + 1]) / (4. * h);

          H_rhs[m] = H_prev[m] * ((1 / tau) - (V_prev[m + 1] - V_prev[m - 1]) / (4 * h)) + f_0 ((timestep) * m_grid.dt(), m * m_grid.dx());
        }
      //fill end H
      H_D[dim - 1] = 1. / tau + V_prev[dim - 1] / (2. * h);
      H_L[dim - 2] = -V_prev[dim - 2] / (2. * h);
      H_rhs[dim - 1] = H_prev[dim - 1] / tau - (H_prev[dim - 1] * (V_prev[dim - 1] - V_prev[dim - 2])) / (2. * h)
                - (1 / (2. * h)) * ((H_prev[dim - 1] * V_prev[dim - 1] - 2 * H_prev[dim - 2] * V_prev[dim - 2] + H_prev[dim - 3] * V_prev[dim - 3])
                            - 0.5 * ((H_prev[dim - 2] * V_prev[dim - 2] - 2 * H_prev[dim - 3] * V_prev[dim - 3] + H_prev[dim - 4] * V_prev[dim - 4]))
                            + H_prev[dim - 1] * ((V_prev[dim - 1] - 2 * V_prev[dim - 2] + V_prev[dim - 3])
                                        - 0.5 * ((V_prev[dim - 2] - 2 * V_prev[dim - 3] + V_prev[dim - 4])))) + f_0 ((timestep) * m_grid.dt(), m_grid.m_X_max);

      preconditioner(H_L);
      preconditioner(H_D);
      preconditioner(H_R);
      preconditioner(H_rhs);


      double H_max = H_prev[0];
      for (const auto &h : H_prev)
        H_max = h > H_max ? h : H_max;

      double tilde_mu = m_pde_info.m_mu / H_max;

      //fill V begin
      V_D[0] = 1;
      V_R[0] = 0;
      V_rhs[0] = 0;
      for (int m = 1; m < dim - 1; m++)
        {

          //fill internal part V
          V_L[m - 1] = - (V_prev[m] + V_prev[m - 1]) / (6. * h) - tilde_mu / (h * h);
          V_D[m] = 1. / tau + (2 * tilde_mu) / (h * h);
          V_R[m] = (V_prev[m] + V_prev[m + 1]) / (6. * h) - tilde_mu / (h * h);

          V_rhs[m] = V_prev[m] / tau - (p(H_prev[m + 1]) - p(H_prev[m - 1])) / (2 * h * H_prev[m]) - (tilde_mu - m_pde_info.m_mu / H_prev[m]) * ((V_prev[m - 1] - 2 * V_prev[m] + V_prev[m + 1]) / (h * h)) + f((timestep) * m_grid.dt(), m * m_grid.dx());
        }
      //fill end V
      V_D[dim - 1] = 1;
      V_L[dim - 2] = 0;
      V_rhs[dim - 1] = 0;

      preconditioner(V_L);
      preconditioner(V_D);
      preconditioner(V_R);
      preconditioner(V_rhs);

      //Solving matrix
      V_prev = solve_3diag_matrix(V_L, V_D, V_R, V_rhs);
      H_prev = solve_3diag_matrix(H_L, H_D, H_R, H_rhs);

//      dump_matrix(H_L, H_D, H_R, H_rhs);
//      dump_matrix(V_L, V_D, V_R, V_rhs);

      dummy ();
    }

  m_answer_H = std::move(H_prev);
  m_answer_V = std::move(V_prev);

  m_calculated = true;

  time = (clock () - time) / CLOCKS_PER_SEC;
  m_last_calc_time = time;

  return true;
}

bool problem_info::parse_cmd_line (int argc, const char *argv[])
{
  std::string usage =
      "./cds X T N0 M0 k_dr n_max m_max mu (Grid Refinment factor)\n"
      "X - border of domain [0;X], double\n"
      "T - maximum time, double\n"
      "N0 - initial time refinment, int\n"
      "M0 - initial domain refinment, int\n"
      "k_dr - grid refinment coefficent for multiple variants of CDS, int\n"
      "n_max - number of grid variants by time, int\n"
      "m_max - number of grid variants by domain, int\n"
      "mu - gas density, double\n"
      "С - coefficent for pressure func, double\n"
      "Gamma - power of pressure func, double\n"
      "(Grid Refinment factor) - optional parameter, for more precision, int\n";

  if (argc != 11 && argc != 12)
    {
      printf ("Incorrect input arguments.\nUsage: %s", usage.c_str());
      return false;
    }

    auto read_arg_int = [&](const char *arg_str, int &arg_dest) {
      if (sscanf(arg_str, "%d", &arg_dest) != 1) {
        printf("Incorrect input arguments.\nUsage: %s", usage.c_str());
        return false;
      }
      return true;
    };

    auto read_arg_double = [&](const char *arg_str, double &arg_dest) {
      if (sscanf(arg_str, "%lf", &arg_dest) != 1) {
        printf("Incorrect input arguments: %s.\nUsage: %s", arg_str, usage.c_str());
        return false;
      }
      return true;
    };

    bool result = true;
    result *= read_arg_double(argv[1], m_X)
            * read_arg_double(argv[2], m_T)
            * read_arg_int(argv[3], m_N0)
            * read_arg_int(argv[4], m_M0)
            * read_arg_int(argv[5], m_k_dr)
            * read_arg_int(argv[6], m_n_max)
            * read_arg_int(argv[7], m_m_max)
            * read_arg_double(argv[8], m_mu)
            * read_arg_double(argv[9], m_C)
            * read_arg_double(argv[10], m_gamma);


    if (argc == 12)
      {
        int grf;
        result *= read_arg_int(argv[11], grf);

        m_gr_factor = grf;
      }

  return result;
}


std::vector<std::pair<PDE_gas_info, domain_grid_info>> problem_info::get_problem_infos ()
{
  std::vector<std::pair<PDE_gas_info, domain_grid_info>> result;
  unsigned int nt = m_N0;
  for (int time_ref = 0; time_ref < m_n_max; time_ref++)
    {
      unsigned int nx = m_M0;
      for (int domain_ref = 0; domain_ref < m_m_max; domain_ref++)
        {
          PDE_gas_info curr_gas_info (m_mu, m_C, m_gamma);
          domain_grid_info curr_grid_info (m_X, nx, m_T, nt);

          result.push_back(std::make_pair(curr_gas_info, curr_grid_info));
          nx *= m_k_dr;
        }
      nt *= m_k_dr;
    }

  return result;
}

