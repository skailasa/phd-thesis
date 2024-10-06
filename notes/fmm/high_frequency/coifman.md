The Fast Multipole Method for the Wave Equation: A Pedestrian Prescription

Ronald Coifman’, Vladimir Rokhlin’, and Stephen Wandzuraz

- Non recursive algorithm presented reduces to $O(N^\frac{3}{2})$

However, even for problems that have an order of magnitude more variables than those currently tractable using
dense-matrix techniques $N \sim 10^5$, we estimate that the performance of the single-stage algorithm should be near optimal.


- Scalar wave equation

$$
(\nabla^2 + k^2) \psi = 0
$$

A Dirichlet boundary condition

$$
\psi(x) = 0 \> \> x \text{ on } S
$$

Using BEM, find a discretisation of the first kind IE, gives a set of linear equations with a dense coefficient (impedance) matrix,

$$
Z_{nn'} = -i \int_S d^2\mathbf{x} \int_S d^2\mathbf{x'} f_n(\mathbf{x}) \frac{e^{ik|x-x'|}}{4\pi|x-x'|}f_{n'}(x')
$$

Basis functions are assumed real, and supported on local subdomains $f_n$.

FMM then rapdly evaluates the matvec:

$$
B_n = \sum_{n'=1}^N Z_{nn'}I_{n'}
$$

$I$ is an arbitrary vector

- Galerkin method (test and trial spaces are same)

Can then use iterative schemes to solve

$$
Z \cdot I = V
$$

where $$V_n(k) = \int_S d^2x f_n(x) e^{i k \cdot x}$$

Is some incident wave with a given wave vector.

Relies on a couple of identities

$$
\frac{e^{ik|X+d|}}{|X+d|} = ik \sum_{l=0}^\infty (-1)^l (2l + 1)j_l(kd) h_1^{(1)}(kX) P_l(\hat{d}\cdot \hat{X})
$$

A form of Gegenbauer's addition theorem all take usual meanings, $|d| < |X|$. See paper fig 1 for geometry.

Nex identify required,

$$
4\pi i^l j_l(kd) P_l(\hat{d} \cdot \hat{X}) = \int d^2\hat{k}e^{ik \cdot d} P_l(\hat{k} \cdot \hat{X})
$$

$\hat{k}$ poorly chosen variable of integration.

Subbing into the above you get,

$$
\frac{e^{ik|X + d|}}{|X + d|} = \frac{ik}{4\pi} \int d^2 \hat{k} e^{ik \cdot d} \sum_{l=0}i^l(2l+1)h_l^{(1)}(kX)P_l(\hat{k}\cdot \hat{X})
$$

Point is that the sum can be precomputed

$$
\mathcal{T}_L(\kappa, \cos{\theta}) = \sum_{l=0}^Li^l (2l + 1)h_l^{(1)}(\kappa)P_l(\cos{\theta})
$$

for various $\kappa$, choose $L+1$ terms in practice, which depends on $kd$ max value, as well as desired accuracy.

In order to obtain accuracy $L > kD$, $D$ is the maximum value of $d$ for which the expansion will be used.

Written this way

$$
\frac{e^{ik |X + d|}}{|X + d|} \approx \frac{ik}{4\pi} \int d^2 \hat{k} e^{ik \cdot d} \mathcal{T}_L(k X, \hat{k} \cdot \hat{X})
$$

stThis is the multipole expansion of the Helmholtz 3D green's functionspack env view regenerate


Can write impedence matrix elements in terms of this function

$$
Z_{nn'} \approx \frac{k}{(4\pi)^2}\int_S d^2x f_n \int_S d^2x' f_{n'}(x') \int d^2 \hat{k} e^{ik \cdot (x-x'-X)}\mathcal{T}_L({kX, \hat{k} \cdot \hat{X}})
$$

This equation gives th matrix element (for well separated interactions) in terms of the Fourier transforms with the wave number $k$ of the basis functions.

The acceleration from the FMM comes frmo the fact that the far fields can be grouped together before the integral over $\hat{k}$.

Algorithm:

1. Divide $N$ basis functions into $M$ groups labeled by index $m$. Rach supporting about $N/M$ basis functions. Basis function index $n$ corresponds to pair $(m, \alpha)$ where $\alpha$ is local index in group $m$.

The centre of the smallest sphere enclosing each group is labelled $X_m$.


- For nearby groups, compute sparse matrix elements directly from original discretised sum.

3. For $K$ directions $\hat{k}$, compute the 'excitation vectors' Fourier transforms of the basis functions

$$
V_{m\alpha}(\hat{k}) = \int_S d^2 x e^{ik \cdot (x - X_m)} f_{n(m, \alpha)}(x)
$$

$k$ is a parameter of the problem, not a variable. i.e. integrating over all directions but $k$ is a constant here

Translations are diagonal

Intuitively, find frequency components associated with radiation from each patch in each direction

- kind of defined the other way round in 18 which looks like incoming waves to each patch, hence the complex conjugate in 21 which describe waves going out from each patch amplified by the source term.

The plane wave part is multiplied by the translation operator, which simply comes from the definition. This is a diagonal operation

The translations basically point in direction of interaction, with associated direction that, that describes the portion of the signal that is being translated in a particle direction.


At the end, have to integrate what we get from the far field over all directions in a surface integral, as well as do 'inverse' transform to compute the incoming effect of the far field for each patch.

Computing a forward transform from source data,

then diagonal translation

then inverse transform + integral over all directions

Operation count minimized with $M = \sqrt{N}$ ie number of patches is roughly square root of $N$ - system size (in terms of number of basis functions)

Results in $O(N^{3/2})$ algorithm, becomes faster with multilevel scheme

Expansion order required related to diameter of patches (basis function groups)

$L \sim kD$

