 Fast kernel summations in high dimensions

 - Linear inference methods such as SVM and dimension reduction methods such as PCA can be efficiently generalised to non-linear methods by replacing inner products with kernel evaluations.
 - ML problems characterised by high dimensional inputs.

 - Can roughly group methods into three categories

 - analytic
    - taylor or kernel dependent special funtion expansions are used to approximate the far field

 - semi analytic
    - kiFMM an example of this, rely only on kernel evaluatoins, but low rank construction relies on the analytical properties of the underlying kernel - e.g. kiFMM requires that the underlying kernel is a Green's function o f a PDE

 - algebraic
    - purely rely on evaluating kernels.
    - Martinsson Rokhlin 2011 An accelerated kernel independent fast multipole method in one dimension