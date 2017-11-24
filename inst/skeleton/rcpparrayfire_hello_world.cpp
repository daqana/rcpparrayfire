// we only include RcppArrayFire.h which pulls Rcpp.h in for us
#include "RcppArrayFire.h"

// via the depends attribute we tell Rcpp to create hooks for
// RcppFire so that the build process will know what to do
//
// [[Rcpp::depends(RcppArrayFire)]]

// RcppArrayFire needs C++11
// add the following comment when you export your
// C++ function to R via Rcpp::SourceCpp()
// [[Rcpp::plugins(cpp11)]]

// simple example of creating two matrices and
// returning the result of an operation on them
//
// via the exports attribute we tell Rcpp to make this function
// available from R
//
// [[Rcpp::export]]
af::array rcpparrayfire_hello_world() {
	af::array m1 = af::identity(3, 3, f32);
	af::array m2 = af::randn(3, 3, f32);

    return m1 + 3 * (m1 + m2);
}


// another simple example: outer product of a vector,
// returning a matrix
//
// [[Rcpp::export]]
af::array rcpparrayfire_outerproduct(const RcppArrayFire::typed_array<f32>& x) { // NOTE: There is no type like colvec in ArrayFire.
	return af::matmulNT(x, x);
}

// and the inner product returns a scalar
//
// [[Rcpp::export]]
double rcpparrayfire_innerproduct(const RcppArrayFire::typed_array<f32>& x) { // NOTE: Here is too. We suppose the x to be a column vector.
    return (af::dot(x, x)).scalar<float>();
}


// and we can use Rcpp::List to return both at the same time
//
// [[Rcpp::export]]
Rcpp::List rcpparrayfire_bothproducts(const RcppArrayFire::typed_array<f32> & x) {
	af::array op = rcpparrayfire_outerproduct(x);
    double    ip = rcpparrayfire_innerproduct(x);
    return Rcpp::List::create(Rcpp::Named("outer")=op,
                              Rcpp::Named("inner")=ip);
}
