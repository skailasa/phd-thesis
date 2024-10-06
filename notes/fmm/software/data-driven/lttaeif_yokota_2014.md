Data-Driven Execution of Fast Multipole Methods

Hatem Ltaief and Rio Yokota

- tackles load balancing problem
    - break time consuming steps up, and use QUARK runtime.
    - results in out of order execution.

- They 'inherently present load balancing isssues due to the irregularity of the data distribution and dynamic nature of the application'

A clever way to solve this dilemma is to record the work load from the previous time step and use it to repartition for the present step. Such strategies were first used in the early 90’s on both sheared memory architectures [28] and distributed memory architectures [40]. The basic idea of using information from the previous step to repartition the present step, can be used with any partitioning scheme such as orthogonal recursive bisection (ORB) [39], partitioning Morton/Hilbert keys [40], and graph based partitioning [34]. The

Since ORB always divides into equal number of particles (which could be weighted according to the previous work load) the resulting binary tree will be perfectly balanced, and there will be no adaptivity in the tree structure itself

Therefore, in terms of load balancing, this is an ideal tree structure.

The advantage of using cubic octrees is the direct correspondence between the proximity of the nodes in the tree and the geometrical proximity of the cells which they represent. This means Morton/Hilbert keys can be used to determine the geometrical location of the cell and vice versa.

Furthermore, the structured layout of cells permits the use of symmetry in the M2L kernels to reduce redundant computation/storage. However, load balancing adaptive octrees remains an open area of research [30, 13]i

Data-driven dynamic task scheduling can solve this issue by stealing work from busy threads,
while optimizing the data flow at the same time. Since moving data is relatively expensive compared to computing data, it is extremely important that the data movement is optimized. In the following section, we will give an overview of QUARK, which is a tool that does precisely what has been described above.


A parameter in a call can be decorated with the LOCALITY flag in order to tell the scheduler that the data item (parameter) should be kept in cache if possible. After a computational core (worker) executes that task, the scheduler will assign by-default any future task using that data item to the same core. Note that the work stealing can disrupt the by-default assign- ment of tasks to cores.

dual tree traversal is a method to find all pairs of well separated cells in the octree in O(N) time [14]. It is more general than the commonly used adaptive lists [12] because the cells need not be perfect cubes

The cells can actually be any shape as long as they are mutually exclusive and are grouped hierarchically

Furthermore, the definition of well-separateness can be adjusted more smoothly because the definition of neighboring cells is based on the distance instead of “how many cells to skip”

Different sized interaction lists as

This allows the exclusion of the corner cells, and yields a list that is closer to a sphere than a cube.

- There exists optimal granularities for tasks

The authors plan to extend this work with the StarPU [4] dynamic runtime, which schedules tasks
on x86 as well as on hardware accelerators (GPUs). Although it has a somewhat similar API than QUARK, the user has still to develop the appropriate kernels for the GPU and can let it up to the run- time to decide on which available resource, x86 or GPU, the task can be executed on. Moreover, StarPU provides a reduction operation, which could further improve our current implementation by adding another dimension of parallelism during the execution of the successive tasks seen in the non-mutual DAG representation. Finally, the authors will eventually tackle the distributed memory environment using the DAGuE