/*
 * STRUMPACK -- STRUctured Matrices PACKage, Copyright (c) 2014, The
 * Regents of the University of California, through Lawrence Berkeley
 * National Laboratory (subject to receipt of any required approvals
 * from the U.S. Dept. of Energy).  All rights reserved.
 *
 * If you have questions about your rights to use or distribute this
 * software, please contact Berkeley Lab's Technology Transfer
 * Department at TTD@lbl.gov.
 *
 * NOTICE. This software is owned by the U.S. Department of Energy. As
 * such, the U.S. Government has been granted for itself and others
 * acting on its behalf a paid-up, nonexclusive, irrevocable,
 * worldwide license in the Software to reproduce, prepare derivative
 * works, and perform publicly and display publicly.  Beginning five
 * (5) years after the date permission to assert copyright is obtained
 * from the U.S. Department of Energy, and subject to any subsequent
 * five (5) year renewals, the U.S. Government is granted for itself
 * and others acting on its behalf a paid-up, nonexclusive,
 * irrevocable, worldwide license in the Software to reproduce,
 * prepare derivative works, distribute copies to the public, perform
 * publicly and display publicly, and to permit others to do so.
 *
 * Developers: Pieter Ghysels, Francois-Henry Rouet, Xiaoye S. Li.
 *             (Lawrence Berkeley National Lab, Computational Research
 *             Division).
 *
 */
#include <iostream>
#include <cstring>
using namespace std;

#include "StrumpackSparseSolver.hpp"
#include "sparse/CSRMatrix.hpp"
#include "misc/RandomWrapper.hpp"

using namespace strumpack;

#define ERROR_TOLERANCE 1e2
#define SOLVE_TOLERANCE 1e-12

template<typename scalar_t,typename integer_t> int
test_sparse_solver(int argc, const char* const argv[],
                   CSRMatrix<scalar_t,integer_t>& A) {
  using real_t = typename RealType<scalar_t>::value_type;
  StrumpackSparseSolver<scalar_t,integer_t> spss;
  spss.options().set_from_command_line(argc, argv);

  int N = A.size();
  vector<scalar_t> b(N), x(N), x_exact(N);
  {
    auto rgen = random::make_default_random_generator<real_t>();
    for (auto& xi : x_exact)
      xi = rgen->get();
  }
  A.spmv(x_exact.data(), b.data());

  spss.set_matrix(A);
  if (spss.reorder() != ReturnCode::SUCCESS) {
    cout << "problem with reordering of the matrix." << endl;
    return 1;
  }
  if (spss.factor() != ReturnCode::SUCCESS) {
    cout << "problem during factorization of the matrix." << endl;
    return 1;
  }
  spss.solve(b.data(), x.data());

  auto comp_scal_res = A.max_scaled_residual(x.data(), b.data());
  cout << "# COMPONENTWISE SCALED RESIDUAL = "
       << comp_scal_res << endl;

  blas::axpy(N, scalar_t(-1.), x_exact.data(), 1, x.data(), 1);
  auto nrm_error = blas::nrm2(N, x.data(), 1);
  auto nrm_x_exact = blas::nrm2(N, x_exact.data(), 1);
  cout << "# RELATIVE ERROR = " << (nrm_error/nrm_x_exact) << endl;

  if (comp_scal_res > ERROR_TOLERANCE*spss.options().rel_tol())
    return 1;
  else return 0;
}


template<typename real_t,typename integer_t>
int read_matrix_and_run_tests(int argc, const char* const argv[]) {
  string f(argv[1]);
  CSRMatrix<real_t,integer_t> A;
  if (A.read_matrix_market(f) == 0)
    return test_sparse_solver(argc, argv, A);
  else {
    CSRMatrix<complex<real_t>,integer_t> Acomplex;
    if (Acomplex.read_matrix_market(f)) {
      std::cerr << "Could not read matrix from file." << std::endl;
      return 1;
    }
    return test_sparse_solver(argc, argv, Acomplex);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout
      << "Solve a linear system with a matrix given in matrix market format\n"
      << "using the sequential/multithreaded C++ STRUMPACK interface.\n\n"
      << "Usage: \n\t./testMMdouble pde900.mtx" << endl;
    return 1;
  }
  cout << "# Running with:\n# ";
#if defined(_OPENMP)
  cout << "OMP_NUM_THREADS=" << omp_get_max_threads() << " ";
#endif
  for (int i=0; i<argc; i++)
    cout << argv[i] << " ";
  cout << endl;

  int ierr = 0;
  // ierr = read_matrix_and_run_tests<float,int>(argc, argv);
  // if (ierr) return ierr;
  ierr = read_matrix_and_run_tests<double,int>(argc, argv);
  if (ierr) return ierr;
  // ierr = read_matrix_and_run_tests<float,long long int>(argc, argv);
  // if (ierr) return ierr;
  ierr = read_matrix_and_run_tests<double,long long int>(argc, argv);
  return ierr;
}
