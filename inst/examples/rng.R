library(RcppArrayFire)
library(rbenchmark)

nbench <- function(N) {
    benchmark(
        rnorm(N),
        fastRnorm(N),
        columns = c("test", "relative", "elapsed", "user.self", "sys.self"),
        order = "relative"
    )
}

ubench <- function(N) {
    benchmark(
        runif(N),
        fastRunif(N),
        columns = c("test", "relative", "elapsed", "user.self", "sys.self"),
        order = "relative"
    )
}

arrayfire_set_seed(12345678901234567890)
n1 <- fastRnorm(10)
u1 <- fastRunif(10)

arrayfire_set_seed(12345678901234567890)
n2 <- fastRnorm(10)
u2 <- fastRunif(10)

stopifnot(all.equal(n1, n2))
stopifnot(all.equal(u1, u2))

N <- 10^6
nbench(N)
ubench(N)

# sessionInfo()
# arrayfire_info()
