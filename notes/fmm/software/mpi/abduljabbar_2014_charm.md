- directly contrast BSP approach to LET vs charm
- asynch + granular control of communication

spectrum of BSP all to all V for all LET to RDMA per task per cell.

The bulk-synchronous communication model can be thought of as an extreme case of aggregation, while something like an RDMA per task per cell would be at the other end of the granularity spectrum.



As mentioned earlier, data-driven execution models add value not by providing load-balancing or data-caching features to parallel N-body methods, but rather by adding flexibility to the granularity at which these mechanisms can be executed. However,

- only worth it if serial/single node performance is good enogh

Previous work with good serial performance have focused
on optimizing the bulk-synchronous all-to-all communication itself rather than data-driven execution models. With these optimizations Lashuk et al. were able to calculate 90 billion particles in approximately 300 seconds on 200K cores of Jaguar and achieved 0.7 Pflops [10]. Similarly, Yokota et al. calculated 64 billion particles in approximately 100 seconds on 4000 GPUs of TSUBAME2.0 and achieved 1.0 Pflops [11]


urthermore, every M2L cell depends on hundreds of M2M cells. It is not a clear data-path where each node in the DAG has one arrow pointing to the next node. It is a DAG with hundreds of arrows pointing to a single M2L node. This is another reason why data-flow programming at this level of granularity is not favorable

FMM has two major communication phases : the partition-
ing of particles (load-balancing), and the LET communication (prefetching).

Partitioning phase

- ORB
    - splits particles equally with bisector at every level/bisection of tree.
    - rectangular subdomains.
    - aspect ratio can become lrge for non-uniform domains
    - sub-optimal interaction list size/comm load
    This problem can be solved by choosing the direction of the geometric bisector to always split in the longest dimension. The original method is limited to cases where the number of processes is a power of two, but the method can be extended to non-powers-of-two by using multi sections instead of bisections [15].

- Use ORB over HOT
- One of the main reasons is that we were able to improve a major defect of ORB – partition- cell alignment issue. Since geometrically closer points interact more densely with each other, it is crucial to keep the particles in the same cell on the same process in order to minimize communication.

One of the main reasons is that we were able to improve a major defect of ORB – partition- cell alignment issue. Since geometrically closer points interact more densely with each other, it is crucial to keep the particles in the same cell on the same process in order to minimize communication


However, if a global Morton/Hilbert key is used to construct the local trees, the ORB may place a bisector in the middle of a cell as

This results in an increase in the interaction list size. We avoid this problem by using local Morton/Hilbert keys that use the bounds of the local partition. This

This may at first seem to increase the interaction list near the partition boundaries since two misaligned tree structures are formed

- ExaFMM pioneered global/local splitting.

While the remote information for the LET is being trans-
ferred, the local tree can be traversed. Conventional fast N- body methods overlap the entire LET communication with the entire local tree traversal.

For load-balancing, the hashed- octree and orthogonal recursive bisection are both effective techniques for maximizing data locality while balancing the workload among the partitions by using the workload from the previous step as weights when partitioning.

We also propose a novel partitioning scheme, which allows
us to geometrically separate the local tree from the global tree. This was only possible because our FMM uses the dual tree traversal, which does not require a global key nor cubic cells

- weighting scheme by interaction list for load distribution.

