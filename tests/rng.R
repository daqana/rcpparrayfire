library(RcppArrayFire)

arrayfire_set_seed(12345678901234567890)
n1 <- fastRnorm(10)
u1 <- fastRunif(10)

arrayfire_set_seed(12345678901234567890)
n2 <- fastRnorm(10)
u2 <- fastRunif(10)

stopifnot(all.equal(n1, n2))
stopifnot(all.equal(u1, u2))
