Sys.setenv("R_TESTS" = "")
library(testthat)
library(RcppArrayFire)

test_check("RcppArrayFire")
