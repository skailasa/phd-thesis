A sparse octree gravitational N-body code that runs entirely on the GPU processor

Jeroen Bédorfa,⇑, Evghenii Gaburov b,a, Simon Portegies Zwart a

- entirely on GPU
- 2.8 million particles per second
- weakly adaptive

- top down 'range search' method for particle binning.

The GPU can contain a large number of cores, because it has fewer resources allocated to control logic compared to a general purpose CPU

- nice phrasing
    For algorithms with few data dependencies, such as direct N-body simulations, programming the GPU is relatively straightforward.

- Implemented in 'Bonsai' no longer maintained, introduces a number of algorithms that are applicable to non-laplace problems.

use masks over morton keys to group into tree
    - a good example of linearising the tree data structure.

- Bonsai is an N log N tree code, not an FMM
 3 digits of accuracy in their codes, well often two digits
 