// -*- mode: C++ -*-
//
// fastLm.cpp: simple but fast lm() alternative using ArrayFire
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
//' @details Single precision floats are used by default since not all devices support double precision.
//' @param X  a model matrix
//' @param y  a vector containing the explained variable
//' @param useDouble  use float or double internally
//' @return \code{fastLmPure} returns a list with three components:
//' \describe{
//'   \item{\code{coefficients}}{a vector of coefficients}
//'   \item{\code{residuals}}{the residuals, that is response minus fitted values}
//'   \item{\code{fitted.values}}{the fitted mean values}
//'   \item{\code{stderr}}{a vector of the (estimated) standard errors of the coefficient estimates}
//'   \item{\code{df.residual}}{a scalar denoting the degrees of freedom in the model}
//'   \item{\code{intercept}}{a boolean denoting if a model with intercept was fitted}
//' }
//' @export
// [[Rcpp::export]]
Rcpp::List fastLmPure(const Rcpp::NumericMatrix& X,
                      const Rcpp::NumericVector& y,
                      bool useDouble = false) {
    af::array _X;
    af::array _y;

    if (useDouble && !af::isDoubleAvailable(af::getDevice())) {
        useDouble = false;
        Rcpp::warning("Double precision is not available with current device.");
    }

    if (useDouble) {
        _X = Rcpp::as<RcppArrayFire::typed_array<f64> >(X);
        _y = Rcpp::as<RcppArrayFire::typed_array<f64> >(y);
    } else {
        _X = Rcpp::as<RcppArrayFire::typed_array<f32> >(X);
        _y = Rcpp::as<RcppArrayFire::typed_array<f32> >(y);
    }

    if(_X.numdims() != 2 || !_y.iscolumn() || _X.dims(0) != _y.dims(0))
        Rcpp::stop("Wrong dimensions");

    dim_t n = _X.dims(0);
    dim_t k = _X.dims(1);

    // solve OLS via X' X beta = X' y
    af::array tXX = af::matmulTN(_X, _X);
    af::array tXy = af::matmulTN(_X, _y);
    af::array coef = af::solve(tXX, tXy);

    // fitted values and residuals
    af::array fit = af::matmul(_X, coef);
    af::array res = _y - fit;

    // standard errors of residuals
    double s2;
    if (useDouble)
        s2 = (af::dot(res, res)).scalar<double>() / (n-k);
    else
        s2 = (af::dot(res, res)).scalar<float>() / (n-k);
    af::array std_err = af::sqrt(s2 - af::diag(af::inverse(tXX)));

    // intercept was included if one column is constant, i.e. max == min
    bool intercept = af::anyTrue<bool>(af::min(_X, 0) == af::max(_X, 0));

    return Rcpp::List::create(
        Rcpp::Named("coefficients") = coef,
        Rcpp::Named("stderr") = std_err,
        Rcpp::Named("df.residual") = n - k,
        Rcpp::Named("residuals") = res,
        Rcpp::Named("fitted.values") = fit,
        Rcpp::Named("intercept") = intercept
    );
}
