[![Travis-CI Build Status](https://travis-ci.org/RInstitute/rcpparrayfire.svg?branch=master)](https://travis-ci.org/RInstitute/rcpparrayfire)
[![Coverage Status](https://img.shields.io/codecov/c/github/RInstitute/rcpparrayfire/master.svg)](https://codecov.io/github/RInstitute/rcpparrayfire?branch=master)

# RcppArrayFire

R and [ArrayFire library](http://www.arrayfire.com/) via Rcpp.

## Prerequisites

In order to use RcppArrayFire you will need R including development tools and Rcpp.
On a Debian based or derived system, this can be achieved with:

```
sudo apt-get install r-base-dev r-cran-rcpp 
```

In principle ArrayFire has been packaged for Debian. However, the CUDA backend 
is not included  and usage of the packaged OpenCL backend is hindered by a 
[bug in the clBLAS package](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=881054). 
For serious usage it is currently better to build from source or use the 
[binary installer](http://arrayfire.com/download/) from ArrayFire. See the 
[ArrayFire documentation](http://arrayfire.org/docs/installing.htm) for details.


## Installation

RcppArrayFire is not on CRAN, but you can install the current version
via [drat](https://cran.r-project.org/package=drat):

```R
if (!requireNamespace("drat", quietly = TRUE)) install.packages("drat")
drat::addRepo("RInstitute")
install.packages("RcppArrayFire")
```

RcppArrayFire uses the unified backend of ArrayFire. If you have
installed ArrayFire in a non-standard directory, you can use the
configure argument `--with-arrayfire`:

```R
install.packages("RcppArrayFire", configure.args = "--with-arrayfire=/opt/arrayfire-3")
```

## Trademark notice

RcppArrayFire is not affiliated with or endorsed by ArrayFire. The
ArrayFire literal mark is used under a limited license granted by
ArrayFire the trademark holder in the United States and other countries.

## Status
RcppArrayFire is based on [RcppFire](https://github.com/kafku/RcppFire) and is under development.

## Authors

Kazuki Fukui and Ralf Stubner

## License

GPL (>= 2)
