Optimizing the multipole-to-local operator in the fast multipole method for graphical processing units

Toru Takahashi1,*,†, Cris Cecka2, William Fong3 and Eric Darve4 1

- one of the few examples of optimising the dense matrix vector product.

Yokota et al. implemented the FMM and a variant (pseudo particle multipole method) for the
Laplace kernel on a PC cluster with 256 GPUs [18].
    Yokota R, Narumi T, Sakamaki T, Kameoka S, Obi S, Yasuoka K. Fast multipole methods on a cluster of GPUs for the meshless simulation of turbulence. Computer Physics Communications 2009; 180(11):2066–2078.

Gumerov - Their elaborate M2L improves on the original M2L on CPU, but it was chal- lenging to obtain an efficient implementation on GPU

Lashuk - do diagonal translation of fft on GPU, low arithmetic intensity.

- uniform trees
- inspired by Coualud paper on SVD
    - Coulaud O, Fortin P, Roman J. High performance BLAS formulation of the multipole-to-local operator in the fast multipole method. Journal ofComputational Physics 2008; 227(3):1836–1862.

AGPU contains multiple streaming multiprocessors (SMs), which are run as single instruction multiple data (SIMD) processors and consist of eight scalar processors (SPs) with 32-bit registers, shared memory, and an instruction unit.

Each SP runs a thread

a predefined number of threads are aggregated in a thread-block. Any thread within a thread-block can be identified with its thread ID,

If two or more threads belong to the same thread-block, the threads can share data via shared memory on the SM.

accomplished by being able to synchronize threads of a thread-block at any time

Finally, a prescribed number of thread-blocks are aggregated in a grid

Although all threads of a grid have access to device memory, it cannot be used to communicate between the threads because there is no synchronization between thread-blocks.

In hardware, an SM decomposes a thread-block into groups of 32 parallel threads called warps.If32threadsinawarp execute one common instruction, the execution time is the minimum (e.g., 32 single-precision floating-point add, multiply, or multiply–add (MAD) instructions can be executed in 4 clock cycles).

In hardware, an SM decomposes a thread-block into groups of 32 parallel threads called warps.If32threadsinawarp execute one common instruction, the execution time is the minimum (e.g.,

Otherwise, the 32 threads diverge (i.e., instructions are executed serially or serialized by the relevant threads), which results in lower performance

. Therefore, it is important to choose the size of the thread-block as a multiple of warp-size (32)

Roughly speaking, threads in a warp
should read from and write to contiguous addresses in memory for coalesced access.

Similarly, threads in a half-warp (either the first or second half of a warp) can efficiently access data in shared memory

- Have to optimise read from CPU of translation matrix as this is the bottleneck, develop techniques to share the values of a read

In the second scheme, we block the loop over T and S by grouping eight sibling boxes into clus-
ters. Considering now a pair of clusters, many pairs .T, S/ share the same D-matrix. We therefore read a D-matrix and perform as many .T, S/ interactions as possible using this D-matrix.


In the third scheme, we block computations one step further by grouping clusters into chunks and
then performing the same optimization. That is, we load a D-matrix and perform as many .T, S/ interactions as possible within a chunk.

Similar to PVFMM approach

- may be redundant with batched blas implementations.


