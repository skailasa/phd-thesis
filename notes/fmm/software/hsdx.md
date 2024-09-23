Communication Reducing Algorithms for Distributed Hierarchical N-Body Problems with Boundary Distributions

- suggest that Morton encoding isn't optimal, modify ORB
- HSDX vf alltoallv

- Bedorf, full scalablility on GPU FMM (2012)
    - B´edorf, J., Gaburov, E., Zwart, S.P.: A sparse octree gravitational N-body code
that runs entirely on the GPU processor. J. Comput. Phys. 231(7), 2825–2839
(2012)
    - one particle per GPU thread, level wise masks to discover hierarchy.
    - threads sorted in Hilbert order.
    - 2.8 Million particles per second.

- Zandifar, M., Abdul Jabbar, M., Majidi, A., Keyes, D., Amato, N.M., Rauchwerger, L.: Composing algorithmic skeletons to express high-performance scientific
applications. In: Proceedings of the 29th ACM on International Conference on
Supercomputing, ser. ICS 2015, pp. 415–424. ACM, New York (2015)
    - Parallel FMM implementation as a benchmark for high-level communication skeletons
    - 

- Two objectives for good partitioning
    - load balance
    - efficient access to non-local data

- hard to simulatneously address both

- It is not clear to what extent spatial locality is maintained by hilbert curves extends to 3D?
    - doesn't contrast morton
- basically saying that for surface distributions there will be discontinuities in curve as most of interior is empty.
- not clear what the criticism is?

- Sender initiated communication, not clear how this works.
    - Common in N-body cosmology codes apparantly


- Conventional (PVFMM, Lashuk etc) the global tree is constructed bottom up, and therefore severed across processors
- merging of LET was complex, and typically largest part of the code.
- hard to implement new features.

- ExaFMM simplifies the structure.
- overlaps communication with computation.
- traditional, BSP alll to all v for LET construction

- Therefore, the tree structure was severed in many places,
which caused the merging of the LET to become quite complicated. Typically,
code for merging the LET would take a large portion of a parallel FMM code,
and this made it difficult to implement new features such as periodic boundary
conditions, mutual interaction, more efficient translation stencils, and dual tree
traversals.

Conventional parallel N-body methods use a bulk-synchronous MPI
alltoallv to communicate the whole LET at once, and overlap this communication with the local tree traversal to hide latency. 
- 
while something like an RDMA per task per cell
would be at the other end of the granularity spectrum.

y. The bulk-synchronous communication model can be thought of
as an extreme case of aggregation,

