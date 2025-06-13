#include "gemm_mkl_oneapi.h"
#include <buffer.hpp>
#include <oneapi/mkl.hpp>
#include <vector>

std::vector<float> GemmMklONEAPI(const std::vector<float> a,
                                 const std::vector<float> b,
                                 size_t size,
                                 sycl::device device) {
  std::vector<float> ans(size * size, 0.0f);

  sycl::queue queue(device);

  {
    sycl::buffer<float> buf_a(a.data(), a.size());
    sycl::buffer<float> buf_b(b.data(), b.size());
    sycl::buffer<float> buf_ans(ans.data(), ans.size());

    auto transA = oneapi::mkl::transpose::nontrans;
    auto transB = oneapi::mkl::transpose::nontrans;

    oneapi::mkl::blas::row_major::gemm(
        queue,
        transA, transB,
        size, size, size,
        1.0f,
        buf_a, size, 
        buf_b, size, 
        0.0f,
        buf_ans, size 
    );
  }

  return ans;
}
