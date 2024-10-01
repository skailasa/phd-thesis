Hierarchical algorithms on hierarchical architectures

- Flops no longer a reasonable proxy for all aspects of complexity.

- Algorithms must squeeze memory
    - data transfer, synchronisations
    - extra flops on locally cached data represents only a small cost in time and energy.

- Hierarchically low-rank matrices realise a rarely achieved combination of optimal storage complexity and high computational intensity for a wide class of formally dense linear operators

- well provisioned for early exascale computers, where bandwidth and processing power are grossly out of step.

- A challenge is that emerging architectures possess (mem) hierarchies of their own which in general do not align with those of the algorithm.

Rumley S, Bahadori N, Polster R, Hammond S, Calhoun D, Wen K, Rodrigues A, Bergman K. 2017 Optical interconnects for extreme scale computing systems. Parallel Comput. 53, 367–380. (doi:10.1016/j.parco.2017.02.001
    - reference for bandwidth vs flops scaling

- Growing latency in memory bandwidth to processsing power, and a growing latency in clock cycles for deep memory accesses. up to 1000 or more for DRAM

- Data sparsity implies that relatively small cache memories can hold relatively highly accurate representations of operators.

- The savings in latency from residing high on the memory hierarchy is even more important than the savings in operation count from working directly with the compressed representation

- Hierarchical matrices shrink the memory footprints of matrices allowing the data to live higher on the memory hierarchy during operations. Furthermore, the algorithms at the core of hierarchical matrix operations can be written in terms of high arithmetic intensity GEMM, QR, randomized SVD, Cholesky factorization, and other dense linear algebraic operations that operate on large batches of small blocks and are able to take advantage of modern manycore architectures

- When a matrix comes from a spatial discretisation, the admissibility criterion is naturally geometric in nature, and depends on the separation between the cluster of nodes corresponding to the rows of hte bloxk/cluster corresponding to the columns of the block.

- For a given target accuracy, compute/memory trade-off between using fewer blocks of larger rank (coarse admiss. criteria and getting closer to weak admissibility) or more blocks of smaller rank (tigher adm. par., )

- Nice summary of H matrices here, with illustration, could definitely be used in my own introduction.

- Hierarchical matrices further classified based on form of the numerical representation of matrix block data

- The simplest representation represents every block independently $\mathcal{H}$ matrices do this.

Eeach low-rank factor at level $l$

$$
A_{ij}^l = U_{ij}^l(V_{ij}^l)^T
$$

For block $ij$, these matrices are of rank $k$.

Requires $O(kn \log{n})$ storage.

Can obtain a better asymptotic memory footprint $O(kn)$, the column/row bases are common for all blocks of a given level,

$$
A_{ij}^l = U_i^l S_{ij}^l (V_j^l)^T
$$

i.e. every block represented by $k \times k$ coupling matrix in these bases.

Better asymptotic complexity obtained when these bases are nested.

I.e. $U_i^l$ not stored explicitly for a block row, but generated on demand from the bases of its children using a recursion,

$$
U_i^l = \sum_c U_{ic}^{l+1}E_{ic}^{l+1}
$$

In this case, known as $\mathcal{H}^2$ matrices. Denoting hierarchies in both the block structure, and in the low rank bases.

- Linalg with hierarchical matrices
- 'HicMA' library - completely unusable, and uninstallable
- CPU+OpenMP/GPU
- H2 matrix format with GPU
- They do something very similar to us, cast algorithms on a level-by-level flattened trees, and use batched dense linear algebra kernels on operations at every level.
- Operate on large batches of small blocks, and very high throughput

- With this design pattern the 'irregularity' of the hierarchical tree is completely flattened.

- The basic implementation in 'two phases'
- marshalling hte irregular data structure in a way that's amenable to batched dense linear algebra - only involve pointer arithmetic, with no data movement or floating point operations - this is the same as my metadata calculations.

- Batched kernels are executed on floating point data

$$
Ax = \left( \sum_l \sum_{(i, j) \in L_l} U_i^l S_{ij}^l (V_{j}^l)^T \right) x
$$

Where $L_l$ are the set of low-rank blocks at level $l$. Each of the three muls are streamed through the GPU over batches of blocks. Even when not enough work for all threads at top levels of the tree. Overlap with 'streams'


Boukaram W, Turkiyyah G, Keyes D. 2019 Hierarchical matrix operations on GPUs: matrix- vector multiplication and compression. ACM Trans. Math. Softw. 45, 3:1–3:28. (doi:10.1145/ 3314951) - full GPU paper

- 78% of theoretical peak bandwidth in their implementation via latency hiding.

- Programming practices 'at the exascale'

- Rumley S, Bahadori N, Polster R, Hammond S, Calhoun D, Wen K, Rodrigues A, Bergman K. 2017 Optical interconnects for extreme scale computing systems. Parallel Comput. 53, 367–380. (doi:10.1016/j.parco.2017.02.001)
    - good reference for flops vs bandwidth

- The #1 ranked system as of this writing, Summit at ORNL, can perform about 2000 flops in the time it takes to load a Byte, or about 16 000 flops in the time it takes to load a double-precision word.
    - where did they get this information, what would it be for summit?

- I like this phrasing
Contemporary architectures charge exorbitant latency and energy penalties for pulling in data from afar. At the same time, the peak flop/s rate promised from exascale hardware is realizable only if SIMT-style vector and matrix operations can be used.
At first glance, this introduces a tension between architecture and complex algorithms with tree-like data structures and scale recurrence. However, through a variety of techniques, this apparent mismatch can be spanned


- Proponent of task based runtime systems, as not restricted to specific algorithmic ordering of tasks.
- removes artificial syncs, expose more native concurrency, and shorten critical path

A DAG-based expression of a computation is usually superior to its expression in a compiled procedural language with loops and subroutine calls. The latter tends to restrict operations to a specific order. DAG-based dynamic runtime engines can remove artifactual synchronizations in the form of subroutine boundaries, remove artifactual orderings in the form of pre-scheduled loops, expose the native concurrency, and shorten the critical path.

Their disadvantages are the overhead of constructing and managing a task graph and the potential loss of memory locality to exploit the maximum concurrency when a core becomes idle and the nearest data is in a different memory basin.

- NUMA aware approaches do exist, are they effective though? Comparing e.g. ScalFMM to kiFMM?

Implemented with task-based dynamic runtime systems, hierarchical and tile-based algorithms expose concurrency at the block level, relaxing the synchrony of traditional full matrix algorithms with global loop limits.


Double-buffering is a technique used to improve performance and efficiency in scenarios where data is being produced and consumed at different rates. It is commonly used in graphics programming, data transfer, and concurrent computing. The key idea is to use two buffers so that one can be used for writing new data while the other is being read. This helps avoid delays or stalls caused by waiting for the buffer to be available.

Non-temporal stores are a type of memory write operation that bypasses the CPU cache. They are used when writing large amounts of data that will not be reused in the near future, thus avoiding unnecessary cache pollution and improving performance for specific scenarios.

- Hicma is incorporated in cuBLAS


NUMA aware / DAG specified runtimes

- StarPU, PaRSec, Charm++, Legion, OmpSs, HPX, ADLB and Argo