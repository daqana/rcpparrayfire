// we only include RcppFire.h which pulls Rcpp.h in for us
#include "RcppFire.h"

// via the depends attribute we tell Rcpp to create hooks for
// RcppFire so that the build process will know what to do
//
// [[Rcpp::depends(RcppFire)]]

// RcppFire needs C++11
// add the following comment when you export your
// C++ function to R via Rcpp::SourceCpp() 
// [[Rcpp::plugins(cpp11)]]

// simple example of creating two matrices and
// returning the result of an operatioon on them
//
// via the exports attribute we tell Rcpp to make this function
// available from R
//
// [[Rcpp::export]]
af::array rcppfire_hello_world() {
	af::array m1 = af::identity(3, f32);
	af::array m2 = af::identity(3, f32);

    return m1 + 3 * (m1 + m2);
}


// another simple example: outer product of a vector, 
// returning a matrix
//
// [[Rcpp::export]]
af::array rcppfire_outerproduct(const RcppFire::typed_array<f32>& x) { // NOTE: There is no type like colvec in ArrayFire.
	af::array m = x * x.t();
    return m;
}

// and the inner product returns a scalar
//
// [[Rcpp::export]]
double rcppfire_innerproduct(const RcppFire::typed_array<f32>& x) { // NOTE: Here is too. We suppose the x to be a column vector.
    double v = (x.t() * x).scalar<float>();
    return v;
}


// and we can use Rcpp::List to return both at the same time
//
// [[Rcpp::export]]
Rcpp::List rcppfire_bothproducts(const RcppFire::typed_array<f32> & x) {
	af::array op = x * x.t();
    double    ip = (x.t() * x).scalar<float>();
    return Rcpp::List::create(Rcpp::Named("outer")=op,
                              Rcpp::Named("inner")=ip);
}
