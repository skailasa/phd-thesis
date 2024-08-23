- Exascale properties of FMM vs FFT (PVFMM vs their FFT code)
- This is useful, as it provides a reference for modern exascale ready FMM
    - Need to find more modern exascale FMM references with explicit timings, Rio Yokota papers are a good source as well as those from the Inria group who've taken quite a different approach.

- FFT is the method of choice for smooth source functions that require uniform resolution, however loses performance when there are highly localised features, in which case FMM and GMG take its place.

- Generically address Poisson solvers

- Must be able to scale to trillions of unknowns.

- TODO: Lookup algebraic and geometric multigrid.

- PVFMM uses chebyhsev polynomials at each leaf node to represent the sources f.

- Scaled up to 600 billion unknowns in their tests.

No other distributed memory FMM allows an arbitrary continuous $f$. Most existing codes are point FMMs.

- The chebyshev approximations are used to approximate continuous f.

- FMM can be used for constant coefficient problems on arbitrary geometries, but can also be extended to variable coefficients using volume integral equations
- TODO: See Dhairya thesis for this.

- parallel GMG is based on meshes derived from hexahedrons and adaptive octrees.

- Morton ordering for GMG allows a re-partition using a parallel scan and point to point communications - no 'interaction' lists to communicate, so embarrasingly parallel with simple communication scheme compared to FMM to achieve load balance.

- Does mean that the number of active processors has to become lower at coarser grids.


