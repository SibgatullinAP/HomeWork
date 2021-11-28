#include "problem_info.h"

const math_vec &CDS_solver::get_answer() {
  if (!m_calculated) {
    m_calculated = true;
    if (!solve())
      m_answer = {};
  }

  return m_answer;
}

bool CDS_solver::solve()
{
  m_calculated = true;
  m_answer = {1.};

  return true;
}
