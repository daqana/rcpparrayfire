[![Travis-CI Build Status](https://travis-ci.org/daqana/rcpparrayfire.svg?branch=master)](https://travis-ci.org/daqana/rcpparrayfire)
[![Coverage Status](https://img.shields.io/codecov/c/github/daqana/rcpparrayfire/master.svg)](https://codecov.io/github/daqana/rcpparrayfire?branch=master)

# RcppArrayFire

R and [ArrayFire library](http://www.arrayfire.com/) via Rcpp.
You can build the ArrayFire library from source or use the 
[binary installer](http://arrayfire.com/download/). See the 
[ArrayFire documentation](http://arrayfire.org/docs/installing.htm) for details.
RcppArrayFire is developed on Linux and has been tested on Linux and MacOS.


## Installation

RcppArrayFire is not on CRAN, but you can install the current version
via [drat](https://cran.r-project.org/package=drat):

```R
if (!requireNamespace("drat", quietly = TRUE)) install.packages("drat")
drat::addRepo("daqana")
install.packages("RcppArrayFire")
```

RcppArrayFire uses the unified backend of ArrayFire. If you have
installed ArrayFire in a non-standard directory, you can use the
configure argument `--with-arrayfire`:

```R
install.packages("RcppArrayFire", configure.args = "--with-arrayfire=/opt/arrayfire")
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
