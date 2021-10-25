#ifndef PROBLEM_INFO_H
#define PROBLEM_INFO_H

class PDE_gas_info {
  double m_x = 0;
  double m_T = 0;
  double m_mu = 0;
};

class domain_grid_info {
  double m_X_min = 0;
  double m_X_max = 0;
  int m_nx = 1; // X axis refinment

  double m_T_min = 0;
  double m_T_max = 0;
  int m_nt = 1; // T axis refinment

  domain_grid_info() = default;
  domain_grid_info(double max_X, int h, double max_T, int t)
      : m_X_max(max_X), m_nx(h), m_T_max(max_T), m_nt(t) {}
};


class CDS_solver
{
  PDE_gas_info m_pde_info;
  domain_grid_info m_grid;

  CDS_solver () = default;
};

class problem_info {
public:
  problem_info();
};

#endif // PROBLEM_INFO_H
