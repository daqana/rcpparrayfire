// -*- mode: C++ -*-
//
// fastRNG.cpp: fast random number generation using ArrayFire
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

//' Fast runif alternative
//' @details Fast generation of uniformly distributed random values. The default is to use single precision,
//'  since not all devices support calculations using double precision.
//' @param n  number of observations
//' @param min  lower limit of the distribution
//' @param max  upper limit of the distribution
//' @param useDouble  use float or double internally
//' @return A numeric vector of random values
//' @seealso \code{\link{runif}} and \url{http://arrayfire.org/docs/group__random__func__randu.htm}
//' @export
// [[Rcpp::export]]
af::array fastRunif(const int32_t n, const double min = 0, const double max = 1, bool useDouble = false) {
    if (useDouble && !af::isDoubleAvailable(af::getDevice())) {
        useDouble = false;
        Rcpp::warning("Double precision is not available with current device.");
    }

    if (useDouble)
        return min + (max - min) * af::randu(static_cast<dim_t>(n), f64);
    else
        return min + (max - min) * af::randu(static_cast<dim_t>(n));
}


//' Fast rnorm alternative
//' @details Fast generation of normaly distributed random values. The default is to use single precision,
//'  since not all devices support calculations using double precision.
//' @param n  number of observations
//' @param mean  mean value of the distribution
//' @param sd  standard deviation of the distribution
//' @param useDouble  use float or double internally
//' @return A numeric vector of random values
//' @seealso \code{\link{rnorm}} and \url{http://arrayfire.org/docs/group__random__func__randn.htm}
//' @export
// [[Rcpp::export]]
af::array fastRnorm(const int32_t n, const double mean = 0, const double sd = 1, bool useDouble = false) {
    if (useDouble && !af::isDoubleAvailable(af::getDevice())) {
        useDouble = false;
        Rcpp::warning("Double precision is not available with current device.");
    }

    if (useDouble)
        return mean + sd * af::randn(static_cast<dim_t>(n), f64);
    else
        return mean + sd * af::randn(static_cast<dim_t>(n));
}
