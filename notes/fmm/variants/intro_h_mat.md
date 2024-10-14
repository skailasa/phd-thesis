Introduction to hierarchical matrices with applications

- The essential operations of matrices, matvec, matmul, addition and inversion up to logarithmic factors performed in optimal complexity.

Two observations

- Integral operators can be efficiently treated by using separble expansions of the corresponding kernel function
- The inverse of an elliptic PDE operator can be cast as integral operator by using the Green's function as as Schwartz kernel.

$$
\mathcal{L}[u] = \int_\Omega g(x, y) u(y) dy
$$

$\Omega \subset \mathbb{R}^d$, may be able to approximate integral operator with wavelet bases.

H matrices based on the fact that for typical kernel functions singularities only occur on the diagonal and the function is smooth everywhere else. Introduce notion of asymptotic smoothness.

$C_{as1}, C_{as2} \in \mathbb{R}_{>0}$ st.

$$
|\partial_x^\alpha \partial_y^\beta g(x, y)| \leq C_{as1} (C_{as2} \|x-y\|)^{-|\alpha| - |\beta|}\alpha + \beta|g(x, y)|
$$

For alll multi-indices alpha beta positive natural numbers.

The idea of panel-clustering method
    - Hackbusch W, Nowak ZP. On the fast matrix multiplication in the boundary element method by panel clustering. Numerische Mathe- matik 1989;54:463–91
    - precursor to H Matrix, published at a similar time to original FMM work

- If we fix $x \in \Omega$ and a subset $\omega \subset \Omega$ satisfies $$dist(x, \omega) := \inf{\{\|x-y\|: y \in \omega\}} \geq C diam(\omega)$$

- i.e. we're some distance away such that we can be considered well separated from the region $\omega$.
- we can replace the kernel function with a degenerate approximation, e.g. a truncated taylor series at a point $y_0 \in \omega$

$$
\tilde{g}(x, y) = \sum_{v = 1}^k p_v^x q_v(y)
$$

$$
\tilde{g}(x, y) = \sum_{v=0}^\infty \frac{1}{v!} \frac{\partial^v}{\partial y^v} g(x, y_0)(y-y_0)^v
$$

In a collocation scheme, and truncate the sum, this is a low-rank approximation of part of the row corresponding to collocation point $x$. (part of the row i.e. all the sources in $\omega$ - which are the columns). The coefficients of this series will be seen to allow for efficient approximations of blocks of the matrix, ie. can apply to multiple neighbouring rows - leads to H matrix methods.

The principal difference between these methods is choosing different degenerate approximations, leading to multipole, H or H2 matrices.

- H matrices require a discrete subspace, together with finite/boundary element bases $(\phi_i)_{i \in I}$

$$
L_{ij} = \langle \phi_i, \mathcal{L}\phi_j \rangle_{L^2}
$$



- Cluster tree, always forget definition
- Each node is a subset of the index set
- the index set is the root of the tree
- if a node is a leaf it contains fewer than a fixed constant amount of indices
- if it's not a leaf, then it has two children and their union is disjoint.
- don't need to use binary trees.

- The support of a cluster $\tau \in T_I$ is given by the union of the supports of the basis functions corresponding to its elements. i.e.

$$
\Omega_\tau := \cup_{i \in \tau} \Omega_i
$$

where $\Omega_i := \text{supp }{\phi_i}$ for all i in Index set

- A simple way to build a cluster tree is geomteric based bisection based on input points.

- Admissibility, assuming asymptotically smooth kernels can define a general one of the form

$$
\min\{diam(\Omega_\tau), diam(\Omega_\sigma)\} \leq \eta dist(\Omega_\tau, \Omega_\sigma)
$$

eta is a positive real number that controls the trade-off between number of blocks considered admissable, i.e. between quality approximation and complexity.

- This condition is replaced in practice using supersets of index sets for each cluster of indices



- Cluster tree used to define a block tree by forming pairs of clusters recursively. Root is cross product of index set, blocks are cross products of source/target indices.
- log linear to construct, c.f. linear for linear octree construction.

- Rk matrices, a straightforward representation of low-rank (k-rank) matrices correspond to $\tau \times \sigma \subset I \times I$, low rank subblocks of H matrix

$$
R = AB^T \> \> A \in \mathbb{R}^{\tau \times k}, B \in \mathbb{R}^{\sigma \times k}
$$

require only O(k(n+m)) storage

- Demonstrate the usage of a polynomial interpolation scheme based on Lagrange polynomials to approximate the kernel function by its interpolant for low-rank blocks, show exponential convergence with this scheme - with no reference to specifics of kernel, except of course basic assumption on it being degenerate and asymptotic smoothness.

- Instead of analytically derived interpolation scheme, can use purely numerical scheme for low-rank approximation
- e.g. best appx wrt spectral and frobenius norm is truncated SVD

## H matrices

- Based on cluster tree and block tree, define H matrix.

- $L \in \mathbb{R}^{I \times I}$ a matrix and $T_{I \times I}$ a block tree consisting of admissible and non-admissible leaves. $L$ is an H matrix of blockwise rank $k$ if for all admissible leaves the rank of the corresponding block is <= k.

- storage complexity k_b - rank o fa given block

$$
\text{stor }_{H} = \sum_{b = s \times t \in P^+} k_b (\#s + \#t) + \sum_{b = s \times t \in P^-} \#s\#t
$$

If we assume all non-admissible blocks in P- are subject to a constraint $\min\{\#s, \#t\} \leq n_{min}$ n_min is a minimal cluster size we find that $\#s\#t \leq n_{min}(\#s + \#t)$, which gives us a bound for storage


$$
\text{stor }_{H} \leq \max\{ n_{min}, k\} \sum_{s \times t \in P} (\#s + \#t)
$$

We need to estimate the number of blocks in the partition $P$, and weigh them according to their size.

For each $s$ the number of blocks with column index $s$ is $\#\{t \in T_i : s \times t \in P\}$, can find similar for row index $t$. The max over these two is called the sparsity constant $C_{sp}$ of $P$.

For each $s$ the term $\#s$ can only appear at most $C_{sp}$ times in a sum over all the blocks

$$
\sum_{s \times t \in P} \# s \leq C_{sp}(P) \sum_{s \in T_I} \# s
$$

On all levels of the tree $T_I$ the index set $s \subset I$ appears at most once, therefore

$$
\sum_{s \in T_I} \#s \leq \#I (1 + depth(T_I))
$$

Assuming n_min <= k

$$
\text{stor }_{H} \leq 2 C_{sp}(P)k \# I (1 + depth(T_I)) = C_{sp}(P)k n (1 + depth(T_I))
$$

For a bounded C_sp, and using the fact that the depth is proportional to log(n)

$$
\text{stor }_H \in O(kn \log{n})
$$

Also reflects matvec cost.


- Note on inversion, the inverse of a 2x2 block matrix can be computed using the Schur complement if PD matrix.

##  Uniform H matrices

- source/target regions are of similar sizes, a subset of H matrices, allow us to improve matvec complexity slightly - though of same order.

- If support of source/target regions are of similar size, interpolate kernel function in both variables.

$$
\tilde{g}(x, y) := \sum_{i=1}^{k_\tau}\sum_{k = 1}^{k_\sigma} g(x_i^\tau, x_k^\sigma) p_i^\tau(x)p_k^\sigma(y)
$$

Now admissibility goes to,

$$
\max \{ \text{diam}(\Omega_\tau), \text{diam}(\Omega_\sigma) \} \leq \eta \text{dist}(\Omega_\tau, \Omega_\sigma)
$$

Our new Galerkin / stiffness matrix elements go to,

$$
L_{ij} = \sum_{i=1}^{k_\tau}\sum_{k = 1}^{k_\sigma}  g(x_i^\tau, x_k^\sigma) \int_\Omega p_i^\tau(x) \phi_i(x) dx \int_\Omega p_k^\sigma (y) \phi_j(y) dy
$$

Can re-write in another form,

$$
L|_{\tau \times \sigma} = V_\tau S_{\tau, \sigma} V^T_\sigma
$$

The interaction between bases is specified by S which is small relative to the block

- A cluster basis.
    - Let $k = (k_\tau)_{\tau \in T_I} \in \mathbb{N}^{T_I}$. A family of matrices $V = (V_\tau)_{\tau \in T_I}$ where $V_\tau \in \mathbb{R}^{\tau \times k_\tau}$ is called a cluster basis with respect to the rank distribution $k$.

- Denote a set of all columns in a row corresponding to $\tau \in T_I$ by $$R_\tau := \{ \sigma \in T_I : \tau \times \sigma \in L_{I \times I} \} $$


$$
y_i = (Lx)_i = \sum_{i \in \tau} V_\tau  \left ( \sum_{\sigma \in R_\tau} S_{\tau \times \sigma} V_\sigma^T x|_\sigma \right  )_i
$$

- Cluster basis is a subspace of the H matrix

Three step procedure, above equivalent to computing potential at one target point in the target cluster.

The pre-post multiplying into the cluster basis is O(nlogn), but the internal multiplication with small matrix is O(n), i.e. diagonal in this basis. Main benefit of uniform H matrices is a reduction in the storage requirement.

In order to overcome the complexity and get the optimal O(n) scaling we want, have to find a way of improving the forward/backward transformation.

Consider polynomial interpolative basis with constant approximation order where

$$
\text{span} \{ p_i^{\tau_1} : i \in \{ 1,...,k_{\tau_1} \} \} = \text{span} \{ p_i^{\tau_2} : i \in \{ 1,...,k_{\tau_2} \} \}
$$

holds for all $\tau_1, \tau_2 \in T_I$ i.e. each polynomial corresponding to a cluster can be expressed in the polynomial basis of any other cluster (as the approximation order is constant).

- Give a specific example of lagrange polynomial basis, and how a transfer matrix can be constructed, such that the cluster bases only have to be stored for leaf boxes.


The name H2 matrix is motivated by the fact that for these matrices, there are two hierarchies involved. The first the hierarchy of clusters like H matrices, and then the hierarchy of cluster bases.

- The focus on storage requirements a little dated, really focus should be on memory transfers.

- Nested cluster basis $B = (B_{\tau', \tau})_{\tau \in T_l, \tau' \in S(\tau)}$ transfer matrices
- satisfying $V_\tau| _{\tau' \times k_\tau} = V_{\tau'} B_{\tau', \tau}$
- tau' is son of tau

- The fast forward/backward procedures they show in the paper are essentially the upward/downward passes.
- Recursive steps each touch a box just once, k_tau times k_tau' operations so can bound with n times k_0 i.e. absorb tree depth into constant as well as k_tau'.
- The M2L (coupling step) still requires same amount of work, giving overall

$$
O(nk_0)
$$

complexity for matvec

$k_0$ essentially a bound on the largest rank, can be improved.

- can have variable order approximations as clusters become larger. Requires additional assumption on kernel function

- Use Singular Value Decomposition.

- Set up a fairly complex recursive scheme to solve for the row and column cluster bases based on orthoogonal diagonalisation QDQ^T = G recursively, computed using QR in practice - so fairly expensive cubic