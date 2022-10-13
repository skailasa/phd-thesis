/*
 * STRUMPACK -- STRUctured Matrices PACKage, Copyright (c) 2014, The
 * Regents of the University of California, through Lawrence Berkeley
 * National Laboratory (subject to receipt of any required approvals
 * from the U.S. Dept. of Energy).  All rights reserved.
 *
 * If you have questions about your rights to use or distribute this
 * software, please contact Berkeley Lab's Technology Transfer
 * Department at TTD@lbl.gov.
 *
 * NOTICE. This software is owned by the U.S. Department of Energy. As
 * such, the U.S. Government has been granted for itself and others
 * acting on its behalf a paid-up, nonexclusive, irrevocable,
 * worldwide license in the Software to reproduce, prepare derivative
 * works, and perform publicly and display publicly.  Beginning five
 * (5) years after the date permission to assert copyright is obtained
 * from the U.S. Department of Energy, and subject to any subsequent
 * five (5) year renewals, the U.S. Government is granted for itself
 * and others acting on its behalf a paid-up, nonexclusive,
 * irrevocable, worldwide license in the Software to reproduce,
 * prepare derivative works, distribute copies to the public, perform
 * publicly and display publicly, and to permit others to do so.
 *
 * Developers: Pieter Ghysels, Francois-Henry Rouet, Xiaoye S. Li.
 *             (Lawrence Berkeley National Lab, Computational Research
 *             Division).
 *
 */
#ifndef FRONTAL_MATRIX_GPU_HPP
#define FRONTAL_MATRIX_GPU_HPP

#include "FrontalMatrixDense.hpp"

#if defined(STRUMPACK_USE_CUDA)
#include "dense/CUDAWrapper.hpp"
#else
#if defined(STRUMPACK_USE_HIP)
#include "dense/HIPWrapper.hpp"
#endif
#endif

namespace strumpack {

  template<typename scalar_t, typename integer_t> class LevelInfo;

  namespace gpu {
    template<typename scalar_t> struct FrontData;
    template<typename scalar_t> struct FwdSolveData;
  }


  template<typename scalar_t,typename integer_t> class FrontalMatrixGPU
    : public FrontalMatrix<scalar_t,integer_t> {
    using F_t = FrontalMatrix<scalar_t,integer_t>;
    using FG_t = FrontalMatrixGPU<scalar_t,integer_t>;
    using DenseM_t = DenseMatrix<scalar_t>;
    using DenseMW_t = DenseMatrixWrapper<scalar_t>;
    using SpMat_t = CompressedSparseMatrix<scalar_t,integer_t>;
    using LInfo_t = LevelInfo<scalar_t,integer_t>;

  public:
    FrontalMatrixGPU(integer_t sep, integer_t sep_begin, integer_t sep_end,
                     std::vector<integer_t>& upd);
    ~FrontalMatrixGPU();

    void release_work_memory() override;

    void extend_add_to_dense(DenseM_t& paF11, DenseM_t& paF12,
                             DenseM_t& paF21, DenseM_t& paF22,
                             const F_t* p, int task_depth) override;

    void multifrontal_factorization(const SpMat_t& A,
                                    const SPOptions<scalar_t>& opts,
                                    int etree_level=0,
                                    int task_depth=0) override;

    std::unique_ptr<GPUFactors<scalar_t>> move_to_gpu() const override;

    void multifrontal_solve(DenseM_t& b,
                            const GPUFactors<scalar_t>* gpu_factors)
      const override;

    void forward_multifrontal_solve(DenseM_t& b, DenseM_t* work,
                                    int etree_level=0, int task_depth=0)
      const override;
    void backward_multifrontal_solve(DenseM_t& y, DenseM_t* work,
                                     int etree_level=0, int task_depth=0)
      const override;

    void extract_CB_sub_matrix(const std::vector<std::size_t>& I,
                               const std::vector<std::size_t>& J,
                               DenseM_t& B, int task_depth) const override {}

    std::string type() const override { return "FrontalMatrixGPU"; }

#if defined(STRUMPACK_USE_MPI)
    void
    extend_add_copy_to_buffers(std::vector<std::vector<scalar_t>>& sbuf,
                               const FrontalMatrixMPI<scalar_t,integer_t>* pa)
      const override;
#endif

  private:
    std::unique_ptr<scalar_t[]> host_factors_, host_Schur_;
    DenseMW_t F11_, F12_, F21_, F22_;
    std::vector<int> pivot_mem_;
    int* piv_ = nullptr;

    FrontalMatrixGPU(const FrontalMatrixGPU&) = delete;
    FrontalMatrixGPU& operator=(FrontalMatrixGPU const&) = delete;

    void front_assembly(const SpMat_t& A, LInfo_t& L,
                        char* hea_mem, char* dea_mem);
    void factor_small_fronts(LInfo_t& L, std::size_t small_fronts,
                             gpu::FrontData<scalar_t>* fdata,
                             const SPOptions<scalar_t>& opts);
    // void factor_large_fronts(LInfo_t& L,
    //                          std::vector<gpu::BLASHandle>& blas_handles,
    //                          std::vector<gpu::SOLVERHandle>& solver_handles,
    //                          std::vector<gpu::Stream>& streams,
    //                          const SPOptions<scalar_t>& opts);
    // void factor_largest_fronts(LInfo_t& L,
    //                            std::size_t small_fronts,
    //                            std::vector<gpu::BLASHandle>& blas_handles,
    //                            std::vector<gpu::SOLVERHandle>& solver_handles,
    //                            std::vector<gpu::Stream>& streams,
    //                            gpu::Stream& copy_streams, scalar_t* pin,
    //                            const SPOptions<scalar_t>& opts);

    void split_smaller(const SpMat_t& A, const SPOptions<scalar_t>& opts,
                       int etree_level=0, int task_depth=0);

    void fwd_solve_phase2(DenseM_t& b, DenseM_t& bupd,
                          int etree_level, int task_depth) const;
    void bwd_solve_phase1(DenseM_t& y, DenseM_t& yupd,
                          int etree_level, int task_depth) const;


    void rhs_to_contig(LInfo_t& L, const DenseM_t& b, scalar_t* bptr) const;
    void rhs_from_contig(LInfo_t& L, DenseM_t& b, const scalar_t* bptr) const;

    void assemble_rhs(int nrhs, LInfo_t& L, scalar_t* db, scalar_t* dbupd,
                      scalar_t* old_dbupd, char* dea_mem, char* hea_mem,
                      std::size_t mem_size) const;
    void extract_rhs(int nrhs, LInfo_t& L, scalar_t* dy, scalar_t* dyupd,
                     scalar_t* old_dyupd, char* dea_mem, char* hea_mem,
                     std::size_t mem_size) const;

    void fwd_solve_gpu(DenseM_t& b, DenseM_t* work,
                       const GPUFactors<scalar_t>* gpu_factors) const;
    void fwd_small_fronts(int nrhs, LInfo_t& L,
                          gpu::FrontData<scalar_t>* fdata,
                          gpu::FrontData<scalar_t>* dfdata,
                          scalar_t* dL, int* dpiv,
                          scalar_t* db, scalar_t* dbupd) const;
    void fwd_large_fronts(int nrhs, LInfo_t& L, scalar_t* dL, int* dpiv,
                          int* derr, scalar_t* db, scalar_t* dbupd,
                          std::vector<gpu::BLASHandle>& blas_handles,
                          std::vector<gpu::SOLVERHandle>& solver_handles)
      const;


    void bwd_solve_gpu(DenseM_t& y, DenseM_t* work,
                       const GPUFactors<scalar_t>* gpu_factors) const;
    void bwd_small_fronts(int nrhs, LInfo_t& L,
                          gpu::FrontData<scalar_t>* fdata,
                          gpu::FrontData<scalar_t>* dfdata,
                          scalar_t* dU, scalar_t* dy, scalar_t* dyupd) const;
    void bwd_large_fronts(int nrhs, LInfo_t& L, scalar_t* dU,
                          scalar_t* db, scalar_t* dbupd,
                          std::vector<gpu::BLASHandle>& blas_handles,
                          std::vector<gpu::SOLVERHandle>& solver_handles)
      const;

    using F_t::lchild_;
    using F_t::rchild_;
    using F_t::dim_sep;
    using F_t::dim_upd;

    template<typename T,typename I> friend class LevelInfo;
  };

} // end namespace strumpack

#endif // FRONTAL_MATRIX_GPU_HPP
