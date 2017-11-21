library(RcppArrayFire)

Rcpp::cppFunction(depends = "RcppArrayFire",
            code = "af::array doubleArray(RcppArrayFire::typed_array<f32> x) {return 2 * x;}")

x <- 1:16
stopifnot(all.equal(2 * x, doubleArray(x)))

x <- array(1:16, dim = c(2, 8))
stopifnot(all.equal(2 * x, doubleArray(x)))

x <- array(1:16, dim = c(2, 2, 4))
stopifnot(all.equal(2 * x, doubleArray(x)))

x <- array(1:16, dim = c(2, 2, 2, 2))
stopifnot(all.equal(2 * x, doubleArray(x)))

x <- array(1:32, dim = c(2, 2, 2, 2, 2))
tryCatch(doubleArray(x), error=print)
