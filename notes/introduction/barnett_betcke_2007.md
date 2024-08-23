- dependence of rank on kR, need to find convergence behaviour in this paper for MFS (at least for Laplace case) They do have some references for this in this paper.

It turns out that if the boundary data is analytic (can be parametrisd by analytic function) MFS gives expoential convergence for the Laplace problem on analytic domains

define the boundary error norm,

$$
t = \|u^N - v\|_{L^2(\partial \Omega)}
$$

$v$ is the boundary data, and $u^N$ the approximation to the solution.

This controls the interior solution error as,

$$
\|u^N - u\|_{L^2(\Omega)} \leq \frac{C_\Omega}{d}\| u^N -v \|_{L^2(\partial \Omega)}
$$

$d := \min_j|k^2 -E_j|/E_j$, the domain's dirichlet eigenvalues, and $C_\Omega$ a domain dependent constant.

i.e. for non-resonant $k$ can use the boundary error norm for the solution norm.

## Section 2

Unit disk

$$
\Omega = \{ \mathbf{x} | |x| < 1 \}
$$

with charge points $y_j = Re^{i\phi}$, $\phi_j = 2\pi_j/N$, ie. equally spaced on a larger circle that bounds the unit disk.

Represent a coefficient vector $\mathbf{\alpha} := \{ \alpha_j \}_{j=1,...,N}$ in a discrete Fourier basis labelled by $k$,

$$
\alpha_j = \sum_{k = -N/2 + 1}^{N/1} \hat{\alpha}_ke^{ik\phi_j}
$$

and

$$
\hat{\alpha_k} = 1/N \sum_{j=1}^N \alpha_j e^{-ik\phi_j}
$$

From parseval's identity, and Euclidean norm,

$$
|\alpha|^2 = N |\hat{\alpha}|^2
$$


Then they map from the layer potential to the Fourier basis on the unit circle, which is the $N \to \infty$ limit of the MFS.


On the outer circle (equivalent surface)

$$
u(x) = \frac{i}{4} \int_0^{2\pi} H_0^1(k|x-Re^{i\phi}|)g(\phi) d\phi
$$

applying Fourier, gives,

$$
\hat{u}(m) = \hat{s}(m)\hat{g}(m)
$$

$m$ - frequency, where the eqigenvalues are,

$$
\hat{s}(m) = \frac{i\pi}{2}H_m^1(kR)J_m(k)
$$

For laplace case, get exponential convergence of eigenvalues,

$$
\hat{s}(m) \to \frac{1}{2|m|} R^{-|m|}
$$

For non-zero $k$ which is fixed, they find the leading order asymptotic behaviour,

$$
\hat{s}(m) \sim \frac{1}{2|m|} R^{-|m|}
$$

Coinciding with the Laplace case.

For some fixed constants,

$$
\frac{c_s}{|m|} R^{-|m|} \leq |\hat{s}(m)| \leq \frac{C_s}{|m|} R^{-|m|} \leq C_sR^{-|m|}
$$

$C_s$ has to be chosen large enough that the first eigenvalue is less than this.