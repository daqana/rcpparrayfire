## RcppFire

R and Arrayfire via Rcpp

### Prerequisites

- gcc (>= 4.8)
- Arrayfire (with BUILD_CUDA=ON option)

### Instllation

You need to set environment variables in advance as follows.

```sh
export AF_ROOT=/path/to/your/arrayfire/library
export CUDA_ROOT=/path/to/your/cuda/library
```

Then open R console and install RcppFire.

```R
library(devtools)
install_github(repo = "RcppFire", username = "kafku")
```

### Status

Under development

### Authors

Kazuki Fukui

### License

GPL (>= 2)
