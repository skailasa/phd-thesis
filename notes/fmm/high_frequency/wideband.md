A wideband fast multipole method for the Helmholtz equation in three dimensions

History
- first group of algorithms $k$ space methods, take advantage of the fact that free space green's functions for Helmholtz are translation invariants and use FFT
- Require N^{3/2} log N operations for boundary integral equations in 3D


The CPU time requirements of the FMMs are propor- tional to N in the low-frequency regime, and to N Æ logN for high-frequency problems involving boundary integrals; the latter estimate becomes O(N) for volume integral equations. Fast Multipole Methods can easily be

While the algorithms known by the term ‘‘FMM’’ share the same basic computational structure, the expansions they use are based on either of two very different principles. For the Laplace equation, or for the Helm- holtz equation in the low-frequency regime, the principle used is that large submatrices of the matrix to be applied are of low rank (to high but finite precision)


While the algorithms known by the term ‘‘FMM’’ share the same basic computational structure, the expan-
sions they use are based on either of two very different principles. For the Laplace equation, or for the Helm- holtz equation in the low-frequency regime, the principle used is that large submatrices of the matrix to be applied are of low rank (to high but finite precision)

$$ h_0(z) = e^{iz}/z $$

$$
\phi_k = sum_{j=1, j \neq k}^N s_j \cdot h_0(\omega \|x_k - x_j\|)
$$

$\phi_i,...,\phi_N \in \mathbb{C}$ $s_i \in \mathbb{C}$ as is $\omega$ - wavenumber


A function is referred to as a spherical harmonic of degree $n$ if

$$
f: S^2 \rightarrow \mathbb{C}
$$

$$r^n f(\theta, \phi)$$

satisfies Laplace in 3D. For any n there are 2n+1 linearly independent spherical harmonics of degree n, which are an orthonormal basis.

$$
Y_n^m(\theta, \phi) = \bar{P}_n^{|m|}(\cos{\theta})e^{im\phi}
$$

P - normalised associated Legendre function of degree n and order m.

Any two sph. harm of different degrees are orthogonal to each other.


3. Classic partial-wave expansions are the primary type of expansion used by the low-frequency Helmholtz FMM.

Referred to as $h$ expansions.


The wideband FMM uses only a small number of angles of rotation, and uses partial-wave expansions only in the low-frequency regime, where they have limited numbers of terms; thus rotation matrices to accomplish this task can easily be precomputed and stored

due to the ease of rotations (see the preceding section), we need only examine translations along the z-axis: any other translation can be performed by rotating the expansion so that its z-axis points along the direction of the desired translation (that is, from the center of the child box to the center of the parent box), translating it along the z-axis, then rotating it back—a procedure referred to as ‘‘point-and-shoot’’.

Each of these steps can be performed in p^3 steps.

However, in the case that the coefficients of the partial-wave expansion are scaled differently from each other, as they are for boxes less than roughly a wavelength in size, these conversions degrade or destroy the accuracy of the expansion, depending on how severe the difference in scaling is