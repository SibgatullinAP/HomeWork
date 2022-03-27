#include "problem_info.h"
#include "io.h"

const math_vec &CDS_solver::get_answer_H() {
  if (!m_calculated) {
    m_calculated = true;
    if (!solve())
      m_answer_H = {};
  }

  if (m_grid.m_grf && *m_grid.m_grf)
    {
      math_vec tmp ((m_grid.m_nx / (2<<*m_grid.m_grf)) + 1);
      for (unsigned int i = 0 ; i < tmp.size (); i++)
        tmp[i] = m_answer_H[i * 2<<*m_grid.m_grf];

      m_answer_H = tmp;
    }

  return m_answer_H;
}

const math_vec &CDS_solver::get_answer_V() {
  if (!m_calculated) {
    m_calculated = true;
    if (!solve())
      m_answer_V = {};
  }

  if (m_grid.m_grf && *m_grid.m_grf)
    {
      math_vec tmp ((m_grid.m_nx / (2<<*m_grid.m_grf)) + 1);
      for (unsigned int i = 0 ; i < tmp.size (); i++)
        tmp[i] = m_answer_V[i * 2<<*m_grid.m_grf];

      m_answer_V = tmp;
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

  auto f = [](double t, double x) -> double {
    return 0;
  };

  auto f_0 = [](double t, double x) -> double {
    return 0;
  };

  auto preconditioner = [this](math_vec &vec) {
    for (auto &i : vec)
      i *= (m_grid.dt() * m_grid.dx());
  };

  unsigned int timestep = 1;
  double eps = 1e-4;

  double V_diff = 0;
  for (timestep = 0; ; timestep++)
    {
    // fill H begin
    H_D[0] = (1. / tau);
    H_R[0] = V_prev[1] / (2. * h);
    H_rhs[0] =
        H_prev[0] / tau - (H_prev[0] * (V_prev[1] - V_prev[0])) / (2. * h) +
        (1. / (2. * h)) *
            ((H_prev[2] * V_prev[2] - 2 * H_prev[1] * V_prev[1] +
              H_prev[0] * V_prev[0]) -
             0.5 * ((H_prev[3] * V_prev[3] - 2 * H_prev[2] * V_prev[2] +
                     H_prev[1] * V_prev[1])) +
             H_prev[0] * ((V_prev[2] - 2 * V_prev[1] + V_prev[0]) -
                          0.5 * ((V_prev[3] - 2 * V_prev[2] + V_prev[1])))) +
        f_0(timestep * m_grid.dt(), 0.);

    for (int m = 1; m < dim - 1; m++) {
      // fill internal part H
      H_L[m - 1] = -(V_prev[m] + V_prev[m - 1]) / (4. * h);
      H_D[m] = 1. / tau;
      H_R[m] = (V_prev[m] + V_prev[m + 1]) / (4. * h);

      H_rhs[m] =
          H_prev[m] * ((1 / tau) - (V_prev[m + 1] - V_prev[m - 1]) / (4. * h)) +
          f_0(timestep * m_grid.dt(), m * m_grid.dx());
    }

    // fill end H
    H_D[dim - 1] = 1. / tau + V_prev[dim - 1] / (2. * h);
    H_L[dim - 2] = -V_prev[dim - 2] / (2. * h);
    H_rhs[dim - 1] =
        H_prev[dim - 1] / tau -
        (H_prev[dim - 1] * (V_prev[dim - 1] - V_prev[dim - 2])) / (2. * h) -
        (1 / (2. * h)) *
            ((H_prev[dim - 1] * V_prev[dim - 1] -
              2 * H_prev[dim - 2] * V_prev[dim - 2] +
              H_prev[dim - 3] * V_prev[dim - 3]) -
             0.5 * (H_prev[dim - 2] * V_prev[dim - 2] -
                    2 * H_prev[dim - 3] * V_prev[dim - 3] +
                    H_prev[dim - 4] * V_prev[dim - 4]) +
             H_prev[dim - 1] *
                 ((V_prev[dim - 1] - 2 * V_prev[dim - 2] + V_prev[dim - 3]) -
                  0.5 * (V_prev[dim - 2] - 2 * V_prev[dim - 3] +
                         V_prev[dim - 4]))) +
        f_0(timestep * m_grid.dt(), (dim - 1) * m_grid.dx());

    preconditioner(H_L);
    preconditioner(H_D);
    preconditioner(H_R);
    preconditioner(H_rhs);

    double tilde_mu = 1. / H_prev[0];
    for (const auto &h : H_prev)
      tilde_mu = 1. / h > tilde_mu ? 1. / h : tilde_mu;

    tilde_mu *= m_pde_info.m_mu;

    // fill V begin
    V_D[0] = 1;
    V_R[0] = 0;
    V_rhs[0] = 0;
    for (int m = 1; m < dim - 1; m++) {

      // fill internal part V
      V_L[m - 1] = -(V_prev[m] + V_prev[m - 1]) / (6. * h) - tilde_mu / (h * h);
      V_D[m] = 1. / tau + (2 * tilde_mu) / (h * h);
      V_R[m] = (V_prev[m] + V_prev[m + 1]) / (6. * h) - tilde_mu / (h * h);

      V_rhs[m] =
          V_prev[m] / tau -
          (p(H_prev[m + 1]) - p(H_prev[m - 1])) / (2. * h * H_prev[m]) -
          (tilde_mu - m_pde_info.m_mu / H_prev[m]) *
              ((V_prev[m - 1] - 2 * V_prev[m] + V_prev[m + 1]) / (h * h)) +
          f(timestep * m_grid.dt(), m * m_grid.dx());
    }
    // fill end V
    V_D[dim - 1] = 1;
    V_L[dim - 2] = 0;
    V_rhs[dim - 1] = 0;

    preconditioner(V_L);
    preconditioner(V_D);
    preconditioner(V_R);
    preconditioner(V_rhs);

    // Solving matrix
    H_prev = solve_3diag_matrix(H_L, H_D, H_R, H_rhs);
    V_prev = solve_3diag_matrix(V_L, V_D, V_R, V_rhs);

    V_diff = abs(norm_c(V_prev));
    if (V_diff < eps)
      break;

    }

  m_calculated = true;

  m_stab_step = timestep;

  time = (clock () - time) / CLOCKS_PER_SEC;
  m_last_calc_time = time;

  return true;
}

bool problem_info::parse_cmd_line (int argc, const char *argv[])
{
  std::string usage =
      "./cds X T N0 M0 mu C Gamma N\n"
      "X - border of domain [0;X], double\n"
      "T - maximum time, double\n"
      "N0 - initial time refinment, int\n"
      "M0 - initial domain refinment, int\n"
      "mu - gas density, double\n"
      "С - coefficent for pressure func, double\n"
      "Gamma - power of pressure func, double\n"
      "N - period of functions, int\n";

  if (argc != 9)
    {
      printf ("Incorrect input arguments.\nUsage: %d %s", argc, usage.c_str());
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
            * read_arg_double(argv[5], m_mu)
            * read_arg_double(argv[6], m_C)
            * read_arg_double(argv[7], m_gamma)
            * read_arg_int(argv[8], m_N_period);

  return result;
}


std::vector<std::pair<PDE_gas_info, domain_grid_info>> problem_info::get_problem_infos ()
{
  std::vector<std::pair<PDE_gas_info, domain_grid_info>> result;

  int column_limit = m_N_period;
  for (int col = 1; col <= column_limit; col++) {
    PDE_gas_info curr_gas_info(m_mu, m_C, m_gamma, col);
    domain_grid_info curr_grid_info(m_X, m_M0, m_T, m_N0);

    result.push_back(std::make_pair(curr_gas_info, curr_grid_info));
  }

  return result;
}

