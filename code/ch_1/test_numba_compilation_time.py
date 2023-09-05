import numba, numpy, time


@numba.njit()
def hello(src, b, c):

    tst = src @ src

n = 20
src = numpy.arange(n**2).reshape(n, n).astype(numpy.float64)
s = time.time()
hello(src, src, src)
print("Compilation time", time.time()-s)

s = time.time()
hello(src, src, src)
print("Runtime", time.time()-s)
