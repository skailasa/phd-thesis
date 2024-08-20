# Modern Software Approaches for Fast Multipole Methods

Message: Evolving hardware and software environments elicit new software approaches to the construction of fast multipole method software.

Chapter 0:

- Abstract
    - one from upgrade is mostly fine

- Summary of main contributions
- highly performant library for single/multinode kernel independent FMM, which is also highly user friendly (BLAS vs FFT Paper, + HF implementation and tests)
    - Explicit comparison study for scalability on modern architectures (BLAS vs FFT paper)
    - Designed for generality both in terms of applications as well as current and future deployment. (Software paper)
    - Benchmarked on HPC machines (HF / Multinode tested)
    - performance model that shows that it can probably scale to future exascale machines (Some theoretical work, similar to Ibeid et. al)
    - enables the simulation of new problems, especially those that arise from HF helmholtz based BIEs while maintaining usability, extensibility and performance.
        - but generic enough to be extended to other problems too.

Smaller contributions:
- Research into programming models for science (Numba paper)

Impact:
- A new framework for developing FMMs both and related algorithms that can effectively be used to adapt code to new architectures via LLVM (Rust) as well as heterogenous codes.
- User friendly with a simple API
- Extensible to new similar algorithms
    - Kernel + Tree + field translations ? (need to check)
- Embedded within wider bempp-rs, but also completely independent
    - Not common within community, as most are built as set piece softwares.

Chapter 1: Introduction and Background.
- Introduction to Fast Multipole and Kernel Independent variants
    - Need good notes on approximation schemes for the ones I choose to mention (principally MFS/Chebyshev) Some understanding of analytical scheme and computational constraints/trade-offs

- FMM, why it's important
    - How the algorithm is structured (in words)
    - How to arrive at the complexity of the algorithm
    - Why complexity isn't the full story
    - How complexity was an issue when the algorithm was first proposed given the archs of that time.
    - Briefly introduce alternative methods of generating expansions here, principally for trading off performance models
        - Appendix of more detail about different FMM approaches and performance issues that arise from them.

- KiFMM + HF variants
    - Why this algorithm is important
        - Formulation + computational structure + software structure.
    - Contrast formulation (interpolation procedure etc) with other FMMs

- Computational issues that arise
    - 1. M2L and P2P bottlenecks
        - M2L on modern hardware paper
        - P2P for Laplace and Helmholtz, generating SIMD on CPU
            - What is SIMD, and why is ILP important, memory wall etcs
    - 2. Communication bottlenecks in M2M and M2L, kernels + trees
        - Communication schemes that arise, e.g. Ibeid et. al.

- Related Ideas
    - H and H2 matrices
        - Need notes on BIE (different integration schemes, Nystrom, Galerkin)
    - vs FFT vs Multigrid (note)

- Computational Structure of FMMs
    - Flow of data in FMM
    - Principal differences between Laplace and Helmholtz FMM
        - Precomputation, growth in Rank
        - Approximation machinery of kiFMM should work anyway despite specialised directional FMMs existing
        - as we show in chapter ..
    - Need a good reason (mathematically) for rank dependence on kD and justification of O(N log N ) complexity

To Review:
    - P.G. Martinsson FDS book
    Key ideas to summarise
        - randomised SVD, and range finding
        - Analytical FMM, optimality of rank (chapter 9)
        - trade-offs of FMM
        - Basically first three sections.

    - H2 matrices Boerm book.
        - Main ideas from first 6 chapters
    - Directional FMM
        - Engquist and Ying
            - What are the key difficulties with this approach?
        - Messner et. al
            - Same as above.


Chapter 2 : Modern programming environments for science (~10 pages)

Requirements for research software
    - Summarise the role of research software in modern academia
    - These two reports
    - https://www.software.ac.uk/blog/not-so-brief-history-research-software-engineers
    - https://www.nature.com/articles/d41586-022-01516-2

    - What are the key requirements for research software that set it apart from that in industry?
    - Why is this challenging?
    - Introduce need for the first Python paper.

Low Level or High Level? Balancing Programming Environments with Performance Requirements.
    - trends in computer hardware, flops/bytes, communication issues at the exascale.
    - trends in computer languages (Mojo)
    - As RSE we want to be able to flexibly adapt codes, and take advantage of software and hardware as it emerges.
    - how does this additionally factor into software design?

Chapter 3: Designing software for the fast multipole method

Data oriented Design with Rust Traits

- Summary of key message from DOD book as applied to FMMs

FMM Software as a Framework

- With reference to results of Chapter 2, need to provide the full design of kiFMM and make it clear how it operates as a framework

Diagrams:
    - Component diagram high level of main software interfaces
    https://www.visual-paradigm.com/guide/uml-unified-modeling-language/what-is-component-diagram/

    - Zoomed in component diagrams of field translation implementors
    - FMM/Tree implementors.

High Performance Trees

- Key algorithms for single node trees that lead to performance
    - Uniform trees
    - Morton encoding
    - neighbour checking algorithm


- Distributed trees
    - My communication pattern for distributed FMM
    - How this is implemented in trees
    - Some theoretical work on communication complexity for my distributed FMM
    - Why this may be acceptable for the problem sizes we consider, if not exactly ready for exascale.

High Performance FMM operators

- P2M, P2P - dependent on the kernel implementation - summarise the method used by green-kernels and cite this work.

- M2M and L2L are using BLAS3, with empirically derived blocks

- M2L
    - Takes up most space, talk explicitly about BLAS3 and direct matrix compression using SVD
    - Talk explicitly about PVFMM approach.
    - Contrast the two methods in terms of complexity and memory accesses.
    - Basically a bulked up version of section 1 and 2 of the paper.

Chapter 4: Comparing Field Translation Approaches for Kernel Independent Fast Multipole Methods

- BLAS algorithm and rSVD accelerated pre-computation.

- Implementation details of BLAS approach
    - overdetermined
    - memory layout
    - required precomputation of interaction lists
    - creating gather/scatter index sets
    - parallelisation (which parts and why)

- Contrast to implementation details of FFT approach
    - not overdetermined
    - complex explicit SIMD (give actual pseudo-code in appendix)
        - why this should generally be avoided - cache oblivious preferred and why
        - explicit blocking too
    - frequency based re-ordering required.
    - redundant calculations.

- Contrast with Precomputation times for FFT.

- Precomputation times and benchmarks for Laplace and Helmholtz for different accuracies and wavenumbers.

- Reflect on approaches given the changes in computer hardware discussed in chapter 2.


Chapter 5: Experiments, (~10 pages)
- Scaling experiments
- Single Node (Low/High frequency)
- Multinode Laplace only

- What remains to be studied?
    - Are communication patterns in the multinode case not sufficient? If not, exactly which parts.
    - GPU acceleration and other novel hardwares, how do they fit into the current design?
    - Arm experiments on HPC and high frequency on HPC.
