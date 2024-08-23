- no all to all communication is required for optimal FMM implementations which instead can be shown (on paper) to scale as O(log P), if implemented in a certain manner.

- At time of writing H matrix software was mostly toolboxes for algorithmic experimentation - I don't think that's true any longer with Borm's work on distributed H2 matrix.

- The scalable solvers of that time use global synch, e.g in dot product (inner product) and won't survive to billions of threads.

- FMM is a geometric version of the H2, i.e. partitions physical space rather than working on the matrix entries - but in practice this is equivalent to kiFMM, which represents the matrix entries and applies compression to them.

- Analytical FMM is matrix free, not sure why they think this results in lower communication costs than H2/algebraic FMM, as same data will have to be communicated.

Open questions of interest
- How should algorithmic hierarchy be adapted to architectural hierarchy in practice.
- In general natural granularities (FMM expansion degree, number of threads in GPU warp, and size of kiFMM bases and capcities of various levels of cache) will not match - should therefore prefer cache-oblivious implementations.
- What is the achievable asynchronicity of the communications of kiFMM in practice - my algorithm requires only a single communication step.
