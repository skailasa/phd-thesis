An FMM Based on Dual Tree Traversal for Many-core Architectures

- task based threading model to maximise thread level parallelism and intra-node balancing
- the inner kernels are optimised using AVX
- interaction lists found using dual tree traversal instead of explicit

- a traditional objection of FMM vs FFT is that it requires more flops, however the changing nature of hardware makes this less relevant.
- optimal communication properties of the FMM are better in this context

- optimal 3D FFT requires two global transpose communications between P processes.
    - therefore O(sqrt{P}) - https://dl.acm.org/doi/pdf/10.1145/2304576.2304604
    - necessary bandwidth only provided by a fat tree or hypercube network.
    - constructing such topologies is expensive and hard at exascale

- CPU optimisation
    - old, so quote chandramowlishahwaran papers
        - A. Chandramowlishwaran, K. Madduri, and R. Vuduc. Diagnosis, tuning, and redesign for multicore performance: A case study of the fast multipole method. In Proceedings of the 2010 ACM/IEEE International Conference for High Performance Computing, Networking, Storage and Analysis, SC’10, 2010.
        - thread level, NUMA aware and manual SIMD initial paper
    - more recent, PVFMM, and us

- GPU optimisation
    - not much work here
    - Takahashi is quoted
        - Use stencils to take M2L kernel into being compute bound
    - alternatives for achieving this on GPU come from
        - increasing number of particles per leaf
        - or simply calculating on the CPU instead
            - Q. Hu, N. A. Gumerov, and R. Duraiswami. Scalable fast multipole methods on distributed heterogeneous architectures. In Proceedings of the 2011 ACM/IEEE International Conference for High Performance Computing, Networking, Storage and Analysis, SC’11, 2011

        - limitation is that Takahashi work relies on appx uniform particle distribution for efficiency.
            in exploiting symmetry of translation stencil
            - ours DOES NOT

    - Entire calculation on GPU, Bedorf code, but only works at low accuracies
        - non uniform, works with sparse adaptive octrees
        - J. Bedorf, E. Gaburov, and S. Portegies Zwart. A sparse octree gravitational N-body code that runs entirely on the GPU processor. Journal of Computational Physics, 231:2825–2839, 2012
        - just 50ms for entire algorithm including tree construction.
        - order of magnitude faster than other GPU codes?
        - cannot adjust order of expansion past p=3

- MPI parallelisation
    - Historical attempts as of 2013
    - Winkel, p2p based communication scheme, a thread dedicated to communication on each node.
        - M. Winkel, R. Speck, H. Hubner, L. Arnold, R. Krause, and P. Gibbon. A massively parallel, multi-disciplinary barnes–hut tree code for extreme-scale N-body simulations. Computer Physics Communications, 183:880–889, 2012.

    - Jetley, use CHARM++ to achieve dynamic load balancing on a large scale heterogenous environment
        - P. Jetley, L. Wesolowski, F. Gioachin, L. V. Kale, and T. R. Quinn. Scaling hierarchical N-body simulations on GPU clusters. In Proceedings of the 2010 ACM/IEEE International Conference for High Performance Computing, Networking, Storage and Analysis, SC’10, 2010.

    - n.b. all these links are dead

- These efforts to provide an alternative to bulk- synchronous communication models could eventually become advantageous, but the lack of comparison against current state-of-the-art bulk-synchronous methods [26, 40] that also scale to the full node of the largest supercomputers, makes it difficult to predict exactly when they will become advantageous (if they do at all)

    - Need to find more recent attempts


- MPI parallelisation of adaptive trees
    - Winkel use 64 bit Morton keys like usl max tree level of 21 (pvfmm deeper than this)
    - however, this isn't really a factor given the nature of modern compute nodes in supercomputers


- Autotuning
    - Yokota and Barba - reference not contained in article pdf...
    - dual tree traversal + autotuning mechanism for selecting between M2L and M2P on adaptive tree
    - selecting between m2l and p2p kernels to toptimise the number of particles at the leaf at which P2P is performed.


- Event driven
    - More recent ones too, but give
        - H. Ltaief and R. Yokota. Data-driven execution of fast multipole methods. arXiv:1203.0889v1, 2012
    - FMM threads scheduled from a DAG representing the data flow - uses QUARK runtime
    - Reference agullo work using StarPU

- Different series expansions have different computational intensities, complexity of operators (in terms of p) and parallelism available.

- The majority of techniques were developed in an era where flops themselves were very expensive

- e.g. precomputation makes runtime flops cheaper, but introduces data loads.

- Common misconception tree codes vs FMMs, treecodes better for low expansion orders, a consequence of expansion choice

    - R. Yokota and L. A. Barba. Hierarchical N-body simulations with auto-tuning for (rest missing)
    - https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=6127848
    - tree codes are slower than FMM

- Furthermore, low level optimization of kernels of this complexity require a significant effort, and the absence of highly tuned open source implementations of these kernels makes it difficult to perform an exhaustive comparison between different expansions.

- DTT

- treecodes, each box contains pointer to children,m recursive function call / stack/queue. All nodes visited once top down manner.

- FMM doesn't rely on actually constructing a tree, loop level by level.
- More advanced techniques for interaction list
    - e.g. gumerov & duaraiswami - stencil to reduce number of V list to 119 in 3D
    - still same adm. criteria though.

    - secondly cubic cells are needed to enforce admissability.
    - rectangular used in tree codes
    - has 'disadvantages for load balanced adaptive trees'

- Traverse target/source tree simulatneously to create interaction list on the fly
- allows for non-square boxes, easy adaption to task based runtime

- distance between cells identified using geometry, so don't need square boxes
- target/source trees can be separate - though this can be done by us anyway.

- Loss of parallelism over outer loop of all target boxes at a level, but can instead use a tasking t=runtime from TBB or OpenMP

- Don't observe anywhere near their published benchmarks on the threadripper in double precision.


- contains table of all expansions which is very useful

