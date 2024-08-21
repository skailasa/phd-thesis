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


- Cluster tree and block cluster tree.
    -