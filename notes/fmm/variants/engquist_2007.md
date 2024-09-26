FAST DIRECTIONAL MULTILEVEL ALGORITHMS FOR OSCILLATORY KERNELS

- Complexity of evaluations scales with wavelength decreasing, as more points per wavelength are required to maintain resolution.

- Dimension N scales quadratically with K^2 where K is the dimension of the domain. As comes from proportionality to surface area which is discretised with a fixed number of points per wavelength.

- The Helmholtz kernel is translation invariant, and can be diagonalised through the Fourier transform.
    - Of O(N^3/2 log N), almost quadratic complexity.
    - early approaches

- Editing Laplace FMM for low frequency Helmholtz
    - [33] L. Greengard,J. Huang,V. Rokhlin,and S. Wandzura, Accelerating fast multipole meth- ods for the Helmholtz equation at low frequencies, IEEE Comput. Sci. Eng., 5 (1998), pp. 32–38

- Approximate rank of the interaction grows linearly with size of the points set.

Note on this

The restrition of Laplacian solutions of degree $n$ to a unit sphere $\mathcal{S}^2$ is called the spherical harmonic of oder $n$.

There exist exactly $2n+1$ linearly independent spherical harmonics of order $n$.

Homogoenous polynomials, of degree $n$, linearly independent, written in sphericla polars as,

$$
H_n = r^n Y_n(\theta, \phi)
$$

Can define in terms of associated Legendre polynomials etc.

We look for solutions of Helmholtz equations of the form,

$$
u(x) = f(k |x|) Y_n(\frac{x}{|x|})
$$

From the form of Laplace for spherical harmonics must satisfy, we get that $f$ must satisfy spherical Bessel equation in order for our solution to satisfy Helmholtz.

$$
t^2 f^{''}(t) + 2t f^{'}(t) + [t^2 - n(n+1)]f(t) =0
$$

$j_n$ and $y_n$ with their definitions in Colton and Kress (32), represent solutions of the spherical Bessel equation, are called the spherical Bessel functions.

- Can be expressed in terms of trig functions. Their linear combinations are known as spherical Hankel functions of the first and second kind of order $n$

$$
h_n^{(1, 2)} := j_n \pm i y_n
$$

$$
u_n(x) = j_n(k|x|)Y_n(\frac{x}{|x|})
$$

is an entire solution of the Helmholtz equation

$$
v_n(x) = h_n^{(1)}(k|x|) Y_n(\frac{x}{|x|})
$$

is a radiating solution to the Helmholtz equation excluding the origin.

Addition theorem for the fundamental solution, for $|x| > |y|$

$$
\frac{e^{ik|x-y|}}{4\pi |x-y|} = ik \sum_{n=0}^\infty \sum_{m=-n}^n h_n^{(1)}(k|x|)Y_n^m(\frac{x}{|x|}) j_n(k|y|)\bar{Y_n^m(\frac{y}{|y|})}
$$

^ remember the conjugate over the second term.

The number of terms in this series corresponds to the rank. There is a double sum here, compared to the single sum requred when expanding Laplace Green's function, which turns out to be

$$
\frac{1}{|x-y|} = \frac{1}{r} \sum_{n=0}^\infty (\frac{r'}{r})^n P_n(\cos \alpha)
$$

I.e. rank grows with $N$ for Laplace, but with $N^2$ for Helmholtz, where $N$ is the expansion order.

But expansion order order needs to be $kD$ for resolution, hence we get the rank growth quadratically with $kD$

- Should still take O(N) operations as the log(N) term comes from the high frequency separation.

