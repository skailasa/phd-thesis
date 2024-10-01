Hybrid MPI-Thread Parallelization of the Fast Multipole Method Olivier

- Another example of a project that is abandoned on the wayside

BLAS M2L for analytical FMM

[3] O. Coulaud, P. Fortin, and J. Roman. High-performance BLAS formulation of the Adaptive Fast Multipole Method. Journal ofSupercomputing. (to appear).
[4] O. Coulaud, P. Fortin, and J. Roman. High performance BLAS formulation of the multipole-to-local operator in the Fast Multipole Method. Journal ofComputational Physics. (submitted, available at: http://hal.inria.fr/inria-00000957).
    - this is a good paper as it summarises all the analytical M2L approaches for Laplace

- Their findings at this point is that BLAS based field translations are better for low-accuracy applications than FFT, i.e. astrophysics/MD

- In practice, if efficient parallelizations have been realized in the uniform case [9, 11, 12, 16], the non uniform case is more difficult to handle. This is due to the irregularity of the particle distribution and to the hardly predictable communication scheme

Interesting to not on how the thinking on this has changed over the past few decades.

    - J. P. Singh, C. Holt, J. L. Hennessy, and A. Gupta. A parallel adaptive fast multipole method. In Supercomputing ’93
    - very early distributed FMM - uses parallel load balancing

- Hilbert ordering offers better data locality than Morton ordering (but with additional memory or computa- tion cost), but as shown in [6], the Hilbert decomposition does not offer in practice better results than the Morton one

- Ultimately this isn't where our data locality comes from anyway, as we organise again on a per level basis, keeping all siblings adjacent.

- could use 'mutual interaction principle' to cut number of P2P in half, but this requires more careful organisation of U list, to make sure you don't double count.

- Could be achieved by a metadata structure that carefully identifies all unique box-pairs, and chunks over them.

- only works if source/target particles are the same set, which in general they are not.

- Use mutexes over leaves

- Don't say much about M2L except that it uses BLAS, and single threaded blas calls, reduction over each leaf.

- Have independent decompositions at each tree level/ operation?

- MPI
    - Cost function based on particles per leaf
    - The internal cells in the octree are then assigned to the process which owns the first child.

- We also overlapp communications with computations in a classic way for the FMM (see [12] for example): nearest neighbor communications (for direct computation) are performed during the upward pass, whereas interaction list communications are performed during the direct computation step

- All communications are thus sender-driven and we use non- blocking MPI calls for sending. For receiving, we use one additional thread, the receiving thread, with blocking MPI calls

