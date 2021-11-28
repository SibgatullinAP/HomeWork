#ifndef PROBLEM_INFO_H
#define PROBLEM_INFO_H

#include "common.h"
#include "math_alg.h"

class PDE_gas_info {
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

class CDS_solver {
  PDE_gas_info m_pde_info;
  domain_grid_info m_grid;

  double m_last_calc_time = 0;
  bool m_calculated = false;

  math_vec m_answer;

  bool solve ();

public:
  CDS_solver() = default;
  CDS_solver(const PDE_gas_info &pde_info, const domain_grid_info &grid)
      : m_pde_info(pde_info), m_grid(grid) {}

  double get_calc_time() const { return m_last_calc_time; }
  const math_vec &get_answer();
};

class problem_info {
public:
  problem_info();
};

#endif // PROBLEM_INFO_H
