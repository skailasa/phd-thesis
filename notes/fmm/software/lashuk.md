- really don't understand the complexity estimates of ghost communication in their scheme.

- Note that we repartition the leaves based solely on work balance ignoring the communication costs. Such an approach is suboptimal, but is not expensive to compute and works reasonably well in practice

- Use Sundar algorithm for balancing based on work load

- Rely on ISend for communicating charges as these are local
- Communicate partial up densities from loacl upward passes
- need a third comm, all reduce.

- Need MPI powers of two

- Communication complexity of all reduce 'reduce and scatter' approach

$$
O(t_s \log{p} +  t_w m (3\sqrt{p} - 2))
$$

$t_s$ - latency, $t_w$ bandwidth, $m$ - shared octants

have $d = \log{p}$ communication rounds, so latency cost term is explained that way.

- In the original paper use a combination of sample/bitonic sort.

- Parallelisation strategy
    - Can visit each octant in an embarrasingly parallel fashion per level
    - all operators are matrix vector products
    - VLI are a diagonal transaltion -using FFT
    - 'Two levels of parallelism exploited' across octants and across rows of the corresponding matrix
        - do much more now with ILP with explicit SIMD
        - blocking for cache utilisation
        - task based parallelism approaches

    - A processor’s relative balance of performance and bandwidth will change these curves, thereby changing the optimal value of q.

- In particular, the faster we can perform the compute-intensive ULI step, the larger we can make q thereby reducing the VLI and other memory-bound steps

Currently, we are working on introducing shared-memory parallelism in the tree construction, sharing the workload between CPUs and GPUs (essentially treating the GPU as another MPI process),

- V List step treated as a reduction on octants a of a given target b.

- Two parallel components, tree construction and evaluation.

- Their approach to tree, is local domain, construct LET of all ancestors and all interaction lists.
    - From warren and salmon original work
    - M. S. WARREN AND J. K. SALMON, A parallel hashed oct- tree N-body algorithm, in Proceedings of Supercomputing, The SCxy Conference series, Portland, Oregon, November 1993, ACM/IEEE.
    - Still use an all gather to exchange geometric domains controlled by each rank


- Send charges
- Sum up upward densities of the contributors of each octamt
- Third, broadcast the complete densities to users of each octant.

- do after local upward passes.
- Reduce/scatter algorithm requires power of two ranks.
- shared octants if the union of contributors and users contains more than one process

- Complexity estimate
- first term (latency relateed costs), depends on number of commmunication rounds.
- second term is related to bandwidth, i.e. amount of data over all communication rounds.

Note that

$$
\sum_{i=0}^{d-1} \min(2^{d-i-1}, 2^i)
$$

symettric sum about point $i=(d-1)/2$, below wihich first term is smaller, and sum of both halves is the same so get,

$$
= 2 \sum_{i=0}^{\frac{d-1}{2}} 2^i = 2(2^\frac{d+1}{2}-1) = 2^\frac{d+3}{2} - 2 = 2\sqrt{2} \sqrt{p} - 2 < 3 \sqrt{p} - 2
$$

So ghost exchange has complexity

$$
O(m (3 \sqrt{p} - 2))
$$

$m$ is the contribution of shared octants by each process

Number of shared octants $m$ for uniform distribution can be estimated from the surface to volume ratio of all leaf octants.

For uniform grid, $N/P$ - number of leaf boxes, therefore in uniform grid this is also proportional to the number of points.

so surface to volume ratio of all leaf boxes of feature size $l_d$

$$
O((Nl_d/P)^{2}/(Nl_d/P)^3)
$$

Taking out $l_d$ in estimate as it's a constant,

$$
O((N/P)^{2/3})
$$


This is the estimate for $m$ i.e. max number of shared octants over all LETs, and $\sqrt{p}$ scaling for scaling of number of octants communicated during each communication round.

The constant will be large next to $m$ as its the maxima, but ghosts will be communicated with each communication round.

- Also contain GPU acceleration
- Involve a copy o fU list metadata into GPU
    - future schemes should avoid this, using DMA/Unified memory, or forming entire scheme on GPU, taking advantage of larger memories now available.

    - at this point, did the Hadamard products on the GPU, even though computational intensity is low
    