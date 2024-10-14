AN IMPLEMENTATION OF THE FAST MULTIPOLE METHOD WITHOUT MULTIPOLES*

- As far as I can tell, the first kernel independent approach suggested in the literature.

- Early approach based on 'panel clustering' of charges over panels.

    - Z. P. NOWAK, Panel clustering technique for lifting potential flows in the three space di- mensions, in Panel Methods in Mechanics, J. Ballman, R. Eppler, and W. Hackbusch, eds., Notes in Numerical Fluid Mechanics, 1360, Vieweg-Verlag, Braunschewig, Wiesbaden, 1987

- Base their approximation on 'poisson's formula' This is a classical result in potential theory.

- The potential is harmonic outside of the support of the disk it's defined on.

$$
\Psi(r, \theta) = \kappa \log{r} + \frac{1}{2\pi} \int_0^{2\pi} \tilde{\Psi(a, s)} \left [ \frac{1-(\frac{a}{r})^2}{1-2\frac{a}{r} \cos((\theta - s) + (\frac{a}{r})^2)} \right ]ds
$$

disk of radius a, at origin, k is the sum of the charges kappa, r is diameter of evaluation point.

Used standard trap rule for integral, but unstable, so remedy this using a Fourier based technique in equation 12 to come up with a stable/accurate scheme.

- Call it the 'outer ring approximation' i.e. the multipole coefficients in this scheme.

Use kernel evaluations for M2M, similar to kifmm.

The above formulation is 2D, but he provides a 3D formulation based on Legendre functions.

- use linked list based tree and octree/quadtree.

- m2l is also based on kernel evaluations.

- Actually a really good point about the kernel independent approach
One of the big advantages of using outer and inner sphere approximations is the simplicity of the process of combining them. This is in contrast to the complicated formulas that must be used if the approximations are based on spherical harmonics.

L2L and M2L:
    If there is a zero in the pointer array location at a given level, then an inner ring approximation is constructed from a parent inner ring approximation and from the appropriate well-separated outer ring approximations. These approximations are combined by merely evaluating the potential they induce at the nodes of the inner ring approximation under construction.