# Upgrade

Current body of work and background:

- Software tools to solve IEs that are accessible to  HPC experts and non-experts alike. Want to create malleable tools that can be compiled and deployed on anything/anywhere, and always achieve great performance. Tools are Tools!

- IEs, their formulation, and the generic discretisation to be solved (ind. of coll., Galerkin choice)

- FDS in context, contrast briefly with iterative solvers (briefly).

- Benefits of FDS, but also trade-offs. Problem setting of FDS.

- Previous investigations, and results - PyExaFMM, successes and failures - points per second metric. Python as a tool?

- Progression to Rust, Rust as a language, and the benefits and trade-offs

- Software products, Rusty-Tree, HykSort and adjoining paper - demonstrating the efficacy of Rust. Scaling experience on Archer 2.

Next steps:

- Maxwell Problems, and their CFIE formulation - ready for a FDS

- Flatiron work on Maxwell FDS based on proxy trick.

- Producing an RS-S implementation within our framework? Or simpler HODLR/HBS? How are they in practice?

- Testing out translation operator implementations. Comparison between cheb/analytic/least-squares. Which is best?

- Galerkin vs Nystrom for FDS?

