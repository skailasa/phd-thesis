<h1 align='center'> PhD Thesis </h1>

## Outline

The goal of this thesis was the implementation of a fully distributed, $O(N)$, fast-direct solver for the integral equations arising from Maxwell's equations for electromagnetism. The compute and memory requirements of these solvers requires careful consideration of the algorithmic and mathematical implementations required of these solvers. The main innovations presented in this thesis are: 

- (1) A flexible, Rust-based, software infrastructure for the __fast__, $O(N)$ forward **and** backward applications of integral operators that arise in the discretisation of numerous problems in science and engineering

- (2) Mathematical investigations for the optimal representations of various aspects of these solvers, with numerical verification of the performance of our choices.

Rust is chosen as it's a promising young programming language with excellent properties for high-performance computational science. Our codes are highly-portable and malleable, with fully Python APIs designed for accessability by the wider community of math/physics/engineering researchers without software expertise.

We demonstrate the performance of our solvers, and the ease of deploying them, with experiments scaling from local workstations all the way up to the latest petascale supercomputing clusters.

## Publications
- [PyExaFMM - Computing in Science and Engineering](https://github.com/betckegroup/pyexafmm-cise/)
- [Rusty Trees - SoftwareX](https://github.com/betckegroup/rusty-trees-softwarex)
- WIP: Formulation of Proxy Compression Method for different Boundary Integral Equations Based on RS-S


## Associated Software
- [PyExaFMM](https://github.com/exafmm/pyexafmm)
- [AdaptOctree](https://github.com/Excalibur-SLE/AdaptOctree)
- [Rusty Tree](https://github.com/rusty-fast-solvers/rusty-tree)
- [Hyksort](https://github/com/rusty-fast-solvers/hyksort)


## Presentations
- [Rust for Computational Science, Rust @ Imperial](https://mora.stream/event/34875)

## Posters
- [Painless-ish HPC with Rust+Python, SuperComputing 22]()

## Citatation

```bash
@phdthesis{Kailasa:PhDThesis:2024,
    author = {Srinath Kailasa},
    title = {{Computational Topics in the Solution of Integral Equations}},
    school = {University College London},
    address = {United Kingdom},
    year = {2024},
}
```
