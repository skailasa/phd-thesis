- Algorithm 967: A Distributed-Memory Fast Multipole Method for Volume Potentials

- TOMS paper

- PVFMM presented for Helmoholtz, Stokes and Poisson.

$$
u(x) = \int_\Omega K(x-y) f(y)
$$

- Volume fast multipole method [Ethridge and Greengard, 2001]. [3D extension, Langston 2011].
    - Represent source density using a non-uniform octree and chebyshev polynomials in each octant.
    - The near-interactions $\int_{\mathcal{N(x)}} K(x-y) f(y)dy$ require computing near/near-singular integrals.
    - They handle this with pre-computed tables.


Several applications require solutions of linear constant-coefficient elliptic PDEs

- TODO: Learn more about non constant coefficient PDE, and whether FMM can apply here.

E.g. Poisson,

$$
-\nabla u(x) = f(x) \implies u(x) = \frac{1}{4\pi} \int_\Omega \frac{1}{\|x-y\|} f(y) dy
$$

for free-space (infinite domain) conditions with $f(x) = 0$ for $x \notin \Omega$

Vector valued problems like Stokes,

$$
\begin{aligned}
-\nabla u(x) + \Delta p(x) = f(x), \> \text{div } u(x) = 0 \implies \\
u(x) = \frac{1}{8\pi}\int_{\Omega}(\frac{1}{\|x-y\|} + \frac{(x-y)(x-y)^T}{\|x-y\|^3})f(y)dy
\end{aligned}
$$

And scattering problems described Helmholtz,

$$
-k^2 u(x) - \Delta u(x) = f(x), \implies u(x) = \frac{1}{4\pi} \int_\Omega \frac{e^{-ik\|x-y\|}}{\|x-y\|}f(y) dy
$$


- PVFMM: four main algorithmic goals, high-order approximations, linear work, single node and parallel scalability.

- TODO: Ying 2006 paper

- TODO: SUndar multigrid reference, and hybrid domain decomposotion Lottese and Fischer 2005

- Two important features of modern solvers
    - Support for non-uniform discretisations
    - high order accuracy

References to other scalable FMM:

- TODO: Hamada 2009 T. Hamada, T. Narumi, R. Yokota, K. Yasuoka, K. Nitadori, andM. Taiji. 2009. 42 TFlops hierarchical N-body simulations on GPUs with applications in both astrophysics and turbulence. In Proceedings ofSC09 (The SCxy Conference series). ACM/IEEE, Portland, OR.
ACM
- TODO: Pritish Jetley, LukaszWesolowski, Filippo Gioachin, Laxmikant V. Kal´e, and ThomasR. Quinn. 2010. Scaling hierarchical N-body simulations on GPU clusters. In Proceedings ofthe 2010 ACM/IEEE International Conference forHigh Performance Computing, Networking, Storage and Analysis. IEEEComputer Society, 1–11.
A.
- TODO: Qi Hu, Nail A. Gumerov, and Ramani Duraiswami. 2011. Scalable fast multipole methods on distributed heterogeneous architectures. In Proceedings of 2011 International Conference for High Performance Computing, Networking, Storage and Analysis. ACM, 36.
Tobin

- TODO: Langston 2011 volumne fast multipole method

Tree construction

- Approximate density at each leaf using degree $q$ Chebshev polynomials, refining based on error of approximation for a fixed $q$ - no wonder he might need extra deep trees.

$$
\hat{f}(x_1, x_2, x_3) = \sum_{i, j, k \geq 0}^{i+j+k \leq q} \alpha_{i, j, k}^\mathcal{B}T_i(x_1)T_j(x_2)T_k(x_3)
$$

The leaf is $\mathcal{B}$

$u \in H^1$ smoother than $f(x) \in L^2$, therefore justify that potential can be represented accurately using the same octree refinement used for the density.

They need to handle the singular/near singular integrals over the leaf octants. The potential within a leaf octant given by,

$$
u(x) = \int_{y \in \mathcal{B}} K(x-y)\hat{f}(y)dy = \sum_{i, j, k} \alpha_{i, j, k}^\mathcal{B} \left [ \int_{y \in \mathcal{B}} K(x-y) T_{i, j, k}(y)\right]
$$

Precompute the integrals in the bracketed term as a part of setup. P2L P2P and P2M can can be represented as matvecs.

e.g. for P2P evaluate at chebyshev nodes inside target box.

- Also use grid search to tune accuracy

- Have an explicit bound for accuracy of solution and expansion order, but it's approximate.

- Perform a series of permutations for W and X list and near field matvecs to reduce to BLAS3 and U List
    - this is one area they get really high P2P performance

- It's odd that they talk about their Hadamard product as a matrix vector product?
    - it's still a hadamard product

- TODO: Use warren and salmon reference as origin of Morton IDs even in my own write up.


- Multipole reduce, each process identifies the list of octants it shares with other processes.
- These are the ancestors of the first/last leaf octants on the local octree, this makes sense for linear octrees.
- The communicates the relationship between all processsors and identifies with whom they communicate for ghost data.











