SkelFMM: A Simplified Fast Multipole Method Based on Recursive Skeletonization

it replaces analytic expansions by using an equivalent set of source points (‘skeleton points’) that replicates the effect of the original source points in the far field.

The algorithm is multi-level, compatible with adaptive trees, and does not require the interaction list

Instead, the algorithm only involves calculations between near-neighbors at every level of the algorithm.

For well separated boxes, the kernel matrix $A$ can be written as

$$
A_{ij} - L_i \tilde{A}_{ij} R_j + O(\epsilon)
$$

$A$ is $m \times m$, $L$ and $R$ are of $m \times k$, $k \times m$ and the middle one is $k \times k$

Use ID to approximate far-field interaction blocks for a given target box.

Replace the far-field points with a proxy surface.

- Skeletonise each box at a given level (can be done in paralllel)

- Well separated boxes interact via skeleton points, near neighbours are modified interactions, depending on the skeleton and redundnat indices with modified relationships specifed in equation 15

- Modified near neighbour interactions and unmodiefied interactions btween skeleton indices

- The way the structure the computation makes it regular in nature, despite operating on an adpative tree structure