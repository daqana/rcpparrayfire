# RcppArrayFire
[![Stories in Ready](https://badge.waffle.io/kafku/RcppArrayFire.svg?label=ready&title=Ready)](http://waffle.io/kafku/RcppArrayFire)

R and Arrayfire via Rcpp

## Prerequisites

- R packages
 - Rcpp
- Arrayfire
- gcc (>= 4.8)

## Installation
```R
install.packages('devtools')
library(devtools)
install_github(repo = 'kafku/RcppArrayFire@develop')
```
If you want to try RcppArrayFire with keeping your
local enviornment clean, then
```R
dev_mode(on = T)
install_github(repo = 'kafku/RcppArrayFire@develop')
# do something with RcppArrayFire
dev_mode(on = F)
```
RcppArrayFire, with its default configuration, uses 
the CUDA version of Arrayfire. For using OpenCL or CPU version, 
invoke `install_github` with _--with-build-type_ argument.
```R
# using OpenCL version
install_github(repo = 'kafku/RcppArrayFire@develop',
               args = c("--configure-args='--with-build-type=opencl'"))

# using CPU version
install_github(repo = 'kafku/RcppArrayFire@develop',
               args = c("--configure-args='--with-build-type=cpu'"))
```

## Status

Under development

## Authors

Kazuki Fukui

## License

GPL (>= 2)
