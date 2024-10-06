A hierarchical O(N log N) force-calculation algorithm

Josh Barnes & Piet Hut

- First hierarchical grouping given by Appel, using a tree structure to represent an N body problem.
Appel, A. SIAM J. Sci. statist. Comput. 6, 85-103 (1985).


- start at root, for a particle $p$ the force at p can be approximated. Let $l$ be the length of the cell being processed and $D$ the distance from the cell's centre of mass to p. if $l/D < \theta \sim 1$ then include the interaction between this cell and $p$ in the total being accumulated., otherwise subdivide into children.

- Once the tree is constructed, each internal node of the tree is associated with a center of mass (the weighted average of the positions of the particles in that region) and a total mass (the sum of the masses of the particles in that region).

If the distance between the particle and the region is large compared to the size of the region (i.e. 𝜃 is small enough), then all the particles in that region are approximated by their center of mass.

l/D ~ 1, corresponds to weak admissibility.

Inside boxes appx by centre of mass

- Fortran used to be an order of magnitude faster than other compilers...
