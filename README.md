# RcppArrayFire

R and ArrayFire via Rcpp

## Prerequisites

- R packages
- Rcpp
- Arrayfire
- gcc (>= 4.8)

## Installation
```R
install.packages('devtools')
library(devtools)
install_github(repo = 'RInstitute/RcppArrayFire@develop')
```
If you want to try RcppArrayFire with keeping your
local enviornment clean, then
```R
dev_mode(on = T)
install_github(repo = 'RInstitute/RcppArrayFire@develop')
# do something with RcppArrayFire
dev_mode(on = F)
```
RcppArrayFire, with its default configuration, uses 
the CUDA version of Arrayfire. For using OpenCL or CPU version, 
invoke `install_github` with _--with-build-type_ argument.
```R
# using OpenCL version
install_github(repo = 'RInstitute/RcppArrayFire@develop',
               args = c("--configure-args='--with-build-type=opencl'"))

# using CPU version
install_github(repo = 'RInstitute/RcppArrayFire@develop',
               args = c("--configure-args='--with-build-type=cpu'"))
```

## Trademark notice

RcppArrayFire is not affiliated with or endorsed by ArrayFire. The
ArrayFire literal mark is used under a limited license granted by
ArrayFire the trademark holder in the United States and other countries.

## Status

Under development

## Authors

Kazuki Fukui

## License

GPL (>= 2)
