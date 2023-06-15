# Upgrade

Story: Modern software approaches for IEs (~30 pages at most)

Context 
- Modern software stacks enable cross platform/architecture development with high-performance.
    - Small teams can now innovate over large code-bases, and build codes that can scale from laptops to supercomputing clusters.
        - Give context of team size at UCL in comparison to other large scale FMM codes (PVFMM, ExaFMM and number of iterations etc)
    - The impact of software comes from its generality and hackability
        - Can I implement new algorithms? Can I write code on my laptop, and easily run a much larger simulation on a supercomputer. Can I do most of the work in a language I'm already familiar with (python/matlab) ?
    - IEs specialised field, complex for non-experts (math) to use something that isn't a black box. Similarly, complex for non-experts (eng/cs) to parse the theoretical aspects. Software for this application needs to be easy to use for both sets of researchers, easy to deploy, and easy to maintain by a small team.

- The goal of this thesis is to bring these tools to the world of integral equation solvers.
- Impact:
    - A highly impactful and widely used unified library for `fast solvers' for IEs - for our purposes the optimal application and inversion of the dense matrices that arise in the discretisation of these problems, with a goal of us being the standard library for these algorithms.
    - Experimentation and innovation with new algorithmic approaches. New scientific investigations.
    - High performance without too much strain on non-software oriented researchers.
    - Re-use of common data structures (trees) for forward/inverse application.
    - A definitive comparison of the merits of different algorithmic approaches - still unclear as of 2023 - as each implementation is often heavily optimised.

- Overview of project goals, and what's reasonable to achieve in remaining PhD time:
        - Distributed FMM library
            - highly optimised translation operators + data exchange via tree implementation.
        - Begin looking into FDS.
        - All accessible from Python.
        - Designed to be future ready, can extend to target heterogenous hardware and software targets with our library in rapidly evolving landscape.

Chapter 1 - A Python FMM.
- Brief introduction to the FMM we use (KiFMM)
    - how it works approximately, and the logic behind it - maybe put the actual algorithm in the appendix.
    - where this algorithm appears in BEM problems, without formulating them.
    - How we approximte the translation operators explicitly with this algorithm.
    - the bottlenecks in the algorithm from computational perspective (tree construction, m2l translation, data exchange)
    - Open implementation issues
        - pluggable translation operators
        - optimal tree data exchange.
        - distributed library that works from python and is easy to deploy.

- Python + Numba / Julia
    - First idea, can we write such algs in Python alone?
    - Experience developing a Python FMM and why this isn't a suitable step forward.
    - Redacted summary of the python paper.
    - emerging tools, and why it's not entirely sufficient for such algorithms. 
         - e.g. Mojo - languages designed for a variety of hardware settings, easy integration to Python, why this shouldn't necessarily trouble us.

Chapter 2 - Rust as a tool for computational science.
    - Its benefits and pitfalls.
        - Traits for bottom up design.
        - Memory safety, contrast with C++/C
        - Python interfaces.
        - Cargo as a package manager/deployment tool.
    - Emerging trends

Chapter 3 - Open work streams

- High performance distributed trees
    - some scaling experiments.
    - Unimplemented innovations to improve trees and hyksort (communicator optimisations)
        - need to contact Rio about this soon as I've forgotten what he said.

- Rust based FMM on a single node
    - Brief discussion on how this would translate to a multinode setting via trait implementations.
    - What kind of problems can we expect to be able to study (tree size). What kind of performance  can we expect to achieve based on the preliminary results ?

- Multipole to local translation operators.
    - E.g. traits for translation operators
        - how these could be re-implemented relatively easily for heterogenous compute kernels.
    - FFT vs SVD approaches
    - brief discussion on these two contrasting approaches (keep as wordy as possible)
        - Need to review SVD and FFT thoroughly before exam.
    - hardware/math optimisations for both approaches briefly spelled out.
    - want to write up as a comparison study - gap in literature.

- Future outlook
    - Comparison study of M2L
    - Completion of distributed FMM
    - Longer term/ final project - incorporation of FDS.
