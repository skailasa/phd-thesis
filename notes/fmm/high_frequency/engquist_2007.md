FAST DIRECTIONAL MULTILEVEL ALGORITHMS FOR OSCILLATORY KERNELS

- Ball or radius r and well separated region as long as it belongs to cone at least r^2 away and spanning angle of cone is 1/r.

- Prove N log N complexity bound when points are sampled from a 2D surface.

- Some assumptions, assume point are bounded by some sphere $|p_i| \leq K/2$. Set wavelength 1 in setup.

In practical applications, K is 100-1000s. Assuming fixed pointer per wavelength, number of samples required is $O(K^2)$

- Where $K$ is close to 1, i.e. wavelength size, low rank property holds.
- When HF, approximate rank grows linearly with size of the points set (look at decomposition of green's function for Helmholtz p=kD)
- Rokhlin work - though of large rank, can be applied efficiently by 'focussing on far field signature of the potentials'
- In some sense analgous to the FFT
    - It utilizes a large family of tools, such as partial wave expansion, far field signature, exponential expansion, filtering, and interpolation of spherical harmonics
Good descriptions of the HF-FMM include [18, 27, 41]

Admissibility condition:
    - 'directional parabolic separation condition'
    - 'drectional low rank property'
        - interaction between two clusters of radius r where X_r is r^2 or greater in distance from Y_r and in its 1/r cone, the rank has an upper bound independent of r.

- Randomised procedure for constructing basis vectors


Algorithm

1. Construct octree

2. Low frequency upward pass $\{ f_k^{B, o} \}$ - equivalent densities for multipoles, k is box index? (running index they call it, I guess over all of the source boxes/elements?)

3. High frequency upward pass $\{ f_k^{B, o, l} \}$ - $l$ are the directions, skip very large boxes larger width than $\sqrt{K}$ as they have empty interaction lists - these are handled directly at the end?

4. Accumulate directional downward check potentials during downward pass. Again skipping those large boxes.

5. Rest of the downwrad pass

Assume N = O(K^2), generally true for BIE, as sampled from a 2D surface.

- Octree is O(K^2) = O(N)

- low frequency upward pass of the same complexity as there are O(N) boxes, each with constant number of operations

- HF upward pass is O(N log N).
    - points are from 2D manifold inside hte ball of K/2 diameter
    - Claim there are O(w^2) directions l, for a box of width w.
    - As points from 2D manifold, there are O(K^2/w^2) of them?
        -


- For each box, partition its far-field into 6 pyramids - this creates appx sphere around them -like a football.
- Eaach of these is partitioned into C = 4w^2 wedges. This results in 96w^2 cones, marked by directional vector l, around the box.
- the wedges are hierarchical over level
- wedges aren't isometric, but some redundancy, so only have to compute translations for 2w^2 wedges.
- Check potentials must be computed by kernel evaluations in their scheme, for each direction.


- For densely distributed

N = O(K^3).

- for directional M2M, O(w^2) directions l. and there are O(K^3/w^3) of them. get O(K^3/w) M2M flops. O(N/w log(N)), grows even slower with increasing w.

Have a study of interaction rank growth being bounded for a fixed accuracy, numerical verification of directional admissibility.


## Randomised construction of separated representation.

1. Sample sources and targets to at least a couple of points per wavelength. For targets no need to sample points outside of ball containing far field boxes

$$
A_{ij} = e^{2\pi i|x_i-y_i|}/|x_i-y_i|
$$

By theorem this can be factorised into a low rank approximation.

Let A_1 be a submatrix containing randomly selected columns, constant multiple of optimal rank cols

Perform QR (with permutation) column pivoted

$$
A_1 P_1 = Q_1 R_1
$$

Remove corresponding elements of R_1 smaller than epsilon,i.e. truncate

$$
A_c = Q_c R_c
$$

Q_c appx spans column space of A, these columns are denoted $y_i^c$

Do the same with the rows, denoted $x_i^c$

Therefore, as these matrices span the col and row spaces of A with proscribed accuracy from the truncations

$$
|A - Q_c M Q_r^*| = O(\epsilon)
$$

This can be very costly to get directly as A is massive.

Have a heuristic method to keep increasing number of samples until error threshold is met.

Using this 'pseudo-skeletal'

$$
|A - A_c (R_c)^\dagger M (R_r^*)^\dagger A_r| = O(\epsilon)
$$

We arrive at an approximation

$$
|A - A_c D(R_r^*)^\dagger A_r| = O(\epsilon)
$$

D has O(T(e)) rows/columns,

$$
\left | \frac{e^{2\pi i |x-y|}}{|x-y|} -\sum_{p, q} \frac{e^{2\pi i |x-y_p^c|}}{|x-y_p^c|} \cdot d_{p, q} \cdot \frac{e^{2\pi i |x_q^c-y|}}{|x_q^c-y|} \right|
$$

for any source/target particle set sampled appropriately. So only things we need to store are the skeleton points used for sampling and the small matrix D.

Due to the uniqueness and existence properties of Dirichlet boundary value problem for Helmholtz, only need to sample on enclosing surface of boxes.

- Close to optimal numerical rank results from SVDs.

- suggests that we can reproduce potential in this direction/sampling, with that produced by those at sampled Y points with given densities. These are called the directional (outgoing densities) - directional multipoles.

These can be computed only with kernel evaluations.

-