- The $N \times NN$ matrix arising out of FMM, can be represented as a larger $M \times M$ matrix where $M \approx 3N$
- while solving the larger extended sparse matrix, the fill-ins that arise in blocks correponding to well-separated clusters are hierarchically compressed.
- order of elimination is different from usual nested dissection approach

- The rank of non-overalpping (weak admissability) clusters is more or less constant in 1D,but no longer valid for singular green's functions of elliptic PDE in 2D and 3D, i.e. the interaction rank is no longer independent of N.
    - Grows as $O(\sqrt{N})$ in 2D and $O(N^\frac{2}{3})$ in 3D.
    - Rank - i.e. number of expansion terms is proportaional to surface area, can see in MFS kiFMM
    clearly, The surface area is directly proportaional to the number of points contained in each
    box, giving the result.
    - Also can see that it comes from the multipole expansions, which have their own estimates for approximate rank. - Need to see Gunnar martinsson book for analytical expansions rank, i.e. number of series terms.

- Dense covariance matrices arise in many applications
    - kalman filtering
    - statistics and machine learning