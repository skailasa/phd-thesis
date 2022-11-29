use rand::prelude::*;
use rand::SeedableRng;

use mpi::{
    environment::Universe,
    topology::UserCommunicator,
    traits::*
};

use rusty_tree::{
    distributed::DistributedTree,
};


fn main () {
    // Generate a set of randomly distributed points
    let mut range = StdRng::seed_from_u64(0);
    let between = rand::distributions::Uniform::from(0.0..1.0);
    let mut points: Vec<[PointType; 3]> = Vec::new();
    let npoints = 1000000;

    for _ in 0..npoints {
        points.push([
            between.sample(&mut range),
            between.sample(&mut range),
            between.sample(&mut range),
        ])
    }

    // Setup an MPI environment
    let universe: Universe = mpi::initialize().unwrap();
    let world: UserCommunicator = universe.world();
    let comm = world.duplicate();

    // Unbalanced
    let unbalanced: DistributedTree = DistributedTree::new(&points, false, &comm)

    // Balanced
    let balanced_tree: DistributedTree = DistributedTree::new(&points, true, &comm)
 
}
