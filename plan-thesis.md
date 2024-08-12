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

Chapter 1: Modern programming environments for science (~10 pages)
- Introduce software problem setting
- First paper and trade-offs made
- New section:
    - trends in computer hardware, flops/bytes, communication issues at the exascale.
        - how does this additionally factor into software design?

Chapter 2: Designing software for the fast multipole method

Problem setting (~40 pages?)
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

- Software issues that arise
    - 3. Designing for single and multinode, low and high freq, all with the same interface.
    - 4. Want to be able to test new hardwares, and new algorithmic approaches, with same infrastructure.
    - JOSS/Software X paper on software design.

- New Section: A performance model for the FMM + HF FMM
    - Need a theoretical performance model for this kind of FMM, like chandramowlishwaram.
    - Can use this to contrast and compare with achieved performance.
    - Is this type of software going to survive in the exascale era? If not what needs to be done?
        - How close are we?
        - What evidence is there that our software is scalable?

Solutions (~20 pages?)
- Code generation via Rust can test multiple machines, and emerging architectures
- Flexible trait based design of interfaces built for extension
    - single interface for all of these problem settings
- Designing kernels to suit hardware, e.g. BLAS based kernels for M2L

Chapter 3: Experiments, Conclusions (~10 pages)
- Scaling experiments
- Single Node (Low/High frequency)
- Multinode (Low/High Frequency)

- Is our software fit for current and emerging architectures in light of benchmark experiments?

- What kind of problems are we going to be able to attack?

- What remains to be studied?
    - Are communication patterns in the multinode case not sufficient?
    - what can be re-purposed for fast direct solvers?
    - how to make designs flexible for HF problems?

- Is the software platform ready for extension to fast direct solvers?
