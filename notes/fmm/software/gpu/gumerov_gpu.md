
Fast multipole methods on graphics processors Nail A. Gumerov *, Ramani Duraiswami

- Use a different set of basis functions, real polynomial

- Need to verify where he gets the decomposition

$$
G(r, r_0) = \frac{1}{|r-r_0|} = \sum_{n=0}^\infty \sum_{m=-n}^n (-1)^n R_n^{-m}(r_0) S_n^m(r)
$$

where R are the local basis functions and S are the multipole basis functions, must be a theorem somewhere in the original FMM papers, i.e. local basis functions evaluated this way are the coefficients of the (singular) multipole expansion functions, therefore can avoid computing singular multipole expansions.

- Finds a recursive formula for computing the locals, which are real polynomials, and avoids spherical coordinate conversion which relies on special functions.

- obviously specialised to the Laplace case.

- Translation operators have $O(p^4)$ complexity if applied directly the translation matrices

- point and shoot (RCR decomposition)
    - initially introduced here
        - C.A. White, M. Head-Gordon, Rotation around the quartic angular momentum barrier in fast multipole method calculations, J. Chem. Phys. 105 (12) (1996) 5061–5067.
    In this decomposition, we first perform rotation of the reference frame to point the z axis towards the target, then perform coaxial translation along the rotated z axis, and then rotate the reference frame back
    - reduces to $O(p^3)$

- [4] H. Cheng, L. Greengard, V. Rokhlin, A fast adaptive multipole algorithm in three dimensions, J. Comput. Phys. 155 (1999) 468–498
    - reduce the number of M2L to 40 in 3D, using a different translation approach.
    - exponential representation, and a stencil that takes advantage of symmetries.

- Gumerov uses point and shoot + stencil

- There exist a number of boxes for which the translations can be made not to children, but to their collective parent., saves apprx 71 translations per box.

- retains error bound.

- Variable truncation numbers, but this is similar to doing an SVD and taking dominant singular values.

21 s for direct GPU calculation at this time for 500k points, this is way slower than modern CPU/GPU
