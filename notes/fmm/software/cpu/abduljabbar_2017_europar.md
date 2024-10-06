Performance Evaluation of Computation and Communication Kernels of the Fast Multipole Method on Intel Manycore Architecture

- NUMA aware, alloc on CPU that contains most of data dependencies

e.g. first touch policy

Tree codes like Barnes-Hut [3] build a geometric quad/oct tree to bring the quadratic com- plexity of N-body problem down to O(N logN). This is done by introducing a cutoff distance beyond which particles interact as cells located at the center of mass.

Fork-join sequence parallelism is a common parallel computing model where a task is divided into smaller, independent sub-tasks (forking) that can be executed concurrently, and then the results of those sub-tasks are combined (joining) to produce the final result. In this model, a program "forks" into multiple threads or processes to work on separate parts of a problem in parallel. Once the parallel tasks complete, they "join" back together at a synchronization point, where the results are merged, and the main task continues. This approach is used in many parallel programming frameworks, such as OpenMP, Java's Fork/Join framework, and Cilk, to efficiently utilize multi-core processors and reduce execution time for complex problems.

- foundational parallel FMM

    - Greengard, L., Gropp, W.D.: A parallel version of the fast multipole method. Comput. Math. Appl. 20(7), 63–71 (1990)


Flops per P2P call is 20 n_i n_j, number of target/source cells respectively

20 flops calculates the laplace potential, and potential gradients.

outer loop parallelised using OpenMP and use explicit SIMD for kernel in P2P

- Nested task parallelism can be achieved as well, in DTT there is no outer loop over target boxes.

DTT - takes a source and target box, expans the larger until either MAC is satisfied or both are leaf boxes.

- tasks can spawn new tasks, algorithm 2 in the paper, very clean interaction specification.


def interact(A, B):
    if A and B are leafs:
        P2P
    else:
        if MAC satisfied:
            M2L
        else:
            if size (A, B) > nspawn:
                spawn(DTT(A, B))
            else:
                DTT(A, B)

def DTT(A, B):
    if A > B
        for c in children(A):
            interact(c, B)
    else:
        for c in children(A):
            interact(A, c)

- The LET is a union of trees representing the entire domain as perceived by local proceses.
- biggest hindrance to perfect scaling

- HSDX and NBX are two methods
    - abduljabbar's ghost exchange method
    - Abduljabbar, M., Markomanolis, G.S., Ibeid, H., Yokota, R., Keyes, D.: Commu- nication reducing algorithms for distributed hierarchical N-body problems with boundary distributions. In: Kunkel, J.M., Yokota, R., Balaji, P., Keyes, D. (eds.) ISC 2017. LNCS, vol. 10266, pp. 79–96. Springer, Cham (2017). doi:10.1007/ 978-3-319-58667-0 5

    - explores sparse all to all via neighbourhood comms
    - Hoefler, T., Siebert, C., Lumsdaine, A.: Scalable communication protocols for dynamic sparse data exchange. In: Proceedings of the 15th ACM SIGPLAN Sym- posium on Principles and Practice of Parallel Programming, PPoPP 2010, pp. 159–168. ACM, New York (2010). http://doi.acm.org/10.1145/1693453.1693476

- Contains a nice table of communication complexities., including point to point and hypercube as well as HSDX



Note that “Hierarchical” protocol means that the data is aggregated along a structured hierarchy such as graphs and trees, whereas “sparse-aware” protocol avoids direct communication with partitions without or with very little data to exchange (almost negligible). In the context of NUMA systems, hierarchical protocols tend to maximize locality of the data within each local caches, and in the case of data exchange, each process requires the data only from its neighboring MPI ranks. Hence, the com- munication is mostly localized inside the NUMA socket. However, if the required data happens to be in different NUMA socket, then MPI would communicate the cache line from the socket’s memory, which is very negligible in proportion to locality maximizing communication protocols.

- Task based threading
    - Intel TBB
    - Intel Cilk Plus
    - OpenMP Tasks

Claim:
    restricting exchanges to neighbors only, which makes it potentially NUMA-aware
    HSDX (Distgraph) performs better that the others, and this is due to
    and yields acceptable on-chip performance. In
