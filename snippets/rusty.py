from mpi4py import MPI
import numpy as np

from rusty_tree.distributed import DistributedTree

# Setup communicator
comm = MPI.COMM_WORLD

# Cartesian points at this process
points = np.random.rand(100000, 3)

# Generate a balanced tree
balanced = DistributedTree.from_global_points(points, True, comm)

# Generate an unbalanced tree
unbalanced = DistributedTree.from_global_points(points, False, comm)

# Trees map between points and the keys that they correspond to contain
point = balanced.points[0].head # grab a point
print(balanced[point]) # find the key that it maps

# Trees map between keys and the points they contain
key = balanced.keys[0].head # grab a point
print(balanced[key]) # find the points that this key contains

# Trees implement iterator protocol as well as slicing and indexing
# (without copy of underlying Rust data)
# Slice of 10 keys
key_slice = balanced.keys[:10]

# Slice of 10 points
point_slice = balanced.points[:10]

def foo(key):
    """Some key processor function"""
    pass

# Iterating in this way avoids copying data from Rust to Python
for key in key_slice:
    foo(key)

# Copy only performed when printing in Python
print(point_slice)
print(key_slice)