Yet Another Fast Multipole Method without Multipoles—Pseudoparticle Multipole Method Junichiro Makino


The new method is similar to Anderson’s method, which uses the values of potential at discrete points to represent the potential field. However, for the same expansion order the new method is more accurate

- motivation is to avoid complex translation operators.

- The barnes hut tree code doesn't do M2L, it uses M2 particle, i.e. neighbouring particles don't share expansion, that's why it is more expensive.

- O(p^2) scaling for tree algorithms, as there's no translations involved. But O(p^4) for FMM due to translations, can be diagonalised, and also FFT to get O(p^2 log p), can also combine these things. Says that FFT only works well if large p, not clear why.

In Anderson’s method, all shifting and transla- tions are realized by evaluating the potential on the sample points on the sphere. Thus, all mathematics are confined into formulae (4) and (3).
3.
    - i.e. the expansion formulae derived from potential theory results.

In Anderson’s method, the multipole expansion ofthe potential due to a clump of particles is effectively expressed in terms of the values of potentials on a sphere surrounding the particles. The potential outside the sphere is given by the surface integral on that sphere, which is then approximated by the sum over sampling points. This method, though elegant, appears to be rather indirect.

alternative approach would be to use multiple particles to represent the multipole expansion. The basic idea here is to place small number of pseudoparticles which reproduce the multipole expansion of the original physical particles.

- He comes up with a new way of locating pseudo-particles in 3D.

In the case of FMM, we still have to specify the algorithms for the M2L part and L2L part. We can use either Anderson’s method or standard harmonic expansion


- Matches to true charges by describing boundary pseudo charges using fourier series, and matching terms with expressions from multipole expansion.

Our pseudoparticle method and Anderson’s method are quite similar. Both approximate
the multipole expansion by a function on a circle (two dimensions) or a sphere (three dimensions). The difference is that the value ofpotential is used in Anderson’s method and the mass distribution itself is used in our method

One practical advantage of our method is that the calculation of the M2L part, which is known to be the dominant part of the computation, is significantly simpler for our method. Therefore, the overall calculation speed for the same expansion order would be faster for our method

In our method, untruncated potential is used in the M2L part. This also introduces the high-order terms which are not in the original multipole expansion. However, this does not cause much degradation in accuracy, since here it is guaranteed that the contribution of the high-order terms is small.

