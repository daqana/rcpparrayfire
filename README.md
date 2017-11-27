[![Travis-CI Build Status](https://travis-ci.org/RInstitute/rcpparrayfire.svg?branch=master)](https://travis-ci.org/RInstitute/rcpparrayfire)

# RcppArrayFire

R and [ArrayFire library](http://www.arrayfire.com/) via Rcpp.

## Prerequisites

- R
- Rcpp
- ArrayFire
- g++ (>= 4.8)

## Installation

RcppArrayFire is not on CRAN, but you can install the current version
via [drat](https://cran.r-project.org/package=drat):

```R
#install.packages("drat")
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
