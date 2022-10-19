/*
 * Test matrix vector product using HSS matrices for the Laplace problem.
 */
#include <iostream>
#include <cmath>
using namespace std;

#include "structured/StructuredMatrix.hpp"
#include "iterative/IterativeSolversMPI.hpp"
using namespace strumpack;

#include <sys/time.h>

/**
 * This takes a pointer to a structured::StructureMatrix and prints
 * out the memory usage, and the maximum rank.
 *
 * MPIComm is a c++ wrapper around an MPI_Comm
 */
template<typename scalar_t> void
print_info(const MPIComm& comm,
           const structured::StructuredMatrix<scalar_t>* H,
           const structured::StructuredOptions<scalar_t>& opts) {
  if (comm.is_root())
    cout << get_name(opts.type()) << endl
         << "  - total_nonzeros(H) = " << H->nonzeros() << endl
         << "  - total_memory(H) = " << H->memory() / 1e6 << " MByte" << endl
         << "  - maximum_rank(H) = " << H->rank() << endl;
}

template<typename scalar_t> void
matvec(int nrhs,
       const DistributedMatrix<scalar_t>& A,
       const structured::StructuredMatrix<scalar_t>* H) {
        
  // Allocate an A.cols vector
  DistributedMatrix<scalar_t> B(A.grid(), H->rows(), 1), X(A.grid(), H->rows(), 1);

  // Pick a random exact solution
  X.random();

  // Compute the right-hand side B as B=H*X
  H->mult(Trans::N, X, B);

}


int main(int argc, char* argv[]) {
    int thread_level;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &thread_level);
    {
        // C++ wrapper around an MPI_Comm, defaults to MPI_COMM_WORLD
        MPIComm world;
        int rank = world.rank(), P = world.size();

        // we need at least MPI_THREADS_FUNNELED support
        if (thread_level != MPI_THREAD_FUNNELED && world.is_root())
        cout << "MPI implementation does not support MPI_THREAD_FUNNELED" << endl;

        // matrix size and number of right-hand sides
        int n = 1000, nrhs = 1;
            if (argc > 1) n = stoi(argv[1]);

        // Define an options object, set to the default options.
        structured::StructuredOptions<double> options;
        // Suppress some output
        options.set_verbose(false);
        // Parse options passed on the command line, run with --help to see
        // more.
        options.set_from_command_line(argc, argv);
        options.set_type(structured::Type::HSS);
        srand(1);

        // Random vector of coordinates
        std::vector<std::vector<double>> coords;

        for (int i=0; i<n; i++) {
            double r1 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            double r2 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            double r3 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            coords.push_back({r1, r2, r3});
        };

        auto LaplaceBase = 
        [](std::vector<double> x, std::vector<double> y) {
            
            double x1 = x[0];
            double x2 = x[1];
            double x3 = x[2];

            double y1 = y[0];
            double y2 = y[1];
            double y3 = y[2];

            double denominator = pow(abs(x1-y1), 2.)  + pow(abs(x2-y2), 2.) + pow(abs(x3-y3), 2.);
            denominator = pow(denominator, 0.5);
            double result = 1./ denominator;
            if (isinf(result)) {
                return 0.;
            } else{
                return result;
            }
        };

        // Calculate elements
        auto Laplace = [&](int i, int j){
            auto x = coords[i];
            auto y = coords[j];
            return LaplaceBase(x, y);
        };

        // Explicit matrix lookup
        // std::vector<std::vector<double>> LaplaceMatrix;
        // for (int i=0; i<n; i++) {
        //     std::vector<double> row;
        //     auto x = coords[i];
        //     for (int j=0; j<n; j++) {
        //         auto y = coords[j]; 
        //         row.push_back(LaplaceBase(x, y));
        //     }
        //     LaplaceMatrix.push_back(row);
        // }
        // auto Laplace = [&](int i, int j){
        //     return LaplaceMatrix[i][j];
        // };

        // Toeplitz matrix for testing
        // auto Laplace = [](int i, int j){
        //     return 1./(i-j + 1);
        // };

        BLACSGrid grid(world);
        DistributedMatrix<double> A2d(&grid, n, n, Laplace); 

        auto H = structured::construct_from_elements<double>
            (world, &grid, n, n, Laplace, options);

        print_info(world, H.get(), options);
        if (world.is_root()) 
            cout << endl << endl
                << "dense (2DBC) " << A2d.rows() << " x " << A2d.cols()
                << " matrix" << endl
                << "  - memory(A2d) = " << A2d.memory() / 1e6 << " MByte"
                << endl << endl;

        matvec(nrhs, A2d, H.get());

    }

    scalapack::Cblacs_exit(1);
    MPI_Finalize();
    return 0;
}
