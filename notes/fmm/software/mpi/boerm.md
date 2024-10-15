# Distributed H2-Matrices for Boundary Element Methods

While earlier efforts required the global tree structure of the H2-matrix to be stored in every node of the distributed system, the new approach needs only local multilevel information that can be obtained via a simple distributed algorithm, allowing us to scale to signif- icantly larger systems. Experiments show that this approach can handle very large meshes with more than 130 million triangles efficiently.

130 million triangle is like 490million points, very small

- demonstrate weak scaling up to this point, which is more interesting.

Although hierarchical matrices, and particularly H2-matrices, tend to be very efficient, handling very large systems still requires a large amount of memory and leads to long run-times.
    - still talking about large amounts of memory, rather than accesses in 2023

tau hat and sigma hat are indices of the basis functions supported in the target and source boxes.

- For commonly used surface meshes, the support of the basis functions has to lie in the target box i for all i in tau hat. This means that tau will vary in diameter and aspect ratio even on the same level of tree, depending on the mesh.

- Do not have option of regular boxes, like FMM, as working with basis functions rather than boxes.

- Not as easy to simply predict clusters on other nodes

## Distributed H2 matrices

- indices of the test functions and trial functions split among nodes, these subsets of indices on each node are non-overalapping partitions of all the test/trial functions ie. the domain.

- Writes out in block matrix form on page 14:8, each block treated as H2 matrix, each node contains multiple blocks. In fact each node is chosen to contain a single block row.

These blocks are like coarse octree leaves, and may need to be split if non-admissable, which needs to be checked between each interaction as cannot be done apriori as geometry dependent/basis functions.

- If admissible, use point to point, if not need to split into children and check again. But need to check on both source/target to communicate that split is required. He does this level by level, recursiing down the coarse tree structure.

- A voting procedure and an infinite loop to keep splitting blocks while inadmissible blocks (corresponding to 'coarse leaves') still exist.

## 2 . H2 matrices

$\tau, \sigma \in \mathbb{R}^d$ - axis parallel boxes. Has an example using Lagrange polynomials and interpolation points.

Cluster tree, again define.

$T_I$ - a tree with root $r$, vertices are subdomains of $\mathbb{R}^d$. Called a cluster tree for the index set I and basis functions $(\phi_i)_{i \in I}$ if

- assign a subset of the total index set to each vertex.

- the root $\hat{r} = I$.
- for all $t \in T_I$ $i \in \hat{\tau}$ we have $supp \phi_i \subseteq \tau$

the other conditions are that child indices don't intersect, and that all elements (nodes) of $\tau \in T_i$ are constructed uniquely from their children,

- Requier that $supp \phi_i \subseteq \tau$ for all $i \in \hat{\tau}$

- This means that because many commonly used surface meshes are not structured clusters will vary in diameter and aspect ratio even on same level of tree.

    - unstructured surface mesh - e.g. adaptive mesh, finer clusters of triangles vs larger ones

- However, could use regular surface mesh - and then it would be very similar to FMM style tree with regular boxes.

- It seems to be an implementation choice rather than a features of the method
    - but then again, the support of the basis functions for a sub-region must be contained in that sub-region. And this will only result in a uniform-ish tree if the sampling of each sub-region is uniform, and the indices are sampled uniformly. Hard to guarantee.

- Nodes cannot simply predict the clusters in other nodes, since they depend on the local geometry of the mesh that isn't available globally.



$p$ nodes connected by network. $I$ are test function indices and $J$ are trial functions, split among nodes, preferebly according to suitable subdomains. $\alpha$ is the subset of indices for a node $\alpha \in [1: p]$ by $I_\alpha \subseteq I$, same for trial function indices.

$\Gamma_\alpha$ is the union of suppports of trial/test functions at this node. All basis functions assinged to each node should intersect as little as possible with supports of other nodes.

Construct a block interaction matrix, and assign a row to each processor.
I.e. each processor is responsible for interactions between a given portion of the domain, and the rest of the domain. These are like coarse block leaves.

- He is doing a global all to all to find admissible blocks.

for each processor, he iterates over all row it contains and corresponding source/target clusters,  does division and sends the parents, and iterates until no more admissible boxes required/max level reached.

- So does a distribution of coarse geometry, similar to me, but refines at runtime to find admissible/inadmissable blocks - his version of ghost exchange.

But his communication routine is O(P^2), point to point won't scale. But he doesn't mention this.

After ghost exchange, can calculate required matrix operators easily, as can get interpolation points from boxes, and the polynomials coefficients are cheap to compute.

Does point to point, it seems, for near field.

- also does local to global split, it's weird that he can publish this as a new idea, when it's been done several years before by another community.

- But he actually creates the global nodes, and share them out among their descendants' containing nodes.

This means that multiple nodes contain overlapping nodes from global tree. He then appoints 'managers' responsible for each cluster's communication needs, similar to very old Lashuk approach.

- Also messy, as children of a cluster may have different shareholders than a parent.

and follow the convention that only the manager of a cluster is allowed to send and receive in- formation regarding this cluster. If the other shareholders need the information received by the manager, it can be provided efficiently by a broadcast operation.

I.e. similar to saying a given processor is responsible for each node in the global tree, and any depdentents can be contacted via broadcast for this data.

take advantage of redundancy in higher levels

- Doesn't seem aware of subcommunicators for collectives.

