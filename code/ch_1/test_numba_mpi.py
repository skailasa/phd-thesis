import numba, numba_mpi, numpy, time

@numba.njit()
def hello(src, b, c):
    print(numba_mpi.rank(), numba_mpi.size())

    tst = src @ src


n = 5
src = numpy.arange(n**2).reshape(n, n).astype(numpy.float64)
s = time.time()
hello(src, src, src)
print("compilation time", time.time()-s)

s = time.time()
hello(src, src, src)
print("runtime time", time.time()-s)

