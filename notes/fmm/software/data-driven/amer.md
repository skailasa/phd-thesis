Scaling FMM with Data-Driven OpenMP Tasks
on Multicore Architectures (2016)

Poor scalability on parallel architectures can be attributed
to several factors, among which idle times, data movement, and runtime
overhead are predominant. Conventional parallel loops and nested parallelism have proved successful for regular computational patterns. For
more complex and irregular cases, however, these methods often perform
poorly because they consider only a subset of these costs


'Data driven' vs Data oriented design, also a way of thinking about data as a first class citizen.

Furthermore, loop tiling, a technique that promotes data
locality and has been successful for regular parallel methods, has received
little attention in the context of dynamic and irregular parallelism

This is good phrasing

"The technology trend of increasing core densities and deepening memory hierarchies in high-end processor packages is exacerbating the difficulty of harnessing
their computational power. Higher core counts imply that applications have to
expose more concurrent work in order to feed the computational units. Moreover, the performance of the memory subsystem is not keeping up with the core
density. Consequently, pressure on the memory subsystem (e.g., caches, interconnects) and the distances that remote data has to traverse are increasing, adding
to the existing CPU-memory performance gap."

- Optimal dynamic scheduling is NP complete even in simple case of static scheduling two processors, and one or two time units for task weights.

- The model tha dictates parallel execution, e.g. the runtime - e.g. BSP/Data Driven, effects the resulting schedule and does not guarantee optimality.

Recent literature has shown that
loss in parallel efficiency can be attributed to three primary factors: idle times,
data movement, and runtime overhead 1 [7,9]. In order to mitigate these costs,
parallel algorithms must expose sufficient parallelism (i.e., parallel slackness)
and reduce data movement while keeping the runtime overhead low

For instance, bulk-synchronous approaches, exemplified by parallel
loops, can suffer from underutilization of resources because of insufficient parallel slackness within or across computational steps. Data-driven methods can
maximize resource utilization but often suffer from poor data locality (e.g., cache
thrashing) and costly task management

Consequently, the resulting mapping can exhibit
little data reuse and often causes substantial cache thrashing. Although some
incentives have been proposed, such as hierarchical place trees
- Yan, Y., Zhao, J., Guo, Y., Sarkar, V.: Hierarchical place trees: a portable abstraction for task parallelism and data movement. In: Gao, G.R., Pollock, L.L., Cavazos,
J., Li, X. (eds.) LCPC 2009. LNCS, vol. 5898, pp. 172–187. Springer, Heidelberg
(2010)
    - help reduce cost of rdma
    - do not provide sufficient data re-use.
    - loop tiling has seen litle application in the context of data-driven and async tasking.


We choose FMM for its rich set of heterogeneous computational kernels and its complex dependencies that stress parallel
efficiency. Furthermore, FMM input parameters allow us to control computation
and synchronization requirements to help generalize our results

- Criticism from BSP perspective weird, as there is very little synchrnnisation required by the FMM.
This is similar to existing cache-blocking techniques found in linear algebra optimizations. In KIFMM, however, we target the
high levels of the memory hierarchy (e.g., last-level cache) because operations on
tree nodes operate on larger data. For instance, an operation between two tree
nodes can be composed of matrix multiplications or FFT transformations. These
computations are carried out by external libraries and are often well optimized
for lower-level caches. F

- sub-optimal tiling, perform nested loops, don't take advantage of geometrical considerations.

- large block sizes hinder parallel slackness as blocks are too large
    - but the subroutines could take advantage of this, e.g BLAS operations/FFT

large values of q imply a compute-intensive regime that does not
benefit from our data locality optimizations.

- Their data locality optimisations are there to help M2L, and P2P is poorly optimised, which is much easier to optimise.

They are measuring what they want to measure.

Also their code doesn't say what the expansion order was taken as, or the error in their final solution which is fishy.

- Their codes would demonstrate a different result if the problem was framed differently. I.e. BSP with P2P offloaded/optimised, and small M2L component.

But interesting result in optimising M2L via data-locality considerations
But their kernels are very simpplistic by the standards of the FMM community, lack of open-source software makes it impossible to verify their claims without rebuilding the whole thing.

