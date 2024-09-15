Matrices with hierarchical low-rank structures
- Ballani, Kressner

If nxn matrix is data-sparse can be represented with much less than n^2 parameres wrt to a certain frmat

- Shermann-Morisson formula
    - inverse of a rank 1 update to a matrix whose inverse has already been computed

    I.e. given invertible matrix A and outer product uv^T, computes a cheap update of

    $$(A+ uv^T)^{-1}$$

$A \in \mathbb{R}^{n \times n}$ is invertible, then $A + uv^T$ is invertible iff $1+v^TA^{-1}u \neq 0$

$$
(A+uv^T)^{-1} = A^{-1} - \frac{A^-1 uv^T A^{-1}}{1+v^T A^{-1} u}
$$

Note the update is of rank 1 as each row is a scalar multiple of v^T, so they are linearly dependent.

- For large m, n the lancxos based method/randomised are methods of choice.
- When A is not readily avaialbe and the computation of its entries is expenseive must use a method that uses a subset of its columns e.g. ACA

- Need to lookup but can expect singular values at or below 10^{-16} \sigma_1 are completely corrupted by roundoff

- Good note on why separability implies low rank

Partitioned Low Rank Matrices

- Only certain blocks rather than whole of A give a low rank appx, driven by admissibility

- HODLR
    - $A \in \mathbb{R}^{n \times n}$
    - $n=2^pn_p$ for simplicity, $p$ is max level $n_p$ are the size of diagonal blocks
    - Assume offdiagonal blocks $A(I^l_i, I^l_j), \> \> i \neq j$ has rank of at most $k$
    - $A(I^l_i, I^l_j) = U^l_i (V_j^l)^T$
    - $2^l$ additional diagonal blocks per level $l$.
    - Can find that storage complexity is $O(k n \log{n})$

    - on level 1
    $$y(I_1^1) = A(I_1^1, I_1^1)x(I_1^1) + A(I_1^1, I_2^1)x(I_2^1)$$
    $$y(I_1^2) = A(I_2^1, I_1^1)x(I_1^1) + A(I_2^1, I_2^1)x(I_2^1)$$

    - off diagonal blocks correspond to a low rank matvec wich cost
    $$c_{LR.v}(n) = 4nk $$
    - $$ c_{LR.v}(n/2) $$
    - Adding with diagonal cost, and vector addition cost
    - $$c_{H.v}(n) = 2 c_{H . v}(n/2) + 4nk + n $$
    - recurrence relation, n log(n) complexity for multiplication.
    - $$ (4k + 1) n \log_2{n} $$
    - This is important that this is where the complexity actually comes from.

- Remember HODLR complexity related to rank, only appropriate if $k$ is small.
- Need to cluster:
    - Want all blocks to have ranks small relative to n
    - Total number of blocks need to be small
    - The notion of re-ordering A and subdibing blocks is driven by locality between indices, and can be induced by the geometry of the underlying problem

### $ \mathcal{H}$ matrices

- HODLR block structure derived from perfect binary tree, more general now.
- Partition constructed from admiisbility condition

- HSS
- Consider off-diagonal block of matrix $A$ in HODLR format at level l
- Has low rank representation $A(I_i^l, I_j^l) = U^l_i S_{i, j}^l (V_j^l)^T$ S is kxk matrix.
- On level $l+1$ the the row index set is subdivided into $I_i^l = I_{2i-1}^{l+1}  \cup I_{2i}^{l+1}$

- On a deeper level $l+1$, the row and column indices are subdivided into $I_{2i-1}^{l+1} \cup I_{2i}^{l+1}$
- HSS format assumes that there exist matrices $X_i^{l} \in \mathbb{R}^{2k \times k}$ such that

$$
U_i^l = \begin{bmatrix}
U_{2i-1}^{l+1} &  0 \\
 0 &  U_{2i}^{l+1}\\
\end{bmatrix} X_i^l
$$

So can recursively construct row and column bases from those at the deepest level

Leads to O(8kn) storage

- All matrices from HSS representation are only touched once, therefore the storage complexity is the same as that for matvec.

- Obviously the drawback is that HSS doesn't work if rank k grows with n,

- A quadratic matrix that is H2 based on a balanced binary cluster tree and block cluster tree with the weak admissability condition is a HSS matrix
- weak admissibility is only adequate for one dimensional problems. e.g. approximate solvers for Toeplitz matrices
- H matrices also have O(nk log(n)) matvec complexity

- GoFMM relies on the fact that any PD admits the factorisation

$$K=G^*G$$

For a Gramian matrix G
    - corresponds to a set of vectors $v_1,...,v_n$ in an inner product space is the Hermitian matrix of inner product $$G_{ij} = \langle v_i, v_j \rangle$$
    - It is positive semidefinite, and every positive semidefinite matrix is the Gramian for some set of vector
    - NB Cholesky decomposition is a decomposition of a Hermitian PD matrix into $LL^*$

If the eigenvalue decomposition of $K = U \Gamma U^*$, then a matrix $G=V\Gamma^{1/2}U^*$ is a Gramian if $V$ is unitary.

- The factorisation suggests that the entries of $K$ are formed by inner products between columns of $G$.
- It's not explicitly needed to find the Gram factors $G$ all that's needed is to organise the points $\{g_i\}_{i=1}^n$ are relative distances and angles between points.
- These can be evalauted from the matrix entries of $K$.

$$
\|g_i - g_j\|^2 = \|g_i\|^2 -2 \text{Re}\langle g_i, g_j \rangle + \|g_j\|^2 = K(i, i) - 2 \text{Re}K(i, j) + K(j, j)
$$

