Geometry-Oblivious FMM for Compressing Dense SPD Matrices Chenhan

- SPD matrices, purely algebraic, no points, just requires matrix entries.

- Talk about crossover point, actually a useful metric I should put in the thesis.

- Construction O(N ln N), matvec at most of same complexity.
- Their approximation scheme cannot guarantee accuracy and complexity bound at same time.
- Since arbitrary SPD matrices may not admit good low rank approximations.
- Describe a hiearrachically compressible low-rank matrix as one that admits.

$$\tilde{K} \in \mathcal{H}$$

$$\tilde{K} = D + S + UV $$

- D is a block diagonal, every block is a H matrix, UV are low rank and S is sparse.

- Note hierarchical low rank structure is not invariant to row and column permutations, therefore any algorithm for constructing K tilde must first appropriately permute K, e.g. in FMM achieved via clustering points.

- Sparse correcitions S are constructed from nearest neighbour structure of input points.
- U, V are the translation operators.
- D are the self interactions.

- Generalises FMM ideas to compressing arbitrary SPD matrices

- Result, any SPD matrix corresponds to a Gram matrix of vectors in some unknown Gram/feature space. Matrix entries are inner products, used to define distances.

- Scheduling improves time drastically in comparison to level by level traversals.
    - in house tree scheduler.

- Compare with HODLR, STRUMPACK and ASKIT
- ASKIT is an algebraic FMM code.
    William B. March, Bo Xiao, Sameer Tharakan, Chenhan D. Yu, and George Biros. 2015. A kernel-independent FMM in general dimensions. In Proceedings ofSC15 (The SCxy Conference series). ACM/IEEE, Austin, Texas. http://dx.doi.org/10.1145/ 2807591.2807647
    William B. March, Bo Xiao, Chenhan Yu, and George Biros. 2015. An algebraic parallel treecode in arbitrary dimensions. In Proceedings ofIPDPS 2015 (29th IEEE International Parallel and Distributed Computing Symposium). Hyderabad, India. DOI:https://doi.org/10.1109/IPDPS.2015.86

- GoFMM supports multiple right hand sides which is useful for MC, optimisation and blocked krylov methods.


- Requires computing matrix entries, other ones like strumpack have inherent support for matrix-free compression


- Low rank approximations of arbitrary matriices from linear algebra
    - e.g. CUR, used in place of SVD where don't need as much accuracy.
    - made of a subset of data samples, basis is taken from columns and rows of A, ulike SVD taken in rotated space.
    - Nystrom based method
        Christopher Williams and Matthias Seeger. 2001. Using the Nyström method to speed up kernel machines. In Proceedings ofthe 14th Annual Conference on Neural Information Processing Systems. 682–688
    - ACA
    - Randomised methods

- Can be applied for H matrix approximations when D is non-zero, applying to off-diagonal

- creating U, V is computationally hard

- H2 and FMM better control for rank, as max rank of U anv V can grow linearly with N, especially in 3D

- HSS and H2 are both O(N) matvec, need to read up about this.