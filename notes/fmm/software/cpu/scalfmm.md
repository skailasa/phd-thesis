TASK-BASED FMM FOR MULTICORE ARCHITECTURES (2014)
- ScalFMM

- Express FMM as a task flow

- Parallel efficiency = Speedup / N Proc
E = T(1) / P T(P)

- Pthreads vs Omp threads
- p threads need to manually manage all aspects of thread creation.
    - unix like
    - low level creation/join/fork mutex etc.





- Study shared memory uniformly discretised octrees

- Consider task based parallelism

- First paradigm canonical fork-join expression, synchronisations between tree levels for each type of task.
- Second, using the fact that near/far field can be computed independently propose a formulation enabling interleaving of far and near tasks.
- Finally, just throw everything into the runtime and let it figure it out.

First two done with OpenMP
Last one, StarPU

- FMM appplicable if kernel can eb approximated accurately in the far field. For asymptotically smooth kernels this is always the case

- Uses the optimisations from Messner paper
    M. Messner, B. Bramas, O. Coulaud, and E. Darve, Optimized M2LKernels for the Chebyshev Interpolation Based Fast Multipole Method, http://hal.inria.fr/hal-00746089, 2012

- StarPU - manages tasks and data transfers optimally.
- Task flows represented as dags, tasks are vertices and edges are dependencies
- multidevices supported (CPU/GPU) but need to be specified by the programmer
- Doesn't release us from writing code for each architecture.
- Data, which can be moved, is accessed via an abstraction layer

- Naive Fork join model
    - progress level by level and split work at each level over threads.
    - parallelisation is split by operator
     - i.e. M2L is parallelised over each target/source box pair...
    - Synchronise between M2N and M2L for some reason

- Fork Join
    - Perform all M2Ms, with synch points between levels
    - then all P2Ps and M2Ls, which provides max concurrency and opportunities for load balance
    - finally all L2Ls and L2Ps
    - block together calls over multiple cells in this model, instead of cell-cell interactions
    - fewer operator calls limits the concurrency available.

- the near and far fields are only 'nearly' independent as the L2P and P2P have to write to same values/
    - this is a weird way of thinking about it, leaf level computations and M2L are completely independent.
    - Only L2P and P2P are dependent



A machine that is cache-coherent with nonuniform memory access (ccNUMA) refers to a type of computer architecture where:

Cache coherence: This ensures that all processors in a multi-core system have a consistent view of memory. When one processor updates the value of a shared variable in its cache, other processors will see the updated value if they access that variable. This avoids situations where different processors might work with different copies of the same data.

Nonuniform memory access (NUMA): In a NUMA architecture, memory is physically divided into different regions, each closer to certain processors than others. This means that accessing memory that is closer (local memory) to a processor is faster, while accessing memory farther away (remote memory) takes more time (hence, "nonuniform" memory access times).

- Though the FMM in principle offers a lot of parallelism, in practice the trade-off between blocking and concurrency makes the problem more difficult.
- Runtime systmes are a useful asset for developers, so less care is needed with parallel communication.

O. Coulaud, P. Fortin, and J. Roman, Hybrid MPI-thread parallelization of the fast mul- tipole method, in ISPDC ’07, Sixth International Symposium on Parallel and Distributed Computing, 2007, p. 52.
 - citation for another Pthread/Blas FMM


 - Quote chandramowlishwaram FMM papers
    - [3] A. Chandramowlishwaran, K. Madduri, and R. Vuduc, Diagnosis, tuning, and redesign for multicore performance: A case study of the fast multipole method, in Proceedings of the 2010 ACM/IEEE Conference on Supercomputing, 2010.
    - [4] A. Chandramowlishwaran, S. Williams, L. Oliker, and G. B. Ilya Lashuk, and R. Vuduc, Optimizing and tuning the fast multipole method for state-of-the-art multicore architectures

- again completely dead software, as examples of exploiting thread affinity to increase cache performance for adaptive FMM.

- early examples of using SIMD/SSE optimisations.

    - B. Zhang, J. Huang, and N. P. Pitsianis, Dynamic prioritization for parallel traversal of irregularly structured spatio-temporal graphs, in Proceedings of the 3rd USENIX Workshop on Hot Topics in Parallelism, 2011.
    - graph based formulation of the FMMi

In this paper, we study the impact of the parallelization method on the performance of the FMM on shared-memory multicore machines with uniform octree. For

- async m2l and p2p

- StarPU manages the data transfers.
- some of them, not all, manage with GPU - need to check which ones, probably most / all of them by now.


In other words, a runtime does not release us from writing code for each specific architecture
- just manages scheduling.

StarPU transparently guarantees that a codelet which needs to access a piece of data will be given a pointer to a valid data replicate.
    - seems like this will wreck caching

- don't talk much about data locality, seemingly only rely on that provided by Morton ordering, not a level wise re-order like us.

- group together blocks of nodes, slightly coarser than per box.

- Scheduler choices.
    - seems really hard to schedule a non-uniform load, across heterogenous devices.
    - developed a custom scheduler 'priority' for the FMM
    - inbuilt Eager scheduler
        - greedy algorithm, releases ead of FIFO queue, no choices, no distinctions between the tasks, no user control
    - Having to design a custom scheduler is a very strange approach for achieving performance, as you focus entirely on load rather than cache coherence and memory accesses.
    - Doesn't even say how their scheduler works.
    - But can give different priority marks with respet to geometry.
    - try and differentiate with small and large P2P tasks, and assign them diffferent priority.
        - why does this even matter? Surely total load is all that's important, rather than priority of execution times

- Indeed, the principle problem with this approach is a focus on runtime and not memory.

- useful for MPI, as DAG can handle data dependencies.

NUMA policies:

We have assessed different NUMA policies for the memory allocation. In the present study, we use a memory interleave policy as it achieved the highest perfor- mance. Memory is allocated using round robin on all memory nodes with the “nu- mactl –interleave=all” option. We have also tuned the OpenMP environment. We have bound the threads to the CPU cores by setting the “OMP PROC BIND=true” environment variable and we have enabled an active waiting policy by setting the “OMP WAIT POLICY=ACTIVE” variable. The OpenMP codes rely on the Intel OpenMP runtime library embedded with the compiler. The task flow codes rely on StarPU 1.0.0rc3