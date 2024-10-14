
For nearly all sparsity patterns of practical relevance, A-1 is a completely dense matrix


- HSS techniques for integral equtaions
    - E. Corona, P.-G. Martinsson, D. Zorin, An O.N/ direct solver for integral equations on the plane. Appl. Comput. Harmon. Anal. 38(2), 284–317 (2015)
    - A. Gillman, P.M. Young, P.G. Martinsson, A direct solver with O.N/ complexity for integral equations on one-dimensional domains. Front. Math. China 7(2), 217–247 (2012)
    - L. Greengard, D. Gueyffier, P.G. Martinsson, V. Rokhlin. Fast direct solvers for integral equations in complex three-dimensional domains. Acta Numer. 18, 243–275 (2009)
    - P.G. Martinsson, V. Rokhlin, A fast direct solver for boundary integral equations in two dimensions. J. Comput. Phys. 205(1), 1–23 (2005)

- Hierarchical low rank approximation + sparse direct factorisation
    - [2, 31, 54, 56, 69, 72]
    - A. Aminfar, E. Darve, A fast sparse solver for finite-element matrices. Preprint arXiv:1410.2697 (2014)
    - P. Ghysels, X.S. Li, F.-H. Rouet, S. Williams, A. Napov, An efficient multi-core implementa- tion of a novel HSS-structured multifrontal solver using randomized sampling. SIAM J. Sci. Comput. 38(5), S358–S384 (2016)
    - A. Napov, X.S. Li, An algebraic multifrontal preconditioner that exploits the low-rank property. Numer. Linear Algebra Appl. 23(1), 61–82 (2016)
    - H. Pouransari, P. Coulier, E. Darve, Fast hierarchical solvers for sparse matrices. Preprint arXiv:1510.07363 (2015)
    - S. Wang, X.S. Li, F. Rouet, J. Xia, M.V. de Hoop, A parallel geometric multifrontal solver using hierarchically semiseparable structure. ACM Trans. Math. Softw. 42(3), 21:1–21:21 (2016)
    - J. Xia, S. Chandrasekaran, M. Gu, X.S. Li, Fast algorithms for hierarchically semiseparable matrices. Numer. Linear Algebra Appl. 17(6), 953–976 (2010)

- Preconditioning with low rank schur complements and HSS
    - P. Gatto, J.S. Hesthaven, A preconditioner based on low-rank approximation of Schur complements. Technical Report, EPFL-MATHICSE-MCSS (2015)

- H Matrix based preconditioning for FE discretisation of Maxwell's equations
    - J. Ostrowski, M. Bebendorf, R. Hiptmair, and F. Krämer. H-matrix based operator precondi- tioning for full Maxwell at low frequencies. IEEE Trans. Magn. 46(8), 3193–3196 (2010)

– Matrix sign function iteration in H-matrix arithmetic for solving matrix Lya- punov and Riccati equations [4, 37];
    - 4. U. Baur, P. Benner, Factorized solution of Lyapunov equations based on hierarchical matrix arithmetic. Computing 78(3), 211–234 (2006)
    - L. Grasedyck, W. Hackbusch, B.N. Khoromskij, Solution of large scale algebraic matrix Riccati equations by use of hierarchical matrices. Computing 70(2), 121–165 (2003)

- Eigenvalue computation [12–14, 68];
    2. P. Benner, T. Mach, Computing all or some eigenvalues of symmetric H`-matrices. SIAM J. Sci. Comput. 34(1), A485–A496 (2012)
    13. P. Benner, T. Mach, The preconditioned inverse iteration for hierarchical matrices. Numer. Linear Algebra Appl. 20, 150–166 (2013)
    14. P. Benner, S. Börm, T. Mach, K. Reimer, Computing the eigenvalues of symmetric H2- matrices by slicing the spectrum. Comput. Visual. Sci. 16, 271–282 (2013)
    68. J. Vogel, J. Xia, S. Cauley, B. Venkataramanan, Superfast divide-and-conquer method and perturbation analysis for structured eigenvalue solutions. SIAM J. Sci. Comput. 38(3), A1358– A1382 (2016)

- Kernel approximation in machine learning [61, 70]
    61. S. Si, C.-J. Hsieh, I.S. Dhillon, Memory efficient kernel approximation, in Proceedings of the 31st International Conference on Machine Learning (ICML), pp. 701–709 (2014)
    R. Wang, R. Li, M.W. Mahoney, E. Darve, Structured block basis factorization for scalable kernel matrix evaluation. Preprint arXiv:1505.00398 (2015)

– Sparse covariance matrix estimation [1, 3] and Kalman filtering [50]
    - 1. S. Ambikasaran, D. Foreman-Mackey, L. Greengard, D.W. Hogg, M. O’Neil, Fast direct methods for Gaussian processes. IEEE Trans. Pattern Anal. Mach. Intell. 38(2), 252–265 (2016)
    - 3. J. Ballani, D. Kressner, Sparse inverse covariance estimation with hierarchical matrices. Technical Report, EPFL-MATHICSE-ANCHP, Oct (2014)
    - 50. J.Y. Li, S. Ambikasaran, E.F. Darve, P.K. Kitanidis, A Kalman filter powered by H2-matrices for quasi-continuous data assimilation problems. Water Resour. Res. 50, 3734–3749 (2014)

- Clustered low-rank approximation of graphs
    - 58. B. Savas, I.S. Dhillon, Clustered low rank approximation of graphs in information science applications, in SDM, pp. 164–175 (2011)

# Algorithms for low-rank approximation

- Choice depends on size of A, and how easy it is to access entries of matrix

- Small, easy entries - truncated SVD, can also be useful if A is given in a factorised form even when min(m, n) is large
- For large m, n (how large?) Randomised or Lanczos based methods are useful, provided matvecs A, AT are possible
- when entries are hard to compute/expensive, you use approaches where only a few are required - ACA.

## SVD

- Assuming m>=n, complexity is O(mn^2).
- (m+n)k storage, in prniciple can be reduced further to (m+n)k -k^2 + O(k), by storing Vk Uk in terms of k Householder reflectors ... but cumbersome, and little benefit for k << m, n
. However, care needs to be applied when interpreting small computed singular values. Performing a backward stable algorithms in double- precision arithmetic introduces a backward error E with ||E||_2 <= 10e-16 x C\sigma_1, so small singular values are corrupted by roundoff.

## Lanczos Based

- Algorithms that use Krylov subspaces of rank $K+1$ for extracting low-rank approximations of $A$.

$$
\mathcal{K}_{K+1}(AA^T, u_1) = \text{span }\{ u_1, AA^Tu_1, ..., (AA^T)^Ku_1\} \\
\mathcal{K}_{K+1}(A^TA, v_1) = \text{span }\{ u_1, A^TAv_1, ..., (A^TA)^Kv_1\}
$$

With a random starting vector u_1, $v_1 = A^T u_1/\|A^Tu_1\|_2$


- The bidiagonal Lanczos process (Algorithm 1), produces matrices U_K+1 V_K+1 such that their columns form orthonormal bases of the first/second Krylov subspaces respectively. The scalars alpha_j, beta_j generated by the GS process can be arranged in a bidiagonal matrix B_k, leading to a Lanczos decomposition

$$
A^TU_k = V_k B_k^T, \> \> AV_k = U_KB_K + \beta_{K+1}u_{K+1}e_K^T
$$


Use approximation

$$
T_k(A) \approx A_K := U_K T_k(B_K)V_K^T
$$

Algorithm 1 is based on subsequent matrix-vector multiplications, which perform poorly on a computer because of the need for fetching the whole matrix A from memory for each multiplication

One way to address this problem is to use a block Lanczos method [34]. The multiplication of A with a block of k vectors can be easily arranged such that A needs to be read only once from memory.

Alternative to block Lanczos method is just to use Randomised SVD

The bound (17) - of rSVD with oversampling improves significantly when performing a few steps of subspace iteration after Step 2 in Algorithm2, which requires a few additional block matrix-vector multiplications with AT and A.

## Adaptive Cross Approximation (ACA)

- construct a low-rank approximation of a matrix directly fom the information provided by well-chosen rows/columns of $A$.

- Introduced in 36. S.A. Goreinov, E.E. Tyrtyshnikov, N.L. Zamarashkin, A theory of pseudoskeleton approxima- tions. Linear Algebra Appl. 261, 1–21 (1997)

- Theorem, $A \in \mathbb{R}^{m \times m}$ there exist row and column indices r, c, and a matrix $S \in \mathbb{R}^{k \times k}$ s.t. |c| = |r| = k.

$$
\|A-A(:, c) S A(r,:)\|_2 \leq (1+2\sqrt{k}(\sqrt{m} + \sqrt{n}))\sigma_{k+1}(A)
$$

i.e. always possible to build a quasi optimal low-rank approximation of $A$ from its rows and columns.

- NP hard to chose c and r roptimally, even when the singular vectors are known.
- Randomised column/row selections have been shown to have good approximations provided A admits a low rank factorisation and some conditions., hard to know apriori if this does though

- Provide a simple greedy algorithm in algorithm 3.

- Since Algorithm 4 takes only partial information produce reliable low-rank approximations in certain cases
    - S. Börm, L. Grasedyck, Hybrid cross approximation of integral operators. Numer. Math. 101(2), 221–249 (2005

- None of the techniques will produce a satisfactory approximation if A cannot be represented by a low rank matrix in the first place, or alternatively, if the singular values don't decay sufficiently fast.

- simplest setting, of matrices associated with bivariate functions.


Suppose that

$$ f(x, y): X \times Y \rightarrow \mathbb{R}
$$

for $x \in X$ and $y \in Y$, and can be well approximated by a sum of separable functions

$$
f(x, y) = f_k(x, y) + \epsilon_k(x, y)
$$

^ Semi-separable approximation

where

$$
f_k(x, y) = g_1(x)h_1(y) + ... + g_k(x)h_k(y)
$$

and the error decays 'quickly' with increasing $k$.

In other words, a good approximation by a short sum of separable functions implies a good low-rank approximation


Many ways to get semi-separable approximation.

E.g. f(x, y) in x around x_0

$$
f_k(x, y) := \sum_{i=0}^{k=1} \frac{1}{i!}\frac{\partial^if(x_0, y)}{\partial x^i}(x-x_0)^i
$$

Immediately gives a semi-separable function

Can show that singular values for 2D laplace kernel decay expontentially as long as admissibility condition holds, using Taylor expansion.

Can also use Lagrange (or Other polynomial) interpolation to obtain a semi-separable approxmation.

- show an exponential decay in error for an analytic function, and the altered admissibility condition.

# Partitioned Low Rank Structures

- I like the phrasing, H matrices seen as case where only certain blocks admit low-rank factorisations, the selection of these blocks is driven by admissibility criteria.

## HODLR

- Remember, multilevel, all off-diagonals are considered low-rank - weak admissibility.

- Assume n = 2^p n_p , p = depth and A of n \times n in size, simplicity, wlog. n_p >= 1.

- Each off-diagonal block at level l is assumed to have at most rank k and kept in a low rank representation

$$
A(I_i^l, I_j^l) = U_i^l (V_j^l)^T
$$

U_i^l \in R^{n_l \times k}

n_l := #I_i^l = #I_j^l = 2^{p-l}n_p

- Short arg shows that the HODLR storage complexity is O(kn \log{n})

- Short arg based on master theorm shows O(kn log_2(n)) complexity for matvec.


In many applications, the particular block partitioning of HODLR matrices is not appropriate and leads either to a poor approximation or to large ranks. Obtaining a block partitioning that is adapted to the situation at hand is by no means trivial and referred to as clustering.

- First step is ordering the index set

- Second step, recursively subdividing the blocks of the re-ordered matrix A.

Goals:

- the ranks of all blocks should be small relative to n
- the total number of blocks should be small.

Often driven by some notion of locality between the indices. Could be induced by the geometry of the underlying problem, or by the incidence graphf of $A$ if it sparse.

Gives an example of a 1D integral opeartor with log kernel, galerkin, piecewise constant basis functions over interval. Apply a semiseparable approximation. Come up with hierarchical format, except now U list interactions are also dense. strong admissibility demonstrated.

If A is sparse, can use graph partitioning strategies to cmompute clustering.

- so geometric clustering still required if applying techniques to IE.

## H-matrices

- generalisation of HODLR matrices, block structure need not be from a binary tree over index set.

# Nested Low Rank Representations

## HSS Matrices

In the HODLR format, each off-diagonal block is expressed independently by a low-rank representation. in HSS, the low-rank representations on each level are nested and depend upon one another in a hierarchical way.

- Leads to O(kn) estimate for complexity of storage, and matvec.

- weakly admissible, as all off-diagonals considered low-rank.

## H2 matrices

- generalisation of HSS matrices. Special case of H matrices.

However, the implementation of approximate algebraic operations such as matrix-matrix additions and multiplications in theH2- matrix format is significantly more difficult than for HODLR

Note that this also makes the computation of approximate factorizations and an approximate inverse in the H2- matrix format more involved,
