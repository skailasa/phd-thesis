A pedestrian introduction to fast multipole methods

- Basically want a summary of the directional FMM's complexity estimate

$$
G(x, y) = \exp(2\pi i k |x-y|)/|x-y|
$$

$k$ is constant, large. In this analysis he assumes $N=O(k)$, sampled uniformly from somooth curve in R2. Wavelength is $1/k = \lambda$ which is also approximately the distance between the points (in order to be able to resolve them).

Consider a box B and its far field F(B): for the Helmholtz kernel, the numerical rank for the interaction between in fact scales like O(diam(B)/λ) - Rokhlin 2D paper

Therefore, the rank goes higher for larger boxes, and if B is a constant fraction of the domain, then the rank is O(k).

Hence M2L won't be effective as expense will grow with decreasing level.

Let B be a box with diameter sλ. We define WB,d to be a wedge in the direction of d, of distance s2λ away from B, and with an opening angle of size O(1/s). Hence, when B gets larger and larger, the wedge becomes further and further away quadratically with a smaller opening angle.

- This is proven to be low rank in more technical Ying papers

If we define F(B) now to be the set which is is the new near field N(B). The low-rank approximation actually used is very similar to the equivalent O(s2λ) away from B, then F(B) is a disjoint union of O(s) wedges {WB,d}. The complement of F(B)

Nesting property still holds between parents/children and their wedges.

Depth  = O(log N) = O(log k)

The algorithm starts from level with boxes of width
$\sqrt{k}\lambda$, because here the wedge is $k \lambda = 1$ away, so for large domains the far field for a given box is outside of the domain $[0, 1]^2$

- Don't understand the complexity argument. Look in original paper.

