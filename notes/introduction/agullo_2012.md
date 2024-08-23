- Pipelining the FMM over a runtime system
    - i.e. breaking up into concurrently scheduled tasks handled by Runtime.


- 200e6 unknowns in 50 seconds.

- 38 million unknowns in 13 seconds on Nehalem + 3 Fermi GPUs.

- TODO: How does this compare to Dask? Or other modern runtimes like Spark.

- StarPU takes care of coherency of data registered at runtime, take care of data movements and relieve burden of explicit data movement in something like MPI.

- Can also optimise for memory transfer to heterogenous system.



