# Modern Software Approaches for Fast Multipole Methods

Message: Evolving hardware and software environments elicit new software approaches to the construction of fast multipole method software.

Main contributions:
- highly performant library for single/multinode kernel independent FMM, which is also highly user friendly (BLAS vs FFT Paper, + HF implementation and tests)
    - Explicit comparison study for scalability on modern architectures (BLAS vs FFT paper)
    - Designed for generality both in terms of applications as well as current and future deployment. (Software paper)
    - Benchmarked on HPC machines (HF / Multinode tested)
    - performance model that shows that it can probably scale to future exascale machines (Some theoretical work, similar to Ibeid et. al)

Smaller contributions:
- Research into programming models for science (Numba paper)






