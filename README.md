## RcppFire

R and Arrayfire via Rcpp

### Prerequisites

- R packages
 - Rcpp
- Arrayfire
- gcc (>= 4.8)

### Instllation
```R
install.packages('devtools')
library(devtools)
install_github(repo = 'kafku/RcppFire@develop')
```
If you want to try RcppFire with keeping your
local enviornment clean, then
```R
dev_mode(on = T)
install_github(repo = 'kafku/RcppFire@develop')
# do something with RcppFire
dev_mode(on = F)
```
RcppFire, with its default configuration, uses 
the CUDA version of Arrayfire. For using OpenCL or CPU version, 
invoke `install_github` with _--with-buid-type_ argument.
```R
# using OpenCL version
install_github(repo = 'kafku/RcppFire@develop',
               args = c("--configure-args='--with-build-type=opencl'"))

# using CPU version
install_github(repo = 'kafku/RcppFire@develop',
               args = c("--configure-args='--with-build-type=cpu'"))
```

### Status

Under development

### Authors

Kazuki Fukui

### License

GPL (>= 2)
