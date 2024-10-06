
N-body Methods Contributed by Rio Yokota and Mustafa AbdulJabbar



- Arithmetic intensity of inner kernel of N-body method

- $O(N^2)$ kernel evaluations, distance requires 10 flops per kernel eval, 3 subs, 3 squares 2 additions, 1 sqrt, 1 inverse, but really depends on the kernel. So not sure where 20 comes form..

- number of data loaded, 3D kernel, is 3N + 3N + 1N -> coordinates + densities = 7N

$$
O(\frac{11N}{7})
$$

arithmetic intensity. nicely linearly increasing with N.

Compared to matrix multiplication

$$
O(\frac{2N^3}{2N^2}) = O(N)
$$

Comparable/slightly higher to evaluate Laplace kernel (thank naive) matrix multiplication.

- Other than this, it's a useful example of using SIMD for P2P with explicit codes.

- Very small problem sizes < 50k particles tested.
- parallelised inner and outer loops of OpenMP vs explicit SIMD