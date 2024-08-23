TODO:

- Steffen Boerm recent papers
    - Distributed H2 matrix
    - directional H matrix for Helmholtz problems.

- N log(N) scaling for Helmholtz problems
- Exactly how are algebraic FMM and H2 matrix similar/different.


Chapters 2-7

## Preliminary

- The application of $\mathcal{H}^2$ matrices is to integral operators solved with Galerkin method, I need a good summary of Galerkin methods here for reference and revision.

### Variational Methods Summary

- Normed Space + Completeness = Banach Space
- Semi norms don't have positive definiteness

Norms:


$V$ is a vector space over a field $\mathbb{F}$. A norm is defined as a function $V \to \mathbb{R}_{\geq 0} = [0, +\infty)$
$$
\begin{aligned}
1. \> \|u + v\| \leq \|u\| + \|v\| \> \> \text{(triangle inequality)} \\
2. \> \|\lambda v\| = |\lambda| \|v\| \> \>  \text{(positive homogeneity)} \\
3. \> \|v\| = 0 \text{ iff } v = 0 \> \> \text{(positive definiteness)}
\end{aligned}
$$

Normed space: $(V, \| . \|)$

Semi-norm if it satisfies 1 and 2, but not 3.

E.g. $\mathcal{l}_p$ is the space of all sequences $v = \{ v_j\}_{j=1}^\infty \subset \mathbb{R}$ s.t. $\|v_p\| < \infty $, where $\|v_p\| = (\sum_{j=1}^\infty |v_p|^p)^\frac{1}{p}$. Normed spaces are not necessarily finite dimensional.

- Usually choose a norm for which the space is complete. Since properties such as convergence of sequences and completeness are the same for all equivalent norms, it's standard practice to leave this implicit.

A sequence $\{v_n\}_{n=1}^\infty$ is Cauchy if for all $\epsilon > 0$ there exists $N \geq 1$ such that $\|v_m - v_n\| \leq \epsilon$ for all $m, n \geq N$. Written as $$ \lim_{m, n \to \infty} \|v_m - v_n\| = 0 $$

- A normed vector space is Banach if it is complete i.e. each Cauchy sequence has a limit in itself.

Space of continuous real valued functions on continuous intervals $C[a, b]$, many norms that leave it Banach. e.g. max norm, not not complete with L2 norm - so not Banach with this norm.

- We're interested in the solvability of operator equations, mapping between normed spaces $T: V \to W$

Theorem 1.3 (page 3), If a contraction mapping exists then $T(u) = u$ exists, i.e. the operator has a unique fixed point in the non-empty closed subset $M$ of $V$ which is Banach with a given norm.

Bounded linear operators that map between subspaces $T(\alpha v \beta w) = \alpha T(v) \beta T(w)$ for $v, w \in V$ where $T: V \to W$. Bounded if we can define

$$
\|T\|_{\mathcal{L}(V, W)} = \underset{v \in V, \|v\|_V \leq 1}{\sup} \|T v\|_W < \infty
$$

I.e. we can define a constant that bounds the operator norm.

The set of all bounded linear operators that map $V \to W$ is denoted by $\mathcal{L}(V, W)$, with its own norm denoted by the operator norm. If $W$ is Banach, so is this space.

From this we define linear functionals on $V$ which is a real normed space, which may not be complete.

The dual space $V^*$ is defined as a space of 'functionals' defined as bounded linear operators from $V \to \mathbb{R}$, it is Banach under the norm

$$
\|\psi\|_* = \underset{v \in V, \|v\| \leq 1}{\sup} |\psi(v)|, \> \> \psi \in V^*
$$


For functionals $\psi \in V^*$ the kernel of $\psi$ on $V$ is defined as,

$$
\ker \psi = \{ v \in V | \psi(v) = 0 \}
$$

i.e. the portion of the subspace for which the functionals vanish.


A vector space $V$ with an inner product is called a Hilbert space if $V$ is Banach under the induced (by the Hilbert space) norm defined by

$$
\|v\| = \sqrt{(v, v)}
$$

$W$ is dense in $V$ if every $v \in V$ is the limit of a sequence of elements in $W$. I.e. can appoximate elements of $V$ using sequences of $W$. Can find examples where non-closed in $V$ i.e. limit points of sequences in $W$ not contained in $W$.

Can get as close as you want to any vector in $V$ using vectors from $W$. Suppose $W$ is dense in $V$, so we can find a sequence $w_n$ that converges to some element $v \in V$.

By definition, the $v$ satisfies $(v, w) = 0$ for all elements of $W$ if $v$ is in the orthogonal complement of $W$. But from density our sequence converges, so $(v, w_n) \to (v, v)$, but $v$ is orthogonal to every element in $W$ so $(v, v) = 0$ this implies that $v$ has to be 0 vector (i.e. the only vector that is orthogonal to itself).

The only vector that can be in $V$ and $W^\perp$ is the zero vector, or if $W$ is dense in $V$ its orthogonal complement is the empty set.

This is intuitive as we must be able to approximate all of $V$ using elements of $W$. A vector in its orthogonal complement must be itself orthogonal to all of $V$.

In the context of Hilbert spaces, the inner products allows us to associate a bounded linear functional to each element $u \in V$,

$$
\psi(v) = (u, v), \> \> \forall v \in V
$$

Riesz representation theorem is that for every such bounded linear functional there is an unique $u \in V$ that allows us to define the above. where $\|\psi\|_* = \|u\|$

the general situation we will encounter is where we seek a solution $u \in V$, of

$$
a(u, v) = \psi(v), \> \> \forall v \in V
$$

Where the lhs is a bilinear form, and the rhs is a functional in the dual space of $V$.

Lax-Milgram offers sufficient conditions under which we can establish the existence and uniqueness of a solution to this problem.

The bilinear form must be 'bounded', i.e. a positive constance $c_1 > 0$ s.t.,

$$
|a(w, v)| \leq c_1 \|w\|\|v\|, \> \> \forall w, v \in V
$$

And is coercive on $V$ if there is a positive constant $c_0$ such that,

$$
c_0 \|v\|^2 \leq a(v, v), \> \> \forall v \in V
$$

Then for any bounded linear functional $\psi \in V^*$ there is a unique $u \in V$ that solves the equation, which itself has a bound (theorem 1.12)

Lax Milgram can thus be seen as generalising the finite dimensional result on the invertibility of PSD matrices to infinite dimensions.

- Continuity focuses on behaviour at individual points, and uniform continuity requires the function's behaviour to be uniformly controlled across the entire domain.
- In continuity $\delta$ can vary depending on the point being tested, in uniform continuity the same $\delta$ is used throughout the domain.
- Uniform continuity is therefore a much stronger condition than continuity alone.

Function spaces I need to grok

- $ C^k(\Omega) $ The space of all continuous real valued functions $v$ defined on the domain for which $D^\alpha v$ exists and is continuous on the domain for each multi-index $|\alpha| \leq k$.

- $ C_b^k(\Omega) $ The subspace of the above where the same differential operator exists, and is bounded for the same multi-indices

- $ C^k(\bar{\Omega}) $ The subspace of the above such that the differential operator is uniformly continuous on the domain for the same multi-indices


Compactly supported functions $v : \Omega \to \mathbb{R}$,

Support:

$$
\text{supp } v = \overline{\{ x \in \Omega | v(x) \neq 0 \}}
$$

Compactly supported in $\Omega$ if this set is a compact subset (closed and bounded) of $\Omega$

The space $C^\infty_0(\Omega)$ is the space of functions in $C^\infty(\Omega)$ that are compactly supported - this is an inmportant subspace as this is where we seek test functions for variational methods.

Some more important spaces that I need to grok.

For an open set $\Omega \subset \mathbb{R}^n$ The space $\mathcal{L}^\infty(\Omega)$ is the space of Lebesgue measurable functions that are essentially bounded (apart from on sets of measure 0) ie.

$$
\underset{x \in \Omega}{\text{ess sup}} |u(x)| < \infty
$$

Can define a semi-norm on this space.

To obtain a normed vector space we need to 'quotient out the kernel' of the seminorm $|.|_{\mathcal{L}_P(\Omega)}$. I.e. we consider two vectors to be equivalent if their difference lies in the kernel of the seminorm

This procedure is important because seminormed spaces often arise naturally in mathematics, but seminorms can be "degenerate" (i.e., they fail to separate points). By quotienting out the kernel, we eliminate this degeneracy and obtain a proper norm, allowing us to work within a normed space, which has more structure and useful properties.

Note that for $u \in \mathcal{L}^p(\Omega)$

$$
|u|_{\mathcal{L}^p(\Omega)} = 0 \text{ iff } u \in \mathcal{N}
$$

where

$$
\mathcal{N} = \{ u | \Omega \to [-\infty, \infty] \text{ st } u \text{ is measurable and } u=0 \text{ a.e in } \Omega \}
$$

Kernel of seminorm - all vectors the seminorm fails to distinguish from 0, the set of equivalence classses under this relation is called the quotient space. In this case we call it $L_P(\Omega)$, which we call the Lebesgue space, with a norm

$$
\|u\|_{L_P(\Omega)} = |\tilde{u}|_{\mathcal{L}_P(\Omega)}
$$

where $\tilde{u} \in \mathcal{L_P(\Omega)}$ is any representative of $u$ in this equivalence class.

The lebesgue space is complete with respect to this norm, i.e. Banach.

Definition of a weak derivative,

Let $v \in L^p(\Omega)$ $p \in [1, \infty]$. Suppose there exists $w \in L^2(\Omega)$ st,

$$
\int_\Omega w \phi dx = (-1)^{|\alpha|} \int_{\Omega} v D^\alpha \phi dx, \> \> \forall \phi \in C_0^\infty(\Omega)
$$

$w$ is called the weak derivative of $v$, $w = D^\alpha v$.

Sobolev spaces $W^{k, p}(\Omega)$ are the spaces of $L^p(\Omega)$ functions that are weakly differentiable up to order $k$ such that the weak derivative is in $L^p(\Omega)$

Norms for Sobolev spaces given on page 9, as well as semi-norms.

even though Sobolev spaces allow for functions that might be rough, jagged, or less regular (because they focus on weak derivatives), these "rough" functions can be very closely approximated by smooth functions. This is quite powerful because it means that, in practical applications, we can often work with smooth functions to approximate solutions in Sobolev spaces, making the problem easier to handle.

However, if Ω had a very irregular boundary, it might be difficult to get a smooth function to approximate the non-smooth function well near those irregularities.

$$
H^k(\Omega) = W^{k, 2}(\Omega)
$$

is Hilbert, and has a norm induced by an inner product (page 12).

The space $H_0^1$ is $v \in H_0^1(\Omega)$ iff v $\in H^1$ and $v$ is the limit in the $H^1$ norm of a sequence of $C_0^\infty$ functions.

i.e. up to some technical details consists of $H^1$ functions that are zero on the boundary. Makes sense as come from convergent sequence of compactly supported functions.

Elliptic PDE

- Leading coefficients $a_{i, j}$ are symettric, and satisfy uniform ellipticity condition,

$$
\sum_{i, j = 1}^n a_{i, j} (x) \xi_i \xi_j \geq c_\star \sum_{i=1}^n |\xi_i|^2, \> \> (\xi_1,...,\xi_n) \in \mathbb{R}^n, \> x \in \Omega
$$

I.e. the coefficient matrix for $a_{i, j}$ is positive definite, the uniformity points to the condition that $c_\star$ is the same for each $x \in \Omega$.

Consider electrostatics, the total potential energy is the integral of the potential energy per unit charge and charge density,

$$
\mathcal{E} = \int_{\mathbb{R}^3} \Psi \rho dx
$$

Using integration by parts

$$
\mathcal{E} = \epsilon_0 \int_{\mathbb{R}^3} |\nabla \Psi|^2 dx = \|\nabla \Psi \|^2_{L^2(\mathbb{R}^3)}
$$

Which is the seminorm for $H^1$, and suggests that the potential lies in this space.

Notion of generalised solution to elliptic PDE, where we can't assume its in $C^2(\bar{\Omega})$. Consider generic elliptic PDE, with a test function taken as $v \in C_0^\infty(\Omega)$, multiply and IBP to pass derivative over to test function in second order derivative. (page 4)

Can write as a bilinear form, then the weak formulation becomes the problem of finding $u \in H^1_0(\Omega)$ such that,

$$
a(u, v) = l(v), \> \> \forall v \in H^1_0(\Omega)
$$

The test function can be taken from the same space as it's from $C_0^\infty$ which is dense in $H^1_0$. Lax Milgram can be applied to show the existence and uniqueness of the solution to the variational problem.

Note that this space was chosen to match homogenous Dirichlet boundary conditions, page shows construction for more general boundary conditions.

### Galerkin Method

Hilbert space $V$ with a bilinear form $a(.,.): V \times V \to \mathbb{R}$ bounded + coercive, apply Lax Milgram which shows that for any $l \in V^*$ there is a unique solution $u$,

$$
a(u, v) = l(v), \> \> \forall v \in V
$$

* Idea: Replace the infinite dimensional $V$ with an approximation using finite dimensional spaces which become dense in the limit to $V$.

For $N>0$ let $V_N \subset V$ be a finite dimensional subspace of $V$ with dimension $N$. The Galerkin approximation $u_N \in V_N$ of $u \in V$ is defined as the unique solution of,

$$
a(u_N, v_N) = l(v_N), \> \> \forall v_N \in V_N
$$

- Need to verify Lax Milgram on subspace by beginning by showing its a closed subspace.

Let $\{ \phi_i\}_{i=1}^N \subset V_N$ denote a basis for this subspace, then. $\mathbf{u} = (U_1,...,U_N) \in \mathbb{R^N}$  is a coefficient vector of the basis expansion of the solution i.e. $u_N = \sum_{j=1}^N U_j \phi_j$. Define

$$
\mathbf{A}_{i, j} = a(\phi_i, \phi_j)
$$

$$
\mathbf{f}_i = l(\phi_i)
$$

Then to solve for Galerkin solution $u_N \in V_N$ involves inverting linear system,

$$
\mathbf{Au=f}
$$

Galerkin orthogonality, even when bilinear form doesn't define an inner product,

$$
a(u-u_N, v_N) = 0, \> \> \forall v_N \in V_N
$$

Error is orthogonal to finite dimensional subspace. I.e. provides the best approximation to the exact solution within this subspace. No other elements in $V_N$ will give a smaller residual with respect to the bilinear form.


The consequence of Cea's lemma is that the Galerkin solution is the near best approximation, up to a fixed constant depending only on coercivity and boundedness constants of the bilinear form.


## Chapter 2

- SLP on an interval for 2D Laplace kernel. The global support of the kernel function leads to a dense matrix (with Galerkin discretisation).
- Data sparsity, non-zero entries - but can apply compression to reduce cost of associated matrix.
- Expansions which are separable in terms of the variables in the kernel function are called degenerate in FMM literature.


Consider SLP for 2D laplace kernel

$$
\mathcal{G}[u](x) = - \int_{0}^1 \log |x-y| u(y) dy
$$

Under Galerkin method using $n$-dim basis $(\phi_i)_{i=1}^n$ of piecewise constant functions

$$
\phi_i(x) = \begin{cases}
1, \text{if } x \in [(i-1)/n, i/n] \> \> \\
0, \text{otherwise}
\end{cases}
$$

Get a dense matrix,

$$
G_{i, j} := \int_0^1 \phi_i(x) \int_0^1 g(x, y) \phi_j(y) dy
$$

where we set the singularities in the kernel function to 0, expressed the density in terms of the test basis and got into weak form by multiplying by the test functions and integrating.


Use taylor series approximation in both variables to get a degenerate approximation,

Get an expression for the approximation of the matrix as,

$$
\tilde{G}_{i, j} = \int_{(i-1)/n}^{i/n} \int_{(j-1)/n}^{j/n} \tilde{g}_{z_0, m}(x, y) dy dx
$$

Inserting taylor series approximation, shows that we end up with low-rank representation of the matrix as,

$$
\tilde{G} = V S W^*
$$

$V, W \in \mathbb{R}^{\mathcal{I} \times K}$, where $K := \{ 0,...,m-1 \}$ and $m$ is the expansion order and $\mathcal{I}$ is the index set $\mathcal{I} = [1,...,n]$ and $S \in \mathbb{R}^{K \times K}$. c.f. SVD


With this, considering the remainder of the Taylor series in some interval $[a, b]$, we get an exponential convergence proportional to

$$\frac{a-b}{2a}$$

For points in this interval, and $a$ is the distance to the singularity. we get this as long as the size of the interval is less than the distance to the singularity (at zero). In this simple analysis, more careful analysis says we get this whenever the distance from the singularity is positive. lemma 2.1. on page 12.

Here the speed of convergence depends on the ratio between $a$ and the radius of the interval [$a, b$]. $\zeta$.

For a positive constant $\eta \in \mathbb{R}_{> 0}$ let $t, s \subseteq \mathbb{R}$ be non-trivial intervals such that,

$$
\text{diam}(t) + \text{diam}(s) \leq 2 \eta \text{dist}(t, s)
$$

This is an admissibility condition.

then we get the error estimate, $z_0 := x_0 - y_0$ i.e. the distance between the midpoints of the interval:

$$
|g(x, y) - \tilde{g}_{z_0, m} (x, y)| \leq \log (\eta + 1) \left ( \frac{\eta} {\eta + 1}\right)^{m-1}
$$

Proof on page 13.

Basically means that the Taylor expansions for the model problem converge exponentiall in $m$, and the speed depends on this ratio of distance between the source and target intervals and their diameter of the intervals.

This implies that we cannot use a global taylor expansion to store the entire matrix G, as at least the diagonal blocks cannot be represented in a low rank form as we won't get the exponential convergence above if our admissibility criterion is not fulfilled.

Instead one uses local expansions, like taylor series, for subblocks of the matrix where the admissibility criteria is fulfilled.

Let $\hat{t}, \hat{s} \subseteq \mathcal{I}$ and intervals $t, s \subseteq [0, 1]$ where

$$
[(i-1)/n, i/n] \subseteq t
$$

same for $j \in \hat{s}$. $x_t$ and $y_s$ be the midpoints of these intervals, when we satisfy the admissibility criterion and can expect exponential convergence for the Taylor series approximation. Get low rank approximations for the interactions

$$
\tilde{G}_{t, s} := V_t S_{t, s} W^*_s
$$



- Cluster tree and block cluster tree.
    - Have to cover the entire matrix with sub blocks that enable the low rank form, or ensure that when we can't the number of entries is small (dense part).

For the model problem assume that there exists $q \in \mathbb{N}_0$, and $n = 2^q$ i.e. number of leaves proportional to number of rows/columns of this matrix.

Define the intervals and index sets,

$$
t_{l, a} := [\alpha 2^{-l}, (\alpha+1)2^{-l}]
$$

$$
\hat{t}_{l, a} := \{ \alpha 2^{q-l} + 1, (\alpha+1)2^{q-l} \}
$$

for levels $l \in \{0,..,q\}$ and the displacements $\alpha \in \{0,...,2^{l-1} \}$

then,

$$
t_{l, \alpha} \subseteq [0, 1], \> \> \hat{t}_{l, \alpha} \subseteq \{1, ..., n \} = \mathcal{I}
$$

So the support of all basis functions $\phi_i$ wiht $i \in \hat{t}_{l, \alpha}$ is contained in the corresponding interval.

The intervals are called 'clusters'. Clusters can be arranged in a hierarchy depending on their level.

Called the tree, with index sets, the cluster tree.

In this construction, the non-compressible index sets are of size one.

The recursive search for admissable pairs of clusters suggests a second tree of pairs of clusters, the elements of this tree are called _blocks_, as each pair corresponds to a block of the matrix being approximated.

This tree is called the _block cluster tree_, $\mathcal{T}_{\mathcal{I} \times \mathcal{I}}$

For level $l$ and $\alpha, \beta \in \{ 0, ..., 2^{l-1} \}$ use the following notation for blocks,

$$
b_{l, \alpha, \beta} := (t_{l, \alpha}, t_{l, \beta})
$$

Can show that the number of blocks only grows linearly with matrix dimension, not quadratically.

### Hierarchical Matrix

Given a block cluster tree, we can define an approximation of the matrix $G$. To avoid using the global index set in notation, we consider submatrices of $G$ as elements of $\mathbb{R} ^ {\mathcal{I} \times \mathcal{I}}$ which vanish outside of the index set for a given block $\hat{t} \times \hat{s}$. For each cluster $t \in \mathcal{T}_\mathcal{I}$ introduce a diagonal matrix $\chi_t \in \mathbb{R}^{\mathcal{I} \times \mathcal{I}}$,

$$
\chi_{i, j} := \begin{cases}
1, \> \> \text{if } i = j \in \hat{t} \\
0, \text{ otherwise}
\end{cases}
$$

for all $i, j \in \mathcal{I}$. So the block becomes, $b = (t, s)$

$$
\chi_t G \chi_s
$$

where we pick up all rows outside of the target indices, and all columns outside of the source indices.

The leaves of the block cluster tree form a disjoint union,

$$
G = \sum_{b = (t, s) \in \mathcal{L}_{\mathcal{I} \times \mathcal{I}}} \chi_t G \chi_s
$$

These leaves can be split into admissible and inadmissable sets, and for admissable sets can be presented by the low-rank approximation leading to the __approximation of G by a hiearchical matrix__

$$
\mathbf{G} := \sum_{b=(t, s) \in \mathcal{L}^+_{\mathcal{I} \times \mathcal{I}}} V_t S_b W_s^* + \sum_{b=(t, s) \in \mathcal{L}^-_{\mathcal{I} \times \mathcal{I}}} \chi_t G \chi_s
$$

This is the $\mathcal{H}$-matrix representation of $G$.

He proves a complexity bound for the storage requirement which is

$$
O(nm \log_2 n)
$$

improving on the quadratic complexity bound of naive storage of the matrix entries.

Probably the source of all of that `matrix free' critique in Yokota et. al.

Also prove an exponential convergence in terms of additional Taylor terms in terms of its approximation to the true matrix.


## $\mathcal{H}^2$ Matrices

The low rank matrices $V_t, W_s$ are now to be treated as entire families $(V_t)_{t \in \mathcal{T}_\mathcal{I}}$, $(W_s)_{s \in \mathcal{T}_\mathcal{I}}$.

These families are referred to as 'cluster bases', as the columns of $V_t$ form a generating set for the range of $\tilde{G}_{t, s}$, and the columns of $W_s$ form a generating set for the range of $\tilde{G}_{t, s}^*$. C.F martinsson notes.

He notes that the columns of these bases don't have to be linearly independent, though they usually are (not sure exactly why he gives no reasoning).

Let's look at a given interval, non-leaf, and its children.

$$
(V_t)_{iv} = \int_{(i-1)/n}^{i/n} \frac{(x-x_t)^v}{v!}dx
$$

where $x_t$ is the midpoint of $t$, $i \in \hat{t}$ and $v \in K$. For $t' \in \text{children}(t)$. Using binomial expansion,

$$
\frac{(x-x_t)^v}{v!} = \frac{1}{v!}(x - x_{t'} + x_{t'} - x_t)^v
$$

After some cancellation and algebra,

$$
= \sum_{\mu = 0}^v \frac{(x-x_{t'})^\mu}{\mu!}\frac{(x_{t'}-x_t)^{v-\mu}}{(v-\mu)!}
$$

So can express the integrand in terms of Taylor monomials centred on the child interval instead of the one of interest,

$$
(V_t)_{iv} = \sum_{\mu = 0}^v \int_{(i-1)/n}^{i/n} \frac{(x-x_{t'})^\mu}{\mu!} dx \frac{(x_{t'}-x_t)^{v-\mu}}{(v-\mu)!}
$$

The first factor is just the column basis for the child interval, the second one describes the change of basis when translating between the child and parent intervals, the M2M or 'transfer' matrix in this book.

So,

$$
(V_t)_{iv} = \sum_{\mu \in K} (V_{t'})_{i\mu} (E_{t'})_{\mu v} = (V_{t'} E_{t'})_{iv}
$$

For all $v, \mu \in K$, $i \in \hat{t}'$.

By definition of the cluster tree there is only one child $t_i \in \text{children}(t)$ with $i \in \hat{t}_i$ for a given $i \in \hat{t}$, therefore we see that,

$$
\sum_{t' \in \text{children}(t)} (V_{t'} E_{t'})_{iv} = (V_{t_i} E_{t_i})_{iv} = (V_t)_{i,v}
$$

Which holds for all clusters that are non-leaves. This is, explicitly spelled out, the concept of cluster bases which gives the FMM ($\mathcal{H}^2$ matrix) its power.


Translation matrices only require $O(m^2)$ storage, far more efficient that $\mathcal{H}$ format.


## Chapter 3

We need to find a general way of constructing block cluster trees for problems, that retain the approximation benefits demonstrated for the model problem with single layer Laplace.

- The price to pay for optimal complexity in H2 matrices is that we cannot compute matrix vector products directly from the representation (like with H), but need a recursive procedure to perform the computation in linear complexity.

- General way of writing a cluster tree

$\mathcal{T} = (V, S, r)$ a triple of a finite set $V$. A mapping

$$
S: V \to \mathcal{P}(V)
$$

of $V$ to subsets of $V$ and element $r \in V$.

A tuple $v_0, v_1,...,v_l \in V$ is called a path connecting $v_0 and v_l$ in $\mathcal{T}$ if

$$
v_i \in S(v_{i-1})
$$

holds for all $i \in \{1,...,l \}$


The triple is a tree if for each $v \in T$ there is a unique path connecting $r$ to $v$. $V$ is seen to be the set of all nodes, $r$ the tree root and $S(v)$ the sons of $v \in V$.

In the model problem there is an index set $\hat{t} \subseteq \mathcal{I}$ associated with each cluster. In the general case we attach labels to each node for additional information.

We can allow for arbitrary partitions of the index set, instead of the contiguous sets used in the previous model problem in 1D.

In this method there is no spatial information encoded in the block cluster tree, we have to apply the admissability criteria between blocks to find this out

- The blocks are no-longer necessarily square as clusters can contain different numbers of indices at the same level, and not all leaves are on the same level either (adaptivity).
- Can also split into more than 2 sons per cluster, as an option.
- Note that if the index sets of two clusters intersect one of them must be a descendent of the other by lemma page 33.



$\mathcal{T}_{\mathcal{I} \times \mathcal{J}}$ is a block cluster tree where

$$
\text{root}(\mathcal{T}_{\mathcal{I} \times \mathcal{J}}) = (\text{root}(\mathcal{T}_{\mathcal{I}}), \text{root}(\mathcal{T}_{\mathcal{J}}))
$$

Each node $b \in \mathcal{T}_{\mathcal{I} \times \mathcal{J}}$ of the form $b=(t,s)$ as before

A more general admissibility condition

$$
\mathcal{A}: \mathcal{T_\mathcal{I}} \times \mathcal{T_\mathcal{J}} \to \{ \text{true}, \text{false} \}
$$

is an admissability condition if,

$$
\mathcal{A}(t, s) \implies \mathcal{A}(t', s)
$$

$t'$ are the sons of the target. And vice versa.

$$
\mathcal{A}(t, s) \implies \mathcal{A}(t, s')
$$


The weaker admissibility condition is

$$
\mathcal{A_{1d, w}}(t, s) := \begin{cases}
\text{true}, \> \> t \neq s \\
\text{false}, \> \> \text{otherwise}
\end{cases}

$$


Acceptable for certain 1D problems with certain algorithmic advantages of the more strong admissability condition.

- Each block cluster tree must be associated with an admissability condition and defined with respect to this condition.

- How to practically construct?
    - Use some kind of hierarchy that already exists implicit in the index set.
    - Can also do if the index set results from a general hierarchy.

- Can also handle geometries which are not cubic with this approach, spheres, rectangles etc All that needs to be done is to adjust the admissability criterion such that that low rank sub-blocks can still be constructed.

- Use characterstic points (based on support of basis functions) to map geometry to H matrix framework.
- The usefulness here is that the geometric partitioning can be quite general, with no-reference to an octree and simply defined by the support of the point data. We'll still get out a nice H2 matrix regardless.
- This is to form the cluster trees, then forming the block cluster trees follows simple recursive algorithm (same for all cluster trees once found for source/target point sets).


- The size of a block is no longer connected to the level in the general H matrix framework, however it is connected to the size of its associated source and target clusters.

- A block cluster tree is considered sparse if block rows and columns only contain a bounded number of elemnts.

- Admissable blocks are not subdivided in the construction.

- Fig 3.10 makes neested cluster bases very clear

- In more general situations such as variable-order approximations, require more flexible methods to control the complexity estimates.

- Definition of a general $\mathcal{H}^2$ matrix.

- Let $V$ be a nested cluster bases for $\mathcal{T}_\mathcal{I}$ with rank distribution $K$. I.e. the cluster tree for the rows, and $W$ be a nested cluster bases for $\mathcal{T}_{\mathcal{J}}$ with another rank distribution $L$ (need not be the same as can have non-square matrices, with different sources/targets)

- The corresponding space of $\mathcal{H}^2$ matrices,

- Let $X \in \mathbb{R}^{\mathcal{I} \times \mathcal{J}}$, it is an $\mathcal{H}^2$ matrix for the block cluster tree $\mathcal{T}_{\mathcal{I} \times \mathcal{J}}$, with row cluster basis $V$ and column cluster basis $W$ if there is a family of matrices $S = (S_b)_{b \in \mathcal{L}^+_{\mathcal{I} \times \mathcal{J}}}$ satisfying $S_b \in \mathbb{R}^{K_t \times L_s}$ for admissable blocks $b=(t, s)$.

$$
X = \sum_{b=(t,s) \in \mathcal{L}^+_{\mathcal{I} \times \mathcal{J}}} V_t S_v W_s^* + \sum_{b=(t,s) \in \mathcal{L}^-_{\mathcal{I} \times \mathcal{J}} } \chi_t X \chi_s
$$

$S_b$ are called the family of coupling matrices.

- We observe that the set of all $\mathcal{H}^2$ matrices for the same block cluster tree and cluster bases is a matrix subspace, i.e. we can add and multiply these matrices efficiently, and also _we can approximate general matrices when projected into this subspace_.

- HSS matrices, a $\mathcal{H}^2$ matrix based on a balances binary cluster tree $\mathcal{T}_\mathcal{I}$ and block cluster tree $\mathcal{T}_{\mathcal{I} \times \mathcal{I}}$ using the weak admissability condition is called a hierarchically semi-separable matrix. Limited to 1D problems where weak admissability is tolerated, otherwise ranks don't decay fast enough.
- Possible to use nested dissection techniques to reduce 2D sparse problems into 1D problems that can be handled with HSS.
- TODO: What's the difference between HSS and HODLR? I guess no nested bases in HODLR, need to check

