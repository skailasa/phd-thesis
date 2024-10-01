Communication Complexity of the Fast Multipole Method and its Algebraic Variants
Rio Yokota1, George Turkiyyah1, David Keyes1

- Likely to be the first to reach exascale.

- Its com- putationally expensive phases have extremely high flop/s to byte/s ratios, a data locality property known as “computational intensity” [38],

- Furthermore, no all-to-all communication is required in an optimal implementation of FMM in a distributed memory environment of P processes, and the O(log P) messages exchanged are permitted, among themselves, a high degree of concurrency and asynchronicity.

our existing code base has been engineered primarily to squeeze out as many floating point operations as possible. Instead, algorithms must now focus on squeezing out synchronizations, memory storage, and memory transfers, while extra flops on locally cacheable data represent small costs in time and energy.

- Bad and good news simultaneously lurk behind every aspect of the evolution of exascale ar-
chitecture. Programmers will have to explicitly control more of the data motion, since it carries the highest energy cost in the computational environmen


Vertical replication has generally been handled beneath the level of programmer concern. However, recently with the rolling of data in and out of accelerators, pro-
grammers have embraced this control, even if they bemoan the slow transmission speed of today’s channels.

computationally optimal methods tend to be storage-optimal because the amount of relevant data cannot be greater than that touched in executing the flops

today’s optimal hierarchical methods, FMM and H-matrices excel in concurrency, tolerance of asynchronicity, arithmetic intensity, and the ability to tune SIMT data sizes to natural boundaries in the hardware hierarchy.


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

