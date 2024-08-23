- Sketch of general idea

- Solution obtainable in $O(N)$

- Start with discretisation of a scalar elliptic BVP, with mesh size $h$ leading to a linear system

$$
L^h u^h = f^h
$$

where $N \propto 1/h^2$, e.g. boundary element scheme, where we have $O(N^2)$ due to density of matrix. Or iterative solver like Gauss-Seidel of the same complexity finite difference.

Idea, map to coarser grid $H$, then the residual term can be modelled as,

$$
L^H v^H = r^H
$$

where $v^h = u^h - u^h_{old}$ and the rhs is the residual with data.

Map to coarse grid, and interpolate solution back on finer grid,

$$
u^h_{new} = u^h{hold} + I^h_H v^H
$$

Use another coarse grid to approximate the coarse grid correction. and use relaxation on coarser and coarser grids, and interpolation back to finer grids.

- The coarse grid correction removes low-frequency errors (i.e. averages over these). Solving at the coarsest level is done with a direct solver.

- GMG and AMG, former rely on underlying mesh for constructing coarser levels, the latter work directly on the matrix structure with no knowledge of the underlying geometry. Keeping the matrix structure ends up in more memory than geometric multigrid, which can be thought of as matrix free. Morover operators can be easily modified at different levels, which can be necessary to conform to certain BCs.

- GMGs major disadvantage is having to construct hierarchical meshes, and is not black box (i.e. operate directly on matrix)

- Can use multigrid methods to build up approximate inverse (preconditioner), and then use a iterative method for computing the solution, e.g. CG.


