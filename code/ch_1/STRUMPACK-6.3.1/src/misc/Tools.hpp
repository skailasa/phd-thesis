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
#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <iomanip>
#include "StrumpackConfig.hpp"
#include "StrumpackParameters.hpp"
#include "dense/BLASLAPACKWrapper.hpp"
#if defined(STRUMPACK_USE_MPI)
#include "MPIWrapper.hpp"
#endif

namespace strumpack {

  inline bool mpi_root() {
#if defined(STRUMPACK_USE_MPI)
    MPIComm c;
    if (MPIComm::initialized())
      return c.is_root();
#endif
    return true;
  }

  template<typename T> class NoInit {
  public:
    using value_type = T;
    value_type* allocate(std::size_t n)
    { return static_cast<value_type*>(::operator new(n*sizeof(value_type))); }
    void deallocate(T* p, std::size_t) noexcept { ::operator delete(p); }
    //template <class U, class ...Args> void construct(U* /*p*/) { }
    template <class U, class ...Args> void construct(U* p, Args&& ...args) {
      ::new(p) U(std::forward<Args>(args)...);
    }
  };
  template <class T, class U> bool operator==
  (const NoInit<T>&, const NoInit<U>&) { return true; }
  template <class T, class U> bool operator!=
  (const NoInit<T>&, const NoInit<U>&) { return false; }


  template<typename scalar_t> class VectorPool {
  public:
#if defined(STRUMPACK_COUNT_FLOPS)
    ~VectorPool() {
      for (auto& v : data_) {
        STRUMPACK_SUB_MEMORY(v.size()*sizeof(scalar_t));
      }
    }
#endif
    std::vector<scalar_t,NoInit<scalar_t>> get() {
      std::vector<scalar_t,NoInit<scalar_t>> v;
#pragma omp critical
      {
        if (!data_.empty()) {
          v = std::move(data_.back());
          data_.pop_back();
        }
      }
      return v;
    }
    void restore(std::vector<scalar_t,NoInit<scalar_t>>& v) {
#pragma omp critical
      data_.push_back(std::move(v));
    }
  private:
    std::vector<std::vector<scalar_t,NoInit<scalar_t>>> data_;
  };


  // this sorts both indices and values at the same time
  template<typename scalar_t,typename integer_t>
  void sort_indices_values(integer_t *ind, scalar_t *val,
                           integer_t begin, integer_t end) {
    if (end > begin) {
      integer_t left = begin + 1, right = end;
      integer_t pivot = (begin+(end-begin)/2);
      std::swap(ind[begin], ind[pivot]);
      std::swap(val[begin], val[pivot]);
      pivot = ind[begin];
      while (left < right) {
        if (ind[left] <= pivot)
          left++;
        else {
          while (left<--right && ind[right]>=pivot) {}
          std::swap(ind[left], ind[right]);
          std::swap(val[left], val[right]);
        }
      }
      left--;
      std::swap(ind[begin], ind[left]);
      std::swap(val[begin], val[left]);
      sort_indices_values<scalar_t>(ind, val, begin, left);
      sort_indices_values<scalar_t>(ind, val, right, end);
    }
  }

  template<class T> std::string number_format_with_commas(T value) {
    struct Numpunct: public std::numpunct<char>{
    protected:
      virtual char do_thousands_sep() const{return ',';}
      virtual std::string do_grouping() const{return "\03";}
    };
    std::stringstream ss;
    ss.imbue({std::locale(), new Numpunct});
    ss << std::setprecision(2) << std::fixed << value;
    return ss.str();
  }

} // end namespace strumpack

#endif // TOOLS_H
