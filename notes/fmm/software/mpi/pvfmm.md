A few different papers, there's the Comm. Com. Phys. One

PVFMM: A parallel kernel independent FMM for particle and volume potentials

- Low frequency helmholtz (<20) is what they claim to support.

- The method uses piecewise Chebyshev polynomials on an adaptive octree to represent the continuous source distribution and also the final potential. Our

- earliest distributed memory algorithms described by Warren and Salmon
    - Michael S Warren and John K Salmon. Astrophysical n-body simulations using hierarchical tree data structures. In Proceedings ofthe 1992 ACM/IEEE Conference on Supercomputing, pages 570–576. IEEE Computer Society Press, 1992
    - Michael S Warren and John K Salmon. A parallel hashed oct-tree n-body algorithm. In Proceedings ofthe 1993 ACM/IEEE conference on Supercomputing, pages 12–21. ACM, 1993.

- Backward stable pseudo-inverse
    - This is important as it's used by me, as well as exafmm.

    - when computing the multipole expansion from the check potential, the linear system is solved by computing the pseudo inverse - i.e. computing the SVD, inverting the diagonal matrix + regularisation, multiplying factors together.
    - this matrix is ill-conditioned - large dynamic range in singluar values.
    - lose precision in finite arithmetic, when computing equivalent density.
        - original FMM they could only achieve around 9 digits in double precision.
    - Two sources of error when computing equivalent density
        - round-off in the check potential, gets amplified by a factor equal to the condition number of matrix inv.
        - the second source is from multiplying the factors of the pseudo inverse together, due to large dynamic range in singular values.
        - first error damped by a similar factor when computing the potential from a check potential.
        - second one handled by storing the pseudo inverse in component form, can multiply the diagonal matrix by one of the two orthonormal matrices.


- Tree construction.
    - discretise a continuous source distribution $f$ using a piecewise polynomial representation.
    - Discretise the domain using an octree and Chebshev polynomials at each leaf node, can evaluate $f$ at a given 3D point as,

    $$
    \hat{f}(x_1, x_2, x_3) = \sum_{i,j,k\geq 0}^{i+j+k \leq q} \alpha_{i, j,k} T_i(x_1)T_j(x_2)T_k(x_3)
    $$

    where $\alpha$ are the Chebyshev coefficients for the $T_i$ Chebsyev polynomials of degree $i$.
    - Use truncation error wrt to polynomials to figure out how deep to make the tree.
    - The final potential is also presented using piecewise chebyshev polynomials by first evaluating the potential at the nodes in each leaf, and then computing the coefficients, can be used to interpolate.

- Newton step etc, for kernel.
- For helmholtz use Intel SVML library for trig functions
- M2L approach measured to achieve over 50% of theoretical peak performance, which is very decent.
- For volume FMM use tasking parallelism between near interactions on co-processor and far interactions on CPU.

- condition number for unitary matrix of being 1 comes from the fact that it's norm preserving.

- Communication scheme for Ghost octants, hypercube all-reduce .
- Scales as

$$
O((N/p)^{2/3} \log{p})
$$

For $p$ processors and $N$ unknowns.

I need a similar estimate for my own communication scheme. Can come from insulation layer size for each local tree, defined by root.

- Show Helmholtz results with wavenumber 10, mention that a larger multipole order should only be used at the coarsest levels of the tree, but it's not supported in their implementation.

- Note non-scale invariance of Helmholtz kernels results in more memory usage, could be something I'm asked about and should add to benchmarks.

- I have no idea how they get to such deep trees. Almost all of the boxes at this point must be empty. There's no other way

- async, use task parallelism for putting U list on co-processors.

- Use the Lashuk et. al communication pattern

- 'perfect scalability' for strong scaling
    - i.e. wall time x number of cores is a constant

Remember parallel efficiency - optimal is a constant (1)

$$
\epsilon = \frac{T_1}{P T_p}
$$

Speedup - optimal is linear

$$
S = P \epsilon
$$

