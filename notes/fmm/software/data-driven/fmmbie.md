# EXTREME SCALE FMM-ACCELERATED BOUNDARY INTEGRAL EQUATION SOLVER FOR WAVE SCATTERING

- Abduljabbar et. al. 2019

- Use exafmm/fmm3d - exafmm for high frequency part
- task based tree traversal
- Is open source, not clear how to use it though, lacking good docs and examples
- architecture specific communication and partitioning algorithms
- weak scalability O(log p), theretical optimal
- demonstrate on soft scattering acoustic
- test to 1e-4 accuracy, relative to l2 norm vs relative error.
- 

- M. Abduljabbar, M. Al Farhan, R. Yokota, and D. Keyes, Performance evaluation of computation and communication kernels of the fast multipole method on Intel manycore architecture, in Euro-Par 2017: Parallel Processing, Lecture Notes in Comput. Sci. 10417, Springer, Cham, 2017, pp. 553--564.
    - Reference on how parallelism is obtained from FMM
    - actually also contains a chandramowlishwaram paper on performance evaluation, and is useful.


- Efficient fast multipole method for low-frequency scattering
    - Darve, Have
    - stable plane wave expansion for helmholtz FMM

- 2 billion dofs
- github link is broken

- Wrap extra functionality to exafmm

- TLP
    - maximising TLP works well with dual tree traversal approach
    - R. Yokota, An FMM based on dual tree traversal for many-core architectures, J. Algorithms Comput. Tech., 7 (2013), pp. 301--324.
[52]
    - sensitive to granularity, i.e. minimum cell-cell interactions to spawn a task
    - have a formulation that fills cache


- In distributed memory
    - the domain has to be decomposed to maximise local computation (near field), while minimising the volume of global communications
    - have to partition so that large amounts of computation can occur between communication events

    - their domain decomposition is based on ORB modified to balance weight in terms of compute and communication
    - graph partitioning library\

- M. Abduljabbar, G. S. Markomanolis, H. Ibeid, R. Yokota, and D. Keyes, Communica- tion reducing algorithms for distributed hierarchical N-body problems with boundary distri- butions, in High Performance Computing, Lecture Notes in Comput. Sci. 10266, Springer, Cham,
    - Introduction of HSDX communication pattern

1. use dist graphs for adjhacent nodes, physically adjacent
2. perform communication all to all with neighbouring ranks
3. 

- Overwhelmingly dominated by evaluating P2P for helmholtz

