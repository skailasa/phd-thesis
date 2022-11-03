import numba
import numpy as np

@numba.njit(cache=True, parallel=True)
def multithreading(A):
    # consider an A as an nxn matrix
    # This is a situation that can lead
    # to thread oversubscription unless
    # Numpy is configured to run single
    # threaded.
    for _ in numba.prange(10):
         B = A @ A

