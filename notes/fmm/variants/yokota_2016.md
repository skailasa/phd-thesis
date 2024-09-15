FMM as a Matrix Free Hierarchical Low Rank Approximation

- One of the few papers that explicitly characterise the trade-offs between analytical and algebraic methods.

- FMM applications can be broadly classified in solving elliptic PDE and kernel summation.

- Integral form of elliptic PDE can be further categorised into
    - BIE for homogenous problems.
    - Discrete volume integrals and continuous volume integrals.


- "elliptic PDE that represent a state of equilibrium, many iterations with global inner products for their solutions, dense matrices in boundary integral equations, and all to all interactions in N body problems and kernel summations with global support are all manifestations of the same source of global data dependency.

- For methods which require uniform resolution the FFT is often the method of choice

- FMM has an advantage when non-uniform resulotion is required.

- Claim that FMM has better communication, reduced synchronisation, and higher arithmetic intensity compared to multigrid and FFT.

- HSS - nested basis, off diagonals considered low rank, weak admissability
- HODLR like HSS but without nested basis

- H doesn't have a nested baseis, H2 does, both have strong admissability
- FMM is a H2 matrix type, but subdivide geometric domain using a 2^d tree in d dimensions.
    - H2 not restricted to this

- 'semi analytic' i.e. basically uses some results from analysis to locate charge points, but essentially equivalent to H2 approach.

- Claim that purely algebraic methods precompute a compressed representation of the entire matrix, which results in mor estorage and data movement than a purely analytic FMM.

- Original tree code J. Barnes and P. Hut. O(NlogN) force-calculation algorithm. Nature, 324:446–449, 1986.

- Panel clustering original reference W. Hackbusch and Z. P. Nowak. On the fast matrix multiplication in the boundary element method by panel clustering. Numerische Mathematik, 54:463–491, 1989. - O(N log N), i.e. probably doesn't re-use basis.

- These analaytical methods only do useful flops - not brute force.

- Software example is Bonsai, performance also comes from DS optimisations e.g. hardcoded quadropoles only, and assumption that all charges are positive. Cannot be transferred to applications iwth higher accuracy, preconditioner though.
    - https://ui.adsabs.harvard.edu/abs/2012ascl.soft12001B/abstract#:~:text=Bonsai%20is%20a%20gravitational%20N,2.8M%20particles%20per%20second.
    - 2.6 M particles/s
    - J. B´edorf, E. Gaburov, M. S. Fujii, K. Nitadori, T. Ishiyama, and S. Portegies Zwart. 24.77 Pflops on a gravitational tree-code to simulate the milky way galaxy with 18600 GPUs. In Proceedings of the 2014 ACM/IEEE International Conference for High Performance Com- puting, Networking, Storage and Analysis, pages 1–12, 2014.
    - can also use as a preconditioner


Fast Translation Operators

Analytic options:

- Rotation of Spherical Harmonics
    C. A. White and M. Head-Gordon. Rotating around the quartic angular momentum barrier in fast multipole method calculations. The Journal of Chemical Physics, 105(12):5061–5067, 1996
    - Get from O(P^4) to O(P^3), by rotating the expansions such that the translation is always along the quantisation/Z axis.
    - requires minimal modifications to original algorithm
    - retains the original error bounds


- Block FFT
    https://epubs.siam.org/doi/pdf/10.1137/S1064827594264259
    - FAST FOURIER TRANSFORM ACCELERATED FAST MULTIPOLE ALGORITHM*
    - interpret M2L as a convolution type operation to which the FFT can be applied.


- Planewaves
    L. Greengard and V. Rokhlin. A new version of the fast multipole method for the Laplace equation in three dimensions. Acta Numerica, 6:229–269, 1997
    - diagonal form of the translation operators

Reducing number of translations
    - level skip M2L
    Y. Wang, Q. Wang, X. Deng, Z. Xia, J. Yan, and H. Xu. Graphics processing unit (GPU) accelerated fast multipole BEM with level-skip M2L for 3D elasticity problems. Advances in Engineering Software, 82:105–118, 2015
    - Detailed explanation of Gumerov work on GPU
        - i.e. for properly separated interaction list boxes, can perform M2L wrt to a box's parent rather than a box itself. This reduces the nunumber of M2L to be handled by each box.
        - preserves the error bound
    - 8,4,2 box method
    D. R. Wilkes and A. J. Duncan. A low frequency elastodynamic fast multipole boundary element method in three dimensions. Computational Mechanics, 56:829–848, 2015.
    - well separated boxes are common to multiple siblings.
    - can apply to a common point at the cenre of siblings, can then be translated to each sibling.
    - similar techniques apply for siblings at edges (2) and faces (4).
    - has an effect on the error.


- Methods that use dual tree traversal alongside multipole acceptance criterion for constructing optimal interaction lists, which automates the process - but still same number of calculations?
    - W. Dehnen. A hierarchical O(N) force calculation algorithm. Journal of Computational Physics, 179(1):27–42, 2002.

- Variable expansion order/optimal parameter FMM
    - smaller expansion orders for distant boxes in interaction list
    - equivalent to using SVD for compression of these interactions.
    H. G. Petersen, D. Soelvason, J. W. Perram, and E. R. Smith. The very fast multipole method. The Journal ofChemical Physics, 101(10):8870–8876, 1994

    - First reference to SVD compression
    Z. Gimbutas and V. Rokhlin. A generalized fast multipole method for nonoscillatory kernels. SIAM Journal on Scientific Computing, 24(3):796–817, 2002
    - reference to BLAS used in Fortin paper

- The mtarices of compressed translation operators precisely correspond to off-diagonal blocks of H2/HSS after compression

- Off-diag blocks with same relative positioning are identical, however for those generated from regular structure mesh such as in FMM for continuous volumen integral equations, even diagonal blocks are identical.
    - leads to O(1) storage at every level in the hierarcy, so total storage cost is log(N).

    - Using redundant blocks for cache like us
        - T. Takahashi, C. Cecka,W. Fong, and E. Darve. Optimizing the multipole-to-local operator in the fast multipole method for graphical processing units. International Journal for Numerical Methods in Engineering, 89:105–133, 2012.
        - E. Darve, C. Cecka, and T. Takahashi. The fast multipole method on parallel clusters, multi- core processors, and graphics processing units. Comptes Rendus Mecanique, 339:185–193, 2011.
        - O. Coulaud, P. Fortin, and J. Roman. High performance BLAS formulation of the multipole- to-local operator in the fast multipole method. Journal ofComputational Physics, 227:1836– 1862, 2008.

- One can think of the FMM as an analytical form of generating the small matrices in the off-diagonals without relying on low-rank compresion schemes.
    - i.e. precomputation time is minimal for the analytical FMM, however in practice might still result in slower computation due to reliance on special functions.


Semi-analytical methods

- Early kifmm referencews
    - C. R. Anderson. An implementation of the fast multipole method without multipoles. SIAM Journal on Scientific and Statistical Computing, 13(4):923–947, 1992.
    - C. L. Berman. Grid-multipole calculations. SIAM Journal on Scientific Computing, 16(5):1082–1091, 1995
    - J. Makino. Yet another fast multipole method without multipoles – Pseudoparticle multipole method. Journal ofComputational Physics, 151(2):910–920, 1999

    - early Chebyshev approach
        A. Dutt, M. Gu, and V. Rokhlin. Fast algorithms for polynomial interpolation, integration, and differntiation. SIAM Journal on Numerical Analysis, 33(5):1689–1711, 1996


Algebraic low-rank approximation

- H, usually use strong admissability, and no nested basis
- analytic counterpart is a typical treecode

- H2 matrices are also hierarchical, but use a nested basis, and strong adm.
    - counterpart is an FMM

- TODO: Need to understand why nested basis reduces complexity, can probably find in Boerm book

- SVD is most naive and expensive way to calculate low-rank
- Can also use QR and LU - equivalent - Martinsson book
    - by using appropriate pivoting strategy.
- Also other methods like Adaptive Cross Approximation and ID
    - Need to look up both as notes from Martinsson book.
- Obviously we use randomised methods

