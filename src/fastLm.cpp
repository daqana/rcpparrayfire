// -*- mode: C++ -*-
//
// fastRNG.cpp: simple but fast lm() alternative using ArrayFire
//
// Copyright (C) 2017 Ralf Stubner (R Institute GmbH)
//
// This file is part of RcppArrayFire.
//
// RcppArrayFire is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// RcppArrayFire is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RcppArrayFire.  If not, see <http://www.gnu.org/licenses/>.

#include <RcppArrayFire.h>

//' Fast and simple linear model
//' @details Single precision floats are used since not all devices support double precision.
//' @param X  a model matrix
//' @param y a vector containing the explained variable
//' @return \code{fastLmPure} returns a list with three components:
//' \describe{
//'   \item{\code{coefficients}}{a vector of coefficients}
//'   \item{\code{stderr}}{a vector of the (estimated) standard errors of the coefficient estimates}
//'   \item{\code{df.residual}}{a scalar denoting the degrees of freedom in the model}
//' }
//' @export
// [[Rcpp::export]]
Rcpp::List fastLmPure(RcppArrayFire::typed_array<f32> X, RcppArrayFire::typed_array<f32> y) {
    dim_t n = X.dims(0);
    dim_t k = X.dims(1);

    // solve OLS via X'X beta = X' y
    af::array tXX = af::matmulTN(X, X);
    af::array tXy = af::matmulTN(X, y);
    af::array coef = af::solve(tXX, tXy);

    // residuals
    af::array res = y - af::matmul(X, coef);

    // standard errors of residuals
    double s2 = (af::dot(res, res)).scalar<float>() / (n-k);
    af::array std_err = af::sqrt(s2 - af::diag(af::inverse(tXX)));

    return Rcpp::List::create(
        Rcpp::Named("coefficients") = coef,
        Rcpp::Named("stderr") = std_err,
        Rcpp::Named("df.residual") = n - k
    );
}
