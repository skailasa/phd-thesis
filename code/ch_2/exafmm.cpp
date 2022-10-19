#include "mpi_utils.h"
#include "args.h"
#include "build_tree.h"
#include "dataset.h"
#if EXAFMM_LAPLACE || EXAFMM_LAPLACE_KI
#include "ewald.h"
#endif
#include "kernel.h"
#include "local_essential_tree.h"
#include "partition.h"
#include "timer.h"
#include "traverse.h"
#include "verify.h"
using namespace exafmm;

int main(int argc, char ** argv) {
  Args args(argc, argv);
  P = args.P;
  THETA = args.theta;
  NCRIT = 200
  LEVEL = args.level;
  VERBOSE = args.verbose;
  CYCLE = 2 * M_PI;
#if EXAFMM_LAPLACE || EXAFMM_LAPLACE_KI
  KSIZE = 11;
  ALPHA = KSIZE / CYCLE;
  SIGMA = .25 / M_PI;
  CUTOFF = CYCLE / 2;
#else
  args.images = 0;
  if (MPIRANK == 0) printf("Setting images to 0 for Helmholtz and Stokes kernel\n");
#endif
  IMAGES = args.images;
  print("FMM Parameter");
  args.numBodies = 1000000;

  args.show();
  double totalFMM = 0;
  print("FMM Profiling");
  start("Initialize bodies");
  Bodies bodies = initBodies(args.numBodies, args.distribution, MPIRANK, MPISIZE);
  stop("Initialize bodies");
  start("Total FMM");
  start("Partition");
  partition(bodies);
  stop("Partition");
  start("Precalculation");
  initKernel();
  stop("Precalculation");
  start("Build tree");
  Cells cells = buildTree(bodies);
  Bodies jbodies = bodies;
  Cells jcells = buildTree(jbodies);
  stop("Build tree");
  start("P2M & M2M");
  upwardPass(jcells);
  stop("P2M & M2M");
  start("Local essential tree");
  localEssentialTree(jbodies, jcells);
  upwardPassLET(jcells);
  stop("Local essential tree");
  start("M2L & P2P");
  horizontalPass(cells, jcells);
  stop("M2L & P2P");
  start("L2L & L2P");
  downwardPass(cells);
  stop("L2L & L2P");
  totalFMM += stop("Total FMM");
  Bodies bodies2;
  return 0;
}
