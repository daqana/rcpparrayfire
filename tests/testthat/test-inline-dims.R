context("inline and dimensions")

doubleArray <- inline::cxxfunction(signature(xs = "RcppArrayFire::typed_array<f32>"),
                    body = "RcppArrayFire::typed_array<f32> x = Rcpp::as<RcppArrayFire::typed_array<f32>>(xs);
                    return Rcpp::wrap(2 * x);",
                    plugin = "RcppArrayFire")


test_that("1d array multiplication works", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    x <- 1:16
    expect_equal(2 * x, doubleArray(x))
})

test_that("2d array multiplication works", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    x <- array(1:16, dim = c(2, 8))
    expect_equal(2 * x, doubleArray(x))
})

test_that("3d array multiplication works", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    x <- array(1:16, dim = c(2, 2, 4))
    expect_equal(2 * x, doubleArray(x))
})

test_that("4d array multiplication works", {
    skip_if(identical(Sys.getenv("TRAVIS_OS_NAME"), "osx"), message = "On Travis Mac")
    x <- array(1:16, dim = c(2, 2, 2, 2))
    expect_equal(2 * x, doubleArray(x))
})
