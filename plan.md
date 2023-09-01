# Upgrade

Title: Modern software approaches for IEs (~30 pages at most)

Chapter 0 - Introduction ~3-5 pages

- The goal of this research project is to contribute significantly towards the design and development of a highly-parallelised, scalable, software infrastructure for `Fast Algorithms'
    - `Fast Algorithms' - explain how they arise from dense matrices with hierarchical structures that allows for numerical compression of off-diagonals for optimal application/inversion.
    - Specific outputs:
        - Parallel tree library
        - Parallel FMM library
        - Re-use of data structures to create fast direct solver library in the near future.
    - Context
        - Next gen BEM software
            - can scale from laptops to supercomputers
            - deployed with ease with interpreted language interfaces for non-computational researchers
        - Problems that can be studied
            - virus simulation
            - geophysics
            - ML
    - Impact
        - solvers in this domain are either
            - designed to numerically validate an algorithmic approach
            - heavily optimised to achieve performance
        - nothing extensible really available
            - as a testbed for algorithmic experimentation
            - extension to differing applications in which these algorithms apply.
            - or as a testbed for new implementation approaches
                - new hardware etc.
        - the impact of a particular method is defined by how easy it is for software to be extended OR to be run as a black box.

Chapter 1 - A Python FMM ~3-5 pages

- What is the FMM?
- What are kernel-independent FMMs?
    - Benefits of this approach
    - Computational bottlenecks and open implementation issues
        - Tree construction
        - Design and implementation of translation operators
        - Simple software interfaces extensible to new techniques/hardware and accessible from familiar interpreted languages (python/matlab etc)

- Why did we try a Python FMM?
    - Fulfills many of the requirements we need for our infrastructure
    - large ecosystem of software for science
    - easy to deploy
    - easy to write and extend
    - JIT compiled approaches make it easy to extend to new hardware targets using LLVM infrastructure.

- Why did it not succeed?
    - Why JIT compiled approaches are not sufficient.
    - What alternatives are emerging (Mojo) and why these aren't necessarily a competitor to compiled languages.
    - What do we need from a language for our approach? And why is Rust a suitable alternative?

Chapter 2 - Rust as a tool for computational science ~ 2 pages
    - Its benefits and pitfalls.
        - Traits for bottom up design.
        - Memory safety, contrast with C++/C
        - Python/C interfaces
        - Cargo as a package manager/deployment tool.
        - Parallel programming safety via the borrow checker.
    - Comparison with major competitors
        - C/C++ and Fortran
        - Also JIT approaches, as well as MoJo's approach.

Chapter 3 - Open work streams ~5-10 pages

- Brief introduction to the FMM we use (KiFMM)
    - Why are the translation operators and tree construction the biggest bottlenecks and what past work has been done to optimise these pieces?
    - SVD based M2L
        - description of approach
        - computational optimisations (BLAS3, precomputation with randomised SVD, multithreading)
    - FFT based M2L
        - description of approach
        - computational optimisations (explicit SIMD, multithreading)
    - Contrast approaches in terms of complexity, as well as practical considerations
    - Identify a gap in the literature to directly compare the optimisation approaches on modern hardware.
        - propose this as upcoming paper.
    - Current benchmark performance of FFT vs SVD
        - how can this be further improved, and why is it not quite as good as the state of the art
            - runtime cache optimisations are not good enough
                - can demonstrate with experiment of saves
            - insufficiently good data structure used for storing data, it's too non-linear
            - FFT is done on array of structs, which is difficult to cache optimise
                - can we do fft on real and imaginary parts separately?
                - Then I still have to find downward check potential, hopefully this isn't too painful

            - I need to find exact numbers for the workload of each thread at the moment
                - how much memory is it touching? How many flops?
                - Then I can try and write down an algorithm such that the amount of memory handled
                in total doesn't exceed the capacity of a typical high performance processor, as well as
                handle generic processors.



    - High performance distributed trees
        - Our algorithmic approach and why its the most appropriate for our usecase
            - double global sort etc justified.
        - Design approach to easily extend single to multiple nodes.
        - Key shared traits and how these help.
    - some preliminary scaling experiments.
        - How many octants can I get scaling on a single node?
        - How many octants can I get on Kathleen?
    - Unimplemented innovations to improve trees and hyksort (communicator optimisations)
        - need to review the tree papers I was reading in vienna, and write down some potential optimisations.
            - yokota (2014?/16) talk a lot about the exact communication bottlenecks in parallel FMM.
            - how can we avoid these bottlenecks, beyond overlapping comm/comp,
                - M2L stage data exchange is the worst part.
                    - will need some discussion on how to take advantage of halos here, just a paragraph or so.
        - Sub communicators to improve strong scaling in M2M/L2L
        - Review p4est's optimisations as they are state of the art
            - suggest how we can incorporate/improve on these - how we differ (two global sorts etc.)

- Design of Rust based FMM on a single node
    - Builder pattern to construct an algorithm, agnostic of runtime
    - Brief discussion on how this would translate to a multinode setting via trait implementations.
    - Explain current status of project code.

- Conclusion ~1 page
    - Comparison study of M2L
    - Completion of distributed FMM
    - Longer term/ final project - incorporation of fast direct solvers into software framework.
