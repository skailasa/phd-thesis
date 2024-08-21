- Wilkinson paraphrase [62]
    - a matrix is data sparse if it has enough internal structure that it pays to take advantage of it.

- Quantifying numerical rank
    - from linear algebraic point of view, how fast do the singular values decay of the corresponding matrix
    - For global problem it would be decay of singular values of subblocks.
    - The faster the decay, the lower the numerical rank.

- Unbounded operators (e.g. differential operators) as there exists no constant $C$ such that $||T(C)|| \leq C ||x||$, the norm of the derivative can grow without bound as the function changes. Discretising e.g. Laplacian operator by finite difference, can lead to large condition numbers with decreasing step size.

- Application of (integral) solution operator is much more mathematically benign.
    - high order methods require only quadrature/

## Chapter 1 Introduction, and problem setting

Prototype elliptic PDE, Poisson equation.

E.g. electrostatics, electric field due to a point charge

$$ E = \frac{q}{4 \pi \epsilon_0 r^2} \mathbf{\hat{r}}$$

Calculating flux, independent of shape of surface relates to charge contained inside,

$$ \phi_E = \oint_{dV} \mathbf{E} \cdot d \mathbf{A}  = \frac{Q_{enc}}{\epsilon_0}$$

Can apply divergence theorem and relate flux to divergence of field in enclosed volume,

$$ \int_V \frac{\rho}{\epsilon_0} dV = \oint_{dV} \mathbf{E} \cdot d \mathbf{A}  = \int_V \nabla \cdot \mathbf{E} dV $$

Giving the differential form of Gauss' law for electrostatics,

$$ \nabla \cdot E = \frac{\rho}{\epsilon_0}  $$

From this, the electric field is defined in terms of the negative gradient of the electric potential (it's conservative, i.e.line integrals are path independent, and the vector field can be represented as the gradient of a scalar potential)

$$ E = -\nabla u $$

substituting into Gauss' law we arrive at Poisson's equation.

$$ -\Delta u = \rho_0 $$

where $\rho_0 = \frac{\rho}{\epsilon_0}$

(remember minus sign comes from the fact that potential change is the negative of the (positive) work done).


In free space, where the load $\rho_0$ has support over some finite domain $\Omega$ we can solve Poisson's equation using the fundamental solution,

$$ u(\mathbf{x}) = \int_{\mathbb{R}^3} K(\mathbf{x-y}) \rho_0(\mathbf{y}) d\mathbf{y} = \int_{\Omega} K(\mathbf{x-y}) \rho_0(\mathbf{y}) d\mathbf{y}, \> \> \> \mathbf{x} \in \mathbb{R}^3 $$

Noting that there must be a condition on the behaviour of $u(\mathbf{x})$ at infinity,

$$ \lim_{|\mathbf{x}| \to \infty} u(\mathbf{x}) = 0$$

Consider some subset of target points $\{ x_i\}_{i=1}^M \in \mathbb{R}^3$, and source points $\{ y_j\}_{i=1}^N \in \Omega$ , the integral transforms into the following sum,

$$ u(x_i) = \sum_{j=1}^N K(x_i - y_j) \rho_0(y_j), \> \> \> i = 1,...,M$$

Evaluating for all $N$ and $M$ results in $O(NM)$ calculations.

Increasing spatial dimension the problem remains the same, however the practical machinery to compute the discrete problem increases in complexity despite the asymptotic speedup offered by fast summation methods.

Where does the application of the Green's function come from? Can verify it's the solution by substitution.

Cannot write down Green's functions for complex domains, so instead seek similar problem form by writing down boundary integral equation formulations.

Consider a general domain $\Omega$ with a boundary $\Gamma$ and the following boundary value problem,

$$
\begin{aligned}
-\Delta u(\mathbf{x})  &= 0, \> \> \mathbf{x} \in \Omega \\
 u(\mathbf{x})  &= f(\mathbf{x}), \> \> \mathbf{x} \in \Gamma
\end{aligned}
$$

another way of writing the solution, when we don't know the Green's function for $\Omega$ is by using the fundamental solution convolved with some density function which is now unknown,

$$
u(\mathbf{x}) = \int_\Gamma K(\mathbf{x-y}) \sigma(\mathbf{y}) dy
$$

We know that a unique $\sigma$ exists for every Dirichlet data $f$. Such that the above formula satisfies the boundary value problem. We can determine $\sigma$ by solving the boundary integral equation,

$$
f(x) = \int_\Gamma K(\mathbf{x-y}) \sigma(\mathbf{y}) dy
$$

And use it to solve for $u$ over $\Omega$. This again requires a fast evaluation of the integral operator in order to be of practical use. The fundamental solution wasn't enough to solve the problem, but its existence for this particular problem was enough to help reduce the dimension of the problem, leading to a matrix problem of the form,

$$
A \mathbf{\sigma} = \mathbf{f}
$$

Can also perform this for functions which have a body load,

$$
\begin{aligned}
-\Delta u(\mathbf{x}) + b(\mathbf{x})u(\mathbf{x})  &= g(\mathbf{x}), \> \> \mathbf{x} \in \mathbb{R}^3 \\
 lim_{|\mathbf{x}| \to \infty} u(\mathbf{x}) = 0
\end{aligned}
$$

Convolving with fundamental solution, we exchange a local continuum operator for a global one. Trading a sparse for a dense coefficient matrix to solve. However, this representation is more benign. The integral operators are smoothing (i.e. improve regularity) which can be particularly advantageous for oscillatory problems, and can improve the accuracy of computations.

##  Chapter 3 Matrix Factorisations

- $A \in \mathbb{R}^{M \times N}$
- $col(A) = range(A) = \{ Ax | x \in \mathbb{R^N} \}$
- $row(A)$, range of $A^T$

Exact rank deficiency,

- columns of $A$ span a subspace $\mathbb{R}^M$ of dimension $k$ (i.e. number of basis vectors to span it)
- rows $A$ span a subspace of $\mathbb{R}^N$ of dimension $k$.
- Can come up with similar statements for nullspaces in terms of number of columns and rows.

If $A$ has rank $k$ it satisfies the factorisation,

$$
\underset{M \times N}{A} = \underset{M \times k}{E} \times \underset{k \times N}{F}
$$

$E$ columns span column space of $A$ and $F$ rows span rows space of $A$.

- Computing $Ax$ requires $kN + kM$ flops
- requires $kN + kM$ storage.
- Can be computed in a multitude of ways (e.g. QR, SVD etc).

Approximate rank deficiency is often used in practice, also called numerical rank. Using PG's definition based on spectral norm of a matrix leads to definition 3.1 (pg 17) which I won't write out. but based on a criterion $\epsilon$, and hence called $\epsilon$-rank of $k$ of $A$. This is a parameter to be controlled in applications.

In the sense of the chosen norm, the SVD can be seen to be optimal.

Algorithms for the SVD are iterative in nature, for $p \geq 5$. For practical purposes can be seen to perform as deterministic algorithms due to their fast convergence.

- With $p = \min(M, N)$, we note that the asymptotic complexity of computing the SVD (or QR, LU) is $O(MNP)$, however with different scaling constants. SVD > column pivoted QR > unpivoted QR.

- At some point need to revise Housholder reflectors and contrast them with Gram-Schmidt.


## Chapter 6: Fast Multipole Method

Greengard and Rokhlin demonstrated that the potential evaluation problem could be evaluated (for Laplace kernel originally) to any desired $\epsilon$ accuracy in $O(N)$, with a scaling constant that logarithmically depends on the inverse of the accuracy as $\epsilon \to 0$.

From a linear algebraic perspective, exploiting rank deficiencies between certain off-diagonal blocks of $A$.

Consider $\mathbb{R}^2$ Laplace case,

$$
\begin{aligned}
K(x,y) &= \log(x-y) = \log((x-c_s) - (y-c_s)) \\
&= \log(x-c_s) + \log(1 - \frac{y-c_s}{x_c-c_s}) \\
&= \log(x-c_s) - \sum_{p=1}^\infty \frac{(y-c_s)^p}{p (x-c_s)^p}
\end{aligned}
$$


The sum becomes,

$$
\phi(x_i) =  \log(x-c_s)\hat{q}_0^s + \sum_{p=1}^\infty \frac{1}{(x-c_s)^p}\hat{q}_p^s
$$

where

$$
\hat{q}_0^s = \sum_{j \in I_s}q_j
$$

$$
\hat{q}_p^s = \sum_{j \in I_s} -\frac{1}{p}(x_j - c_s)q_j, \> \> p=1,...,P-1
$$

The exponential convergence of this series, given admissability, is given in theorem 6.1.

M2L Translation

Consider $x \in \Omega_t$, the potential,

$$
v(x) = \sum_{j \in I_s} G(x, y_j) q_j = \log(x-c_s)\hat{q}_0^s + \sum_{p=1}^\infty \frac{1}{(x-c_s)^p}\hat{q}_p^s
$$

i.e. it's harmonic (Solves Poisson) in $\Omega_t$, consequently it can be expressed with a convergent expansion,

$$
v(x) = \sum_{p=0}^\infty (x-c_t)^p\hat{v}_p^t
$$

centered on the target box. M2L finds the coefficients $\hat{v}_p^t$ from the coefficients $\hat{q}_p^s$.

Shown on page 64 for d=2, Laplace.

The outgoing expansion is a compact representation of the field generated by all sources contained within that box. The incoming expansion is a compact representation of the potential in the box that is generated by all well-separated sources.

The incoming expansion (in 2D laplace) is analytic (i.e. represented by a convergent power series) centered at $c_t$ of $\Omega_t$.

- General harmonic function, a function that is harmonic in the entire domain under consideration - allowing for possibly an infinite series representation.

- TODO: Need to lookup error estimates in original kiFMM paper.

- FMM vs PPPM (particle particle, particle mesh) methods
    - Claim adaptive FMM is decisive for non-uniform distributions.
    - Idea of PPPM methods is to lay down an artificial uniform grid in the computational domain, create some equivalent charges at these new points and use the grid-based problem for evaluating long-range interactions, and local correction for short range interactions (not disimilar to PVFMM/ExaFMM approach.)
    - Suffer in terms of performance when the distributions are non-uniform, and there are non-periodic boundary conditions.

- Rokhlin and Greengard FMM with diagonal translation operators
    TODO: A new version of the fast multipole method ... 1997
    - split the interaction list into pieces contained in solid angles.

- Other approach to accelerate M2L suggested by PG
    - Carry out local rotation of coordinate system. so that $\theta = 0$ goes through box centers. Then each Fourier mode in the azimuthal variable communicates independently of all others, shown in same paper as above.


Helmholtz FMM

Consider time harmonic waves which are sinusoidal in time with a position dependent amplitude, and some phase.

$$
u(\mathbf{x}, t) = A(\mathbf{x}) \cos(\omega t - \psi(\mathbf{x}))
$$

$$
\begin{aligned}
u(\mathbf{x}, t) &= \text{Re} \{ A(\mathbf{x}) e^{-i\omega t + i \psi(\mathbf{x})} \} \\
u(\mathbf{x}, t) &= \text{Re} \{  e^{-i\omega t} \hat{u}(\mathbf{x}) \}
\end{aligned}
$$

Plugging into homogenous wave equation,

$$
\frac{1}{c^2} \frac{\partial^2p}{\partial t^2} u(\mathbf{x}, t) - \nabla^2u(\mathbf{x}, t) = 0
$$

Can factor out homogenous Helmholtz equation,

$$
\Delta \hat{u}(\mathbf{x}) + k^2  \hat{u}(\mathbf{x}) = 0 , \> \> k = w/c
$$

Consider a set of sources and targets which wlog can be considered the same set, and a radiation condition at infinity for the evaluated potential.

Similar to the Laplace case, the Helmholtz potential can be written using

$$
u(x_i) = \sum_{j \neq i} G(x_i, x_j)q_j, \> \> i=1,..,N
$$

Where $G(x,y) = H_0^{(1)}(k |x-y| ) = J_0(k|x-y|) + iY_0(k|x-y|)$

The foundation for Helmholtz (analytic) FMM is the expression of the kernel function using the addition theorem for the first kind Hankel function,

$$
H_0^1(k|x-y|) = \sum_{p=-\infty}^\infty (J_p(ks)e^{ip\beta})(H_p^{(1)}(kr)e^{-ip\alpha})
$$

The number of terms required in this summation crucially depends on the size of the box. The larger the box, the more terms needed. So length of expansions grows with reducing tree level.

TODO: These scale as $P \sim kD$, for analytic 2D Helmholtz FMM. D is box diameter. Need to see Barnett and Betcke paper for MFS results that show this relationship.

Linear algebraic interpretation of FMM

- The FMM exploits the fact that a dense matrix $A$ can be tesselated into $O(N)$ pieces, each of which has a low numerical rank.

## Chapter 9: The Potential Evaluation Map

- How optimal are multipole expansions? Is it possible to improve on them, if so can we improve on the FMM?

- For a relatively dense distribution of sources, there is not much difference between the ranks generated for a particular realisation and the ranks generated by an optimal 'generic' compression.

- TODO: A tuned and scalable fast multipole method as a preeminent algorithm for exascale systems, Yokota and Barba 2012

