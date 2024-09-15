TASK-BASED FMM FOR MULTICORE ARCHITECTURES (2014)
- ScalFMM

- Express FMM as a task flow

- Parallel efficiency = Speedup / N Proc
E = T(1) / P T(P)

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