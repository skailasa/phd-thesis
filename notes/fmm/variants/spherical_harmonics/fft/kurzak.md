# Fast multipole methods for particle dynamics


State of the art are the methods referred to as Fourier- based Ewald summation methods. Representative of this group is the particle–particle particle–mesh method, PPPM or P3M

- Big constants under linear complexity of FMM reference
    - T.C. Bishop, R.D. Skeel, K. Schulten. Difficulties with multiple time stepping and fast multipole algorithm in molecular dynamics. J. Comput. Chem., 18, 1785 (1997)
    - S. Aluru. Greengard’s N-body algorithm is not order N. SIAM J. Sci. Comput., 17, 773 (1996)

It was even claimed that in comparison to the P3M method “FMM can only become faster at some unphysical size N . 1060” [62].
    E.L. Pollock, J. Glosli. Comments on P3M, FMM, and the Ewald method for large periodic coulombic systems. Comput. Phys. Commun., 95, 93 (1996).

- interactions between sets of particles and all of their infinite periodic images.

- express as short/long range force components. The latter is calculated using a regular grid and the FFT. Becomes O(n log N) - at this time, was popular in MD.


The milestones on the road to FMM were the papers by Appel [7] and Barnes and Hut [8].

- Representation of basis in 'solid harmonics'

Spherical harmonics are functions defined on the surface of a sphere (in spherical coordinates). They represent angular components of solutions to Laplace's equation (or wave equation) in three dimensions. Physically, spherical harmonics describe the angular part of fields (like gravitational, electric, or quantum mechanical wave functions) that are naturally suited to spherical symmetry, such as those found in atoms, planets, or stars.

Solid harmonics extend spherical harmonics into three-dimensional space. They are functions that depend on the full three-dimensional coordinates, not just the angles. They include a radial part (which depends on the distance from the origin) combined with the angular part (which is described by the spherical harmonics).



Point and shoot was invented by White and Head-Gordon.
    - C.A. White, M. Head-Gordon. Rotating around the quartic angular momentum barrier in fast multipole method calculations. J. Chem. Phys., 105, 5061 (1996).


-- GG and Rokhlin introduced FFT for M2L, 'perfected by elliot and board'
    - L. Greengard, V. Rokhlin. On the efficient implementation of the fast multipole algorithm. Tech. Report RR-602, Yale University, Department of Computer Science, New Haven, CT (1988).
    - W.D. Elliott, J.A. Board Jr.. Fast Fourier transform accelerated fast multipole algorithm. SIAM J. Sci. Comput., 17, 398 (1996).


- requires convolution grid, zero padding to go from circular to linear convolution.
- largely discuss the flops requirement, from scaling/padding etc, rather than low throughput.

- Requirement for scaling to unit box to avoid numerical stability issues, addressed by Elliot and Board for high expansion orders with block decomposition approach.

- GG and Rokhlin introduced plane wave/exponential expansion, described in @d Hrycak and Rokhlin and 3D in cheng paper.

is only used as an intermediate representation of electrostatic field for the duration of the translation operation. The

They give a formula (7.8) for the diagonal transformation of the multipole to local coefficients in expontential form.

By scaling all M2L to same level, can be performed at once separate to l2l and not directly in the downward pass.

Therefore, can do all diagonal / FFT at once.


- In MD highly non-uniform distributions are uncommon and there is little justification for the overhead associated with the adaptive FMM algorithm.

- may be handy though for things like gas-surface interactions and astrophysical stellar dynamics.

- Actually, should come back to as shows applications of FMM to molecular dynamics

Other performance techniques

- Using spherical blobs and MAC based on these can improve size of interaction lists with same error bound.

- 8, 4, 2 - stencil - similar to child to parent to child V list interactions in Gumerov is suggested by Elliot and Board too.


It is still a remarkable gain in performance resulting in the number of multipole interactions dropping down from 651 to 315 for the spherical region equivalent to the classic separation of two cells.

- Also a comment on using symmetries available in interaction lists, i.e. can flip signs and positions/conjugations and get m2l for a bunch of directions in one go.

- Constant scaling of all multipole coefficients actually really slow, as well as the fact that they scale coefficient data reather than opreators.

- Their attempts at parallelisation

[47] J. Kurzak, B.M. Pettitt. Communications overlapping in fast multipole particle dynamics methods. J. Comput. Phys., 203, 731 (2005).
[48] J. Kurzak, B.M. Pettitt. Massively parallel implementation of a fast multipole method for distributed memory machines. J. Parallel Distrib. Comput., 65, 870 (2005).

