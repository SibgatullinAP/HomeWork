#ifndef PROBLEM_INFO_H
#define PROBLEM_INFO_H

#include "common.h"
#include "math_alg.h"

struct PDE_gas_info {
  PDE_gas_info (double mu, double C, double gamma, int max_timestep) : m_mu (mu), m_C(C), m_gamma(gamma), m_max_timestep(max_timestep) {};
  PDE_gas_info &operator= (const PDE_gas_info &) = default;
  PDE_gas_info () = default;
  double m_mu = 0;
  double m_C = 0;
  double m_gamma = 0;
  unsigned int m_max_timestep = 0;
};

struct domain_grid_info {
  double m_X_min = 0;
  double m_X_max = 0;
  unsigned int m_nx = 1; // X axis refinment

  double m_T_min = 0;
  double m_T_max = 0;
  unsigned int m_nt = 1; // T axis refinment

  std::optional<int> m_grf;

  domain_grid_info() = default;
  domain_grid_info(double max_X, unsigned int h, double max_T, unsigned int t, std::optional<int> grf = std::nullopt)
      : m_X_max(max_X), m_nx(h), m_T_max(max_T), m_nt(t), m_grf(grf)
  {
    if (m_grf && *m_grf)
      {
          m_nx *= (1<<*m_grf);
          m_nt *= (1<<*m_grf);
      }
  }

  double dx () const {return (m_X_max - m_X_min) / m_nx;}
  double dt () const {return (m_T_max - m_T_min) / m_nt;}
};

class CDS_solver {
  double m_last_calc_time = 0;
  bool m_calculated = false;

  math_vec m_answer_H;
  math_vec m_answer_V;

  int m_stab_step;

  math_vec m_h_n4;
  math_vec m_h_n2;
  math_vec m_h_3n4;
  math_vec m_h_n;

  math_vec m_v_n4;
  math_vec m_v_n2;
  math_vec m_v_3n4;
  math_vec m_v_n;

  double m_mass_n4;
  double m_mass_n2;
  double m_mass_3n4;
  double m_mass_n;

public:
  PDE_gas_info m_pde_info;
  domain_grid_info m_grid;

  CDS_solver() = default;
  CDS_solver(const PDE_gas_info &pde_info, const domain_grid_info &grid)
      : m_pde_info(pde_info), m_grid(grid) {}

  double get_calc_time() const { return m_last_calc_time; }
  bool solve ();

  const math_vec &get_answer_H();
  const math_vec &get_answer_V();

  const math_vec get_ethalon_H() const;
  const math_vec get_ethalon_V() const;

  double get_stab_time () const {return m_stab_step * m_grid.dt();}
  unsigned int get_stab_step () const {return m_stab_step;}

  const math_vec &get_h_n4 () const {return m_h_n4;}
  const math_vec &get_h_n2 () const {return m_h_n2;}
  const math_vec &get_h_3n4 () const {return m_h_3n4;}
  const math_vec &get_h_n () const {return m_h_n;}

  const math_vec &get_v_n4 () const {return m_v_n4;}
  const math_vec &get_v_n2 () const {return m_v_n2;}
  const math_vec &get_v_3n4 () const {return m_v_3n4;}
  const math_vec &get_v_n () const {return m_v_n;}

  double get_mass_n4 () const {return m_mass_n4;}
  double get_mass_n2 () const {return m_mass_n2;}
  double get_mass_3n4 () const {return m_mass_3n4;}
  double get_mass_n () const {return m_mass_n;}

  //First task
//  double r (double t, double x) const
//  {
//    if (t > 1e-16)
//      printf("Assert: in func r, time is not 0\n");

//    return x <= 5.5 && x >= 4.5 ? 2 : 1;
//  }

    //Second task
  double r (double t, double x) const
  {
    if (t > 1e-16)
      printf("Assert: in func r, time is not 0\n");

      return 1.;
  }

//  double r (double t, double x) const {return std::exp(t) * (std::cos(M_PI * x / 10.) + 1.5);}
//  double r (double t, double x) const {return std::exp(t) * (std::cos(3. * M_PI * x) + 1.5);}
  double dr_dt (double t, double x) const {return r(t, x);}
  double dr_dx (double t, double x) const {return -3. * M_PI * std::exp(t) * std::sin(3. * M_PI * x);}

//    double u (double t, double x) const
//    {
//      return 0;
//    }

    //Second task
    double u (double t, double x) const
    {
      if (x < 1e-16 || fabs(x - 10.0) < 1e-15)
        return 0.;

      if (t < 1e-16)
        return x <= 5.5 && x >= 4.5 ? 1 : 0;

      return 0;
    }

//  double u (double t, double x) const {return std::cos(2. * M_PI * t) * std::sin(M_PI * x * x / 100.);}
//  double u (double t, double x) const {return std::cos(2. * M_PI * t) * std::sin(4. * M_PI * x);}
  double du_dt (double t, double x) const {return -2. * M_PI * std::sin(2. * M_PI * t) * std::sin(4. * M_PI * x);}
  double du_dx (double t, double x) const {return 4. * M_PI * std::cos(2. * M_PI * t) * std::cos(4. * M_PI * x);}
  double d2u_dxdx (double t, double x) const {return -16. * M_PI * M_PI * std::cos(2. * M_PI * t) * std::sin(4. * M_PI * x);}
  double du2_dx(double t, double x) const {return 8. * M_PI * (std::cos(2. * M_PI * t) * std::cos(2. * M_PI * t)) * std::sin(4. * M_PI * x) * std::cos(4. * M_PI * x);}

  double dru_dx(double t, double x) const {
    return M_PI * std::exp(t) * std::cos(2. * M_PI * t) *
           (4. * (std::cos(3 * M_PI * x) + 1.5) *
                std::cos(4 * M_PI * x) -
            3. * std::sin(3 * M_PI * x) *
                std::sin(4 * M_PI * x));
  }

  double p (double r) const {return m_pde_info.m_C * std::pow(r, m_pde_info.m_gamma);}
  double dp_dr(double r) const {return m_pde_info.m_C * m_pde_info.m_gamma * std::pow(r, m_pde_info.m_gamma - 1.);}
};

struct problem_info {
  double m_C = 0;
  double m_gamma = 0;
  double m_mu = 0;

  double m_X = 0;
  double m_T = 0;

  int m_N0 = 0;
  int m_M0 = 0;

  int m_k_dr = 0;

  int m_n_max = 0;
  int m_m_max = 0;

  int m_max_timestep = 0;

  std::optional<int> m_gr_factor;

public:
  problem_info() = default;
  bool parse_cmd_line (int argc, const char *argv[]);
  std::vector<std::pair<PDE_gas_info, domain_grid_info>> get_problem_infos ();
};

#endif // PROBLEM_INFO_H